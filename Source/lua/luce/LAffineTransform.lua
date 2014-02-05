local luce, new = nil, nil
local myType = "LAffineTransform"
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

--[[ ************************************** ]]--

function mt:isIdentity()
    return  (self.mat01 == 0)
        and (self.mat02 == 0)
        and (self.mat10 == 0)
        and (self.mat12 == 0)
        and (self.mat00 == 1.0)
        and (self.mat11 == 1.0);
end

function mt:transformPoint(x, y)
    local x, y = x, y
    local oldX = x
    x = self.mat00 * oldX + self.mat01 * y + self.mat02
    y = self.mat10 * oldX + self.mat11 * y + self.mat12
    return x, y
end

function mt:transformPoints(x1, y1, x2, y2, x3, y3)
    local oldX1, oldX2, oldX3 = x1, x2, x3
    x1 = self.mat00 * oldX1 + self.mat01 * y1 + self.mat02
    y1 = self.mat10 * oldX1 + self.mat11 * y1 + self.mat12
    x2 = self.mat00 * oldX2 + self.mat01 * y2 + self.mat02
    y2 = self.mat10 * oldX2 + self.mat11 * y2 + self.mat12
    if(x3 and y3)then
        x3 = self.mat00 * oldX3 + self.mat01 * y3 + self.mat02
        y3 = self.mat10 * oldX3 + self.mat11 * y3 + self.mat12
    end
    return x1, y2, x2, y2, x3, y3
end

function mt:followedBy(other)
    return self:new{ other.mat00 * self.mat00 + other.mat01 * self.mat10,
                 other.mat00 * self.mat01 + other.mat01 * self.mat11,
                 other.mat00 * self.mat02 + other.mat01 * self.mat12 + other.mat02,
                 other.mat10 * self.mat00 + other.mat11 * self.mat10,
                 other.mat10 * self.mat01 + other.mat11 * self.mat11,
                 other.mat10 * self.mat02 + other.mat11 * self.mat12 + other.mat12
    }
end

function mt:translated(dx, dy)
    local dx, dy = dx, dy
    if not(dy)then dy = dx.y; dx = dx.x end
    return self:new{self.mat00, self.mat01, self.mat02 + dx,
                    self.mat10, self.mat11, self.mat12 + dy}

end

function mt:withAbsoluteTranslation(tx, ty)
    return self:new{ self.mat00, self.mat01, tx,
                     self.mat10, self.mat11, ty}

end

function mt:rotated(rad, pivotX, pivotY)
    if(pivotX and pivotY)then
        return self:followedBy( self:rotation(rad, pivotX, pivotY) )
    end
    local cosRad = math.cos (rad)
    local sinRad = math.sin (rad)
    return self:new{ cosRad * self.mat00 + -sinRad * self.mat10,
                     cosRad * self.mat01 + -sinRad * self.mat11,
                     cosRad * self.mat02 + -sinRad * self.mat12,
                     sinRad * self.mat00 +  cosRad * self.mat10,
                     sinRad * self.mat01 +  cosRad * self.mat11,
                     sinRad * self.mat02 +  cosRad * self.mat12}
end

function mt:scaled(factorX, factorY, pivotX, pivotY)
    if not(factorY)then
    return self:new{factorX * self.mat00, factorX * self.mat01, factorX * self.mat02,
                    factorX * self.mat10, factorX * self.mat11, factorX * self.mat12}

    elseif not(pivotX) then
    return self:new{factorX * self.mat00, factorX * self.mat01, factorX * self.mat02,
                    factorY * self.mat10, factorY * self.mat11, factorY * self.mat12}
    end
    return self:new{factorX * self.mat00, factorX 
                    * self.mat01, factorX * self.mat02 + pivotX * (1.0 - factorX),
                    factorY * self.mat10, factorY 
                    * self.mat11, factorY * self.mat12 + pivotY * (1.0 - factorY)}
end

function mt:sheared(shearX, shearY)
    return self:new{self.mat00 + shearX * self.mat10,
                    self.mat01 + shearX * self.mat11,
                    self.mat02 + shearX * self.mat12,
                    shearY * self.mat00 + self.mat10,
                    shearY * self.mat01 + self.mat11,
                    shearY * self.mat02 + self.mat12}
end

function mt:inverted()
    local determinant = (self.mat00 * self.mat11 - self.mat10 * self.mat01);
    if (determinant ~= 0) then
        determinant = 1.0 / determinant;
        local dst00 =  self.mat11 * determinant
        local dst10 = -self.mat10 * determinant
        local dst01 = -self.mat01 * determinant
        local dst11 =  self.mat00 * determinant

        return self:new{dst00, dst01, -self.mat02 * dst00 - self.mat12 * dst01,
                        dst10, dst11, -self.mat02 * dst10 - self.mat12 * dst11}
    else
        return self
    end
