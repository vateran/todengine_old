-- a = new("XFileNode", "/usr/scene/test2")
-- b = new("XFileNode", "/usr/scene/test3")
-- a:setInt(10)
-- a:setInt(a:getInt() + 10)


f = new('XFileNode', '/usr/scene/test2')
t = getmodulelist()
t = gettypelist(t[1])
todprint(t)

