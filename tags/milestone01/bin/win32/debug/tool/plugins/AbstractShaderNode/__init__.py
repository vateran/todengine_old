# coding: mbcs 

import wx
import MainFrame
from todpython import *    

#-------------------------------------------------------------------------------
def initialize(parent, obj):
    frame = AbstractShaderNodeEditor(MainFrame.MainFrame.instance())
    frame.initialize(obj)
    MainFrame.MainFrame.instance().auimgr.AddPane(frame, wx.aui.AuiPaneInfo().MinSize(wx.Size(200, 100)).
        Caption('AbstractShaderNode').Dockable(True).Right().CloseButton(True).MinimizeButton(True).DestroyOnClose(True).Float())
    MainFrame.MainFrame.instance().auimgr.Update()


#-------------------------------------------------------------------------------
# coding: mbcs 

import wx
import MainFrame
from todpython import *    

#-------------------------------------------------------------------------------
def initialize(parent, obj):
    frame = AbstractShaderNodeEditor(MainFrame.MainFrame.instance())
    frame.initialize(obj)
    MainFrame.MainFrame.instance().auimgr.AddPane(frame, wx.aui.AuiPaneInfo().MinSize(wx.Size(200, 100)).
        Caption('RenderPath - Base Editor').Dockable(True).Right().CloseButton(True).MinimizeButton(True).DestroyOnClose(True).Float())
    MainFrame.MainFrame.instance().auimgr.Update()


#-------------------------------------------------------------------------------
class AbstractShaderNodeEditor(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, style=wx.WANTS_CHARS)
                                                           
    def initialize(self, obj):
        self.obj = obj

        self.mainSizer = wx.BoxSizer(wx.VERTICAL)

        for i in range(0, self.obj.getShaderParamNum()):
            name, semantic, type, value = self.obj.getShaderParamDesc(i)

            bsizer = wx.BoxSizer(wx.HORIZONTAL)
            static = wx.StaticText(id=wx.NewId(), label=name, parent=self, style=wx.ALIGN_RIGHT)
            static.SetMinSize(wx.Size(150, 14))
            bsizer.Add(static)
            textctrl = wx.TextCtrl(id=wx.NewId(), name=name + ":" + type, value=value, parent=self)
            self.Bind(wx.EVT_TEXT_ENTER, self.OnTextEnter, id=textctrl.GetId())
            bsizer.Add(textctrl, 1, wx.ALL | wx.EXPAND)

            self.mainSizer.Add(bsizer, 0, wx.ALL | wx.EXPAND)            

        self.SetSizer(self.mainSizer)
        self.Fit()

    def OnTextEnter(self, event):
        t = event.GetEventObject()
        n = t.GetName().split(':')
        param_name = str(n[0])
        param_type = str(n[1])

        if param_type == 'TYPE_FLOAT':
            self.obj.setFloat(param_name, float(t.GetValue()))
        elif param_type == 'TYPE_TEXTURE':
            self.obj.setTexture(param_name, str(t.GetValue()))
        
class Editor(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, style=wx.WANTS_CHARS)
                                                           
    def initialize(self, obj):
        self.obj = obj

        self.mainSizer = wx.BoxSizer(wx.VERTICAL)

        for i in range(0, self.obj.getShaderParamNum()):
            name, semantic, type, value = self.obj.getShaderParamDesc(i)

            bsizer = wx.BoxSizer(wx.HORIZONTAL)
            static = wx.StaticText(id=wx.NewId(), label=name, parent=self, style=wx.ALIGN_RIGHT)
            static.SetMinSize(wx.Size(150, 14))
            bsizer.Add(static)
            textctrl = wx.TextCtrl(id=wx.NewId(), name=name + ":" + type, value=value, parent=self)
            self.Bind(wx.EVT_TEXT_ENTER, self.OnTextEnter, id=textctrl.GetId())
            bsizer.Add(textctrl, 1, wx.ALL | wx.EXPAND)

            self.mainSizer.Add(bsizer, 0, wx.ALL | wx.EXPAND)            

        self.SetSizer(self.mainSizer)
        self.Fit()

    def OnTextEnter(self, event):
        t = event.GetEventObject()
        n = t.GetName().split(':')
        param_name = str(n[0])
        param_type = str(n[1])

        if param_type == 'TYPE_FLOAT':
            self.obj.setFloat(param_name, float(t.GetValue()))
        elif param_type == 'TYPE_TEXTURE':
            self.obj.setTexture(param_name, str(t.GetValue()))
        

