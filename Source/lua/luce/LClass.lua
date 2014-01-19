local new = function(self, ...)
    local self = self or {}
    local me = self.class.new(class, ...)
    self.__self = me.__self
    for k,v in next, me do
        if ( k == "methods" ) then
            for _,f in next, v do
                self[f] = me[f] -- better than the methods table
            end
        -- TODO: find a smart way to get values when dumping
        elseif ( k == "vars" ) then
            self["vars"] = v
        else
            self[k] = v
        end
    end
    return setmetatable(self, {
        __tostring = me.__tostring,
        __self = me.__self,
        __index = function(t,k)
            return me.__index(me, k) 
        end,
        -- FIXME: if returned value is nil, we can't detect if it's a nil index or a nil value !
        --
        __newindex = function(t, k, v)
            if not(me.__exists(me,k)) then
                rawset(t,k,v)
            else
                me[k] = v
            end
            --[[
            if not ( me.__index(me,k)
                and not ( me.__index(me,k) ) then
                    rawset(t,k,v)
                end
            else
                me[k] = v
            end
            --]]
        end
    })
end

local mt = setmetatable({}, {
    __call = function(self, c, ...)
        assert(c, "Missing base class")
        return setmetatable({}, {
            __call = function(_, ...) return new({class=c}, ...) end
        })
    end
})
module(...)
return mt
