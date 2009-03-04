# coding: mbcs

from todpython import *
import wx

#-------------------------------------------------------------------------------
class SceneViewPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.NewId(), style=wx.NO_FULL_REPAINT_ON_RESIZE)
        self.Bind(wx.EVT_PAINT, self.OnPaint, id=self.GetId())
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

        dc = wx.PaintDC(self)
        dc.SetBackgroundMode(wx.TRANSPARENT)
        self.sceneView.render()

    def setSceneRoot(self, scene_root):
        self.sceneRoot = scene_root
        self.sceneView.setSceneRoot(scene_root)
        
    def setCamera(self, camera):
        self.camera = camera
        self.sceneView.setCamera(camera)  
