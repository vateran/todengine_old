#!/usr/bin/env python
#Boa:App:BoaApp

import sys, os, time
sys.path.append(os.getcwd() + '/..')

import wx

import MainFrame

from todpython import *
from lib.PropertyGrid import *

modules ={u'MainFrame': [1, 'Main frame of Application', u'MainFrame.py']}

class BoaApp(wx.App):
    def OnInit(self):
        self.keepGoing_ = True
        self.triggerServer = new('TriggerServer', '/sys/server/trigger')
        
        PropertyGroup.addPropertyValueEditorType('', 'b', PropertyItemValueBool)
        PropertyGroup.addPropertyValueEditorType('property boolean editor', 's', PropertyItemValueString)
        
        self.main = MainFrame.create(None)
        self.main.app = self
        self.main.Show()
        self.SetTopWindow(self.main)
        return True
    
    def update(self, event_loop):
        self.main.update()
        while event_loop.Pending():
            event_loop.Dispatch()
        self.ProcessIdle()
        
    def MainLoop(self):
        event_loop = wx.EventLoop()
        old = wx.EventLoop.GetActive()
        wx.EventLoop.SetActive(event_loop)
        while self.keepGoing_:
            self.update(event_loop)
            self.triggerServer.trigger()
            time.sleep(0.001)
        wx.EventLoop.SetActive(old)

def main():
    try:
        app_name, resource_root = sys.argv[1]
        resroot(resource_root)
    except:
        resroot('../data')
    
    application = BoaApp(0)
    application.MainLoop()

if __name__ == '__main__':
    main()
