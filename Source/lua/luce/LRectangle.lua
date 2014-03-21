--[[----------------------------------------------------------------------------

  LRectangle.lua

  Luce implementation of Rectangle

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce, new = _G.Luce, nil
local className = "LRectangle"
local mt = {}

local function hypot(a,b)
    math.sqrt(a*a + b*b)
end

local function limit(l, u, v)
    return (v < l) and l
        or ( (u < v) and upperLimit or v )
end
local function min(a, b)
    return (b < a) and b or a;
end

local function max(a, b)
    return (a < b) and b or a;
end


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
    local a = (a<self.h) and a or self.h
    local r = self:new{ self.x, self.y + self.h - a, self.w, a }
    self.h = self.h-a
    return r
end

function mt:setLeft(l)
    self.x, self.w = l, self.w-(l*2)
    return self
end

function mt:withLeft(l)
    return self:new{ l, self.y, self.w-(l*2), self.h }
end

function mt:withTop(t)
    return self:new{ self.x, t, self.w, (self.y + self.h - t) }
    --return self:new{ self.x, t, self.w, self.h - (t*2) }
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
    self.y = (b<self.y) and b or self.y
    self.h = b - self.y
    return self
end

function mt:withBottom(b)
    local y = (b<self.y) and b or self.y
    return self:new{ self.x, y, self.w, b-y}
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

function mt:withWidth(w)
    return self:new{ self.x, self.y, w, self.h }
end

function mt:setWidth(w)
    self.w = w
    return self
end

function mt:withHeight(h)
    return self:new{ self.x, self.y, self.w, h }
end

function mt:setHeight(h)
    self.h = h
    return self
end

function mt:getRight()
    return self.x + self.w
end

function mt:getBottom()
    return self.y + self.h
end

function mt:getCentreX()
    return self.x + self.w / 2
end

function mt:getCentreY()
    return self.y + self.h / 2
end
function mt:getCentre()
    return { self.x+self.w/2, self.y+self.h/2 }
end

function mt:setCentre(...)
    local x, y
    if(#{...}==1)then
        local p = ...
        x, y = p.x or p[1], p.y or p[2]
    else x, y = ...  end
    self.x = x - self.w / 2
    self.y = x - y - self.h / 2
    return self
end

function mt:withCentre(...)
    return self:new( self:setCentre(...) )
end

function mt:isEmpty()
    return ( (self.h == 0) and (self.w==0) )
end

function mt:contains(other, y, w, h)
    local other = (w and luce:Rectangle(other,y,w,h)) 
            or (y and luce:Point(other,y)) 
            or other
    local t = other.__ltype
    if("LRectangle"==t)then
        return self.x <= other.x 
            and self.y <= other.y
            and self.x + self.w >= other.x + other.w 
            and self.y + self.h >= other.y + other.h
    elseif("LPoint"==t)then
        return other.x >= self.x 
            and other.y >= self.y 
            and other.x < self.x + self.w 
            and other.y < self.y + self.h
    else
        error("Wrong object given to contains")
    end
end
function mt:intersects(other)
    -- Rectangle or Line
    local other = other
    local t = other.__ltype or type(other)
    if(t=="table" and #other==4)then
            other = luce:Rectangle(other) end
    local t = other.__ltype
    if("LRectangle"==t)then
        return self.x + self.w > other.x
            and self.y + self.h > other.y
            and self.x < other.x + other.w
            and self.y < other.y + other.h
            and self.w > 0 and h > 0
            and other.w > 0 and other.h > 0

    elseif("LLine"==t)then
        return self:contains( other:getStart() )
            or self:contains( other:getEnd() )
            or other:intersects( luce:Line(self:getTopLeft()    , self:getTopRight())    )
            or other:intersects( luce:Line(self:getTopRight()   , self:getBottomRight()) )
            or other:intersects( luce:Line(self:getBottomRight(), self:getBottomLeft())  )
            or other:intersects( luce:Line(self:getBottomLeft() , self:getTopLeft())     )
    else
        error("Wrong object given to intersects")
    end
end

function mt:getSmallestIntegerContainer()
    -- int
    local x1 = math.floor( self.x )
    local y1 = math.floor( self.y )
    local x2 = math.ceil( self.x + self.w )
    local y2 = math.ceil( self.y + self.h )
    return self:new({ x1, y1, x2 - x1, y2 - y1 }, "int")
end

function mt:copyWithRounding(result)
    if(result.__type == "int")then
        return result:getSmallestIntegerContainer()
    else
        return self:new({self.x, self.y, self.w, self.h}, result.__type)
    end
end

function mt:enlargeIfAdjacent(other)
    if (self.x == other.x) 
        and (self:getRight() == other:getRight())
        and ((other:getBottom() >= self.y)
            and (other.y <= self:getBottom()))
    then
        local newY = min (self.y, other.y)
        self.h = max(self:getBottom(), other:getBottom()) - newY
        self.y = newY
        return true;
    end

    if (self.y == other.y) and (self:getBottom() == other:getBottom())
         and ((other.getRight() >= pos.x) 
            and (other.pos.x <= getRight()))
    then
        local newX = min(self.x, other.x)
        w = max(self:getRight(), other:getRight()) - newX
        self.x = newX
        return true
    end
    return false
end

function mt:toType(t)
    return self:new({ self.x, self.y, self.w, self.h }, t)
end

-- [[ STATICS ]] --

local function leftTopRightBottom(self, left, top, right, bottom)
    return self:new{left, top, right - left, bottom - top}
end
mt.leftTopRightBottom = leftTopRightBottom

-- [[ INTERNAL ]] --

local __index = {
    leftTopRightBottom = leftTopRightBottom,
}

function mt:copy()
    return self:new({self.x, self.y, self.w, self.h})
end

function mt:dump()
    return { self.x, self.y, self.w, self.h, __type = self.__type }
end

function mt:toString()
    return string.format("%s %s %s %s", self.x, self.y, self.w, self.h)
end

function mt:type()
    return self.__type
end

new = function(me, t, __type)
    if(t and t.start_manual)then error("wrong self !", 1) end
    -- TODO: Point constructor, x,y,w,h constructor, w,h constructor
    local self = {}
    if(t and not("table"==type(t)))then
        error("LRectangle: table expected, got "..type(t), 2)
    end
    local t = t or {}
    self.x = t[1] or t.x or 0
    self.y = t[2] or t.y or 0
    self.w = t[3] or t.w or 0
    self.h = t[4] or t.h or 0
    self.__type = __type or t.__type or me.__type or "int"
    self.__ltype = className
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = className,
        __tostring = function(self)
            return string.format("%s %s %s %s", self.x, self.y, self.w, self.h)
        end,
        __add = function(self, delta)
            local delta = luce:Point(delta)
            return self:new{self.x + delta.x, self.y + delta.y, self.w, self.h}
        end,
        __sub = function(self, delta)
            local delta = luce:Point(delta)
            return self:new{self.x - delta.x, self.y - delta.y, self.w, self.h}
        end,
        __mul = function(self, scale)
            if("number"==type(scale))then
                local r = self:new{self.x*scale, self.y*scale, self.w*scale, self.h*scale}
                return r:copyWithRounding(r)
            else
                local r = self:new{self.x*scale.x, self.y*scale.y, self.w*scale.x, self.h*scale.y}
                return r:copyWithRounding(self)
            end
        end,
        __div = function(self, scale)
            if("number"==type(scale))then
                local r = self:new{self.x/scale, self.y/scale, self.w/scale, self.h/scale}
                return r:copyWithRounding(self)
            else
                local r = self:new{self.x/scale.x, self.y/scale.y, self.w/scale.x, self.h/scale.y}
                return r:copyWithRounding(self)
            end

        end,
    })
end
mt.new = new
-- TODO: check if it works as expected !!!
setmetatable(mt, {__index=__index})

return setmetatable({}, {
    __call = new,
    __tostring = function()return className end,
})
