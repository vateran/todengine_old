# coding: mbcs

from todpython import *
import wx
import lib.CommandConsole as CommandConsole
import lib.FileDialog as FileDialog

split_control_width = 4

#-------------------------------------------------------------------------------
class ProperyItemName(wx.StaticText):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        wx.StaticText.__init__(self, parent, id, ' ' + value,
            wx.Point(pos[0], pos[1] + 1),
            wx.Size(size.GetWidth(), size.GetHeight() - 2), style, name)
        self.SetBackgroundColour(wx.Colour(255, 255, 255))
        tooltip = wx.ToolTip(value)
        tooltip.SetDelay(0)
        tooltip.Enable(True)
        self.SetToolTip(tooltip)
        self.Bind(wx.EVT_SET_FOCUS, self.OnSetFocus, id=id)
        self.Bind(wx.EVT_KILL_FOCUS, self.OnKillFocus, id=id)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnLeftDown, id=id)
        self.readonly = readonly
        if self.readonly:
            self.SetForegroundColour(wx.Colour(167, 166, 170))
        self.value = value
        
    def OnSetFocus(self, event):
        self.SetForegroundColour(wx.Colour(255, 255, 255))
        self.SetBackgroundColour(wx.Colour(51, 94, 168))
        self.Refresh()
        self.GetParent().GetParent().GetParent().OnSelectedProperty(self)
        
    def OnKillFocus(self, event):
        if self.readonly:
            self.SetForegroundColour(wx.Colour(167, 166, 170))
        else:
            self.SetForegroundColour(wx.Colour(0, 0, 0))
        self.SetBackgroundColour(wx.Colour(255, 255, 255))
        self.Refresh()
        
    def OnLeftDown(self, event):
        self.SetFocus()



#-------------------------------------------------------------------------------
class PropertyItemValue(wx.Window):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        wx.Window.__init__(self, parent, id, wx.Point(pos[0] + 1, pos[1] + 1),
            wx.Size(size[0] - 2, size[1] - 2), style, name)
        self.SetBackgroundColour(wx.Colour(255, 255, 255))
        if readonly:
            self.SetForegroundColour(wx.Colour(167, 166, 170))
        
    def bindProprtyItemEvents(self, child):
        child.Bind(wx.EVT_SET_FOCUS, self.OnSetFocus, id=child.GetId())
        child.Bind(wx.EVT_KILL_FOCUS, self.OnKillFocus, id=child.GetId())
    
    def OnSetFocus(self, event):
        self.updateValue()
        self.nameControl.OnSetFocus(event)
        event.Skip()
        
    def OnKillFocus(self, event):        
        self.nameControl.OnKillFocus(event)
        event.Skip()
        
    def setValue(self, value):        
        PropertyGrid.instance().OnChangePropertyValue(self.object, self.propertyName, value)
        
    def updateValue(self):
        prop_name, prop_value, prop_type, readonly = self.object.getProperty(self.propertyName)
        self.update_value(prop_value)

    def GetArrangeSize(self):
        w, h = self.GetSize()
        return wx.Size(w, h + 1)

    
#-------------------------------------------------------------------------------
class PropertyItemValueString(PropertyItemValue):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        PropertyItemValue.__init__(self, parent, id, pos, size, style, name, value, readonly)
        style |= wx.NO_BORDER | wx.TE_PROCESS_ENTER
        if readonly:
            style |= wx.TE_READONLY
        self.textCtrl =  wx.TextCtrl(self, wx.NewId(), value, wx.Point(0, 0),
            wx.Size(0, 0), style=style)
        self.update_textctrl_size()
        if readonly:
            self.textCtrl.SetForegroundColour(wx.Colour(167, 166, 170))
        self.textCtrl.Bind(wx.EVT_TEXT_ENTER, self.OnTextEnter, id=self.textCtrl.GetId())
        self.bindProprtyItemEvents(self.textCtrl)
        
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())

    def OnTextEnter(self, event):
        self.setValue(str(self.textCtrl.GetValue()))
        
    def update_value(self, value):
        self.textCtrl.SetValue(value)

    def OnSize(self, event):
        self.update_textctrl_size()
        
    def update_textctrl_size(self):
        w, h = self.GetSize()
        self.textCtrl.SetSize(wx.Size(w - 20, h))


