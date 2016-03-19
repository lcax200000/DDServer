


conf = {}

conf.pid = 1

unit = {}

unit.name = "world"
unit.path = "./world/main.lua"

table.insert(conf,unit.name.."&&"..unit.path)

unit.name = "zone1"
unit.path = "./zone/main.lua"

table.insert(conf,unit.name.."&&"..unit.path)

