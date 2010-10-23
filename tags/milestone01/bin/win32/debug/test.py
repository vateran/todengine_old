from todpython import *

new('Node', '/usr/scene1')
new('Node', '/usr/scene2')
new('Node', '/usr/scene3')
new('Node', '/usr/scene4')
new('Node', '/usr/scene5')
n = get('/usr')
n.setName('test')
print n
print n.getNumChildren()
pushcwn(n)
print ls()
popcwn()
print ls()

print n.findChild('scene')
print n.getAbsolutePath()
print n.getName()
print n.getRef()
for c in n.getChildren():
    print c.getName()

