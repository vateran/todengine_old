#Boa:Frame:MainFrame
# coding: mbcs

from todpython import *
import wx
import wx.grid
import wx.aui
from lib.NOHTree import *
from lib.PropertyGrid import *
from lib.SceneView import *

def create(parent):
    return MainFrame(parent)

[wxID_MAINFRAME, wxID_MAINFRAMESTATUSBAR, 
] = [wx.NewId() for _init_ctrls in range(2)]

[wxID_MAINFRAMETOOLBAR1TOOLS0, wxID_MAINFRAMETOOLBAR1TOOLS1, 
] = [wx.NewId() for _init_coll_toolBar1_Tools in range(2)]

[wxID_MAINFRAMEFILEMENUITEMS1, wxID_MAINFRAMEFILEMENUITEMS2, 
 wxID_MAINFRAMEFILEMENUITEMS3, wxID_MAINFRAMEFILEMENUITEMS4, 
 wxID_MAINFRAMEFILEMENUITEMS6, 
] = [wx.NewId() for _init_coll_fileMenu_Items in range(5)]

class MainFrame(wx.Frame):
    def _init_coll_menuBar_Menus(self, parent):
        # generated method, don't edit

        parent.Append(menu=self.fileMenu, title=u'\ud30c\uc77c(&F)')
        parent.Append(menu=self.editMenu, title=u'\ud3b8\uc9d1(&E)')
        parent.Append(menu=self.viewMenu, title=u'\ubcf4\uae30(&V)')
        parent.Append(menu=self.windowMenu, title=u'\ucc3d(&W)')
        parent.Append(menu=self.helpMenu, title=u'\ub3c4\uc6c0\ub9d0(&H)')

    def _init_coll_fileMenu_Items(self, parent):
        # generated method, don't edit

        parent.Append(help='', id=wxID_MAINFRAMEFILEMENUITEMS1,
              kind=wx.ITEM_NORMAL, text=u'\uc0c8\ub85c \ub9cc\ub4e4\uae30(&N)')
        parent.Append(help='', id=wxID_MAINFRAMEFILEMENUITEMS2,
              kind=wx.ITEM_NORMAL, text=u'\uc5f4\uae30(&O)')
        parent.AppendSeparator()
        parent.Append(help='', id=wxID_MAINFRAMEFILEMENUITEMS4,
              kind=wx.ITEM_NORMAL, text=u'\ucd94\uac00(&D)')
        parent.AppendSeparator()
        parent.Append(help='', id=wxID_MAINFRAMEFILEMENUITEMS3,
              kind=wx.ITEM_NORMAL, text=u'\ub2eb\uae30(&C)')
        parent.AppendSeparator()
        parent.Append(help='', id=wxID_MAINFRAMEFILEMENUITEMS6,
              kind=wx.ITEM_NORMAL, text=u'\ub05d\ub0b4\uae30(&X)')

    def _init_utils(self):
        # generated method, don't edit
        self.menuBar = wx.MenuBar()

        self.fileMenu = wx.Menu(title=u'')

        self.editMenu = wx.Menu(title=u'')

        self.windowMenu = wx.Menu(title='')

        self.helpMenu = wx.Menu(title='')

        self.viewMenu = wx.Menu(title='')

        self._init_coll_menuBar_Menus(self.menuBar)
        self._init_coll_fileMenu_Items(self.fileMenu)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_MAINFRAME, name=u'MainFrame',
              parent=prnt, pos=wx.Point(434, 144), size=wx.Size(777, 463),
              style=wx.MAXIMIZE | wx.DEFAULT_FRAME_STYLE, title=u'TodEditor')
        self._init_utils()
        self.SetThemeEnabled(True)
        self.SetToolTipString(u'TodEditor')
        self.SetMenuBar(self.menuBar)
        self.Bind(wx.EVT_CLOSE, self.OnMainFrameClose)

        self.statusBar = wx.StatusBar(id=wxID_MAINFRAMESTATUSBAR,
              name=u'statusBar', parent=self, style=0)
        self.SetStatusBar(self.statusBar)

    def __init__(self, parent):
        self._init_ctrls(parent)
        self.auimgr = wx.aui.AuiManager()
        self.auimgr.SetManagedWindow(self)
        
        # initialize servers
        trigger_server = get('/sys/server/trigger')
        time_server = new('TimeServer', '/sys/server/time')
        trigger_server.add(time_server, 0)
        self.renderer = new('D3D9Renderer', '/sys/server/renderer')
        self.renderer.setDisplayMode('w[640]h[480]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]')
        new('TransformNode', '/usr/scene')
        
        mesh = new('MeshNode', '/usr/scene/tiger')
        mesh.euler_rotation = (0, 0, 0)
        mesh.shader_uri = 'managed://shader#mesh.fx'
        mesh.technique = 'EnvMapMesh'
        mesh.scaling = (0.3, 0.3, 0.3)
        mesh.translation = (0, -1, 0)
        mesh.mesh_uri = 'managed://mesh#skullocc.x'    
        #mesh.addTexture('EnvMap', 'managed://texture#uffizi_cross.dds')
        mesh.addCubeTexture('EnvMap', 'managed://texture#uffizi_cross_cube.dds')
        
        mesh = new('MeshNode', '/usr/scene/skybox')
        mesh.euler_rotation = (0, 0, 0)
        mesh.scaling = (2, 2, 2)
        mesh.translation = (0, 0, 0)
        mesh.shader_uri = 'managed://shader#mesh.fx'
        mesh.technique = 'SkyBox'
        mesh.mesh_uri = 'managed://mesh#alley_skybox.x'
        mesh.addCubeTexture('SkyBoxEnvMap', 'managed://texture#uffizi_cross_cube.dds')
                
        camera = new('CameraNode', '/usr/scene/camera')
        camera.renderpath_section = 'default'
        camera.shader_uri = 'managed://shader#camera.fx'
        camera.translation = (0, 0, -4)
        
        render_path = new('RenderPath', '/sys/server/renderpath')
        rpsection = new('RpSection', '/sys/server/renderpath/default')
        
        '''rppass = new('RpPass', '/sys/server/renderpath/default/010_scaled_scene')
        rppass.clear_color = (0, 0, 255, 0)
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'BrightPass'        
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/010_scaled_scene/rt')
        rt.texture_uri = 'managed://rt#final_scene'
        rt.texture_format = 'A16B16G16R16F'
        rt.relative_size = 0.3'''
        
        rppass = new('RpPass', '/sys/server/renderpath/default/100_final_scene')
        rppass.clear_color = (0, 0, 255, 255)
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'ComposeScene'        
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/100_final_scene/rt')
        rt.texture_uri = 'managed://rt#final_scene'
        rt.texture_format = 'A16B16G16R16F'
        rt.relative_size = 1
        
        
        
        # PropertyGrid
        self.propertyGrid = PropertyGrid(self, wx.NewId(), wx.Point(0, 0),
            wx.Size(300, 300), wx.CLIP_CHILDREN, '')

        # NOHTree
        self.nohTree = NOHTree(self, wx.NewId(),
            wx.Point(8, 8), wx.Size(360, 392),
            style=wx.TR_LINES_AT_ROOT | wx.TR_HAS_BUTTONS | wx.TR_EDIT_LABELS)
        self.nohTree.Bind(wx.EVT_TREE_SEL_CHANGED, self.onSelChanged, id=self.nohTree.GetId())
        self.nohTree.build('/')
        
        # SceneView
        self.sceneView = SceneView(self)
        self.sceneView.addViewPanel('Perspective View')
        self.sceneView.addViewPanel('Top View')
        self.sceneView.addViewPanel('Left View')
        self.sceneView.addViewPanel('Front View')
        
        # AddPanes
        self.auimgr.AddPane(self.nohTree, wx.aui.AuiPaneInfo().
            Caption('Node of Hierarchy').Dockable(True).Right().CloseButton(True).MinimizeButton(True))
        self.auimgr.AddPane(self.propertyGrid, wx.aui.AuiPaneInfo().
            Caption('Property').Dockable(True).Right().CloseButton(True).MinimizeButton(True))
        self.auimgr.AddPane(self.sceneView, wx.aui.AuiPaneInfo().
            Caption('Render View').Center().CloseButton(False))
        
        self.auimgr.Update()
        
    def onSelChanged(self, event):
        self.propertyGrid.setObject(get(self.nohTree.getSelectionAbsolutePath()))

    def OnMainFrameClose(self, event):
        self.app.keepGoing_ = False
        self.Destroy()
        
