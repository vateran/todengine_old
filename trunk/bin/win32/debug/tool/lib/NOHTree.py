# coding: mbcs

import sys, os
import wx
import lib.NOHImageProvider as NOHImageProvider
import lib.NodeCreator as NodeCreator
import lib.FileDialog as FileDialog
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

    def setSelectedItem(self, item):
        self.selectedItem = item
        
    def setTargetObject(self, obj):
        self.targetObject = obj
        self.runEditorMenuItem.Enable(False)
        for type_name in obj.getGenerations():
            if os.path.exists('plugins/' + type_name):
                self.runEditorMenuItem.Enable(True)
                break
        
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
        del self.targetObject
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
        
    def load_NOH_icons(self):
        pass

# ------------------------------------------------------------------------------
class NOHTree(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size, style):
        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)
        self.ip = NOHImageProvider.NOHImageProvider('data/NOHTreeImages')
        self.SetImageList(self.ip.getImageList())
        
        self.popupMenu = NOHPopupMenu(self)
        
        self.Bind(wx.EVT_TREE_ITEM_EXPANDING, self.OnExpending, id=id)
        self.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown, id=self.GetId())
        self.Bind(wx.EVT_TREE_END_LABEL_EDIT, self.OnEndLabelEdit, id=self.GetId())
        self.Bind(wx.EVT_TREE_ITEM_MENU, self.OnItemMenu, id=self.GetId())
        self.Bind(wx.EVT_TREE_BEGIN_DRAG, self.OnBeginDrag, id=self.GetId())
        self.Bind(wx.EVT_TREE_END_DRAG, self.OnEndDrag, id=self.GetId())
        
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

    def addNode(self, parent_item, node):
        child_item = self.add_child_item(parent_item, node)
        self.SetItemHasChildren(parent_item, True)
        self.SelectItem(child_item)
            
    # Events -------------------------------------------------------------------
    def OnExpending(self, event):
        self.expend_item(event.GetItem())
        
    def OnItemMenu(self, event):
        tpath = self.get_absolute_path_by_item(event.GetItem())
        if len(tpath) == 0:
            return
        self.popupMenu.setSelectedItem(event.GetItem())
        self.popupMenu.setTargetObject(get(str(tpath)))
        self.PopupMenu(self.popupMenu)
        
    def OnKeyDown(self, event):
        kc = event.GetKeyCode()        
        if kc == wx.WXK_DELETE:
            node = self.getSelectedNode()
            node.detach()
            del node
            self.Delete(event.GetItem())

    def OnEndLabelEdit(self, event):
        if event.IsEditCancelled():
            return
        node = self.getSelectedNode()
        node.setName(str(event.GetLabel()))

    def OnBeginDrag(self, event):
        self.beginDragItem = event.GetItem()
        event.Allow()
        event.Skip()

    def OnEndDrag(self, event):
        self.endDragItem = event.GetItem()
        if self.beginDragItem == self.endDragItem:
            return
        src_node = self.get_node_by_item(self.beginDragItem)
        dst_node = self.get_node_by_item(self.endDragItem)
        src_node.detach()
        dst_node.attach(src_node)
        self.Delete(self.beginDragItem)
        self.AppendItem(self.endDragItem, unicode(src_node.getName()))
        self.SetItemHasChildren(self.endDragItem, True)
        self.set_item_icon(self.beginDragItem, src_node)
        self.Expand(self.endDragItem)
    
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
        return child_item
        
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

    def get_node_by_item(self, item):
        return get(self.get_absolute_path_by_item(item))
    
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
