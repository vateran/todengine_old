# coding: mbcs

from todpython import *
import wx
import wx.grid
import wx.aui

class Class(wx.Panel):
    def __init__(self, parent, pos, size):
        wx.Panel.__init__(self, parent, wx.NewId(), pos=pos, size=size)

        self.nameStaticText = wx.StaticText(self, wx.NewId(), label='test',
            style=wx.ALIGN_CENTRE)

        self.Bind(wx.EVT_PAINT, self.OnPaint)

        self.boxSizer = wx.BoxSizer(wx.VERTICAL)
        self.boxSizer.Add(self.nameStaticText, 0, wx.EXPAND | wx.ALL)
        self.SetSizer(self.boxSizer)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        w, h = self.GetSize()
        dc.DrawRectangle(0, 0, w, h)


class ClassDiagram(wx.Panel):
    def __init__(self, parent, id):
        wx.Panel.__init__(self, parent, id)

        self.test = Class(self, (0, 0), (100, 100))

