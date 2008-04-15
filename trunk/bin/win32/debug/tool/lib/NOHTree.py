import wx
from todpython import *

# ------------------------------------------------------------------------------
class NOHTree(wx.TreeCtrl):
    def __init__(self, parent, id, pos, size, style):
        wx.TreeCtrl.__init__(self, parent, id, pos, size, style)
        
        self.Bind(wx.EVT_TREE_ITEM_EXPANDING, self.onExpending, id=id)
        
    # public members -----------------------------------------------------------
    def build(self, root_path):
        root_item = self.AddRoot("/")
        root_node = get(root_path)
        self.SetItemHasChildren(root_item, root_node.getNumChildren() > 0)
        
    def getSelectionAbsolutePath(self):
        return str(self.get_absolute_path_by_item(self.GetSelection()))
            
    # Events -------------------------------------------------------------------
    def onExpending(self, event):
        self.expend_item(event.GetItem())
    
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

