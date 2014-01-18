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
            for _,f in next, v do
                self[f] = f
            end
        else
            self[k] = v
        end
    end
    return setmetatable(self, {
        __tostring = me.__tostring,
        __self = me.__self,
        __index = function(t,k) return me.__index(me, k) end,
        __newindex = function(t, k, v)
            if not ( getmetatable(me).__index(me, k) ) 
                and not ( getmetatable(me).__newindex(me, k, v) ) then
                rawset(t,k,v)
            else
                me[k] = v
            end
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
