# coding: mbcs

import wx
from todpython import *

class CommandConsole(wx.Panel):
    s_instance = None
    
    def _init_coll_boxSizer3_Items(self, parent):
        parent.AddWindow(self.commandLine, 0, border=1, flag=wx.TOP | wx.EXPAND)

    def _init_coll_boxSizer1_Items(self, parent):
        parent.AddSizer(self.boxSizer2, 1, border=0, flag=wx.EXPAND)
        parent.AddSizer(self.boxSizer3, 0, border=0, flag=wx.EXPAND)

    def _init_coll_boxSizer2_Items(self, parent):
        parent.AddWindow(self.scriptText, 1, border=0, flag=wx.EXPAND)
        parent.AddWindow(self.executeButton, 0, border=0,
              flag=wx.EXPAND | wx.ALIGN_CENTER)

    def _init_sizers(self):
        self.boxSizer1 = wx.BoxSizer(orient=wx.VERTICAL)
        self.boxSizer2 = wx.BoxSizer(orient=wx.HORIZONTAL)
        self.boxSizer3 = wx.BoxSizer(orient=wx.VERTICAL)

        self._init_coll_boxSizer1_Items(self.boxSizer1)
        self._init_coll_boxSizer2_Items(self.boxSizer2)
        self._init_coll_boxSizer3_Items(self.boxSizer3)

        self.SetSizer(self.boxSizer1)

    def _init_ctrls(self, prnt):
        self.scriptText = wx.TextCtrl(id=wx.NewId(),
              name=u'scriptText', parent=self, pos=wx.Point(0, 0),
              size=wx.Size(178, 93), style=wx.TE_LINEWRAP | wx.TE_MULTILINE,
              value='')
        self.scriptText.SetMinSize(wx.Size(200, 50))

        self.commandLine = wx.TextCtrl(id=wx.NewId(),
              name=u'commandLine', parent=self, pos=wx.Point(4, 97),
              size=wx.Size(245, 22), style=0, value='')
        self.commandLine.Bind(wx.EVT_TEXT_ENTER, self.OnCommandLineTextEnter,
              id=self.commandLine.GetId())

        self.executeButton = wx.Button(id=wx.NewId(),
              label=u'Execute', name=u'executeButton', parent=self,
              pos=wx.Point(178, 0), size=wx.Size(75, 93), style=0)

        self._init_sizers()
        
    def __init__(self, parent, id, pos, size, style):
        if CommandConsole.s_instance == None:
            CommandConsole.s_instance = self
        wx.Panel.__init__(self, parent, id, pos, size, style)
        self._init_ctrls(parent)
        
        self.script = get('/sys/server/script/python')
        
    def execute(self, command):        
        if self.script.run(str(command)):
            self.scriptText.AppendText(command + '\n')
        
    def OnCommandLineTextEnter(self, event):
        self.execute(self.commandLine.GetValue())
        self.commandLine.Clear()
        
    @classmethod
    def instance(self):
        return CommandConsole.s_instance
        