#-------------------------------------------------------------------------------
class PropertyItemValueBool(PropertyItemValue):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        PropertyItemValue.__init__(self, parent, id, pos, size, style, name, value, readonly)
        self.checkBox =  wx.CheckBox(self, wx.NewId(), 'false', wx.Point(1, 2), wx.DefaultSize, style=0)
        self.checkBox.Bind(wx.EVT_CHECKBOX, self.OnCheckBox, id=self.checkBox.GetId())
        self.update_value(value)
        self.bindProprtyItemEvents(self.checkBox)

    def OnCheckBox(self, event):
        self.setValue(str(self.checkBox.IsChecked()))
        if self.checkBox.IsChecked():
            self.update_value('true')
        else:
            self.update_value('false')
        
    def update_value(self, value):
        self.checkBox.SetValue(value == 'true')
        self.checkBox.SetLabel(value)
        self.checkBox.Refresh()


#-------------------------------------------------------------------------------
class PropertyItemValueVector3(PropertyItemValue):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        PropertyItemValue.__init__(self, parent, id, pos, size, style, name, value, readonly)
        self.SetForegroundColour(wx.Colour(167, 166, 170))

        self.checkbox = PropertyGridGroupTreeItemButton(self, wx.Point(4, 4))
        self.checkbox.SetValue(False)

        self.style = style | wx.NO_BORDER | wx.TE_PROCESS_ENTER
        if readonly:
            self.style |= wx.TE_READONLY
        self.textCtrl =  wx.TextCtrl(self, wx.NewId(), value, wx.Point(14, 0),
            wx.Size(0, 0), style=self.style)
        self.update_textctrl_size()
        if readonly:
            self.textCtrl.SetForegroundColour(wx.Colour(167, 166, 170))
        self.textCtrl.Bind(wx.EVT_TEXT_ENTER, self.OnTextEnter, id=self.textCtrl.GetId())
        self.bindProprtyItemEvents(self.textCtrl)
        
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())
        self.checkbox.Bind(wx.EVT_CHECKBOX, self.OnExpand, id=self.checkbox.GetId())

        self.textCtrls = []
        self.subWindow = None
        self.curHeight = size[1] - 1
        self.value = value.split(' ')

    def OnTextEnter(self, event):
        self.sync_text_values(True)
        self.setValue(str(self.textCtrl.GetValue()))

    def OnSubTextEnter(self, event):
        self.sync_text_values(False)
        self.setValue(str(self.textCtrl.GetValue()))

    def OnSubTextMouseWheel(self, event):
        t = event.GetEventObject()
        if event.GetWheelRotation() > 0:
            t.SetValue(str(float(t.GetValue()) + 10))
        else:
            t.SetValue(str(float(t.GetValue()) - 10))
        self.sync_text_values(False)
        self.setValue(str(self.textCtrl.GetValue()))

    def sync_text_values(self, dir):        
        if len(self.textCtrls) == 0:
            return
        if dir:
            self.value = self.textCtrl.GetValue().split(' ')
            for i in range(0, 3):
                t = self.textCtrls[i]
                t.SetValue(self.value[i])
        else:
            value = ''
            for i in range(0, 3):
                t = self.textCtrls[i]
                value = value + t.GetValue() + ' '
            self.textCtrl.SetValue(value)
    
    def OnSize(self, event):
        self.update_textctrl_size()

    def OnExpand(self, event):
        height = PropertyGroup.lineHeight - 1
        # expanded
        if event.IsChecked():
            self.subWindow = wx.Window(self, wx.NewId(), wx.Point(0, self.textCtrl.GetSize().GetHeight() - 1),
                    wx.Size(self.GetSize().GetWidth(), 0), 0)
            self.subWindow.SetBackgroundColour(wx.Colour(241, 239, 226))
            y = 1
            for i in range(0, 3):
                textctrl = wx.TextCtrl(self.subWindow, wx.NewId(), self.value[i], 
                        wx.Point(14, y), wx.Size(self.subWindow.GetSize().GetWidth(), height - 1),
                        name=str(i), style=self.style)
                self.textCtrls.append(textctrl)
                textctrl.Bind(wx.EVT_TEXT_ENTER, self.OnSubTextEnter, id=textctrl.GetId())
                textctrl.Bind(wx.EVT_MOUSEWHEEL, self.OnSubTextMouseWheel, id=textctrl.GetId())
                y += height
            self.curHeight = height * 4
            w, h = self.GetSize()
            self.SetSize(wx.Size(w, self.curHeight))
            w, h = self.subWindow.GetSize()
            self.subWindow.SetSize(wx.Size(w, height * 3 + 1))
        # collapsed
        else:
            if self.subWindow != None:
                self.subWindow.Destroy()
            self.textCtrls = []
            w, h = self.GetSize()
            self.curHeight = height
            self.SetSize(wx.Size(w, self.curHeight - 1))

        self.GetParent().GetParent().GetParent().arrange()    

    def GetArrangeSize(self):
        return wx.Size(self.GetSize().GetWidth(), self.curHeight)

    def update_value(self, value):
        self.textCtrl.SetValue(value)
           
    def update_textctrl_size(self):
        w, h = self.GetSize()
        self.textCtrl.SetSize(wx.Size(w - 20, PropertyGroup.lineHeight - 1))


