--[[----------------------------------------------------------------------------

  LRange.lua

  Luce implementation of Range

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce = _G.luce
local className = "LRange"
local mt = {}

function mt:getStart()
    return self.lstart
end

function mt:getEnd()
    return self.lend
end

function mt:getLength()
    return self.lend - self.lstart
end

function mt:isEmpty()
    return self.lstart == lend
end

function mt:setStart(s)
    self.lstart = s
    if(self.lend < s)then self.lend = s end
    return self
end

function mt:withStart(s)
    return self:new(s, math.max(s, self.lend))
end

function mt:movedToStartAt(s)
    return self:new(s, self.lend+(s-self.lstart))
end

function mt:setEnd(e)
    self.lend = e
    if(self.e<self.lstart)then
        self.lstart = e
    end
    return self
end

function mt:withEnd(e)
    return self:new(math.min(self.lstart, e), e)
end

function mt:movedToEndAt(e)
    return self:new(self.lstart+(e-self.lend), e)
end

function mt:setLength(l)
    self.lend = self.lstart + math.max(0, l)
    return self
end

function mt:withLength(l)
    return self:new(self.lstart, self.lstart+l)
end

function mt:contains(pos)
    if(pos.__type and assert(pos.__type == "LRange"))then
        return self.lstart <= pos.lstart and self.lend >= pos.lend
    else
        return self.lstart <= pos and pos < self.lend
    end
end

function mt:clipValue(val)
    return (val<self.lstart) 
            and self.lstart
            or ( (self.lend < val) and self.lend or val )
end

function mt:intersect(r)
    return r.lstart < self.lend and self.lstart < r.lend
end

function mt:getIntersectionWith(r)
    return self:new( math.max(self.lstart, r.lstart), math.min(self.lend, r.lend) )
end

function mt:getUnionWith(r)
    if("number"==type(r))then
        return self:new( math.min(r, self.lstart), math.max(r, self.lend) )
    else
        return self:new( math.min(self.lstart, r.lstart), math.max(self.lend, r.lend) )
    end
end

function mt:constrainRange(r)
    local l = r:getLength()
    if(self:getLength() <= l)then
        return self
    else
        local limSup = self.lend - l
        return (r.lstart < self.lstart) 
                and self.lstart
                or ( (limSup < r.lstart) and limSup or r.lstart )
    end
end

function mt:dump()
    return { self.lstart, self.lend, __type = self.__type }
end

local function new(_, ...)
    local lstart, lend, __type = 0, 0, "int"
    local n = #{...}
    if n >= 2 then
        local b, e, t = ...
        lstart = b
        lend   = math.max(b, e)
        __type = t
    elseif n == 1 then
        local r = ...
        lstart = r:getStart()
        lend   = r:getEnd()
        __type = r.__type
    end
    
    local self = {
        lstart = lstart,
        lend   = lend,
    }
    self.__type = __type or "int"
    self.__ltype = className

    self.new = mt.new
    return setmetatable(self, {
        __self = className,
        __index = mt,
        __tostring = function()
            return string.format("%s %s", self.lstart, self.lend)
        end,
        -- __eq, __add,...
    })
end
mt.new = new

function mt:between(pos1, pos2)
    return (pos1<pos2) and new(pos1,pos2) or new{pos2,pos1}
end

function mt:emptyRange(self,start)
    return new(start, start)
end

function mt:findMinAndMax(self,values)
    if (numValues <= 0) then
        return new()
    end

    local first = values[1]
    local r = luce:Range(first, first)

    for i=2, #values do
        local v = values[i]
        if (r.lend < v) then r.lend = v end
        if (v < r.lstart) then  r.lstart = v end
    end

    return r
end

local mt_static = {
    between    = mt.between,
    emptyRange = mt.emptyRange,
}

return setmetatable({}, {
    __call = new,
    __index = mt_static,
    __tostring = function()return className end,
})
