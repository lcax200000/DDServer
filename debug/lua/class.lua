Class = {sub = 0}

function Class:new(o)
  -- body
  o = o or {}
  setmetatable(o, self)
  self.__index = self
  return o
end


function Class:PrintSelf()
  -- body
  print("cp  ",self.sub)
end


function Class:AddSelf()
  -- body
  self.sub = self.sub+1
  print("ad sub ",self.sub)
end

function Class:get_env()
    -- body
    local env_mt = { __index = _ENV }
    local value = setmetatable({}, env_mt)
    return value 
end

return Class