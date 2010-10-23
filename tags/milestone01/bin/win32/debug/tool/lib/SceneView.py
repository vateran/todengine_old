# coding: mbcs

from todpython import *
from SceneViewPanel import *
import wx

#-------------------------------------------------------------------------------
class SceneView(wx.aui.AuiNotebook):
    def __init__(self, parent):
        wx.aui.AuiNotebook.__init__(self, parent, style=wx.aui.AUI_NB_DEFAULT_STYLE | wx.aui.wx.NO_BORDER | wx.aui.AUI_NB_WINDOWLIST_BUTTON)
        if SceneView.s_instance == None:
            SceneView.s_instance = self
        self.eventSubscriber = {}
        
    def addViewPanel(self, title, scene_root=None, camera=None, panel=SceneViewPanel):
        panel = panel(self)
        panel.setSceneRoot(scene_root)
        panel.setCamera(camera)
        self.AddPage(panel, title)
        return panel

    def removeViewPanel(self, panel):
        self.DeletePage(self.GetPageIndex(panel))

    def setSelection(self, panel):
        self.SetSelection(self.GetPageIndex(panel))

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

