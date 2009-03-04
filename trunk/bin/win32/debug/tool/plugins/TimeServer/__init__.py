# coding: mbcs 

import wx
import MainFrame
from todpython import *

#-------------------------------------------------------------------------------
def initialize(parent, obj):
    frame = TimeServerEditor(MainFrame.MainFrame.instance())
    frame.initialize(obj)
    MainFrame.MainFrame.instance().auimgr.AddPane(frame, wx.aui.AuiPaneInfo().MinSize(wx.Size(260, 130)).
        Caption('TimeServerEditor').Dockable(True).Left().CloseButton(True).MinimizeButton(True).DestroyOnClose(True))
    MainFrame.MainFrame.instance().auimgr.Update()


#-------------------------------------------------------------------------------
class TimeServerEditor(wx.Panel):
    def _init_coll_gridSizer1_Items(self, parent):
        parent.AddWindow(self.stepBackwardButton, 0, border=0, flag=0)
        parent.AddWindow(self.playButton, 0, border=0, flag=0)
        parent.AddWindow(self.stepForwardButton, 0, border=0, flag=0)

    def _init_coll_staticBoxSizer1_Items(self, parent):
        parent.AddSizer(self.gridSizer1, 0, border=5,
              flag=wx.ALIGN_CENTER | wx.ALL)

    def _init_coll_boxSizer1_Items(self, parent):
        parent.AddSizer(self.staticBoxSizer1, 0, border=5,
              flag=wx.EXPAND | wx.BOTTOM | wx.LEFT | wx.RIGHT | wx.TOP)
        parent.AddSizer(self.boxSizer2, 0, border=5, flag=wx.ALL | wx.EXPAND)

    def _init_coll_boxSizer2_Items(self, parent):
        parent.AddWindow(self.timeScaleSlider, 1, border=0,
              flag=wx.RIGHT | wx.EXPAND)
        parent.AddWindow(self.timeScaleStaticText, 0, border=0,
              flag=wx.ALIGN_CENTER)

    def _init_sizers(self):
        self.staticBoxSizer1 = wx.StaticBoxSizer(box=self.staticBox1,
              orient=wx.VERTICAL)

        self.boxSizer1 = wx.BoxSizer(orient=wx.VERTICAL)

        self.gridSizer1 = wx.GridSizer(cols=3, hgap=0, rows=1, vgap=5)

        self.boxSizer2 = wx.BoxSizer(orient=wx.HORIZONTAL)

        self._init_coll_staticBoxSizer1_Items(self.staticBoxSizer1)
        self._init_coll_boxSizer1_Items(self.boxSizer1)
        self._init_coll_gridSizer1_Items(self.gridSizer1)
        self._init_coll_boxSizer2_Items(self.boxSizer2)

        self.SetSizer(self.boxSizer1)

    def _init_ctrls(self, prnt):
        self.staticBox1 = wx.StaticBox(id=wx.NewId(), label=u'',
              name='staticBox1', parent=self, pos=wx.Point(5, 5),
              size=wx.Size(337, 48), style=0)

        self.stepBackwardButton = wx.Button(id=wx.NewId(),
              label=u'\u2502\u25c0', name=u'stepBackwardButton',
              parent=self, pos=wx.Point(61, 19), size=wx.Size(75, 24),
              style=0)
        self.Bind(wx.EVT_BUTTON, self.OnStepBackwardButton, id=self.stepBackwardButton.GetId())

        self.playButton = wx.Button(id=wx.NewId(), label=u'||',
              name=u'playButton', parent=self, pos=wx.Point(136, 19),
              size=wx.Size(75, 24), style=0)
        if self.play:
            self.playButton.SetLabel('||')
        else:
            self.playButton.SetLabel('¢º')
        self.Bind(wx.EVT_BUTTON, self.OnPlayButton, id=self.playButton.GetId())

        self.stepForwardButton = wx.Button(id=wx.NewId(),
              label=u'\u25b6\u2502', name=u'stepForwardButton',
              parent=self, pos=wx.Point(211, 19), size=wx.Size(75, 24),
              style=0)
        self.Bind(wx.EVT_BUTTON, self.OnStepForwardButton, id=self.stepForwardButton.GetId())

        self.timeScaleSlider = wx.Slider(id=wx.NewId(),
              maxValue=self.timeResolution * 2, minValue=0, name=u'timeScaleSlider',
              parent=self, pos=wx.Point(5, 63), size=wx.Size(307, 24),
              style=wx.SL_HORIZONTAL, value=0)
        self.Bind(wx.EVT_COMMAND_SCROLL, self.OnTimeScaleSliderScroll, id=self.timeScaleSlider.GetId())

        self.timeScaleStaticText = wx.StaticText(id=wx.NewId(),
              label=u'1x', name=u'timeScaleStaticText', parent=self,
              pos=wx.Point(312, 67), size=wx.Size(30, 16),
              style=wx.ALIGN_CENTRE)
        self.timeScaleStaticText.SetMinSize(wx.Size(50, 16))

        self._init_sizers()

    def __init__(self, parent):
        self.obj = get('/sys/server/time')
        self.play = not self.obj.isPause()
        self.timeResolution = 100

        wx.Panel.__init__(self, parent, style=wx.WANTS_CHARS)
        self._init_ctrls(parent)
        
        self.setTimeScaleByValue(self.obj.getScale())

    def setTimeScaleByValue(self, scale):
        self.timeScaleSlider.SetValue(scale * self.timeResolution)
        self.update_timescale_static_text(scale)
        self.obj.scale(scale)
                                          
    def initialize(self, obj):
        pass

    def OnPlayButton(self, event):
        if self.play:
            self.play = False
            self.playButton.SetLabel('¢º')
            self.obj.pause()
        else:
            self.play = True
            self.playButton.SetLabel('||')
            self.obj.resume()

    def OnStepBackwardButton(self, event):
        self.obj.step(-0.01)

    def OnStepForwardButton(self, event):
        self.obj.step(0.01)

    def OnTimeScaleSliderScroll(self, event):
        scale = (float)(self.timeScaleSlider.GetValue()) / self.timeResolution
        if scale > 0.98 and scale < 1.02:
            scale = 1
            self.timeScaleSlider.SetValue(scale * self.timeResolution)
        self.update_timescale_static_text(scale)
        self.obj.scale(scale)

    def update_timescale_static_text(self, scale):
        self.timeScaleStaticText.SetLabel('%.2fx' % (scale,))



#-------------------------------------------------------------------------------
def isEditor():
    return True


#-------------------------------------------------------------------------------
def getEditorName():
    return 'Time Editor'

