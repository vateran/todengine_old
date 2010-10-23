# coding: mbcs

import sys, os
import wx
import lib.NOHImageProvider as NOHImageProvider
import lib.NOHPopupMenu as NOHPopupMenu
from todpython import *

# ------------------------------------------------------------------------------
class NOHTree(wx.TreeCtrl):
    s_instance = None
    def __init__(self, parent, id, pos, size,
            style=wx.TR_LINES_AT_ROOT | wx.TR_HAS_BUTTONS | wx.TR_EDIT_LABELS):
        if NOHTree.s_instance == None:
            NOHTree.s_instance = self

        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)
        self.ip = NOHImageProvider.NOHImageProvider('data/NOHTreeImages')
        self.SetImageList(self.ip.getImageList())
        
        self.popupMenu = NOHPopupMenu.NOHPopupMenu(self)
        
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

    def selectNode(self, node):
        item = self.GetRootItem()
        path = node.getAbsolutePath()
        path_split = path.split('/')[1:]
        for p in path_split:
            self.Expand(item)
            (child, cookie) = self.GetFirstChild(item)
            while child.IsOk():
                if self.GetItemText(child) == p:
                    item = child
                    break
                (child, cookie) = self.GetNextChild(item, cookie)
        self.SelectItem(item)            
            
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
            parent_item = None
            for item in self.GetSelections():
                parent_item = self.GetItemParent(item)
                path = self.get_absolute_path_by_item(item)
                node = get(path)
                node.detach()
                del node
                self.Delete(item)
            if parent_item != None:
                self.SetItemHasChildren(parent_item,
                    self.get_item_children_count(parent_item) > 0)
    
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
    def get_item_children_count(self, item):
        count = 0
        (child, cookie) = self.GetFirstChild(item)
        while child.IsOk():
            count = count + 1
            (child, cookie) = self.GetNextChild(item, cookie)
        return count

    def is_children_changed(self, item, node):
        children = node.getChildren()
        index = 0
        (child, cookie) = self.GetFirstChild(item)
        while child.IsOk():
            if index >= len(children):
                return True
            if self.GetItemText(child) == children[index].getName():
                index = index + 1
                (child, cookie) = self.GetNextChild(item, cookie)
            else:
                return True
        return index != len(children)

    def expend_item(self, item):
        path = self.get_absolute_path_by_item(item)
        node = get(str(path))
        if self.is_children_changed(item, node):
            self.DeleteChildren(item)
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

    @classmethod
    def instance(self):
        return NOHTree.s_instance

