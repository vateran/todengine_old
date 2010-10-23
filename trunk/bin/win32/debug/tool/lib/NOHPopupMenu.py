# coding: mbcs

import sys, os
import wx 
import lib.NOHImageProvider as NOHImageProvider
import lib.NodeCreator as NodeCreator
import lib.FileDialog as FileDialog
import MainFrame
from todpython import *

# ------------------------------------------------------------------------------
class NOHPopupMenu(wx.Menu):
    def __init__(self, parent, title=''):
        wx.Menu.__init__(self, title)
        self.parent = parent
        self.ap = wx.ArtProvider()

        self.menuData = [(u'Add Node\tAlt-A', self.ap.GetBitmap(wx.ART_NEW), self.OnAddNode),
            None,
            (u'Rename\tF2', self.ap.GetBitmap(wx.ART_HELP_SETTINGS), self.OnRename),
            (u'Cut\tCtrl-X', self.ap.GetBitmap(wx.ART_CUT), self.OnCut),
            (u'Copy\tCtrl-C', self.ap.GetBitmap(wx.ART_COPY), self.OnCopy),
            (u'Paste\tCtrl-V', self.ap.GetBitmap(wx.ART_PASTE), self.OnPaste),
            (u'Delete\tDel', self.ap.GetBitmap(wx.ART_DELETE), self.OnDeleteNode),
            None,
            (u'Run Editor...', self.ap.GetBitmap(wx.ART_FIND), self.OnRunEditor),
            (u'New SceneView...', self.ap.GetBitmap(wx.ART_NEW), self.OnNewSceneView),
            None,
            (u'&Save ...', self.ap.GetBitmap(wx.ART_FILE_SAVE), self.OnSave),
            (u'&Load ...', self.ap.GetBitmap(wx.ART_FILE_OPEN), self.OnLoad)]

        for md in self.menuData:
            if md == None:
                self.AppendSeparator()
            else:
                mi = wx.MenuItem(self, wx.NewId(), md[0])
                mi.SetBitmap(md[1])
                self.AppendItem(mi)
                self.Bind(wx.EVT_MENU, md[2], id=mi.GetId())
        
        self.runEditorMenuItem = self.FindItemByPosition(8)
        self.newSceneViewMenuItem = self.FindItemByPosition(9)

    def setSelectedItem(self, item):
        self.selectedItem = item
        
    def setTargetObject(self, obj):
        self.targetObject = obj
        self.runEditorMenuItem.Enable(False)
        for type_name in obj.getGenerations():
            if os.path.exists('plugins/' + type_name):
                self.runEditorMenuItem.Enable(True)
                break
        self.newSceneViewMenuItem.Enable(False)
        for type_name in obj.getGenerations():
            if type_name == 'SceneNode':
                self.newSceneViewMenuItem.Enable(True)
                break;
                
    def OnAddNode(self, event):
        frame = NodeCreator.create(self.parent)
        frame.setSelectedItem(self.selectedItem)
        frame.setParentNode(self.targetObject)
        frame.Show()

    def OnRename(self, event):
        self.parent.SelectItem(self.selectedItem)
        self.parent.EditLabel(self.selectedItem)

    def OnCut(self, event):
        event.Skip()

    def OnCopy(self, event):
        event.Skip()

    def OnPaste(self, event):
        event.Skip()

    def OnDeleteNode(self, event):
        parent_node = self.targetObject.getParent()
        parent_item = self.parent.GetItemParent(self.selectedItem)
        # delete node
        self.targetObject.detach()
        self.targetObject = None
        # update parent
        self.parent.Delete(self.selectedItem)
        self.parent.SetItemHasChildren(parent_item, parent_node.getNumChildren() > 0)

    def OnSave(self, event):
        fd = FileDialog.FileDialog(self.parent)
        fd.setupSaveMode()
        fd.setFileName(self.targetObject.getName() + '.xml')
        if fd.ShowModal() == wx.ID_OK:
            if len(fd.getUri()) != 0:
                if serialize(fd.getUri(), self.targetObject):
                    md = wx.MessageDialog(self.parent, fd.getUri() + ' saved', 'Information', wx.OK)
                    md.ShowModal()

    def OnLoad(self, event):
        fd = FileDialog.FileDialog(self.parent)
        fd.setupOpenMode()
        if fd.ShowModal() == wx.ID_OK:
            obj = deserialize(self.targetObject, fd.getUri())
            if obj != None:
                self.parent.Collapse(self.selectedItem)
                self.parent.SetItemHasChildren(self.selectedItem, True)
                self.parent.Expand(self.selectedItem)
        
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
        
    def OnNewSceneView(self, event):
        MainFrame.MainFrame.instance().newSceneView(self.targetObject);
        
    def load_NOH_icons(self):
        pass

