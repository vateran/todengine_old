#Boa:Frame:NodeCreatorFrame

import wx
import wx.lib.buttons
import lib.NOHImageProvider as NOHImageProvider
from todpython import *

def create(parent):
    return NodeCreatorFrame(parent)

[wxID_NODECREATORFRAME, wxID_NODECREATORFRAMECANCELBUTTON, 
 wxID_NODECREATORFRAMEMODULETREE, wxID_NODECREATORFRAMENODENAME, 
 wxID_NODECREATORFRAMENODETYPE, wxID_NODECREATORFRAMENODETYPETREE, 
 wxID_NODECREATORFRAMEOKBUTTON, wxID_NODECREATORFRAMEPANEL1, 
 wxID_NODECREATORFRAMEPARENTPATH, wxID_NODECREATORFRAMESTATICBITMAP1, 
 wxID_NODECREATORFRAMESTATICBITMAP2, wxID_NODECREATORFRAMESTATICBITMAP3, 
 wxID_NODECREATORFRAMESTATICBOX1, wxID_NODECREATORFRAMESTATICBOX2, 
 wxID_NODECREATORFRAMESTATICTEXT1, wxID_NODECREATORFRAMESTATICTEXT2, 
 wxID_NODECREATORFRAMESTATICTEXT3, 
] = [wx.NewId() for _init_ctrls in range(17)]

