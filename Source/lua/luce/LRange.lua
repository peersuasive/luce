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
    return self.rstart
end

function mt:getEnd()
    return self.rend
end

function mt:getLength()
    return self.rend - self.rstart
end

function mt:isEmpty()
    return self.rstart == rend
end

function mt:setStart(s)
    self.rstart = s
    if(self.rend < s)then self.rend = s end
    return self
end

function mt:withStart(s)
    return self:new(s, math.max(s, self.rend))
end

function mt:movedToStartAt(s)
    return self:new(s, self.rend+(s-self.rstart))
end

function mt:setEnd(e)
    self.rend = e
    if(self.e<self.rstart)then
        self.rstart = e
    end
    return self
end

function mt:withEnd(e)
    return self:new(math.min(self.rstart, e), e)
end

function mt:movedToEndAt(e)
    return self:new(self.rstart+(e-self.rend), e)
end

function mt:setLength(l)
    self.rend = self.rstart + math.max(0, l)
    return self
end

function mt:withLength(l)
    return self:new(self.rstart, self.rstart+l)
end

function mt:contains(pos)
    if(pos.__type and assert(pos.__type == "LRange"))then
        return self.rstart <= pos.rstart and self.rend >= pos.rend
    else
        return self.rstart <= pos and pos < self.rend
    end
end

function mt:clipValue(val)
    return (val<self.rstart) 
            and self.rstart
            or ( (self.rend < val) and self.rend or val )
end

function mt:intersect(r)
    return r.rstart < self.rend and self.rstart < r.rend
end

function mt:getIntersectionWith(r)
    return self:new( math.max(self.rstart, r.rstart), math.min(self.rend, r.rend) )
end

function mt:getUnionWith(r)
    return self:new( math.min(self.rstart, r.start), math.max(self.rend, r.rend) )
end

function mt:constrainRange(r)
    local l = r:getLength()
    if(self:getLength() <= l)then
        return self
    else
        local limSup = self.rend - l
        return (r.rstart < self.rstart) 
                and self.rstart
                or ( (limSup < r.rstart) and limSup or r.rstart )
    end
end


local function new(_, ...)
    local rstart, rend = 0, 0
    local n = #{...}
    if n >= 2 then
        local b, e = ...
        rstart = b
        rend = math.max(b, e)
    elseif n == 1 then
        local r = ...
        rstart = r:getStart()
        rend = r:getEnd()
    end
    
    local self = {
        rstart = rstart,
        rend   = rend,
    }
    self.new = mt.new
    return setmetatable(self, {
        __index = self,
        -- __eq, __add, moins...
    })
end
mt.new = new

function mt.between(pos1, pos2)
    return (pos1<pos2) and new(pos1,pos2) or new{pos2,pos1}
end

function mt.emptyRange(start)
    return new(start, start)
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
