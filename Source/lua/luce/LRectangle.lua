local mt = {}

function mt:reduce(d, dy)
    local d, dy = d, dy or d
    self.x = self.x+d
    self.y = self.y+dy
    self.w = self.w-(d*2)
    self.h = self.h-(dy*2)
    self.w = (self.w<=0) and 0 or self.w
    self.h = (self.h<=0) and 0 or self.h
    return self
end

function mt:reduced(d, dy)
    local d, dy = d, dy or d
    local self = self:new{self.x+d, self.y+dy, self.w-(d*2), self.h-(dy*2)}
    self.w = (self.w<0) and 0 or self.w
    self.h = (self.h<0) and 0 or self.h
    return self
end

function mt:expand(d, dy)
    local dy = dy or d
    self.x, self.y, self.w, self.h = self.x-d, self.y-dy, self.w+(d*2), self.h+(dy*2)
    return self
end

function mt:expanded(d, dy)
    local dy = dy or d
    return self:new{ self.x-d, self.y-dy, self.w+(d*2), self.h+(dy*2) }
end

function mt:removeFromTop(a)
    local removed = self:new{self.x, self.y, self.w, a}
    self.y, self.h = self.y + a, self.h - a
    return removed
end

function mt:removeFromLeft(a)
    local removed = self:new{self.x, self.y, a, self.h}
    self.x, self.w = self.x+a, self.w-a
    return removed
end

function mt:removeFromRight(a)
    local removed = self:new{self.x+(self.w - a), self.y, a, self.h}
    self.w = self.w - a
    return removed
end

function mt:removeFromBottom(a)
    local rh
    rh, self.h = a, self.h - a
    return self:new{ self.x, self.y, self.w, h }
end

function mt:setLeft(l)
    self.x, self.w = l, self.w-(l*2)
    return self
end

function mt:withLeft(l)
    return self:new{ l, self.y, self.w-(l*2), self.h }
end

function mt:withTop(t)
    return self:new{ self.x, t, self.w, self.h - (t*2) }
end

function mt:setTop(t)
    self.y, self.h = t, self.h-(t*2)
    return self
end

function mt:setRight(l)
    self.w = self.w - l
    return self
end

function mt:withRight(l)
    return self:new{ self.x, self.y, self.w-l, self.h }
end

function mt:setBottom(b)
    self.h = self.h - l
    return self
end

function mt:withBottom(b)
    return self:new{ self.x, self.y, self.w, self.h-l }
end

function mt:withTrimmedRight(a)
    return self:new{ self.x+a, self.y, self.w-(a*2), self.h }
end

function mt:withTrimmedLeft(a)
    return self:new{ self.x+a, self.y, self.w-a, self.h }
end

function mt:withTrimmedTop(a)
    return self:new{ self.x, self.y+a, self.w, self.h - (a*2) }
end

function mt:withTrimmedBottom(a)
    return self:new{ self.x, self.y, self.w, self.h - a }
end

function mt:translate(d, dy)
    local d, dy = d or 0, dy or 0
    self.x, self.y = self.x+d, self.y+dy
    return self
end

function mt:translated(d, dy)
    local d, dy = d or 0, dy or 0
    return self:new{ self.x+d, self.y+dy, self.w, self.h }
end

function mt:getX()
    return self.x
end

function mt:getY()
    return self.y
end

function mt:getWidth()
    return self.w
end

function mt:getHeight()
    return self.h
end

function mt:setWidth(w)
    self.w = w
end

function mt:setHeight(h)
    self.h = h
end

function mt:getRight()
    return self.x + self.w
end

function mt:getBottom()
    return self.y + self.h
end

function getCentreX()
    return self.x + self.w / 2
end

function getCentreY()
    return self.y + self.h / 2
end
function getCentre()
    return { self.x+w/2, self.y+h/2 }
end

function mt:dump()
    return { self.x, self.y, self.w, self.h }
end

function new(_, t)
    local self = {}
    -- TODO: copy instanciation (self.x = t.x, ...)
    local t = t or {}
    self.x = t[1] or 0
    self.y = t[2] or 0
    self.w = t[3] or 0
    self.h = t[4] or 0
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = "LRectangle",
        __tostring = function(self)
            return "LRectangle {x = "..self.x..", y = "..self.y..", w = "..self.w..", h = "..self.h .. "}"
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
