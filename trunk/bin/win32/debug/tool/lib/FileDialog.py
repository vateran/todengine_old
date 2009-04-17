#Boa:Dialog:FileDialog
# coding: mbcs 

import time
import wx
import wx.lib.buttons
import wx.lib.platebtn as platebtn
import lib.ImageProvider as ImageProvider
from todpython import *

def create(parent):
    return FileDialog(parent)

[wxID_FILEDIALOG, wxID_FILEDIALOGCANCELBUTTON, wxID_FILEDIALOGFILELISTCTRL, 
 wxID_FILEDIALOGFILENAMECOMBOBOX, wxID_FILEDIALOGLOCATIONCOMBOBOX, 
 wxID_FILEDIALOGOPENBUTTON, wxID_FILEDIALOGSTATICTEXT1, 
 wxID_FILEDIALOGSTATICTEXT2, wxID_FILEDIALOGSTATICTEXT3, 
 wxID_FILEDIALOGSTORAGETREEVIEW, wxID_FILEDIALOGURICOMBOBOX, 
] = [wx.NewId() for _init_ctrls in range(11)]

class FileDialog(wx.Dialog):
    def _init_coll_mainSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.headerSizer, 0, border=5,
              flag=wx.BOTTOM | wx.TOP | wx.RIGHT | wx.LEFT | wx.EXPAND)
        parent.AddSizer(self.midSizer, 1, border=5,
              flag=wx.EXPAND | wx.BOTTOM | wx.LEFT | wx.RIGHT)

    def _init_coll_footSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.footSizer2, 1, border=8,
              flag=wx.TOP | wx.ALIGN_CENTER_VERTICAL | wx.EXPAND | wx.RIGHT)
        parent.AddSizer(self.buttonSizer, 0, border=0, flag=0)

    def _init_coll_uriSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText2, 0, border=0,
              flag=wx.ALIGN_CENTER_VERTICAL)
        parent.AddWindow(self.uriComboBox, 1, border=0,
              flag=wx.RIGHT | wx.EXPAND)

    def _init_coll_midSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.storageTreeView, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.EXPAND)
        parent.AddSizer(self.midSizer2, 1, border=0,
              flag=wx.EXPAND | wx.BOTTOM | wx.RIGHT)

    def _init_coll_footSizer2_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.uriSizer, 0, border=6, flag=wx.BOTTOM | wx.EXPAND)
        parent.AddSizer(self.fileNameSizer, 0, border=0,
              flag=wx.EXPAND | wx.ALL)

    def _init_coll_buttonSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.openButton, 0, border=5,
              flag=wx.BOTTOM | wx.TOP | wx.RIGHT | wx.LEFT)
        parent.AddWindow(self.cancelButton, 0, border=5,
              flag=wx.BOTTOM | wx.RIGHT | wx.LEFT)

    def _init_coll_fileNameSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText3, 0, border=0,
              flag=wx.ALIGN_CENTER_VERTICAL)
        parent.AddWindow(self.fileNameComboBox, 1, border=0,
              flag=wx.EXPAND | wx.RIGHT)

    def _init_coll_headerSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText1, 0, border=30,
              flag=wx.ALIGN_RIGHT | wx.ALIGN_CENTER_VERTICAL | wx.RIGHT | wx.LEFT)
        parent.AddWindow(self.locationComboBox, 1, border=3,
              flag=wx.TOP | wx.RIGHT | wx.LEFT | wx.EXPAND)

    def _init_coll_midSizer2_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.fileListCtrl, 1, border=0,
              flag=wx.BOTTOM | wx.RIGHT | wx.EXPAND)
        parent.AddSizer(self.footSizer, 0, border=10, flag=wx.EXPAND)

    def _init_sizers(self):
        # generated method, don't edit
        self.mainSizer = wx.BoxSizer(orient=wx.VERTICAL)

        self.headerSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.midSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.midSizer2 = wx.BoxSizer(orient=wx.VERTICAL)

        self.fileNameSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.uriSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.footSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.buttonSizer = wx.BoxSizer(orient=wx.VERTICAL)

        self.footSizer2 = wx.BoxSizer(orient=wx.VERTICAL)

        self._init_coll_mainSizer_Items(self.mainSizer)
        self._init_coll_headerSizer_Items(self.headerSizer)
        self._init_coll_midSizer_Items(self.midSizer)
        self._init_coll_midSizer2_Items(self.midSizer2)
        self._init_coll_fileNameSizer_Items(self.fileNameSizer)
        self._init_coll_uriSizer_Items(self.uriSizer)
        self._init_coll_footSizer_Items(self.footSizer)
        self._init_coll_buttonSizer_Items(self.buttonSizer)
        self._init_coll_footSizer2_Items(self.footSizer2)

        self.SetSizer(self.mainSizer)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Dialog.__init__(self, id=wxID_FILEDIALOG, name=u'FileDialog',
              parent=prnt, pos=wx.Point(721, 328), size=wx.Size(693, 454),
              style=wx.DIALOG_MODAL | wx.CLOSE_BOX | wx.CAPTION | wx.RESIZE_BORDER,
              title=u'\ud30c\uc77c \uc5f4\uae30')
        self.SetClientSize(wx.Size(677, 418))
        self.SetMinSize(wx.Size(693, 454))
        self.SetMaxSize(wx.Size(-1, -1))
        self.Center(wx.BOTH)

        self.staticText1 = wx.StaticText(id=wxID_FILEDIALOGSTATICTEXT1,
              label=u'\ucc3e\ub294 \uc704\uce58(&I):', name='staticText1',
              parent=self, pos=wx.Point(35, 10), size=wx.Size(66, 15),
              style=wx.ALIGN_RIGHT)
        self.staticText1.SetFont(wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, u'\ub9d1\uc740 \uace0\ub515'))

        self.locationComboBox = wx.ComboBox(choices=[],
              id=wxID_FILEDIALOGLOCATIONCOMBOBOX, name=u'locationComboBox',
              parent=self, pos=wx.Point(134, 8), size=wx.Size(535, 22), style=0,
              value=u'')
        self.locationComboBox.SetLabel(u'')

        self.storageTreeView = wx.TreeCtrl(id=wxID_FILEDIALOGSTORAGETREEVIEW,
              name=u'storageTreeView', parent=self, pos=wx.Point(10, 35),
              size=wx.Size(136, 378), style=wx.TR_HAS_BUTTONS)

        self.fileListCtrl = wx.ListCtrl(id=wxID_FILEDIALOGFILELISTCTRL,
              name=u'fileListCtrl', parent=self, pos=wx.Point(151, 35),
              size=wx.Size(521, 315), style=wx.LC_REPORT)
        self.fileListCtrl.Bind(wx.EVT_LIST_ITEM_SELECTED,
              self.OnFileListCtrlListItemSelected,
              id=wxID_FILEDIALOGFILELISTCTRL)

        self.staticText2 = wx.StaticText(id=wxID_FILEDIALOGSTATICTEXT2,
              label=u'URI (&T): ', name='staticText2', parent=self,
              pos=wx.Point(151, 362), size=wx.Size(80, 14),
              style=wx.ALIGN_RIGHT)
        self.staticText2.SetFont(wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, u'\ub9d1\uc740 \uace0\ub515'))
        self.staticText2.SetMinSize(wx.Size(80, 14))

        self.staticText3 = wx.StaticText(id=wxID_FILEDIALOGSTATICTEXT3,
              label=u'\ud30c\uc77c \uc774\ub984(&N): ', name='staticText3',
              parent=self, pos=wx.Point(151, 390), size=wx.Size(80, 14),
              style=wx.ALIGN_RIGHT)
        self.staticText3.SetFont(wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL,
              False, u'\ub9d1\uc740 \uace0\ub515'))
        self.staticText3.SetMinSize(wx.Size(80, 14))

        self.uriComboBox = wx.ComboBox(choices=[],
              id=wxID_FILEDIALOGURICOMBOBOX, name=u'uriComboBox', parent=self,
              pos=wx.Point(231, 358), size=wx.Size(332, 22), style=0,
              value=u'')
        self.uriComboBox.SetLabel(u'')

        self.openButton = wx.Button(id=wxID_FILEDIALOGOPENBUTTON,
              label=u'\uc5f4\uae30(&O)', name=u'openButton', parent=self,
              pos=wx.Point(576, 355), size=wx.Size(91, 24), style=0)
        self.openButton.Bind(wx.EVT_BUTTON, self.OnOpenButtonButton,
              id=wxID_FILEDIALOGOPENBUTTON)

        self.cancelButton = wx.Button(id=wxID_FILEDIALOGCANCELBUTTON,
              label=u'\ucde8\uc18c', name=u'cancelButton', parent=self,
              pos=wx.Point(576, 384), size=wx.Size(91, 24), style=0)
        self.cancelButton.Bind(wx.EVT_BUTTON, self.OnCancelButtonButton,
              id=wxID_FILEDIALOGCANCELBUTTON)

        self.fileNameComboBox = wx.ComboBox(choices=[],
              id=wxID_FILEDIALOGFILENAMECOMBOBOX, name=u'fileNameComboBox',
              parent=self, pos=wx.Point(231, 386), size=wx.Size(332, 22),
              style=0, value=u'')
        self.fileNameComboBox.SetLabel(u'')
        self.fileNameComboBox.Bind(wx.EVT_TEXT, self.OnFileNameComboBoxText,
              id=wxID_FILEDIALOGFILENAMECOMBOBOX)

        self._init_sizers()

    def __init__(self, parent):
        self._init_ctrls(parent)
        
        self.selectedPath = ''
        self.ip = ImageProvider.ImageProvider('data/FileDialog')
        
        self.buildButtons()
        self.buildStorages()
        self.buildFileListCtrl()
        
    def setupOpenMode(self):
        self.SetTitle('파일 열기')
        self.openButton.SetLabel('열기(&O)')
        
    def setupSaveMode(self):
        self.SetTitle('파일 저장')
        self.openButton.SetLabel('저장(&S)')
        
    def setupSaveAsMode(self):
        self.SetTitle('다른 이름으로 파일 저장')
        self.openButton.SetLabel('저장(&S)')        
                
    def buildStorages(self):        
        self.storageTreeView.SetImageList(self.ip.getImageList())    
        root_item = self.storageTreeView.AddRoot('Storages')
        self.storageTreeView.SetItemImage(root_item, 0)
        self.storageTreeView.SetItemHasChildren(root_item, True)
        self.Bind(wx.EVT_TREE_ITEM_EXPANDING, self.OnStorageTreeViewExpending, id=self.storageTreeView.GetId())
        self.Bind(wx.EVT_TREE_ITEM_COLLAPSING, self.OnStorageTreeViewCollapsing, id=self.storageTreeView.GetId())
        self.Bind(wx.EVT_TREE_SEL_CHANGED, self.OnStorageTreeViewSelChanged, id=self.storageTreeView.GetId())
        self.storageTreeView.Expand(root_item)
        
    def buildFileListCtrl(self):
        self.fileListCtrl.SetImageList(self.ip.getImageList(), wx.IMAGE_LIST_SMALL)
        col_data = ((u'이름', wx.LIST_FORMAT_LEFT, 200),
            (u'수정한 날짜', wx.LIST_FORMAT_RIGHT, 140),
            (u'유형', wx.LIST_FORMAT_LEFT, -1),
            (u'크기', wx.LIST_FORMAT_RIGHT, -1),
            (u'태그', wx.LIST_FORMAT_LEFT, -1))
        i = 0
        for cd in col_data:
            self.fileListCtrl.InsertColumn(i, cd[0], cd[1], cd[2])
            i = i + 1
        
    def OnStorageTreeViewExpending(self, event):
        evt_item = event.GetItem()
        if self.storageTreeView.GetRootItem() == evt_item:
            if self.storageTreeView.GetChildrenCount(evt_item) > 0:
                event.Veto()
            else:
                rm = res()
                for s in rm.getStorages():
                    item = self.storageTreeView.AppendItem(evt_item, s.getName())
                    self.storageTreeView.SetItemHasChildren(item, len(s.findEntries('*', False)) > 0)
                    self.storageTreeView.SetItemImage(item, 0)
            return
        parent_item = self.storageTreeView.GetItemParent(evt_item)
        # stoarge
        self.storageTreeView.DeleteChildren(evt_item)
        if parent_item == self.storageTreeView.GetRootItem():
            rm = res()
            storage_name = str(self.storageTreeView.GetItemText(evt_item))
            s = rm.findStorage(storage_name)
            for e in s.findEntries('*', False):
                item = self.storageTreeView.AppendItem(evt_item, e.getName())
                self.storageTreeView.SetItemHasChildren(item, len(s.findEntries(e.getName() + '/*', False)) > 0)
                self.storageTreeView.SetItemImage(item, 0)
        # directory
        else:
            rm = res()
            storage_name, path = self.convert_to_path(evt_item)
            s = rm.findStorage(str(storage_name))
            entries = s.findEntries(str(path + '/*'), False)
            for e in entries:
                item = self.storageTreeView.AppendItem(evt_item, e.getName())
                self.storageTreeView.SetItemImage(item, 0)
                self.storageTreeView.SetItemHasChildren(item, len(s.findEntries(str(path + '/' + e.getName() + '/*'), False)) > 0)
            
    def OnStorageTreeViewCollapsing(self, event):
        if self.storageTreeView.GetRootItem() == event.GetItem():
            event.Veto()
            return
        event.Skip()
        
    def OnStorageTreeViewSelChanged(self, event):
        evt_item = event.GetItem()
        rm = res()            
        ctp = self.convert_to_path(evt_item)
        if ctp == None:
            event.Veto()
            return
        storage_name, path = ctp
        s = rm.findStorage(str(storage_name))
        self.fileListCtrl.DeleteAllItems()
        index = 0
        for e in s.findEntries(str(path + '/*'), True):
            self.fileListCtrl.InsertImageStringItem(
                index, e.getName(), self.ip.getImageIndex('file'))
            lt = time.localtime(e.getWriteTime())
            t = time.strftime('%Y-%m-%d', lt)
            ampm = time.strftime('%p', lt)
            if ampm == 'AM':
                t = t + ' 오전 '
            else:
                t = t + ' 오후 '
            t = t + time.strftime('%I:%M', lt)
            self.fileListCtrl.SetStringItem(index, 1, t)
            self.fileListCtrl.SetStringItem(index, 2, e.getFileType())
            self.fileListCtrl.SetStringItem(index, 3, str(e.getSize()))
            self.fileListCtrl.SetStringItem(index, 3, str(e.getSize()))
            self.fileListCtrl.SetItemFont(index, wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL,
                False, u'\ub9d1\uc740 \uace0\ub515'))
            index = index + 1
        self.selectedPath = storage_name + '#' + path
        self.update_textctrls()
    
    def convert_to_path(self, item):
        if self.storageTreeView.GetRootItem() == item:
            return None
        path = ''
        storage_name = ''
        i = item
        while True:            
            if self.storageTreeView.GetItemParent(i) == self.storageTreeView.GetRootItem():
                storage_name = self.storageTreeView.GetItemText(i)
                break
            path = self.storageTreeView.GetItemText(i) + '/' + path
            i = self.storageTreeView.GetItemParent(i)
            
        return (storage_name, path[:-1])
            
    def buildButtons(self):
        self.backButton = platebtn.PlateButton(
              bmp=wx.Bitmap('data/FileDialog/back.png', wx.BITMAP_TYPE_PNG),
              name=u'backButton', parent=self, size=wx.Size(16, 16),
              style=platebtn.PB_STYLE_SQUARE)
        self.backButton.SetPressColor(wx.SystemSettings.GetColour(wx.SYS_COLOUR_MENU))
        self.backButton.Bind(wx.EVT_BUTTON, self.OnBackButton,
              id=self.backButton.GetId())
        self.headerSizer.AddWindow(self.backButton, 0, border=3,
              flag=wx.TOP | wx.LEFT)
              
        self.parentDirectoryButton = platebtn.PlateButton(
              bmp=wx.Bitmap('data/FileDialog/parent_directory.png', wx.BITMAP_TYPE_PNG),
              name=u'parentDirectoryButton', parent=self, size=wx.Size(31, 30),
              style=platebtn.PB_STYLE_SQUARE)
        self.parentDirectoryButton.SetPressColor(wx.SystemSettings.GetColour(wx.SYS_COLOUR_MENU))
        self.parentDirectoryButton.Bind(wx.EVT_BUTTON, self.OnParentDirectoryButton,
              id=self.parentDirectoryButton.GetId())
        self.headerSizer.AddWindow(self.parentDirectoryButton, 0, border=3,
              flag=wx.TOP | wx.LEFT)
              
        self.deleteButton = platebtn.PlateButton(
              bmp=wx.Bitmap('data/FileDialog/delete.png', wx.BITMAP_TYPE_PNG),
              name=u'deleteButton', parent=self, size=wx.Size(31, 30),
              style=platebtn.PB_STYLE_SQUARE)
        self.deleteButton.SetPressColor(wx.SystemSettings.GetColour(wx.SYS_COLOUR_MENU))
        self.deleteButton.Bind(wx.EVT_BUTTON, self.OnDeleteButton,
              id=self.deleteButton.GetId())
        self.headerSizer.AddWindow(self.deleteButton, 0, border=3,
              flag=wx.TOP | wx.LEFT)
              
        self.newDirectoryButton = platebtn.PlateButton(
              bmp=wx.Bitmap('data/FileDialog/new_directory.png', wx.BITMAP_TYPE_PNG),
              name=u'newDirectoryButton', parent=self, size=wx.Size(31, 30),
              style=platebtn.PB_STYLE_SQUARE)
        self.newDirectoryButton.SetPressColor(wx.SystemSettings.GetColour(wx.SYS_COLOUR_MENU))
        self.newDirectoryButton.Bind(wx.EVT_BUTTON, self.OnNewDirectoryButton,
              id=self.newDirectoryButton.GetId())
        self.headerSizer.AddWindow(self.newDirectoryButton, 0, border=3,
              flag=wx.TOP | wx.LEFT)
              
        self.viewModeButton = platebtn.PlateButton(
              bmp=wx.Bitmap('data/FileDialog/view_mode.png', wx.BITMAP_TYPE_PNG),
              name=u'viewModeButton', parent=self, size=wx.Size(31, 30),
              style=platebtn.PB_STYLE_SQUARE)
        self.viewModeButton.SetPressColor(wx.SystemSettings.GetColour(wx.SYS_COLOUR_MENU))
        self.viewModeButton.Bind(wx.EVT_BUTTON, self.OnViewModeButton,
              id=self.viewModeButton.GetId())
        self.headerSizer.AddWindow(self.viewModeButton, 0, border=3,
              flag=wx.TOP | wx.LEFT)
        menu = wx.Menu()
        self.menuData = [(u'축소판 그림(&T)', 'data/FileDialog/thumb_view.png', 'data/FileDialog/thumb_view_v.png'),
            (u'타일(&S)', 'data/FileDialog/tile_view.png', 'data/FileDialog/tile_view_v.png'),
            (u'아이콘(&N)', 'data/FileDialog/icon_view.png', 'data/FileDialog/icon_view_v.png'),
            (u'간단히(&D)', 'data/FileDialog/simple_view.png', 'data/FileDialog/simple_view_v.png'),
            (u'자세히(&L)', 'data/FileDialog/detail_view.png', 'data/FileDialog/detail_view_v.png')]
        for md in self.menuData:
            mi = wx.MenuItem(menu, wx.NewId(), md[0], kind=wx.ITEM_RADIO)
            mi.SetBitmap(wx.Bitmap(md[1], wx.BITMAP_TYPE_PNG))
            menu.AppendItem(mi)
            self.Bind(wx.EVT_MENU, self.OnViewModeMenu, id=mi.GetId())
        self.viewModeButton.SetMenu(menu)
        mi = menu.FindItemByPosition(4)
        mi.Check(True)
        self.OnViewModeMenu(0)

    def OnBackButton(self, event):
        event.Skip()
    
    def OnParentDirectoryButton(self, event):
        event.Skip()
        
    def OnDeleteButton(self, event):
        event.Skip()
        
    def OnNewDirectoryButton(self, event):
        event.Skip()

    def OnViewModeButton(self, event):
        event.Skip()
       
    def OnViewModeMenu(self, event):
        menu = self.viewModeButton.GetMenu()
        i = 0
        for m in menu.GetMenuItems():
            if m.IsChecked():
                m.SetBitmap(wx.Bitmap(self.menuData[i][2]))
            else:
                m.SetBitmap(wx.Bitmap(self.menuData[i][1]))
            i = i + 1

    def OnFileListCtrlListItemSelected(self, event):
        self.fileNameComboBox.SetValue(event.GetLabel())
        self.update_textctrls()

    def OnFileNameComboBoxText(self, event):
        self.update_textctrls()
        
    def update_textctrls(self):
        try:
            uri = 'managed://' + self.selectedPath
            if self.selectedPath[-1] != '#' and self.selectedPath[-1] != '/':            
                uri += '/'
            uri += self.fileNameComboBox.GetValue()
            self.uriComboBox.SetValue(uri)
        except:
            pass

    def OnOpenButtonButton(self, event):
        self.EndModal(wx.ID_OK)

    def OnCancelButtonButton(self, event):
        self.uriComboBox.SetValue('')
        self.EndModal(wx.ID_CANCEL)
        
    def setFileName(self, name):
        self.fileNameComboBox.SetValue(name)
        self.update_textctrls()
        
    def getUri(self):
        return self.uriComboBox.GetValue()
        
