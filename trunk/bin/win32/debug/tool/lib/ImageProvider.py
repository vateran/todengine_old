import sys, os
import wx

# ------------------------------------------------------------------------------
class ImageProvider:
    def __init__(self, root_path, width=16, height=16):
        self.images = {}
        self.imageList = wx.ImageList(width, height)
        self.load(root_path)
        
    def load(self, root_path):
        # add default icon
        try:
            bitmap = wx.Bitmap(root_path + '/Default.png', wx.BITMAP_TYPE_PNG)
            self.imageList.Add(bitmap)
        except:
            raise

        # add icons
        fnames = os.listdir(root_path)
        for fname in fnames:
            path = root_path + '/' + fname
            if not os.path.isfile(path):
                continue
            head, tail = os.path.split(path)
            name, ext = os.path.splitext(tail)
            ext = ext.lower()
            image_type = wx.BITMAP_TYPE_BMP
            if ext == '.gif':
                image_type = wx.BITMAP_TYPE_GIF
            elif ext == '.png':
                image_type = wx.BITMAP_TYPE_PNG
            elif ext == '.jpg':
                image_type = wx.BITMAP_TYPE_JPG
            elif ext == '.bmp':
                image_type = wx.BITMAP_TYPE_BMP
            else:
                continue
            bitmap = wx.Bitmap(path, image_type)
            self.images[name] = self.imageList.Add(bitmap)
            
    def getImageList(self):
        return self.imageList
    
    def getImage(self, name):
        try:
            return self.images[name]
        except:
            raise


