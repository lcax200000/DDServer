


local unit = {}
local lint = 0
unit.num=888
unit.ABB = 123
abb=0
function print_t(t)
    -- body
    if type(t)=="table" then
      for k, v in pairs(t) do
        --if type(t)=="table" then
           -- print_t(v)
       -- else
            print("k = ",k," v = ",v)
       -- end
      end

    else
      print(t)
    end
    
    
end

function unit.addi()
    lint = lint+1
    --abb=abb+1
    print("unit.num ",lint)
end



return unit