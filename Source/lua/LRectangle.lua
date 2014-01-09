local mt = {}

function mt:reduced(i)
    local self = self:new{self.x+i, self.y+i, self.w-(i*2), self.h-(i*2)}
    self.w = (self.w<=0) and 0 or self.w
    self.h = (self.h<=0) and 0 or self.h
    return self
end

function mt:dump()
    return { self.x, self.y, self.w, self.h }
end

function new(self, t)
    local self = {}
    local t = t or {}
    self.x = t[1] or self.x or 0
    self.y = t[2] or self.y or 0
    self.w = t[3] or self.w or 0
    self.h = t[4] or self.h or 0
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = "LRectangle",
        __tostring = function(self)
            return "{[0] = "..self.x..", [1] = "..self.y..", [2] = "..self.w..", [3] = "..self.h .. "}"
        end,
    })
end

mt.new = new
local xmeta = setmetatable({}, {
    __call = new,
    new = new
})
module(...)
return xmeta
