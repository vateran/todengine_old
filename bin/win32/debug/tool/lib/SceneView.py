# coding: mbcs

from todpython import *
import wx

#-------------------------------------------------------------------------------
class SceneViewPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.NewId(), style=wx.NO_FULL_REPAINT_ON_RESIZE)
        self.sceneView = newobj('SceneView')
        self.sceneView.setSceneRootPath('/usr/scene')
        self.sceneView.setWindowId(self.GetHandle())
        
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        self.Bind(wx.EVT_MOTION, self.OnMotion, id=self.GetId())
        self.Bind(wx.EVT_LEFT_UP, self.OnLeftUp, id=self.GetId())
        self.Bind(wx.EVT_LEFT_DOWN, self.OnLeftDown, id=self.GetId())
        self.Bind(wx.EVT_RIGHT_UP, self.OnRightUp, id=self.GetId())
        self.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown, id=self.GetId())
        self.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown, id=self.GetId())
        
    def OnPaint(self, event):
        mstat = wx.GetMouseState()
        x, y = self.ScreenToClient((mstat.GetX(), mstat.GetY()))
        w, h = self.GetClientSizeTuple()
        if mstat.LeftDown():
            self.sceneView.pick(x, y, w, h)

        dc = wx.PaintDC(self)
        dc.SetBackgroundMode(wx.TRANSPARENT)
        self.sceneView.render()
        
    def OnMotion(self, event):
        self.GetParent().OnMotion(self, event)

        x = event.GetX()
        y = event.GetY()
        if event.AltDown():
            if event.LeftIsDown():
                delta_x = self.prev[0] - x
                delta_y = y - self.prev[1]
                self.camera.eulerRotateX((float)(delta_y) / 100)
                self.camera.eulerRotateY(-(float)(delta_x) / 100)
            if event.RightIsDown():
                delta_x = self.prev[0] - x
                delta_y = self.prev[1] - y
                self.camera.moveForward((float)(delta_y) / 100)
                self.camera.moveLeft((float)(delta_x) / 100)
        self.prev = (x, y)

    def OnLeftUp(self, event):
        self.GetParent().OnLeftUp(self, event)
        event.Skip()

    def OnLeftDown(self, event):
        self.GetParent().OnLeftDown(self, event)
        event.Skip()

    def OnRightUp(self, event):
        self.GetParent().OnRightUp(self, event)
        event.Skip()

    def OnRightDown(self, event):
        self.GetParent().OnRightDown(self, event)
        event.Skip()
    
    def OnKeyDown(self, event):
        dist = 1
        kc = event.GetKeyCode()        
        if kc == wx.WXK_UP or kc == 87:
            self.camera.moveForward(dist)
        if kc == wx.WXK_DOWN or kc == 83:
            self.camera.moveForward(-dist)
        if kc == wx.WXK_LEFT or kc == 65:
            self.camera.moveLeft(dist)
        if kc == wx.WXK_RIGHT or kc == 68:
            self.camera.moveRight(dist)
        
    def setCamera(self, camera):
        self.camera = camera

#-------------------------------------------------------------------------------
class SceneView(wx.aui.AuiNotebook):
    def __init__(self, parent):
        wx.aui.AuiNotebook.__init__(self, parent, style=wx.aui.AUI_NB_DEFAULT_STYLE | wx.aui.wx.NO_BORDER | wx.aui.AUI_NB_WINDOWLIST_BUTTON)
        if SceneView.s_instance == None:
            SceneView.s_instance = self
        self.eventSubscriber = {}
        
    def addViewPanel(self, title, camera=0):
        panel = SceneViewPanel(self)
        panel.setCamera(camera)
        self.AddPage(panel, title)

    def update(self):
        s = self.GetPageCount()
        i = 0
        while i < s:
            page = self.GetPage(i)
            page.Refresh(False)
            i = i + 1

    def addEventSubscriber(self, type, s):
        if type in self.eventSubscriber.keys():
            self.eventSubscriber[type].append(s)
        else:
            self.eventSubscriber[type] = [s]

    def removeEventSubscriber(self, type, s):
        if type in self.eventSubscriber.keys():
            self.eventSubscriber[type].remove(s)

    def OnMotion(self, sv_panel, event):
        try:
            for s in self.eventSubscriber['Motion']:
                s.OnMotion(sv_panel, event)
        except:
            pass

    def OnLeftUp(self, sv_panel, event):
        try:
            for s in self.eventSubscriber['LeftUp']:
                s.OnLeftUp(sv_panel, event)
        except:
            pass

    def OnLeftDown(self, sv_panel, event):
        try:
            for s in self.eventSubscriber['LeftDown']:
                s.OnLeftDown(sv_panel, event)
        except:
            pass

    def OnRightUp(self, sv_panel, event):
        try:
            for s in self.eventSubscriber['RightUp']:
                s.OnRightUp(sv_panel, event)
        except:
            pass

    def OnRightDown(self, sv_panel, event):
        try:
            for s in self.eventSubscriber['RightDown']:
                s.OnRightDown(sv_panel, event)
        except:
            pass

    s_instance = None
    @classmethod
    def instance(self):
        return SceneView.s_instance

