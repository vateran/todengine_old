# coding: mbcs

from todpython import *
import wx
import lib.ImageProvider as ImageProvider

#-------------------------------------------------------------------------------
class SceneViewPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, wx.NewId())
        
                
        #toolbar
        self.imageProvider = ImageProvider.ImageProvider('data')        
        tb = wx.ToolBar(self, -1, style=wx.TB_HORIZONTAL | wx.NO_BORDER | wx.TB_FLAT)
        tb.AddCheckLabelTool(wx.NewId(), "WireFrame", self.imageProvider.getImage('wireframe'), shortHelp="WireFrame")
        tb.AddCheckLabelTool(wx.NewId(), "Lighting", self.imageProvider.getImage('lighting'), shortHelp="Lighting")
        tb.AddCheckLabelTool(wx.NewId(), "Shadow", self.imageProvider.getImage('shadow'), shortHelp="Shadow")
        tb.AddSeparator()
        tb.Realize()        
                
        
        #viewer
        self.view = wx.Panel(self, wx.NewId())
        self.sceneView = newobj('EditorSceneView')
        self.sceneView.setWindowId(self.view.GetHandle())        
        
        
        #sizer
        sizer = wx.BoxSizer(wx.VERTICAL)
        sizer.Add(tb, 0, wx.EXPAND | wx.RIGHT, 0)
        sizer.Add(self.view, 1, wx.EXPAND | wx.RIGHT | wx.Bottom, 0)        
        self.SetSizer(sizer)
        
        
        #event
        tb.Bind(wx.EVT_TOOL, self.OnToolBar)        
        self.view.Bind(wx.EVT_PAINT, self.OnPaint)
        self.view.Bind(wx.EVT_SIZE, self.OnSize)
        self.view.Bind(wx.EVT_MOTION, self.OnMotion)
        

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
        target_window = event.GetEventObject()        
        dc = wx.PaintDC(target_window)
        s = target_window.GetSize()
        self.camera.onChangedWindowSize(s.GetWidth(), s.GetHeight());
        self.sceneView.render()
        
    def OnToolBar(self, event):
        event.Skip()

    def setSceneRoot(self, scene_root):
        self.sceneRoot = scene_root
        self.sceneView.setSceneRoot(scene_root)
        
    def setCamera(self, camera):
        self.camera = camera
        self.sceneView.setCamera(camera)
        
    def Refresh(self, eraseBackground=True, rect=0):
        self.view.Refresh(eraseBackground)

    def OnToolBar(self, event):
        pass
    
    def OnMotion(self, event):        
        x = event.GetX()
        y = event.GetY()
        if event.AltDown():
            if event.LeftIsDown() and event.RightIsDown():
                delta_x = self.prev[0] - x
                delta_y = y - self.prev[1]
                self.camera.moveForward(-(float)(delta_y) / 100)
                self.camera.moveSideward(-(float)(delta_x) / 100)
            else:
                if event.LeftIsDown():
                    delta_x = self.prev[0] - x
                    delta_y = y - self.prev[1]
                    self.camera.eulerRotateX((float)(delta_y) / 100)
                    self.camera.eulerRotateY(-(float)(delta_x) / 100)
                if event.RightIsDown():
                    delta_x = self.prev[0] - x
                    self.camera.eulerRotateZ((float)(delta_x) / 100)
        self.prev = (x, y)
