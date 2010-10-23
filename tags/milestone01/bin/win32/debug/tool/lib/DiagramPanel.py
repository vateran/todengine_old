# coding: mbcs

from todpython import *
import wx
import wx.grid
import wx.aui

#-----------------------------------------------------------------------------
class DiagramRectangle(wx.Panel):
    def __init__(self, parent, pos, size):
        wx.Panel.__init__(self, parent, wx.NewId(), pos=pos)

        self.nameStaticText = wx.StaticText(self, wx.NewId(), label='test',
            style=wx.ALIGN_CENTRE)

        self.boxSizer = wx.BoxSizer(wx.VERTICAL)
        self.boxSizer.AddWindow(self.nameStaticText, 0, wx.EXPAND)
        self.SetSizer(self.boxSizer)

        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.SetSize(size)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        w, h = self.GetSize()
        dc.DrawRectangle(0, 0, w, h)


#-----------------------------------------------------------------------------
class DiagramPanel(wx.Panel):
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent, id)

        self.test = DiagramRectangle(self, (10, 10), (100, 100))
        
