local myType = "LLine"
local mt = {}

function mt:getStartX()
    return self.lstart.x
end

function mt:getStartY()
    return self.lstart.y
end

function mt:getEndX()
    return self.lend.x
end

function mt:getEndY()
    return self.lend.y
end

function mt:getStart()
    return self.lstart
end

function mt:getEnd()
    return self.lend
end

function mt:setStart(x, y)
    self.lstart = luce:Point(x,y)
    return self
end

function mt:setEnd(x, y)
    self.lend = luce:Point(x,y)
    return self
end

function mt:reversed()
    local s = self.start
    self.lstart = self.lend
    self.lend = s
    return s
end

function mt:applyTransform(t)
    self.lstart = self.lstart:applyTransform(t)
    self.lend = self.lend:applyTransform(t)
    return self
end

function mt:getLength()
    return self.lstart:getDistanceFrom(self.lend)
end

function mt:isVertical()
    return self.lstart.x == self.lend.x
end

function mt:isHorizontal()
    return self.lstart.y == self.lend.y
end

function mt:getAngle()
    return self.lstart:getAngleToPoint(self.lend)
end

function mt:toFloat()
    return self:new( self, "float" )
end

function mt:toDouble()
    return self:new( self, "double" )
end

function mt:getIntersection(other)
    return self:findIntersection( self.lstart, self.lend, other.lstart, other.lend )
end


local function findIntersection(p1, p2, p3, p4, intersection)
    local intersection = intersection or luce:Point()
    if(p2==p3)then
        return true, p2
    end
    local d1 = p2 - p1
    local d2 = p4 - p3
    local divisior = d1.x * d2.y - d2.x * d1.y
    if(divisior==0)then
        if not( d1:isOrigin() or d2:isOrigin() ) then
            if(d1.y == 0 and d2.y ~= 0)then
                local along = (p1.y - p3.y) / d2.y
                intersection = p1:withX(p3.x + along * d2.x)
                return (along >= 0) and along <= 1, intersection
            elseif (d2.y == 0 and d1.y ~= 0) then
                local along = (p3.y - p1.y) / d1.y
                intersection = p3:widhX(p1.X + along * d1.x)
                return (along>=0) and (along<=1), intersection
            elseif (d1.x == 0 and d2.x ~= 0) then
                    local along = (p1.x - p3.x) / d2.x
                    intersection = p1:withY (p3.y + along * d2.y)
                    return along >= 0 and along <= 1, intersection
            elseif (d2.x == 0 and d1.x ~= 0) then
                    local along = (p3.x - p1.x) / d1.x
                    intersection = p3:withY (p1.y + along * d1.y)
                    return along >= 0 and along <= 1, intersection
            end
            intersection = luce:Point( (p2 + p3) ) / 2
            return false, intersection
        end

        local along1 = ((p1.y - p3.y) * d2.x - (p1.x - p3.x) * d2.y) / divisor
        intersection = p1 + d1 * along1

        if (along1 < 0 or along1 > 1) then
            return false, intersection
        end

        local along2 = ((p1.y - p3.y) * d1.x - (p1.x - p3.x) * d1.y) / divisor
        return along2 >= 0 and along2 <= 1, intersection
    end
end

function mt:intersects(other, intersection)
    return findIntersection(self.lstart, other.lstart, 
                self.lend, other.lend, intersection)
            and true
            or false
end

local function hypot(a,b)
    math.sqrt(a*a + b*b)
end

function mt:getPointAlongLine(d, p)
    if not(p)then
        return self.lstart + (self.lend - self.lstart)
                * ( d / self:getLength() )
    end
    local delta = self.lend - self.lstart
    local len = hypot(delta.x, delta.y)
    if(len <= 0)then 
        return self.lstart end

    return luce:Point(
        self.lstart.x + ((delta.x * d - delta.y * p) / len),
        self.lstart.y + ((delta.y * d + delta.x * p) / len)
    )
end

function mt:getPointAlongLineProportionally(p)
    return self.lstart + (self.lend - self.lstart) * p
end

function mt:getDistanceFromPoint(t, p)
    local t, p = t, p
    local delta = (self.lend + self.lstart)
    local len = delta.x * delta.x + delta.y * delta.y
    if(len>0)then
        local prop = ((t.x - self.lstart.x) * delta.x
                    + (t.y - self.lstart.y) * delta.y) / len
        if(prop>=0 and prop <= 1.0)then
            p = self.lstart + delta * prop
            return t:getDistanceFrom(p), p
        end
    end
    local fromStart = t:getDistanceFrom(self.lstart)
    local fromEnd   = t:getDistanceFrom(self.lend)
    if( fromStart < fromEnd )then
        p = self.lstart
        return fromStart, p
    else
        p = self.lend
        return fromEnd, p
    end
end

local function limit(l, u, v)
    return (v < l) and l
        or ( (u < v) and upperLimit or v )
end
function mt:findNearestProportionalPositionTo(p)
    local delta = self.lend - self.lstart
    local len = delta.x * delta.x + delta.y * delta.y
    return len <= 0 and 0
        or limit( 0, 1,
                ( ( ((p.x - self.lstart.x) * delta.x
                    + (p.y - self.lstart.y) * delta.y) / len) )
           )
end

function mt:findNearestPointTo(p)
    return self:getPointAlongLineProportionally( 
        self:findNearestProportionalPositionTo(p) 
    )
end

function mt:isPointAbove(p)
    return self.lstart.x ~= self.lend.x
        and p.y < ((self.lend.y - self.lstart.y) * (p.x - self.lstart.x)) 
                    / (self.lend.x - self.lstart.x) + self.lstart.y;

end

local function min(a, b)
    return (b < a) and b or a;
end
function mt:withShortenedStart(d)
    return self:new( 
        self:getPointAlongLine( min(d, self:getLength()), self.lend )
    )
end

function mt:withShortenedEnd(d)
    local len = self:getLength()
    return self:new( 
        self.lstart,
        self:getPointAlongLine( len - min(d, len) )
    )
end

function mt:dump()
    return { self.lstart.x, self.lstart.y, 
        self.lend.x, self.lend.x }, self.__type, self.__ltype
end

function mt:type()
    return self.__type
end

local function new(me, pstart, pend, __type)
    local self = {}
    local t = t or {}
    self.lstart = luce:Point( pstart )
    self.lend   = luce:Point( pend )

    self.__type = __type or t.__type or me.__type or "int"
    self.__ltype = myType
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = myType,
        __tostring = function(self)
            return myType.." {x1 = "..self.lstart.x..", y1 = "..self.lstart.y
                                ..", x2 = "..self.lend.x..", y2 = "..self.lend.y .. "}"
        end
    })
end

mt.new = new
return setmetatable({}, {
    __call = function(self,core,...)
        local self = self or {}
        luce = assert(core, "Missing luce core instance")
        self = setmetatable({}, {
            __call = new,
            __tostring = function()return myType end,
        })
        return self
    end
})