#-------------------------------------------------------------------------------
class PropertyItemValueUri(PropertyItemValue):
    def __init__(self, parent, id, pos, size, style, name, value, readonly):
        PropertyItemValue.__init__(self, parent, id, pos, size, style, name, value, readonly)

        self.findButton = wx.Button(self, wx.NewId(), '...', wx.Point(0, 0), wx.Size(16, 16))
        self.Bind(wx.EVT_BUTTON, self.OnFindButton, id=self.findButton.GetId())

        style |= wx.NO_BORDER | wx.TE_PROCESS_ENTER
        if readonly:
            style |= wx.TE_READONLY
        self.textCtrl =  wx.TextCtrl(self, wx.NewId(), value, wx.Point(0, 0),
            wx.Size(0, 0), style=style)
        self.update_textctrl_size()
        if readonly:
            self.textCtrl.SetForegroundColour(wx.Colour(167, 166, 170))
        self.textCtrl.Bind(wx.EVT_TEXT_ENTER, self.OnTextEnter, id=self.textCtrl.GetId())
        self.bindProprtyItemEvents(self.textCtrl)        
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())

    def OnTextEnter(self, event):
        self.setValue(str(self.textCtrl.GetValue()))
        
    def update_value(self, value):
        self.textCtrl.SetValue(value)

    def OnSize(self, event):
        self.update_textctrl_size()

    def OnFindButton(self, event):
        fd = FileDialog.FileDialog(self)
        fd.setupOpenMode()
        if fd.ShowModal() == wx.ID_OK:
            self.update_value(fd.getUri())
            self.setValue(fd.getUri())
        
    def update_textctrl_size(self):
        w, h = self.GetSize()
        self.textCtrl.SetSize(wx.Size(w - 40, h))
        self.findButton.SetPosition(wx.Point(w - 36, 0))


#-------------------------------------------------------------------------------
class PropertyGridGroupTreeItemButton(wx.CheckBox):
    def __init__(self, parent, pos):
        wx.CheckBox.__init__(self, parent, wx.NewId(), '', pos, wx.Size(9, 9))
        
        self.SetValue(True)
        
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        
    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        dc.DrawRectangle(0, 0, self.GetSize()[0], self.GetSize()[1])
        render = wx.RendererNative.Get()
        r = (0, 0, 10, 10)
        if self.IsChecked():
            render.DrawTreeItemButton(self, dc, r, wx.CONTROL_EXPANDED)
        else:
            render.DrawTreeItemButton(self, dc, r)


