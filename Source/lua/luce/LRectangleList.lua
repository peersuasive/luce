--[[----------------------------------------------------------------------------

  LRectangleList.lua

  Luce implementation of RectangleList

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce, new = _G.Luce, nil
local className = "LRectangleList"
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



function mt:isEmpty()
    return (#self.rects==0)
end

function mt:getNumRectangles()
    return #self.rects
end

function mt:getRectangle(i)
    return self.rects[i]
end

function mt:clear()
    self.rects = {}
    return self
end

function mt:add(x, y, w, h)
    local r = x
    if (y) then
        r = luce:Rectangle({x, y, w, h}, self.__type)
    elseif("LRectangleList"==r.__ltype)then
        for _, rc in next, r.rects do
            self:add( rc )
        end
        return self
    elseif not("LRectangle"==r.__ltype) then
        error("Unknown type to add: ".. (r.__ltype or type(r)))
        -- assume Rectangle
        --r = luce:Rectangle({x, y, w, h}, self.__type)
    end
    if(#self.rects==0)then
        self.rects[1] = r
        return self
    end
    if not(r:isEmpty())then
        if (#self.rects == 0) then
            self.rects[1] = r
        else
            local anyOverlaps = false
            for j=#self.rects,1,-1 do
                local ourRect = self.rects[j]
                if (r:intersects(ourRect))then
                    if (r:contains(ourRect)) then
                        table.remove(self.rects, j)
                    elseif not( ourRect:reduceIfPartlyContainedIn(r) ) then
                        anyOverlaps = true;
                    end
                end
            end
            if ( anyOverlaps and (#self.rects > 0) ) then
                -- local rl = self:new( r:dump() , self.__type )
                local rl = self:new( r, self.__type )

                for i=#self.rects, 1, -1 do
                    ourRect = self.rects[i]
                    if (r:intersects(ourRect) ) then
                        rl:substract(ourRect)
                        if (#rl.rects == 0) then
                            return self
                        end
                    end
                end
                for _,n in next, rl.rects do
                    self.rects[#self.rects+1] = n
                end
            else
                self.rects[#self.rects+1] = r
            end
        end
    end
    return self
end

function mt:addWithoutMerging(r)
    if not(r:isEmpty()) then
        self.rects[#self.rects+1] = r
    end
    return self
end

function mt:substract(rect)
    local rect = rect
    if("LRectangleList"==rect.__ltype) then
        for _, n in next, rect.rects do
            self:substract(n)
        end
    elseif not ("LRectangle"==rect.__ltype) then
        error("Unknown type to substract: ".. (rect.__ltype or type(rect)))
    end

    local originalNumRects = #self.rects

    if (originalNumRects > 0) then
        local x1 = rect:getX()
        local y1 = rect:getY()
        local x2 = x1 + rect:getWidth()
        local y2 = y1 + rect:getHeight()

        for i = self:getNumRectangles(), 1, -1 do
            local r = self.rects[i]:copy()

            local rx1 = r:getX()
            local ry1 = r:getY()
            local rx2 = rx1 + r:getWidth()
            local ry2 = ry1 + r:getHeight()

            if not( (x2 <= rx1) or (x1 >= rx2) or (y2 <= ry1) or (y1 >= ry2)) then
                if ( (x1 > rx1) and (x1 < rx2) ) then
                    if (y1 <= ry1) and (y2 >= ry2) and (x2 >= rx2) then
                        r:setWidth (x1 - rx1);
                    else
                        r:setX (x1);
                        r:setWidth (rx2 - x1);

                        i = i+1
                        self.rects[i] = luce:Rectangle{rx1, ry1, x1-rx1, ry2 -ry1}
                        i = i+1
                    end
                elseif (x2 > rx1) and (x2 < rx2) then
                    r:setX (x2)
                    r:setWidth (rx2 - x2)

                    if (y1 > ry1) or (y2 < ry2) or (x1 > rx1) then
                        i = i+1
                        self.rects[i] = luce:Rectangle{rx1, ry1, x2 - rx1,  ry2 - ry1}
                        i = i+1
                    end
                elseif (y1 > ry1) and (y1 < ry2) then
                    if (x1 <= rx1) and (x2 >= rx2) and (y2 >= ry2) then
                        r:setHeight(y1 - ry1)
                    else
                        r:setY(y1)
                        r:setHeight(ry2 - y1)

                        i = i+1
                        self.rects[i] = luce:Rectangle{rx1, ry1, rx2 - rx1, y1 - ry1}
                        i = i+1
                    end
                elseif (y2 > ry1) and (y2 < ry2) then
                    r:setY(y2)
                    r:setHeight(ry2 - y2)

                    if (x1 > rx1) or (x2 < rx2) or (y1 > ry1) then
                        i = i+1
                        self.rects[i] = luce:Rectangle{rx1, ry1, rx2 - rx1, y2 - ry1}
                        i=i+i
                    end
                else
                    table.remove(self.rects,i)
                end
            end
        end
    end
    return self
end

function mt:clipTo(rect)
    if("LRectangle"==rect.__ltype)then
        if ( rect:isEmpty() ) then
            self:clear()
            return self
        end
        for i = #self.rects, 1, -1 do
            local r = self.rects[i]
            if not( rect:intersectRectangle( r ) ) then
                table.remove(self.rects, i)
            end
        end
        return self, (#self.rects~=0)

    elseif("LRectangleList"==rect.__ltype)then

        if (#self.rects == 0) then
            return self, false end
        
        local result = self:new()
        for j = 1, #self.rects do
            local rect = self.rects[j]
            for _, r in next, other.rects do
                local clipped = r:toType(self.__type)
                if (rect:intersectRectangle(clipped)) then
                    result.rects[#result.rects+1] = clipped
                end
            end
        end
        self:swapWith (result)
        return self
    end
    error("Unknown given object type: "..(rect.__ltype or type(rect)))
end

function mt:getIntersectionWith(rect, destRegion)
    destRegion:clear()
    if not(rect:isEmpty()) then
        for i = #self.rects, 1, -1 do
            local r = self.rects[i]:copy()
            if ( rect:intersectRectangle(r) ) then
                destRegion.rects[#destRegion.rects+1] = r
            end
        end
    end
    return self, (#self.rects>0)
end

function mt:swapWith(other)
    self.rects = other.rects
    return self
end

function mt:containsPoint( ... )
    local point = ...
    if(#{...}==2)then
        point = luce:Point(...)
    end
    for _, r in next, self.rects do
        if r:containts(point) then
            return true
        end
    end
    return false
end

function mt:containsRectangle(rectangleToCheck)
    if (#self.rects > 1) then
        local r = self:new{ rectangleToCheck }
        for i = #self.rects, 1, -1 do
            r:subtract(self.rects[i])
            if (#r.rects == 0) then
                return true
            end
        end
    elseif(#self.rects > 0) then
        return self.rects[1]:contains(rectangleToCheck)
    end
    return false;
end

function mt:intersectsRectangle( rectangleToCheck )
    for _, r in next, self.rects do
        if (r:intersects(rectangleToCheck)) then
            return true
        end
    end
    return false;
end

function mt:intersects(other)
    for _, r in next, other.rects do
        if (other:intersectsRectangle(r)) then
            return true
        end
    end
    return false
end

function mt:getBounds()
    if (#self.rects <= 1) then
        if (#self.rects == 0) then
            return luce:Rectangle() end
        return self.rects[1]
    end
    local r = self.rects[0]

    local minX = r:getX();
    local minY = r:getY();
    local maxX = minX + r:getWidth();
    local maxY = minY + r:getHeight();

    for i = #self.rects, 1, -1 do
        local r2 = self.rects[i]

        minX = min (minX, r2:getX())
        minY = min (minY, r2:getY())
        maxX = max (maxX, r2:getRight())
        maxY = max (maxY, r2:getBottom())
    end
    return luce:Rectangle({minX, minY, maxX - minX, maxY - minY}, self.__type)
end

function mt:consolidate()
    for i = 1, self:getNumRectangles() do
        local r = self.rects[i]
        local rx1 = r:getX()
        local ry1 = r:getY()
        local rx2 = rx1 + r:getWidth()
        local ry2 = ry1 + r:getHeight()

        for j = #self.rects, 1, -1 do
            local r2 = self.rects[j]
            local jrx1 = r2:getX()
            local jry1 = r2:getY()
            local jrx2 = jrx1 + r2:getWidth()
            local jry2 = jry1 + r2:getHeight()

            if (jrx1 == rx2) or (jrx2 == rx1) then
                if (jry1 > ry1) and (jry1 < ry2) then
                    r:setHeight(jry1 - ry1)
                    self.rects[#self.rects+1] = luce:Rectangle( {rx1, jry1, rx2 - rx1, ry2 - jry1}, self.__type )
                    i = -1
                    break
                end

                if (jry2 > ry1) and (jry2 < ry2) then
                    r:setHeight (jry2 - ry1);
                    self.rects[#self.rects+1] = luce:Rectangle( {rx1, jry2, rx2 - rx1, ry2 - jry2}, self.__type )
                    i = -1
                    break
                elseif (ry1 > jry1) and (ry1 < jry2) then
                    r2:setHeight(ry1 - jry1)
                    self.rects[#self.rects+1] = luce:Rectangle( {jrx1, ry1, jrx2 - jrx1, jry2 - ry1}, self.__type )
                    i = -1
                    break
                elseif (ry2 > jry1) and (ry2 < jry2) then
                    r2:setHeight(ry2 - jry1)
                    self.rects[#self.rects+1] = luce:Rectangle( {jrx1, ry2, jrx2 - jrx1, jry2 - ry2}, self.__type )
                    i = -1
                    break
                end
            end
        end
    end

    for i=1, #self.rects do
        local r = self.rects[i]
        for j = #rects.size, 1, -1 do
            if (r:enlargeIfAdjacent(self.rects[j])) then
                table.remove(self.rects, j)
                i = -1
                break
            end
        end
    end
end

function mt:offsetAll(...)
    local point = ...
    if(#{...}==2)then
        point = luce:Point(...)
    end
    for i, r in next, self.rects do
        self.rects[i] = r + offset
    end
end

function mt:transformAll(aff)
    for i,r in next, self.rects do
        self.rects[i] = r:transformedBy( aff )
    end
end

function mt:toPath()
    local p = luce:Path()
    for _,r in next, self.rects do
        p:addRectangle(r)
    end
    return p
end

-- [[ INTERNAL ]] --

function mt:dump()
    --[[
    local res = {}
    for i,r in next, self.rects do
        res[#res+1] = (r:dump())
    end
    res.__type = self.__type
    return res
    --]]
    return self.rects
end

function mt:type(__type)
    if(__type)then
        self.__type = __type
    else
        return self.__type
    end
end

new = function(me, t, __type)
    local self = {}
    local t = t or {}
    self.__type = __type or t.__type or (me and me.__type) or "int"
    self.__ltype = className
    self.rects = {}
    if ("LRectangle"==t.__ltype) then
        self.rects[1] = t
    elseif("LRectangleList"==t.__ltype) then
        for i,r in next, t.rects do
            self.rects[#self.rects+1] = r:copy()
        end
    end

    return setmetatable(self, {
        __index = mt,
        __call = new,
        __self = className,
        __tostring = function(self)
            return className.." {x = "..self.x..", y = "..self.y..", w = "..self.w..", h = "..self.h .. "}"
        end,
    })
end
mt.new = new

return setmetatable({}, {
    __tostring = function()return className end,
    __call = new,
})
