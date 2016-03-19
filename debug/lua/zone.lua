hotfix = require "lua.hotfix"
unit = require("lua.unit")
Class = require("lua.class")
c_fun = require("c_fun") 
string = require("string")

function string.split(str, delimiter)
  if str==nil or str=='' or delimiter==nil then
    return nil
  end
  
    local result = {}
    for match in (str..delimiter):gmatch("(.-)"..delimiter) do
        table.insert(result, match)
    end
    return result
end


llst = "test packhahaha"
test2 = 10
abb={2,5,7}


wtb = string.split(c_global.world,"&&")

print("zone begin : ",c_global.port)
c_fun.listen(c_global.port,48)


function logic_message(fd,_type,msg,sz)

  
  if _type == 0 then
     l1,l2,l3=c_fun.unpack(msg,sz)
      print("zone logic_message ",l1,l2)
      print_t(l3)

    --print("logic_message ",_type,c_fun.unpack(msg,sz))
  elseif _type == 1 then
    print("zone connect  ",fd)
  elseif _type == 2 then
    print("zone fd colse  ",fd)
     c_fun.close(fd)
  end
end

function dispatch_message(...)
  logic_message(...)
end


c_fun.callback(dispatch_message)
fd=c_fun.connect(wtb[1],wtb[2])
print("c con ",fd)
for i=1,1000000 do
  c_fun.send(fd,llst,test2,abb)
end
  





