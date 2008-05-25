# coding: mbcs

import wx
from todpython import *

class CommandConsole(wx.Panel):
    def __init__(self, parent, id, pos, size, style):
        wx.Panel.__init__(self, parent, id, pos, size, style)