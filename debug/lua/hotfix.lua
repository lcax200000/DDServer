
--local si = require "snax.interface"

hotfix = {}

function hotfix.envid(f)
	local i = 1
    local t = {}
	while true do
		print("==================================i   ",i)
		local name, value = debug.getupvalue(f, i)
		--print(name, value)
        --t[name]=value
      --  print(name , t[name])
		
		if name == nil then
            print("nnnnnnnnnnnnnnnnnnnnnnnnn ",type(t))
			return t
		end
        if type(value)=="table" then
            for k2,v2 in pairs(value) do
               -- print("k2 v2, ",k2,v2)
                 t[k2]=v2
            end
        else
             t[name]=value
        end
         
          --print("name va",name,value)
		--if name == "_ENV" then
         -- print(type(t))
			--return debug.upvalueid(f, i)
		--end
		i = i + 1
	end
    print("eeeeeee ",type(t))
    return t
end

local function collect_uv(f , uv, env)
	local i = 1
	while true do
		local name, value = debug.getupvalue(f, i)
		if name == nil then
			break
		end
		local id = debug.upvalueid(f, i)

		if uv[name] then
			assert(uv[name].id == id, string.format("ambiguity local value %s", name))
		else
			uv[name] = { func = f, index = i, id = id }

			if type(value) == "function" then
				if envid(value) == env then
					collect_uv(value, uv, env)
				end
			end
		end

		i = i + 1
	end
end

local function collect_all_uv(funcs)
	local global = {}
	for _, v in pairs(funcs) do
		if v[4] then
			collect_uv(v[4], global, envid(v[4]))
		end
	end
	if not global["_ENV"] then
		global["_ENV"] = {func = collect_uv, index = 1}
	end
	return global
end

return hotfix