end

function mt:isSingularity()
    return (self.mat00 * self.mat11 - self.mat10 * self.mat01) == 0;
end

function mt:isOnlyTranslation()
    return  (self.mat01 == 0)
        and (self.mat10 == 0)
        and (self.mat00 == 1.0)
        and (self.mat11 == 1.0);
end

function mt:getTranslationX()
    return self.mat02
end

function mt:getTranslationY()
    return self.mat12
end

function mt:getScaleFactor()
    return (self.mat00 + self.mat11) / 2.0
end

-- [[ STATIC METHODS ]]--

local function translation(self, dx, dy)
    return self:new{1.0, 0, dx,
                    0, 1.0, dy}
end
mt.translation = translation

local function rotation(self, rad, pivotX, pivotY)
    if not(pivotX)then
    local cosRad = math.cos(rad)
    local sinRad = math.sin(rad)
    return self:new{cosRad, -sinRad, 0,
                      sinRad, cosRad, 0}
    else
    return self:new{cosRad, -sinRad, -cosRad * pivotX + sinRad * pivotY + pivotX,
                    sinRad, cosRad, -sinRad * pivotX + -cosRad * pivotY + pivotY}
    end
end
mt.rotation = rotation

local function scale(self, factorX, factorY, pivotX, pivotY)
    if not( factorY ) then
        return self:new{factorX, 0, 0, 0, factorX, 0}
    elseif not( pivotX ) then
        return self:new{factorX, 0, 0, 0, factorY, 0}
    end
    return self:new{factorX, 0, pivotX * (1.0 - factorX),
                    0, factorY, pivotY * (1.0 - factorY)}
end
mt.scale = scale

local function shear(self, shearX, shearY)
    return self:new{1.0, shearX, 0,
                    shearY, 1.0, 0}
end
mt.shear = shear

local function verticalFlip(height)
    return self:new{1.0, 0, 0, 0, -1.0, height}
end
mt.verticalFlip = verticalFlip

local function fromTargetPoints(...)
    if (#{...} == 6) then
    local x00, y00, x10, y10, x01, y01 = unpack{...}
    return self:new{x10 - x00, x01 - x00, x00,
                    y10 - y00, y01 - y00, y00}
    else
    local sx1, sy1, tx1, ty1,
          sx2, sy2, tx2, ty2,
          sx3, sy3, tx3, ty3 = unpack{...}
    return self:fromTargetPoints(sx1, sy1, sx2, sy2, sx3, sy3)
            :inverted()
            :followedBy (self:fromTargetPoints (tx1, ty1, tx2, ty2, tx3, ty3))
    end
end
mt.fromTargetPoints = fromTargetPoints

-- [[ INTERNAL ]] --

function mt:eq(self, other)
    return self.mat00 == other.mat00
        and self.mat01 == other.mat01
        and self.mat02 == other.mat02
        and self.mat10 == other.mat10
        and self.mat11 == other.mat11
        and self.mat12 == other.mat12
end

function mt:dump()
    return { self.mat00,
            self.mat01,
            self.mat02,
            self.mat10,
            self.mat11,
            self.mat12
    }
end

function mt:type()
    return self.__type
end

new = function(me, t, __type)
    local self = {}
    local t = t or {}
    self.mat00 = t[1] or t.mat00 or 1.0
    self.mat01 = t[2] or t.mat01 or 0
    self.mat02 = t[3] or t.mat02 or 0
    self.mat10 = t[4] or t.mat10 or 0
    self.mat11 = t[5] or t.mat11 or 1.0
    self.mat12 = t[6] or t.mat12 or 0
    self.__type = __type or t.__type or me.__type or "float"
    self.__ltype = myType
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = myType,
        __tostring = function(self)
            return self.x..", "..self.y
        end,
        __eq = eq,
    })
end
mt.new = new

local __index = {
    identity = new{},
    translation = translation,
    rotation = rotation,
    scale = scale,
    shear = shear,
    verticalFlip = verticalFlip,
    fromTargetPoints = fromTargetPoints,
    new = new,
}
-- TODO: check if it works as expected !!!
setmetatable(mt, {__index=__index})

local xmeta = setmetatable({}, {
    __call = function(self,core,...)
        local self = self or {}
        luce = assert(core, "Missing luce core instance")
        self = setmetatable({}, {
            __call = new,
            __index = __index,
            __tostring = function()return myType end,
        })
        return self
    end
})

module(...)
return xmeta
