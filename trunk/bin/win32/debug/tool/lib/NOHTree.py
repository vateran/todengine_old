# coding: mbcs

import sys, os
import wx
import lib.NOHImageProvider as NOHImageProvider
import lib.NodeCreator as NodeCreator
from todpython import *

# ------------------------------------------------------------------------------
class NOHPopupMenu(wx.Menu):
    def __init__(self, parent, title=''):
        wx.Menu.__init__(self, title)
        self.parent = parent
        self.ap = wx.ArtProvider()
        
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Add Node\tAlt-A')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_NEW))
        self.Bind(wx.EVT_MENU, self.OnAddNode, id=item.GetId())
        
        self.AppendSeparator()
        
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Rename\tF2')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_HELP_SETTINGS))
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Cut\tCtrl-X')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_CUT))
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Copy\tCtrl-C')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_COPY))
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Paste\tCtrl-V')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_PASTE))
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Delete\tDel')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_DELETE))
        self.Bind(wx.EVT_MENU, self.OnDeleteNode, id=item.GetId())
        
        self.AppendSeparator()
        
        self.run_editor_item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'Run Editor...')
        self.run_editor_item.SetBitmap(self.ap.GetBitmap(wx.ART_FIND))
        self.Bind(wx.EVT_MENU, self.OnRunEditor, id=self.run_editor_item.GetId())
                
        self.AppendSeparator()
        
        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'&Save ...')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_FILE_SAVE))
        self.Bind(wx.EVT_MENU, self.OnSave, id=item.GetId())

        item = self.Append(help='', id=wx.NewId(), kind=wx.ITEM_NORMAL, text=u'&Load ...')
        item.SetBitmap(self.ap.GetBitmap(wx.ART_FILE_OPEN))
        
    def setTargetObject(self, obj):
        self.targetObject = obj
        self.run_editor_item.Enable(False)
        for type_name in obj.getGenerations():
            if os.path.exists('plugins/' + type_name):
                self.run_editor_item.Enable(True)
                break
        
    def OnAddNode(self, event):
        frame = NodeCreator.create(self.parent)
        frame.setParentNode(self.targetObject)
        frame.Show()

    def OnDeleteNode(self, event):
        self.targetObject.detach()
        del self.targetObject

    def OnSave(self, event):
        serialize('managed://test#test.xml', self.targetObject)
        
    def OnRunEditor(self, event):
        try:
            for type_name in self.targetObject.getGenerations():                
                if os.path.exists('plugins/' + type_name):
                    plugins_module = __import__('plugins.' + type_name)
                    module = getattr(plugins_module, type_name)
                    reload(module)
                    module.initialize(self.parent, self.targetObject)
                    break
        except:
            raise
        
    def load_NOH_icons(self):
        pass

# ------------------------------------------------------------------------------
class NOHTree(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size, style):
        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)
        self.ip = NOHImageProvider.NOHImageProvider('data/NOHTreeImages')
        self.SetImageList(self.ip.getImageList())
        
        self.popupMenu = NOHPopupMenu(self)
        
        self.Bind(wx.EVT_TREE_ITEM_EXPANDING, self.onExpending, id=id)
        self.Bind(wx.EVT_TREE_ITEM_RIGHT_CLICK, self.onRClick, id=id)
        self.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown, id=self.GetId())
        
    # public members -----------------------------------------------------------
    def build(self, root_path):
        root_item = self.AddRoot("/")
        root_node = get(root_path)
        self.SetItemImage(root_item, self.ip.getImage('tod'))
        self.SetItemHasChildren(root_item, root_node.getNumChildren() > 0)
        
    def getSelectionAbsolutePath(self):
        return str(self.get_absolute_path_by_item(self.GetSelection()))
    
    def getSelectedNode(self):
        return get(self.getSelectionAbsolutePath())
            
    # Events -------------------------------------------------------------------
    def onExpending(self, event):
        self.expend_item(event.GetItem())
        
    def onRClick(self, event):
        tpath = self.get_absolute_path_by_item(event.GetItem())
        if len(tpath) == 0:
            return
        self.popupMenu.setTargetObject(get(str(tpath)))
        self.PopupMenu(self.popupMenu)
        
    def OnKeyDown(self, event):
        kc = event.GetKeyCode()        
        if kc == wx.WXK_DELETE:
            node = self.getSelectedNode()
            node.detach()
            del node
    
    # private members-----------------------------------------------------------
    def expend_item(self, item):
        self.DeleteChildren(item)
        path = self.get_absolute_path_by_item(item)
        node = get(str(path))
        child_nodes = node.getChildren()
        for child_node in child_nodes:
            self.add_child_item(item, child_node)
    
    def add_child_item(self, parent_item, child_node):
        child_item = self.AppendItem(parent_item, unicode(child_node.getName()))
        self.SetItemHasChildren(child_item, child_node.getNumChildren() > 0)
        self.set_item_icon(child_item, child_node)
        
    def get_absolute_path_by_item(self, item):
        if self.GetRootItem() == item:
            return self.GetItemText(item)
        path = ''
        while item != self.GetRootItem():
            try:
                path = '/' + self.GetItemText(item) + path
                item = self.GetItemParent(item)
            except:
                break
        root_item_text = self.GetItemText(self.GetRootItem())
        if root_item_text != '/':
            path += root_item_text + path
        return path
    
    def set_item_icon(self, item, node):
        self.SetItemImage(item, 0)
        g = list(node.getGenerations())
        g.reverse()
        for type_name in g:
            try:
                self.SetItemImage(item, self.ip.getImage(type_name))
            except:
                pass
        try:
            self.SetItemImage(item, self.ip.getImage(node.getName()))
        except:
            pass