#-------------------------------------------------------------------------------
class PropertyGroup(wx.Panel):
    headerWidth = 16
    headerHeight = 18
    lineHeight = 18
    sashRatio = 1.0 / 3
    font = None
    propertyEditorType = {}
        
    def __init__(self, parent, id, pos, size, style, name):
        wx.Panel.__init__(self, parent, id, pos, size, style, name)
        self.SetBackgroundColour(wx.Colour(241, 239, 226))
        if PropertyGroup.font == None:
            PropertyGroup.font = wx.Font(9, wx.SWISS, wx.NORMAL, wx.BOLD, False, u'Tahoma')
        self.treeItemButton = PropertyGridGroupTreeItemButton(self, wx.Point(5, 5))
        
        self.sw = wx.SplitterWindow(self, wx.NewId(),
            wx.Point(PropertyGroup.headerWidth, PropertyGroup.headerHeight),
            wx.Size(size[0] - PropertyGroup.headerWidth, size[1] - PropertyGroup.headerHeight), 0, '')
        self.namePanel = wx.Panel(self.sw, id=wx.NewId())
        self.valuePanel = wx.Panel(self.sw, id=wx.NewId())
        self.sw.SplitVertically(self.namePanel, self.valuePanel, self.sw.GetSize().GetWidth() * PropertyGroup.sashRatio)
        self.sw.SetSashSize(1)
        self.sw.SetMinimumPaneSize(20)
        self.sw.Bind(wx.EVT_SPLITTER_SASH_POS_CHANGED,
              self.OnSplitterSashPosChanged, id=self.sw.GetId())
        
        self.bestWidth = size.GetWidth()
        self.curY = 0
        self.item = []

        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())
        self.treeItemButton.Bind(wx.EVT_CHECKBOX, self.OnTreeItemButton,
              id=self.treeItemButton.GetId())
              
    def addProperty(self, object, name, value, type, readonly):
        w = self.GetSize().GetWidth()
        item_name = ProperyItemName(self.namePanel, wx.NewId(),
            wx.Point(0, self.curY),
            wx.Size(w, self.lineHeight), 0, '', name, readonly)
        editor_cls = PropertyGroup.findPropertyValueEditorType(type)
        item_value = None
        if editor_cls != None:
            item_value = editor_cls(self.valuePanel,
                wx.NewId(), wx.Point(0, self.curY),
                wx.Size(0, PropertyGroup.lineHeight), 0, '', value, readonly)
        else:
            item_value = PropertyItemValueString(self.valuePanel,
                wx.NewId(), wx.Point(0, self.curY),
                wx.Size(0, PropertyGroup.lineHeight), 0, '', value, readonly)
        item_value.SetMaxSize(wx.Size(4096, PropertyGroup.lineHeight))
        item_value.nameControl = item_name
        item_value.object = object
        item_value.propertyName = name
        self.item.append((item_name, item_value))
        self.curY += PropertyGroup.lineHeight - 1
    
    @classmethod
    def addPropertyValueEditorType(self, name, type, cls):
        PropertyGroup.propertyEditorType[type] = (name, cls)
        
    @classmethod
    def findPropertyValueEditorType(Self, type):
        if not (type in PropertyGroup.propertyEditorType.keys()):
            return None
        return PropertyGroup.propertyEditorType[type][1]
        
    def update_sash_ratio(self, pos):
        PropertyGroup.sashRatio = float(pos) / float(self.sw.GetSize().GetWidth())

    def arrange(self):
        self.curY = 1
        for item_name, item_value in self.item:
            w, h = item_value.GetArrangeSize()
            item_name.SetPosition(wx.Point(0, self.curY))
            item_value.SetPosition(wx.Point(1, self.curY))
            self.curY += h

        self.SetSize(self.GetBestSize())
        self.GetParent().layoutPropertyGroups()
                
    def SetSashPosition(self, pos):
        self.sw.SetSashPosition(pos)
        self.setSashPos(pos)
        
    def OnSplitterSashPosChanged(self, event):
        pos = event.GetSashPosition()
        self.update_sash_ratio(pos)
        self.setSashPos(pos)
        self.GetParent().OnSplitterSashPosChanged(self, pos)
                
    def setSashPos(self, pos):
        value_panel_w = self.valuePanel.GetSize().GetWidth()
        for item_name, item_value in self.item:
            # change size item_name
            w, h = item_name.GetSize()
            item_name.SetSize(wx.Size(self.GetSize()[0], h))
            # change size item_value
            w, h = item_value.GetSize()
            item_value.SetSize(wx.Size(value_panel_w, h))
            
    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        dc.SetTextForeground(wx.Colour(0, 0, 0))
        dc.SetBackgroundMode(wx.TRANSPARENT)
        dc.SetFont(PropertyGroup.font)
        dc.DrawText(self.GetName(), 20, 2)
        
    def OnSize(self, event):
        w, h = self.GetSize()
        self.sw.SetSize(wx.Size(w - PropertyGroup.headerWidth, h - PropertyGroup.headerHeight))
        self.SetSashPosition(w * PropertyGroup.sashRatio)
        
    def OnTreeItemButton(self, event):
        self.SetSize(self.GetBestSize())
        self.GetParent().OnTreeItemButton(self, event)
        
    def OnSelectedProperty(self, child):
        self.GetParent().OnSelectedProperty(child)
        
    def GetBestSize(self):
        self.bestWidth = self.GetParent().GetSize().GetWidth()
        if self.treeItemButton.IsChecked():
            return wx.Size(self.bestWidth, self.curY + PropertyGroup.headerHeight + 1)
        else:
            return wx.Size(self.bestWidth, PropertyGroup.headerHeight)
        
    def GetSplitterBestSize(self):
        self.bestWidth = self.GetParent().GetSize().GetWidth()
        if self.treeItemButton.IsChecked():
            return wx.Size(self.bestWidth, self.curY + PropertyGroup.headerHeight - PropertyGroup.lineHeight + 1)
        else:
            return wx.Size(self.bestWidth, 0)



