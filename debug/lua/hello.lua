
unit = require("lua.unit")
Class = require("lua.class")

unit.addi()
print(unit["ABB"])
f = load([[
	--unit.num=199
    --abb=2999
    local lint = 999
    function unit.addi()
    lint=lint-1
    --unit.num = unit.num-1
    --abb=abb-1
    print(lint)
end ]])


local ok, err = pcall(f)
assert(ok,err)


print("dffff  ",ok,err)
unit.addi()


local c1 = Class:new()
c1:AddSelf()


f2 = load([[
	Class.sub = 99

function Class:AddSelf()
  -- body
  self.sub = self.sub-1+unit.num
  print("ad sub ",self.sub)
end

   ]])

ok, err = pcall(f2)
assert(ok,err)




for k,v in pairs(Class) do
	print("k  v  , ",k,v)
end


c1:PrintSelf()
local c2 = Class:new()
c2:AddSelf()

c1:AddSelf()

