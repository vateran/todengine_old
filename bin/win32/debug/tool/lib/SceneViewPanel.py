# coding: mbcs

from todpython import *
import wx

#-------------------------------------------------------------------------------
class SceneViewPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.NewId(), style=wx.NO_FULL_REPAINT_ON_RESIZE)
        self.sceneView = newobj('GbSceneView')
        self.sceneView.setWindowId(self.GetHandle())

        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
        self.Bind(wx.EVT_MOTION, self.OnMotion, id=self.GetId())
        self.Bind(wx.EVT_LEFT_UP, self.OnLeftUp, id=self.GetId())
        self.Bind(wx.EVT_LEFT_DOWN, self.OnLeftDown, id=self.GetId())
        self.Bind(wx.EVT_RIGHT_UP, self.OnRightUp, id=self.GetId())
        self.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown, id=self.GetId())
        self.Bind(wx.EVT_KEY_DOWN, self.OnKeyDown, id=self.GetId())
        self.Bind(wx.EVT_SIZE, self.OnSize, id=self.GetId())

        self.camera = None
        self.sceneRoot = None

    def OnSize(self, event):
        s = event.GetSize()
        try:
            if self.camera != None:
                self.camera.onChangedWindowSize(s.GetWidth(), s.GetHeight());
        except:
            pass
        
    def OnPaint(self, event):
        mstat = wx.GetMouseState()
        x, y = self.ScreenToClient((mstat.GetX(), mstat.GetY()))
        w, h = self.GetClientSizeTuple()
        #if mstat.LeftDown():
        #    self.sceneView.pick(x, y, w, h)

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
                self.camera.eulerRotateZ((float)(delta_y) / 100)
                self.camera.eulerRotateY(-(float)(delta_x) / 100)
            if event.RightIsDown():
                delta_x = self.prev[0] - x
                self.camera.eulerRotateX((float)(delta_x) / 100)
                #delta_x = self.prev[0] - x
                #delta_y = self.prev[1] - y
                #self.camera.moveForward((float)(delta_y) / 100)
                #self.camera.moveSideward(-(float)(delta_x) / 100)
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
            self.camera.moveSideward(-dist)
        if kc == wx.WXK_RIGHT or kc == 68:
            self.camera.moveSideward(dist)

    def setSceneRoot(self, scene_root):
        self.sceneRoot = scene_root
        self.sceneView.setSceneRoot(scene_root)
        
    def setCamera(self, camera):
        self.camera = camera
        self.sceneView.setCamera(camera)  
