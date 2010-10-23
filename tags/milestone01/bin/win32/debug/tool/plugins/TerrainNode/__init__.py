# coding: mbcs 

import wx
import wx.lib.buttons
import wx.aui
import lib.NOHImageProvider as NOHImageProvider
import lib.SceneView as SV
import MainFrame
from todpython import *    


#-------------------------------------------------------------------------------
def initialize(parent, obj):
    frame = TerrainEditTool(MainFrame.MainFrame.instance())
    frame.initialize(obj)
    MainFrame.MainFrame.instance().auimgr.AddPane(frame, wx.aui.AuiPaneInfo().MinSize(wx.Size(200, 100)).
        Caption('Terrain Edit Tool').Dockable(True).Right().CloseButton(True).MinimizeButton(True).DestroyOnClose(True).Float())
    MainFrame.MainFrame.instance().auimgr.Update()


#-------------------------------------------------------------------------------
class TerraformPanel(wx.Panel):
    def __init__(self, parent, obj):
        wx.Panel.__init__(self, parent, wx.NewId(), style=wx.NO_FULL_REPAINT_ON_RESIZE)
        self._init_ctrls(self)
        
        self.toggleButtons = [self.raiseButton, self.lowerButton, self.levelButton, self.grabButton, self.smoothButton, self.erodeButton]
        self.obj = obj

        SV.SceneView.instance().addEventSubscriber('Motion', self)
        SV.SceneView.instance().addEventSubscriber('LeftUp', self)

        self.defaultSetting()

    def __del__(self):
        SV.SceneView.instance().removeEventSubscriber('Motion', self)
        SV.SceneView.instance().removeEventSubscriber('LeftUp', self)

    def defaultSetting(self):
        self.radius.SetRange(1, 10)
        self.radius.SetValue(5)

        self.strength.SetRange(1, 100)
        self.strength.SetValue(1)

        self.softness.SetRange(1, 100)
        self.softness.SetValue(70)

        self.radiusText.SetValue('5')
        self.strengthText.SetValue('0.1')
        self.softnessText.SetValue('0.7')

        self.raiseButton.SetValue(True)

        self.makeKernel()

    def makeKernel(self):
        radius = int(self.radiusText.GetValue())
        strength = float(self.strengthText.GetValue())
        softness = float(self.softnessText.GetValue())
        self.obj.makeKernel(radius, strength, softness)

    def OnMotion(self, sv_panel, event):
        if event.AltDown():
            return

        if event.LeftIsDown():
            if self.raiseButton.GetValue():
                w, h = sv_panel.GetClientSizeTuple()
                self.obj.raiseTerrain(event.GetX(), event.GetY(), w, h)
            elif self.lowerButton.GetValue():
                w, h = sv_panel.GetClientSizeTuple()
                self.obj.lower(event.GetX(), event.GetY(), w, h)

    def OnLeftUp(self, sv_panel, event):
        self.obj.computeNormal()
        
    def OnTerraformToolButton(self, event):
        for b in self.toggleButtons:
            b.SetToggle(False)
        event.GetEventObject().SetToggle(True)
        
    def _init_coll_staticBoxSizer1_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.buttonGridSizer, 0, border=10,
              flag=wx.ALL | wx.ALIGN_CENTER)
        parent.AddSizer(self.radiusBoxSizer, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.EXPAND)
        parent.AddSizer(self.strengthBoxSizer, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.EXPAND)
        parent.AddSizer(self.softnessBoxSizer, 0, border=5,
              flag=wx.RIGHT | wx.LEFT | wx.EXPAND)

    def _init_coll_mainBoxSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddSizer(self.staticBoxSizer1, 1, border=5,
              flag=wx.ALL | wx.EXPAND)

    def _init_coll_buttonGridSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.raiseButton, 0, border=0, flag=0)
        parent.AddWindow(self.lowerButton, 0, border=0, flag=0)
        parent.AddWindow(self.levelButton, 0, border=0, flag=0)
        parent.AddWindow(self.grabButton, 0, border=0, flag=0)
        parent.AddWindow(self.smoothButton, 0, border=0, flag=0)
        parent.AddWindow(self.erodeButton, 0, border=0, flag=0)

    def _init_coll_radiusBoxSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText1, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.radius, 1, border=0,
              flag=wx.EXPAND | wx.RIGHT | wx.LEFT)
        parent.AddWindow(self.radiusText, 0, border=0, flag=wx.ALIGN_CENTER)

    def _init_coll_strengthBoxSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText2, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.strength, 1, border=0,
              flag=wx.EXPAND | wx.RIGHT | wx.LEFT)
        parent.AddWindow(self.strengthText, 0, border=0, flag=wx.ALIGN_CENTER)

    def _init_coll_softnessBoxSizer_Items(self, parent):
        # generated method, don't edit

        parent.AddWindow(self.staticText3, 0, border=0, flag=wx.ALIGN_CENTER)
        parent.AddWindow(self.softness, 1, border=0,
              flag=wx.EXPAND | wx.LEFT | wx.RIGHT)
        parent.AddWindow(self.softnessText, 0, border=0, flag=wx.ALIGN_CENTER)

    def _init_sizers(self):
        # generated method, don't edit
        self.mainBoxSizer = wx.BoxSizer(orient=wx.VERTICAL)

        self.staticBoxSizer1 = wx.StaticBoxSizer(box=self.staticBox1,
              orient=wx.VERTICAL)

        self.radiusBoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.strengthBoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.softnessBoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)

        self.buttonGridSizer = wx.GridSizer(cols=4, hgap=0, rows=2, vgap=0)

        self._init_coll_mainBoxSizer_Items(self.mainBoxSizer)
        self._init_coll_staticBoxSizer1_Items(self.staticBoxSizer1)
        self._init_coll_radiusBoxSizer_Items(self.radiusBoxSizer)
        self._init_coll_strengthBoxSizer_Items(self.strengthBoxSizer)
        self._init_coll_softnessBoxSizer_Items(self.softnessBoxSizer)
        self._init_coll_buttonGridSizer_Items(self.buttonGridSizer)

        self.SetSizer(self.mainBoxSizer)

    def _init_ctrls(self, prnt):
        self.staticBox1 = wx.StaticBox(id=wx.NewId(),
              label=u'Terraform', name='staticBox1', parent=self,
              pos=wx.Point(5, 5), size=wx.Size(292, 176), style=0)

        self.staticText1 = wx.StaticText(id=wx.NewId(),
              label=u'Radius', name='staticText1', parent=self,
              pos=wx.Point(15, 107), size=wx.Size(60, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText1.SetMinSize(wx.Size(60, 14))

        self.radius = wx.Slider(id=wx.NewId(), maxValue=100, minValue=0,
              name=u'radius', parent=self, pos=wx.Point(75, 103),
              size=wx.Size(112, 22), style=wx.SL_HORIZONTAL, value=0)
        self.radius.Bind(wx.EVT_COMMAND_SCROLL, self.OnRadiusCommandScroll,
              id=self.radius.GetId())

        self.radiusText = wx.TextCtrl(id=wx.NewId(),
              name=u'radiusText', parent=self, pos=wx.Point(187, 103),
              size=wx.Size(30, 22), style=0, value=u'')

        self.staticText2 = wx.StaticText(id=wx.NewId(),
              label=u'Strength', name='staticText2', parent=self,
              pos=wx.Point(15, 129), size=wx.Size(60, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText2.SetMinSize(wx.Size(60, 14))

        self.strength = wx.Slider(id=wx.NewId(), maxValue=100,
              minValue=0, name=u'strength', parent=self, pos=wx.Point(75,
              125), size=wx.Size(112, 22), style=wx.SL_HORIZONTAL, value=0)
        self.strength.SetMinSize(wx.Size(184, 22))
        self.strength.Bind(wx.EVT_COMMAND_SCROLL, self.OnStrengthCommandScroll,
              id=self.strength.GetId())

        self.strengthText = wx.TextCtrl(id=wx.NewId(),
              name=u'strengthText', parent=self, pos=wx.Point(187, 125),
              size=wx.Size(30, 22), style=0, value=u'')

        self.staticText3 = wx.StaticText(id=wx.NewId(),
              label=u'Softness', name='staticText3', parent=self,
              pos=wx.Point(15, 151), size=wx.Size(60, 14),
              style=wx.ALIGN_CENTRE)
        self.staticText3.SetMinSize(wx.Size(60, 14))

        self.softness = wx.Slider(id=wx.NewId(), maxValue=100,
              minValue=0, name=u'softness', parent=self, pos=wx.Point(75,
              147), size=wx.Size(112, 22), style=wx.SL_HORIZONTAL, value=0)
        self.softness.SetMinSize(wx.Size(184, 22))
        self.softness.Bind(wx.EVT_COMMAND_SCROLL, self.OnSoftnessCommandScroll,
              id=self.softness.GetId())

        self.softnessText = wx.TextCtrl(id=wx.NewId(),
              name=u'softnessText', parent=self, pos=wx.Point(187, 147),
              size=wx.Size(30, 22), style=0, value=u'')

        self.raiseButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/04.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'raiseButton',
              parent=self, pos=wx.Point(89, 33), size=wx.Size(31, 30),
              style=0)
        self.raiseButton.SetToolTipString(u'Raise')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.raiseButton)
        
        self.lowerButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/03.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'lowerButton',
              parent=self, pos=wx.Point(120, 33), size=wx.Size(31, 30),
              style=0)
        self.lowerButton.SetToolTipString(u'Lower')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.lowerButton)

        self.levelButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/05.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'levelButton',
              parent=self, pos=wx.Point(151, 33), size=wx.Size(31, 30),
              style=0)
        self.levelButton.SetToolTipString(u'Level')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.levelButton)

        self.grabButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/01.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'grabButton', parent=self,
              pos=wx.Point(182, 33), size=wx.Size(31, 30), style=0)
        self.grabButton.SetToolTipString(u'Grab')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.grabButton)

        self.smoothButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/05.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'smoothButton',
              parent=self, pos=wx.Point(89, 63), size=wx.Size(31, 30),
              style=0)
        self.smoothButton.SetToolTipString(u'Smooth')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.smoothButton)

        self.erodeButton = wx.lib.buttons.GenBitmapToggleButton(bitmap=wx.Bitmap('data/TerrainNode/02.png', wx.BITMAP_TYPE_PNG),
              id=wx.NewId(), name=u'erodeButton',
              parent=self, pos=wx.Point(120, 63), size=wx.Size(31, 30),
              style=0)
        self.erodeButton.SetToolTipString(u'Erode')
        self.Bind(wx.EVT_BUTTON, self.OnTerraformToolButton, self.erodeButton)

        self._init_sizers()

    def OnRadiusCommandScroll(self, event):
        self.radiusText.SetValue(str(self.radius.GetValue()))
        self.makeKernel()

    def OnStrengthCommandScroll(self, event):
        value = self.strength.GetValue() / 100.0
        self.strengthText.SetValue(str(value))
        self.makeKernel()

    def OnSoftnessCommandScroll(self, event):
        value = self.softness.GetValue() / 100.0
        self.softnessText.SetValue(str(value))
        self.makeKernel()


#-------------------------------------------------------------------------------
class TerrainEditTool(wx.aui.AuiNotebook):
    def __init__(self, parent):
        wx.aui.AuiNotebook.__init__(self, parent,
            style=wx.aui.AUI_NB_DEFAULT_STYLE | wx.aui.wx.NO_BORDER | wx.aui.AUI_NB_WINDOWLIST_BUTTON)

    def initialize(self, obj):
        self.AddPage(TerraformPanel(self, obj), 'Terraform')
