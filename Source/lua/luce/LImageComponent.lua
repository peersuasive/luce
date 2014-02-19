--[[----------------------------------------------------------------------------

  LImageComponent.lua

  Luce implementation of ImageComponent

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce
local className = "LImageComponent"
local mt = {}

local new_vars = setmetatable({}, {
    __call = function()
        return setmetatable({}, {
            __newindex = function(self,k,v)
                rawset(self, k, function(...) if(...)then v[k]=... else return v[k] end end)
            end
        })
    end
})

function mt:setImage(newImage, placement)
    if(newImage ~= self.image)then
        self.image = newImage
        self.placement = placement or self.placement
        self:repaint()
    end
end

function mt:setImagePlacement(placement)
    if( self.placement.flags ~= placement.flags)then
        self.placement = placement 
    end
end

function mt:getImage()
    return self.image
end

function mt:getImagePlacement()
    return self.placement
end

local __index = {}

local function new(_,name, placement)
    -- init
    local int_index = {}
    local self = setmetatable({
        name = name or className,
        placement = placement or luce.RectanglePlacement.Flags.centred,
        __unlocal = function(t,k)
            int_index[k] = nil
            rawset(t,k,nil)
        end,
    }, {
        __newindex = function(t,k,v)
            print("setting new entry", k, v)
            int_index[k] = true
            rawset(t,k,v)
        end,
    })
    self.image = nil
    local comp = luce:Component(self.name)
    local __vars = new_vars()

    comp:paint(function(g)
        g:setOpacity(1.0)
        g:drawImageWithin(self.image, 0, 0, comp:getWidth(), comp:getHeight(), self.placement, false)
    end)

    -- internal
    self.__self = comp.__self
    return setmetatable(self, {
        __self = comp.__self,
        __index = function(_, k)
            if(int_index[k]) then return nil         -- self
            elseif(mt[k]) then return mt[k]          -- upper self
            elseif(__vars[k])then return __vars[k]() -- sub components or specifics, may override comp
            else return comp[k] end                  -- comp
        end,
        __newindex = function(t,k,v)
            if(__vars[k])then __vars[k](v)
            elseif(comp.__exists(k))then comp[k] = v
            else rawset(t,k,v) end
        end,
        __tostring = function(self)return className.."("..self.name..")"end
    })
end
mt.new = new
setmetatable(mt, { __index = __index })

return setmetatable({}, {
    __tostring = function()return className end,
    __call = function(self,core,...)
        luce = assert(core, "Missing luce core instance")
        return setmetatable({}, {
            __call = new,
            __tostring = function()return className end,
            __index = __index,
        })
    end
})
