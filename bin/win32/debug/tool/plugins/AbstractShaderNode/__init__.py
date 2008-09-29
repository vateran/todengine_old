# coding: mbcs 

import wx
import MainFrame
from todpython import *    

#-------------------------------------------------------------------------------
def initialize(parent, obj):
    frame = AbstractShaderNodeEditor(MainFrame.MainFrame.instance())
    frame.initialize(obj)
    MainFrame.MainFrame.instance().auimgr.AddPane(frame, wx.aui.AuiPaneInfo().MinSize(wx.Size(200, 100)).
        Caption('AbstractShaderNode Editor').Dockable(True).Right().CloseButton(True).MinimizeButton(True).DestroyOnClose(True).Float())
    MainFrame.MainFrame.instance().auimgr.Update()


#-------------------------------------------------------------------------------
class AbstractShaderNodeEditor(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent)

    def initialize(self, obj):
        self.obj = obj
