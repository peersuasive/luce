local luce = require"luce.core_d"
local LClass = require"LClass"

local mt = {}
for k,v in next, luce do
    if ("table"==type(v)) then
        mt[k] = v
    elseif k:match("^[A-Z]") then
        local l = LClass( v() )
        mt[k] = function(self,...) return l(...) end
    else
        mt[k] = v
    end
end

local xmeta = setmetatable(mt, {
    __index = mt
})

print("!!!!!!!!!!!!!!!! LOADED !!!!!!!!!!!!!!!")
module(...)
return xmeta
