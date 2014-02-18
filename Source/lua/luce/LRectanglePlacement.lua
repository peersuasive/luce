local luce, bit
local myType = "LRectanglePlacement"
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


local Flags = {
    xLeft               = 1,
    xRight              = 2,
    xMid                = 4,
    yTop                = 8,
    yBottom             = 16,
    yMid                = 32,
    stretchToFit        = 64,
    fillDestination     = 128,
    onlyReduceInSize    = 256,
    onlyIncreaseInSize  = 512,
    doNotResize         = 768, -- onlyIncreaseInSize | onlyReduceInSize
    centred             = 4 + 32
}

function mt:getFlags()
    return self.flags
end

function mt:testFlags(f)
    return bit.band(self.flags, f) ~= 0
end

function mt:applyTo(x, y, w, h, dx, dy, dw, dh)
    if (w == 0) or (h == 0) then
        return;
    end

    if (bit.band(self.flags, Flags.stretchToFit) ~= 0) then
        x = dx;
        y = dy;
        w = dw;
        h = dh;
    else
        local scale = (bit.band(self.flags, Flags.fillDestination) ~= 0) 
                                and max (dw / w, dh / h)
                                or min (dw / w, dh / h)

        if ( bit.band(self.flags, Flags.onlyReduceInSize) ~= 0) then
            scale = min (scale, 1.0)
        end

        if ( bit.band(self.flags, Flags.onlyIncreaseInSize) ~= 0) then
            scale = max (scale, 1.0);
        end

        w = w * scale
        h = h * scale

        if ( bit.band(self.flags, Flags.xLeft) ~= 0) then
            x = dx

        elseif ( bit.band(self.flags, FlagsxRight) ~= 0) then
            x = dx + dw - w

        else
            x = dx + (dw - w) * 0.5
        end

        if ( bit.band(self.flags, Flags.yTop) ~= 0) then
            y = dy
        elseif ( bit.band(self.flags, Flags.yBottom) ~= 0) then
            y = dy + dh - h
        else
            y = dy + (dh - h) * 0.5
        end
    end
    return x, y, w, h, dx, dy, dw, dh
end

function mt:appliedTo(s, d)
    local x, y, w, h = self:applyTo( s:getX(), s:getY(), s:getWidth(), s:getHeight(),
                  d:getX(), d:getY(), d:getWidth(), d:getHeight() )
    
    return d:new{x,y,w,h}
end

function mt:getTransformToFit(s, d)
    if (s:isEmpty()) then
        return luce.AffineTransform.identity
    end

    local newX = d:getX()
    local newY = d:getY()

    local scaleX = d:getWidth() / s:getWidth()
    local scaleY = d:getHeight() / s:getHeight()

    if ( bit.band(self.flags, Flags.stretchToFit) == 0) then
        scaleX = (bit.band(self.flags, Flags.fillDestination) ~= 0)
                    and max (scaleX, scaleY)
                    or  min(scaleX, scaleY)

        if ( bit.band(self.flags, Flags.onlyReduceInSize) ~= 0) then
            scaleX = min(scaleX, 1.0)
        end

        if ( bit.band(self.flags, Flags.onlyIncreaseInSize) ~= 0) then
            scaleX = max(scaleX, 1.0)
        end

        scaleY = scaleX

        if ( bit.band(self.flags, Flags.xRight) ~= 0) then
            newX = newX + d:getWidth() - s:getWidth() * scaleX

        elseif ( bit.band(self.flags, Flags.xLeft) == 0) then
            newX = newX + (d:getWidth() - s:getWidth() * scaleX) / 2.0
        end

        if ( bit.band(self.flags, Flags.yBottom) ~= 0) then
            newY = newY + d:getHeight() - s:getHeight() * scaleX

        elseif ( bit.band(self.flags, Flags.yTop) == 0) then
            newY = newY + (d:getHeight() - s:getHeight() * scaleX) / 2.0
        end
    end

    return luce.AffineTransform
                :translation(-s:getX(), -s:getY())
                :scaled (scaleX, scaleY)
                :translated (newX, newY)
end

-- internal
function mt:dump()
    return self:getFlags()
end

function mt:type()
    return self.__type
end

local function new(me, t, __type)
    local self = {}
    local t = ("table"==type(t)) and t or { flags = t }
    self.Flags = Flags
    self.flags = t.flags or Flags.centered
    self.__type = "int"
    self.__ltype = myType
    bit = bit or luce.bit
    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = myType,
        __tostring = function(self)
            return self:getFlags()
        end,
    })
end
mt.new = new

return setmetatable({}, {
    __call = function(self,core,...)
        local self = self or {}
        luce = assert(core, "Missing luce core instance")
        bit = luce.bit
        self = setmetatable({}, {
            __call = new,
            __tostring = function()return myType end,
        })
        return self
    end
})
