# coding: mbcs

from todpython import *

class EditorCommand:
    def selectNode(self, path):
        pass


class PythonEditorCommand(EditorCommand):
    def selectNode(self, path):
        return "_sel = get('%s')" % (path)


class LuaEditorCommand(EditorCommand):
    def selectNode(self, path):
        return "_sel = get('%s')" % (path)
    
