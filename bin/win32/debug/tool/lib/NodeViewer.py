# coding: mbcs

import sys, os
import wx
import lib.ImageProvider as ImageProvider
import lib.NOHTree as NOHTree
import lib.NOHImageProvider as NOHImageProvider
import lib.NodeCreator as NodeCreator
import lib.FileDialog as FileDialog
import lib.PropertyGrid as PropertyGrid
from todpython import *


#---------------------------------------------------------------------------
class NodeSearchByNameControl(wx.SearchCtrl):
    maxSearches = 5
    
    def __init__(self, parent, id=-1, value="",
                 pos=wx.DefaultPosition, size=wx.DefaultSize, style=0,
                 do_search=None):
        style |= wx.TE_PROCESS_ENTER
        wx.SearchCtrl.__init__(self, parent, id, value, pos, size, style)
        self.Bind(wx.EVT_TEXT_ENTER, self.OnTextEntered)
        self.Bind(wx.EVT_MENU_RANGE, self.OnMenuItem, id=1, id2=self.maxSearches)
        self.doSearch = do_search
        self.searches = []

    def OnTextEntered(self, evt):
        text = self.GetValue()
        if self.doSearch(text):
            self.searches.append(text)
            if len(self.searches) > self.maxSearches:
                del self.searches[0]
            self.SetMenu(self.MakeMenu())            
        #self.SetValue("")

    def OnMenuItem(self, evt):
        text = self.searches[evt.GetId()-1]
        self.doSearch(text)
        
    def MakeMenu(self):
        menu = wx.Menu()
        item = menu.Append(-1, "Recent Searches")
        item.Enable(False)
        for idx, txt in enumerate(self.searches):
            menu.Append(1+idx, txt)
        return menu


#---------------------------------------------------------------------------
class ObjectHierarchyViewCtrl(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size):
        wx.TreeCtrl.__init__(self, parent, id, pos, size,
            style=wx.TR_LINES_AT_ROOT | wx.TR_HAS_BUTTONS)
        self.ip = NOHImageProvider.NOHImageProvider('data/NOHTreeImages')
        self.SetImageList(self.ip.getImageList())
        self.build()

    def build(self):
        self.DeleteAllItems()
        root_item = self.AddRoot("Object")
        self.SetItemHasChildren(root_item, True)
        self.build_derived_types(root_item)

    def build_derived_types(self, parent_item):
        type_name = self.GetItemText(parent_item)
        name, is_abstract, module_name = getTypeInfo(type_name)
        if is_abstract:
            self.SetItemFont(parent_item, wx.Font(9, wx.SWISS, wx.FONTSTYLE_ITALIC, wx.NORMAL, False, u'Tahoma'))
        else:
            self.SetItemFont(parent_item, wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL, False, u'Tahoma'))
        self.set_item_icon(parent_item, type_name)
        type_names = getDerivedTypes(type_name)
        if len(type_names) > 0:
            self.SetItemHasChildren(parent_item, True)
        for tn in type_names:
            item = self.AppendItem(parent_item, tn)
            self.build_derived_types(item)

    def set_item_icon(self, item, type_name):
        self.SetItemImage(item, 0)
        try:
            self.SetItemImage(item, self.ip.getImage(type_name))
        except:
            pass


#---------------------------------------------------------------------------
class SettingDialog(wx.Dialog):
    def __init__(self, parent, id):
        wx.Dialog.__init__(self, parent, id)
        self.oo = ObjectHierarchyViewCtrl(self, wx.NewId(), (0, 0), (300, 200))

#---------------------------------------------------------------------------
class NodeViewer(wx.Panel):
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent, id)

        self.imageProvider = ImageProvider.ImageProvider('data')

        tb = wx.ToolBar(self, -1, style=wx.TB_HORIZONTAL | wx.NO_BORDER | wx.TB_FLAT)
        self.filterButton = tb.AddLabelTool(wx.NewId(), "Filter",
            self.imageProvider.getImage('filter'), shortHelp="Filter")
        self.replaceButton = tb.AddLabelTool(wx.NewId(), "Replace",
            self.imageProvider.getImage('replace'), shortHelp="Replace")
        self.settingButton = tb.AddLabelTool(wx.NewId(), "Settings",
            self.imageProvider.getImage('setting'), shortHelp="Settings")
        tb.AddSeparator()
        self.autoUpdateCheckBox = tb.AddCheckLabelTool(wx.NewId(), "Auto Update",
            self.imageProvider.getImage('refresh'), shortHelp="Auto Update")
        tb.AddSeparator()
        self.nodeSearchByNameCtrl = NodeSearchByNameControl(
            tb, size=(140, -1), do_search=self.doSearch)
        tb.AddControl(self.nodeSearchByNameCtrl)
        self.prevSearchButton = tb.AddLabelTool(wx.NewId(), "Previous Search",
            self.imageProvider.getImage('previous'), shortHelp="Previous Search")
        self.nextSearchButton = tb.AddLabelTool(wx.NewId(), "Next Search",
            self.imageProvider.getImage('next'), shortHelp="Next Search")
        tb.Realize()
        tb.Bind(wx.EVT_TOOL, self.onToolBar)

        self.tree = NOHTree.NOHTree(self, wx.NewId(), (0, 0), (0, 0))
        self.tree.Bind(wx.EVT_TREE_SEL_CHANGED, self.onSelChanged, id=self.tree.GetId())
        self.tree.build('/')

        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(tb, 0, wx.EXPAND | wx.RIGHT, 0)
        sizer.Add(self.tree, 1, wx.EXPAND | wx.RIGHT | wx.Bottom, 0)
        self.SetSizer(sizer)

        self.curSearchText = None
        self.searchResult = []
        self.curSearchIndex = 0

    def doSearch(self, text):
        if text != self.curSearchText:
            self.searchResult = []
            self.curSearchIndex = -1
            self.curSearchText = str(text)
            self.search_node_by_name(get('/'))
            if len(self.searchResult) == 0:
                self.search_node_by_name_fraction(get('/'))
        self.nextSearch()

    def prevSearch(self):
        if len(self.searchResult) == 0:
            return
        self.curSearchIndex = self.curSearchIndex - 1
        if self.curSearchIndex < 0:
            self.curSearchIndex = len(self.searchResult) - 1
        self.tree.selectNode(self.searchResult[self.curSearchIndex])

    def nextSearch(self):
        if len(self.searchResult) == 0:
            return
        self.curSearchIndex = self.curSearchIndex + 1
        if self.curSearchIndex >= len(self.searchResult):
            self.curSearchIndex = 0
        self.tree.selectNode(self.searchResult[self.curSearchIndex])

    def search_node_by_name(self, node):
        if node.getName() == self.curSearchText:
            self.searchResult.append(node)
        for cn in node.getChildren():
            self.search_node_by_name(cn)
    
    def search_node_by_name_fraction(self, node):
        if node.getName().find(self.curSearchText) != -1:
            self.searchResult.append(node)
        for cn in node.getChildren():
            self.search_node_by_name_fraction(cn)

    def onSelChanged(self, event):
        PropertyGrid.PropertyGrid.instance().setObject(get(self.tree.getSelectionAbsolutePath()))

    def onToolBar(self, event):
        sel = event.GetId()
        if sel == self.settingButton.GetId():
            sd = SettingDialog(self, wx.NewId())
            ret = sd.ShowModal()
        elif sel == self.prevSearchButton.GetId():
            self.prevSearch()
        elif sel == self.nextSearchButton.GetId():
            self.nextSearch()
               
