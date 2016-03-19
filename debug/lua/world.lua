hotfix = require "lua.hotfix"
unit = require("lua.unit")
Class = require("lua.class")
c_fun = require("c_fun") 

llst = "test packhahaha"
test2 = 10
abb={2,5,7}


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



print("world server begin")
c_fun.listen(c_global.port,48)


function logic_message(fd,_type,msg,sz)
  if _type == 1 then
    c_fun.close(fd)
    print("world connect !!! fd ",fd)
   -- c_fun.send(fd,llst,test2,abb)
  elseif _type == 0 then
    --todo
      l1,l2,l3=c_fun.unpack(msg,sz)
      print("world logic_message ",l1,l2)
      print_t(l3)
      c_fun.close(fd)
  elseif _type == 2 then
     c_fun.close(fd)
  end
end

function dispatch_message(...)
  logic_message(...)
end


c_fun.callback(dispatch_message)