#-------------------------------------------------------------------------------
class PropertyList(wx.ScrolledWindow):
    def __init__(self, parent, id, pos, size, style, name):
        wx.ScrolledWindow.__init__(self, parent, id, pos, size, style, name)
        self.SetBackgroundColour(wx.Colour(255, 255, 255))
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        self.groups = []
        
    def clear(self):
        for group in self.groups:
            group.Destroy()
        self.groups = []
        
    def addGroup(self, name):
        group = PropertyGroup(self, wx.NewId(), wx.DefaultPosition, wx.DefaultSize, 0, name)
        self.groups.append(group)
        return group
        
    def OnSplitterSashPosChanged(self, child, pos):
        for group in self.groups:
            group.SetSashPosition(pos)

    def OnTreeItemButton(self, child, event):
        self.OnSize(event)
        
    def OnSelectedProperty(self, child):
        self.GetParent().GetParent().OnSelectedProperty(child)

    def OnSize(self, event):
        self.layoutPropertyGroups()
            
    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        w, h = self.GetSize()
        dc.SetPen(wx.Pen(wx.Colour(167, 166, 170)))
        dc.DrawLine(0, h - 1, self.GetSize().GetWidth(), h - 1)
        
    def layoutPropertyGroups(self):
        y = 0
        for group in self.groups:
            w, h = group.GetBestSize()
            group.SetSize(wx.Size(w, h))
            group.SetPosition(wx.Point(0, y))
            y += h
        self.update_scrollbar(y)
        self.Refresh()
        
    def update_scrollbar(self, y):
        w, h = self.GetSize()
        if y > h:
            self.SetScrollbars(0, 10, 0, y / 10)
        else:
            self.SetScrollbars(0, 0, 0, 0)