class NodeCreatorFrame(wx.Frame):
    def _init_coll_staticBoxSizer1_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.parentSizer, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.TOP | wx.EXPAND)
        parent.AddSizer(self.nodeNameSizer, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.TOP | wx.EXPAND)
        parent.AddSizer(self.nodeTypeSizer, 0, border=5,
              flag=wx.ALL | wx.EXPAND)

    def _init_coll_staticBoxSizer2_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.nodeTypeTreeSizer, 1, border=5,
              flag=wx.ALL | wx.EXPAND)

    def _init_coll_mainSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.staticBoxSizer1, 0, border=5,
              flag=wx.ALL | wx.EXPAND)
        parent.AddSizer(self.staticBoxSizer2, 1, border=5,
              flag=wx.ALL | wx.EXPAND)
        parent.AddSizer(self.buttonSizer, 0, border=5,
              flag=wx.ALL | wx.ALIGN_RIGHT)

    def _init_coll_nodeNameSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticBitmap2, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.staticText2, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.nodeName, 1, border=0, flag=wx.EXPAND)

    def _init_coll_parentSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticBitmap1, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.staticText1, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.parentPath, 1, border=0, flag=wx.EXPAND)

    def _init_coll_nodeTypeTreeSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.moduleTree, 0, border=5,
              flag=wx.RIGHT | wx.EXPAND)
        parent.AddWindow(self.nodeTypeTree, 1, border=0, flag=wx.EXPAND)

    def _init_coll_nodeTypeSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticBitmap3, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.staticText3, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.nodeType, 1, border=0, flag=wx.EXPAND)

    def _init_coll_buttonSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.okButton, 0, border=0, flag=0)
        parent.AddWindow(self.cancelButton, 0, border=0, flag=0)

    def _init_sizers(self):
        # generated method, don't edit
        self.mainSizer = wx.BoxSizer(orient=wx.VERTICAL)

        self.staticBoxSizer1 = wx.StaticBoxSizer(box=self.staticBox1,
              orient=wx.VERTICAL)

        self.staticBoxSizer2 = wx.StaticBoxSizer(box=self.staticBox2,
              orient=wx.VERTICAL)

        self.buttonSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.parentSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.nodeNameSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.nodeTypeSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.nodeTypeTreeSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self._init_coll_mainSizer_Items(self.mainSizer)
        self._init_coll_staticBoxSizer1_Items(self.staticBoxSizer1)
        self._init_coll_staticBoxSizer2_Items(self.staticBoxSizer2)
        self._init_coll_buttonSizer_Items(self.buttonSizer)
        self._init_coll_parentSizer_Items(self.parentSizer)
        self._init_coll_nodeNameSizer_Items(self.nodeNameSizer)
        self._init_coll_nodeTypeSizer_Items(self.nodeTypeSizer)
        self._init_coll_nodeTypeTreeSizer_Items(self.nodeTypeTreeSizer)

        self.panel1.SetSizer(self.mainSizer)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_NODECREATORFRAME,
              name=u'NodeCreatorFrame', parent=prnt, pos=wx.Point(746, 167),
              size=wx.Size(400, 500), style=wx.DEFAULT_FRAME_STYLE,
              title=u'Node Creator')
        self.SetClientSize(wx.Size(392, 466))
        self.Center(wx.BOTH)
        self.SetMinSize(wx.Size(400, 500))
        self.SetHelpText(u'')

        self.panel1 = wx.Panel(id=wxID_NODECREATORFRAMEPANEL1, name='panel1',
              parent=self, pos=wx.Point(0, 0), size=wx.Size(392, 466),
              style=wx.TAB_TRAVERSAL)

        self.staticBox1 = wx.StaticBox(id=wxID_NODECREATORFRAMESTATICBOX1,
              label=u'Creation Information', name='staticBox1',
              parent=self.panel1, pos=wx.Point(5, 5), size=wx.Size(382, 109),
              style=0)
        self.staticBox1.SetToolTipString(u'Node Creator')
        self.staticBox1.SetMinSize(wx.Size(300, 100))
        self.staticBox1.SetAutoLayout(True)

        self.staticText1 = wx.StaticText(id=wxID_NODECREATORFRAMESTATICTEXT1,
              label=u'Parent Path', name='staticText1', parent=self.panel1,
              pos=wx.Point(31, 32), size=wx.Size(80, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText1.SetMinSize(wx.Size(80, -1))

        self.staticText2 = wx.StaticText(id=wxID_NODECREATORFRAMESTATICTEXT2,
              label=u'Node Name', name='staticText2', parent=self.panel1,
              pos=wx.Point(31, 59), size=wx.Size(80, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText2.SetMinSize(wx.Size(80, -1))

        self.staticText3 = wx.StaticText(id=wxID_NODECREATORFRAMESTATICTEXT3,
              label=u'Node Type', name='staticText3', parent=self.panel1,
              pos=wx.Point(31, 86), size=wx.Size(80, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText3.SetMinSize(wx.Size(80, -1))

        self.parentPath = wx.TextCtrl(id=wxID_NODECREATORFRAMEPARENTPATH,
              name=u'parentPath', parent=self.panel1, pos=wx.Point(111, 28),
              size=wx.Size(266, 22), style=wx.TE_READONLY, value=u'')
        self.parentPath.SetMinSize(wx.Size(339, 22))

        self.nodeName = wx.TextCtrl(id=wxID_NODECREATORFRAMENODENAME,
              name=u'nodeName', parent=self.panel1, pos=wx.Point(111, 55),
              size=wx.Size(266, 22), style=0, value=u'')
        self.nodeName.SetMinSize(wx.Size(339, 22))
        self.nodeName.SetToolTipString(u'Node Name')
        self.nodeName.Bind(wx.EVT_TEXT_ENTER, self.OnNodeNameTextEnter,
              id=wxID_NODECREATORFRAMENODENAME)
        self.nodeName.Bind(wx.EVT_TEXT, self.OnNodeNameText,
              id=wxID_NODECREATORFRAMENODENAME)

        self.nodeType = wx.ComboBox(choices=[],
              id=wxID_NODECREATORFRAMENODETYPE, name=u'nodeType',
              parent=self.panel1, pos=wx.Point(111, 82), size=wx.Size(266, 22),
              style=0, value=u'')
        self.nodeType.SetLabel(u'')
        self.nodeType.SetToolTipString(u'Node Type')
        self.nodeType.Bind(wx.EVT_COMBOBOX, self.OnNodeTypeCombobox,
              id=wxID_NODECREATORFRAMENODETYPE)
        self.nodeType.Bind(wx.EVT_TEXT_ENTER, self.OnNodeTypeTextEnter,
              id=wxID_NODECREATORFRAMENODETYPE)

        self.staticBox2 = wx.StaticBox(id=wxID_NODECREATORFRAMESTATICBOX2,
              label=u'Node Type', name='staticBox2', parent=self.panel1,
              pos=wx.Point(5, 124), size=wx.Size(382, 303), style=0)
        self.staticBox2.SetMinSize(wx.Size(300, 100))
        self.staticBox2.SetAutoLayout(True)

        self.okButton = wx.Button(id=wxID_NODECREATORFRAMEOKBUTTON, label=u'Ok',
              name=u'okButton', parent=self.panel1, pos=wx.Point(212, 437),
              size=wx.Size(100, 24), style=0)
        self.okButton.SetMinSize(wx.Size(100, 24))
        self.okButton.Bind(wx.EVT_BUTTON, self.OnOkButtonButton,
              id=wxID_NODECREATORFRAMEOKBUTTON)

        self.cancelButton = wx.Button(id=wxID_NODECREATORFRAMECANCELBUTTON,
              label=u'Cancel', name=u'cancelButton', parent=self.panel1,
              pos=wx.Point(312, 437), size=wx.Size(75, 24), style=0)
        self.cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelButtonButton,
              id=wxID_NODECREATORFRAMECANCELBUTTON)

        self.moduleTree = wx.TreeCtrl(id=wxID_NODECREATORFRAMEMODULETREE,
              name=u'moduleTree', parent=self.panel1, pos=wx.Point(15, 147),
              size=wx.Size(136, 270),
              style=wx.TR_LINES_AT_ROOT | wx.TR_SINGLE | wx.TR_HAS_BUTTONS)
        self.moduleTree.Bind(wx.EVT_TREE_SEL_CHANGED,
              self.OnModuleTreeTreeSelChanged,
              id=wxID_NODECREATORFRAMEMODULETREE)

        self.staticBitmap1 = wx.StaticBitmap(bitmap=wx.NullBitmap,
              id=wxID_NODECREATORFRAMESTATICBITMAP1, name='staticBitmap1',
              parent=self.panel1, pos=wx.Point(15, 31), size=wx.Size(16, 16),
              style=0)

        self.staticBitmap2 = wx.StaticBitmap(bitmap=wx.NullBitmap,
              id=wxID_NODECREATORFRAMESTATICBITMAP2, name='staticBitmap2',
              parent=self.panel1, pos=wx.Point(15, 58), size=wx.Size(16, 16),
              style=0)

        self.staticBitmap3 = wx.StaticBitmap(bitmap=wx.NullBitmap,
              id=wxID_NODECREATORFRAMESTATICBITMAP3, name='staticBitmap3',
              parent=self.panel1, pos=wx.Point(15, 85), size=wx.Size(16, 16),
              style=0)

        self.nodeTypeTree = wx.TreeCtrl(id=wxID_NODECREATORFRAMENODETYPETREE,
              name=u'nodeTypeTree', parent=self.panel1, pos=wx.Point(156, 147),
              size=wx.Size(221, 270),
              style=wx.TR_LINES_AT_ROOT | wx.TR_HAS_BUTTONS)
        self.nodeTypeTree.Bind(wx.EVT_TREE_SEL_CHANGED,
              self.OnNodeTypeTreeTreeSelChanged,
              id=wxID_NODECREATORFRAMENODETYPETREE)

        self._init_sizers()

    def __init__(self, parent):
        self._init_ctrls(parent)
        
        self.editedNodeName = False
        
        self.staticBitmap1.SetBitmap(wx.Bitmap('data/favorite_icon.png', wx.BITMAP_TYPE_PNG))
        self.staticBitmap2.SetBitmap(wx.Bitmap('data/netvibes.png', wx.BITMAP_TYPE_PNG))
        self.staticBitmap3.SetBitmap(wx.Bitmap('data/newsvine.png', wx.BITMAP_TYPE_PNG))
        
        self.ip = NOHImageProvider.NOHImageProvider('data/NOHTreeImages')
        self.nodeTypeTree.SetImageList(self.ip.getImageList())
        
        self.build_module_list()
        self.build_type_list()
        
    def setParentNode(self, node):
        self.parentNode = node
        path = node.getAbsolutePath()
        if len(path) == 0:
            self.parentPath.SetValue('/')
        else:
            self.parentPath.SetValue(path)
                
    def build_module_list(self):
        mlist = getModuleList()
        
        self.moduleTree.DeleteAllItems()
        root_item = self.moduleTree.AddRoot('modules')
        
        for mname in mlist:
            self.moduleTree.AppendItem(root_item, mname)
            
        self.moduleTree.ExpandAll()
        
    def build_type_list(self):
        self.nodeType.Clear()
        
        self.nodeTypeDict = {}
        for mname in getModuleList():
            for tname in getTypeList(mname):
                self.nodeType.Append(tname)
                self.nodeTypeDict[tname] = 0

    def OnModuleTreeTreeSelChanged(self, event):
        item = event.GetItem()
        mname = self.moduleTree.GetItemText(item)
        tlist = getTypeList(mname)
        
        self.nodeTypeTree.DeleteAllItems()
        root_item = self.nodeTypeTree.AddRoot('types')
        for tname in tlist:
            img_index = 0
            try:
                img_index = self.ip.getImage(tname)
            except:
                img_index = 0
            item = self.nodeTypeTree.AppendItem(root_item, tname, img_index)
            
        self.nodeTypeTree.ExpandAll()

    def OnOkButtonButton(self, event):
        node_type = str(self.nodeType.GetValue())
        node_name = str(self.nodeName.GetValue())
        
        if len(node_name) == 0:
            self.error_msg('Please input into the \'Node Name\' field')
            return
        
        if self.parentNode.findChild(node_name):
            self.error_msg('Specified node name already exist on parent node')
            return
        
        if not node_type in self.nodeTypeDict.keys():
            self.error_msg('unable to create specified type')
            return
        
        pushcwn(self.parentNode)
        new_node = new(node_type, node_name)
        popcwn()

        self.Destroy()

    def OnCancelButtonButton(self, event):
        self.Destroy()
        
    def OnNodeNameTextEnter(self, event):
        self.nodeType.SetFocus()
        
    def OnNodeNameText(self, event):
        self.editedNodeName = True

    def OnNodeTypeCombobox(self, event):
        self.generate_node_name_by_type(event.GetString())

    def OnNodeTypeTextEnter(self, event):
        self.OnOkButtonButton(0)

    def OnNodeTypeTreeTreeSelChanged(self, event):
        tname = self.nodeTypeTree.GetItemText(event.GetItem())
        self.nodeType.SetValue(tname)
        self.generate_node_name_by_type(tname)
        
    def generate_node_name_by_type(self, type):
        if self.editedNodeName:
            return
        index = 0
        new_node_name = ''
        children = self.parentNode.getChildren()
        for child in children:
            new_node_name = type + '_%02d' % (index,)
            if child.getName().find(new_node_name) != -1:
                index = index + 1
        new_node_name = type + '_%02d' % (index,)
        self.nodeName.SetValue(new_node_name)

    def error_msg(self, msg):
        dlg = wx.MessageDialog(self, msg, 'Error', wx.OK | wx.ICON_INFORMATION)
        dlg.ShowModal()
        dlg.Destroy()
