local myType = "LPoint"
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

function mt:isOrigin()
    return self.x == 0 and self.y == 0
end

function mt:getX()
    return self.x
end

function mt:getY()
    return self.y
end

function mt:setX(x)
    self.x = x
    return self
end

function mt:setY(y)
    self.y = y
    return self
end

function mt:withX(x)
    return self:new{x, self.y}
end

function mt:withY(y)
    return self:new{self.x, y}
end

function mt:setXY(x,y)
    self.x = x
    self.y = y
    return self
end

function mt:translated(x, y)
    return self:new{ x + self.x, y + self.y }
end

function mt:getDistanceFromOrigin()
    return hypot(self.x, self.y)
end

function mt:getDistanceFrom(other)
    return hypot( self.x - other.x, self.y - other.y )
end

function mt:getAngleToPoint(other)
    -- as float, might as well return a LNumber
    return math.atan2(other.x - self.x, self.y - other.y)
end

function mt:rotatedAboutOrigin(a)
    return self:new{ self.x * math.cos(a) - self.y * math.sin(a),
                     self.x * math.sin(a) + self.y * math.cos(a) }
end

function mt:getPointOnCircumference(rx, ry, a)
    if not(a)then
        return self:new({
                self.x + rx * math.sin(rx),
                self.y - rx * math.cos(rw)
            }, "float") 
    else
        return self:new({
                self.x + rx * math.sin(a),
                self.y - ry * math.cos(a),
            }, "float" )
    end
end

function mt:getDotProduct(other)
    -- float
    return self.x * other.x + self.y * other.y
end

function mt:applyTransform(aff)
    self.x, self.y = aff:transformPoint(
            luce:LNumber(self.x, self.__type),
            luce:LNumber(self.y, self.__type)
    )
    return self
end

function mt:transformBy(aff)
    return self:new{
        aff.mat00 * self.x + aff.mat01 * self.y + aff.mat02,
        aff.mat10 * self.x + aff.mat11 * self.y + aff.mat12
    }
end

function mt:toInt()
    self.__type = "int"
    return self
end

function mt:toFloat()
    self.__type = "float"
    return self
end

function mt:toDouble()
    self.__type = "double"
    return self
end

function mt:dump()
    return { self.x, self.y }, self.__type, self.__ltype
end

function mt:type()
    return self.__type
end

local function new(me, t, __type)
    local self = {}
    local t = t or {}
    self.x = t[1] or t.x or 0
    self.y = t[2] or t.y or 0
    self.__type = __type or t.__type or me.__type or "int"
    self.__ltype = myType
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = myType,
        __tostring = function(self)
            return self.x..", "..self.y
        end,
        __add = function(self,other)
            return self:new{ self.x + other.x, self.y + other.y }
        end,
        __sub = function(self, other)
            return self:new{ self.x - other.x, self.y - other.y }
        end,
        __mul = function(self, other)
            if("number"==type(other))then
            self.x = self.x * other
            self.y = self.y * other
            return self
            else
            return self:new{ self.x * other.x, self.y * other.y }
            end
        end,
        __div = function(self, other)
            if("number"==type(other))then
            self.x = self.x / other
            self.y = self.y / other
            return self
            else
            return self:new{ self.x / other.x, self.y / other.y }
            end
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