#-------------------------------------------------------------------------------
class PropertyDocPanel(wx.Panel):
    nameFont = None
    descFont = None
    
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent, id, wx.DefaultPosition, wx.DefaultSize, 0, '')
        if PropertyDocPanel.nameFont == None:
            PropertyDocPanel.nameFont = wx.Font(9, wx.SWISS, wx.NORMAL, wx.BOLD, False, u'Tahoma')
            PropertyDocPanel.descFont = wx.Font(9, wx.SWISS, wx.NORMAL, wx.NORMAL, False, u'Tahoma')
        
        self.name = ''
        self.desc = ''
                
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        
    def SetDesc(self, name, desc):
        self.name = name
        self.desc = desc
        
    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        dc.SetPen(wx.Pen(wx.Colour(167, 166, 170)))
        dc.DrawLine(0, 0, self.GetSize().GetWidth(), 0)
        
        dc.SetTextForeground(wx.Colour(0, 0, 0))
        dc.SetBackgroundMode(wx.TRANSPARENT)
        
        dc.SetFont(PropertyDocPanel.nameFont)
        dc.DrawText(self.name, 3, 1)
        dc.SetFont(PropertyDocPanel.descFont)
        dc.DrawText(self.desc, 3, 16)

#-------------------------------------------------------------------------------
class PropertyGrid(wx.Panel):
    s_instance = None
    
    def __init__(self, parent, id,  pos, size, style, name):
        if PropertyGrid.s_instance == None:
            PropertyGrid.s_instance = self
        wx.Panel.__init__(self, parent, id, pos, size, style, name)
        self.objectListComboBox = wx.ComboBox(choices=[''],
              id=wx.NewId(), name='', parent=self,
              pos=wx.Point(2, 4), size=wx.Size(300, 22), style=0, value=u'')

        self.sw = wx.SplitterWindow(self, wx.NewId(), wx.Point(0, 28),
            self.GetSize(), 0, '')
        self.list = PropertyList(self.sw, wx.NewId(), wx.Point(0, 0), size, 0, '')
        self.docPanel = PropertyDocPanel(self.sw, wx.NewId())
        self.sw.SplitHorizontally(self.list, self.docPanel, self.sw.GetSize().GetHeight() / 5 * 4)
        self.sw.SetSashSize(3)
        self.sw.SetMinimumPaneSize(20)
        
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())
        
    def setObject(self, object):
        self.object = object
        self.list.clear()
        for type_name in object.getGenerations():
            prop_names = object.getPropertyNames(type_name)
            if len(prop_names) == 0:
                continue
            group = self.addGroup(type_name)
            for prop_name in prop_names:
                prop_name, prop_value, prop_type, readonly = object.getProperty(prop_name)
                group.addProperty(object, prop_name, prop_value, prop_type, readonly)
        apath = self.object.getAbsolutePath()
        if len(apath) == 0:
            apath = '/'
        self.objectListComboBox.SetValue(apath)
        self.list.OnSize(0)        

    def addGroup(self, name):
        return self.list.addGroup(name)
    
    def OnSize(self, event):
        w, h = self.GetSize()
        self.objectListComboBox.SetSize(
            wx.Size(w - 4, self.objectListComboBox.GetSize().GetHeight()))
        self.sw.SetSize(self.GetSize())
        self.sw.SetSashPosition(h / 5 * 4)
        
    def OnSelectedProperty(self, child):
        apath = self.object.getAbsolutePath()
        if len(apath) == 0:
            apath = '/'
        self.objectListComboBox.SetValue(apath + ':' + child.value)
        self.docPanel.SetDesc(child.value, '')
        self.docPanel.Refresh()
        
    def OnChangePropertyValue(self, object, prop_name, value):
        object.setProperty(prop_name, value)
        self.GetParent().Refresh(False)
    
    @classmethod
    def instance(self):
        return PropertyGrid.s_instance

