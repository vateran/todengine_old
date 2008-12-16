#Boa:Frame:MainFrame
# coding: mbcs

from todpython import *
import wx
import wx.grid
import wx.aui
from lib.NOHTree import *
from lib.PropertyGrid import *
from lib.SceneView import *
from lib.CommandConsole import *

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

        self.popupMenu = wx.Menu(title='')

        self._init_coll_menuBar_Menus(self.menuBar)
        self._init_coll_fileMenu_Items(self.fileMenu)

    def _init_ctrls(self, prnt):
        # generated method, don't edit
        wx.Frame.__init__(self, id=wxID_MAINFRAME, name=u'MainFrame',
              parent=prnt, pos=wx.Point(230, 42), size=wx.Size(777, 620),
              style=wx.MAXIMIZE | wx.DEFAULT_FRAME_STYLE, title=u'TodEditor')
        self._init_utils()
        self.SetThemeEnabled(True)
        self.SetToolTipString(u'TodEditor')
        self.SetMenuBar(self.menuBar)
        self.SetClientSize(wx.Size(769, 586))
        self.Bind(wx.EVT_CLOSE, self.OnMainFrameClose)

        self.statusBar = wx.StatusBar(id=wxID_MAINFRAMESTATUSBAR,
              name=u'statusBar', parent=self, style=0)
        self.SetStatusBar(self.statusBar)

    def __init__(self, parent):
        self._init_ctrls(parent)
        if MainFrame.s_instance == None:
            MainFrame.s_instance = self

        self.SetIcon(wx.Icon('data/tod.png', wx.BITMAP_TYPE_PNG))
        
        self.auimgr = wx.aui.AuiManager()
        self.auimgr.SetManagedWindow(self)
        
        # initialize servers
        trigger_server = get('/sys/server/trigger')
        time_server = new('TimeServer', '/sys/server/time')
        trigger_server.add(time_server, 0)
        self.renderer = new('D3D9Renderer', '/sys/server/renderer')
        self.renderer.setDisplayMode('w[800]h[600]f[A8R8G8B8]sbuf[8]zbuf[24]fullscreen[false]title[test]')
        new('TransformNode', '/usr/scene')

        camera = new('CameraNode', '/usr/scene/camera')
        camera.renderpath_section = 'default'
        camera.shader_uri = 'managed://shader#camera.fx'
        camera.translation = (0, 0.0, 0.0)
        
        mesh = new('MeshNode', '/usr/scene/tiger')
        mesh.euler_rotation = (0, 0, 0)
        mesh.shader_uri = 'managed://shader#mesh.fx'
        mesh.technique = 'EnvMapMesh'
        mesh.euler_rotation = (0, 0.4, 0)
        mesh.scaling = (0.2, 0.2, 0.2)
        mesh.translation = (0, -0.5, 2.5)
        mesh.mesh_uri = 'managed://mesh#skullocc.x'
        #mesh.setTexture('EnvMap', 'managed://texture#uffizi_cross.dds')
        mesh.setCubeTexture('EnvMap', 'managed://texture#uffizi_cross_cube.dds')
        
        mesh = new('MeshNode', '/usr/scene/camera/skybox')
        mesh.euler_rotation = (0, 0, 0)
        mesh.scaling = (50, 50, 50)
        mesh.translation = (0, 0, 0)
        mesh.shader_uri = 'managed://shader#mesh.fx'
        mesh.technique = 'SkyBox'
        mesh.mesh_uri = 'managed://mesh#alley_skybox.x'
        #mesh.setCubeTexture('SkyBoxEnvMap', 'managed://texture#sky_cube.dds')
        mesh.setCubeTexture('SkyBoxEnvMap', 'managed://texture#uffizi_cross_cube.dds')
        
        '''terrain = new('TerrainNode', '/usr/scene/terrain')
        terrain.heightmap_uri = 'managed://texture#hmap5x5_tile.png'
        terrain.shader_uri = 'managed://shader#terrain.fx'
        terrain.technique = 'Terrain'
        terrain.scaling = (1, 0.50, 1)
        terrain.setTexture('DiffuseMap', 'managed://texture#grass.jpg')

        tree = new('TreeNode', '/usr/scene/tree')
        tree.shader_uri = 'managed://shader#terrain.fx'
        tree.technique = 'Terrain'

        x = new('TreeNode', '/usr/scene/xesh')
        x.shader_uri = 'managed://shader#mesh.fx'
        x.technique = 'Mesh'
        '''
        
        render_path = new('RenderPath', '/sys/server/renderpath')
        rpsection = new('RpSection', '/sys/server/renderpath/default')
        
        rppass = new('RpPass', '/sys/server/renderpath/default/scene')
        rppass.clear_color = (0, 0, 255, 255)
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'ScenePass'
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/scene/rt')
        rt.texture_uri = 'managed://rt#scene'
        rt.texture_format = 'X8R8G8B8'
        rt.relative_size = 1
        
        rppass = new('RpPass', '/sys/server/renderpath/default/downscaled4x')
        rppass.clear_target = False;
        rppass.clear_depth = False;
        rppass.clear_stencil = False;
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'DownFilterPass'
        rppass.setTexture('SceneMap', 'managed://rt#scene')
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/downscaled4x/rt')        
        rt.texture_uri = 'managed://rt#downscaled4x_scene'
        rt.texture_format = 'X8R8G8B8'
        rt.relative_size = 0.125
        
        rppass = new('RpPass', '/sys/server/renderpath/default/brightpass')
        rppass.clear_target = False;
        rppass.clear_depth = False;
        rppass.clear_stencil = False;
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'BrightPass'
        rppass.setTexture('SceneMap', 'managed://rt#downscaled4x_scene')
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/brightpass/rt')
        rt.texture_uri = 'managed://rt#brightpass_scene'
        rt.texture_format = 'X8R8G8B8'
        rt.relative_size = 0.125
        
        rppass = new('RpPass', '/sys/server/renderpath/default/bloom_h')
        rppass.clear_target = False;
        rppass.clear_depth = False;
        rppass.clear_stencil = False;
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#bloom.fx'
        rppass.technique = 'BloomHPass'
        rppass.setTexture('SceneMap', 'managed://rt#brightpass_scene')
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/bloom_h/rt')
        rt.texture_uri = 'managed://rt#bloomh_scene'
        rt.texture_format = 'X8R8G8B8'
        rt.relative_size = 0.125
        
        rppass = new('RpPass', '/sys/server/renderpath/default/bloom_v')
        rppass.clear_target = False;
        rppass.clear_depth = False;
        rppass.clear_stencil = False;
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#bloom.fx'
        rppass.technique = 'BloomVPass'
        rppass.setTexture('SceneMap', 'managed://rt#bloomh_scene')
        rt = new('RpRenderTarget', '/sys/server/renderpath/default/bloom_v/rt')
        rt.texture_uri = 'managed://rt#bloomv_scene'
        rt.texture_format = 'X8R8G8B8'
        rt.relative_size = 0.125
        
        rppass = new('RpPass', '/sys/server/renderpath/default/final')
        rppass.clear_target = False;
        rppass.clear_depth = False;
        rppass.clear_stencil = False;
        rppass.draw_quad = True
        rppass.shader_uri = 'managed://shader#hdr.fx'
        rppass.technique = 'ComposeScenePass'
        #rppass.setTexture('SceneMap', 'managed://rt#downscaled4x_scene')
        rppass.setTexture('SceneMap', 'managed://rt#scene')
        #rppass.setTexture('SceneMap', 'managed://rt#bloomv_scene')
        rppass.setTexture('ToneMap', 'managed://rt#bloomv_scene')
        
        # PropertyGrid
        self.propertyGrid = PropertyGrid(self, wx.NewId(), wx.Point(0, 0),
            wx.Size(300, 300), wx.CLIP_CHILDREN, '')

        # NOHTree
        self.nohTree = NOHTree(self, wx.NewId(),
            wx.Point(8, 8), wx.Size(360, 392),
            style=wx.TR_LINES_AT_ROOT | wx.TR_HAS_BUTTONS | wx.TR_EDIT_LABELS)
        self.nohTree.Bind(wx.EVT_TREE_SEL_CHANGED, self.onSelChanged, id=self.nohTree.GetId())
        self.nohTree.build('/')
        
        # CommandConsole
        self.commandConsole = CommandConsole(self, wx.NewId(), wx.DefaultPosition, wx.Size(300, 80), 0)
       
        # SceneView
        self.sceneView = SceneView(self)
        self.sceneView.addViewPanel('Perspective View', get('/usr/scene/camera'))
        self.sceneView.addViewPanel('Top View')
        self.sceneView.addViewPanel('Left View')
        self.sceneView.addViewPanel('Front View')
        
        # AddPanes
        self.auimgr.AddPane(self.nohTree, wx.aui.AuiPaneInfo().
            Caption('Node of Hierarchy').Dockable(True).Right().CloseButton(True).MinimizeButton(True))
        self.auimgr.AddPane(self.propertyGrid, wx.aui.AuiPaneInfo().
            Caption('Property').Dockable(True).Right().CloseButton(True).MinimizeButton(True))
        self.auimgr.AddPane(self.commandConsole, wx.aui.AuiPaneInfo().
            Caption('Command Console').Dockable(True).Bottom().CloseButton(True).MinimizeButton(True))
        self.auimgr.AddPane(self.sceneView, wx.aui.AuiPaneInfo().
            Caption('Render View').Center().CloseButton(False))
       
        self.auimgr.Update()
        
    def onSelChanged(self, event):
        self.propertyGrid.setObject(get(self.nohTree.getSelectionAbsolutePath()))

    def OnMainFrameClose(self, event):
        self.app.keepGoing_ = False
        self.Destroy()

    def update(self):
        self.sceneView.update()
 
    @classmethod
    def instance(self):
        return MainFrame.s_instance
    s_instance = None
        
