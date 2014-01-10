---
-- LClass( luce:CLASS():new(...) )
-- LClass( "AClass", ... )
---
local new = function(_, name, ...)
    local self = {}
    local class
    if("string"==type(name)) then
        local luce = require"luce"
        class = luce[name](luce):new(...)
    else
        class = name
    end
    for k,v in next, class do
        if ( k == "methods" ) then
            for _,f in next, v do
                self[f] = class[f] -- better than the methods table
            end
        -- TODO: find a smart way to get values when dumping
        elseif ( k == "vars" ) then
            for _,f in next, v do
                self[f] = f
            end
        else
            self[k] = v
        end
    end
    return setmetatable(self, {
        __self = class.__self,
        __index = function(t,k) return class.__index(class, k) end,
        __newindex = function(t, k, v)
            if not ( getmetatable(class).__index(class, k) ) 
                and not ( getmetatable(class).__newindex(class, k, v) ) then
                rawset(t,k,v)
            else
                class[k] = v
            end
        end
    })
end

local mt = setmetatable({ new = new }, {
    __call = new
})
module(...)
return mt
