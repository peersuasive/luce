--[[----------------------------------------------------------------------------

  LImageComponent.lua

  Luce implementation of ImageComponent

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local luce = _G.Luce
local mt = { className = "LImageComponent" }

function mt:setImage(newImage, placement)
    if not(newImage) then
        self.image = nil
        self:repaint()
    elseif(newImage ~= self.image)then
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
    local name = name or mt.className
    local comp = luce:Component(name)
    local self, class = luce.class.self(mt, comp, name)
    self.image = nil
    self.placement = placement or luce.RectanglePlacement.Flags.centred

    -- fully or partially overridable paint
    local function paint(g)
        isPainting = true
        g:setOpacity(1.0)
        if not self.image then return end
        g:drawImageWithin(self.image, 0, 0, comp:getWidth(), comp:getHeight(), self.placement, false)
    end
    local paint_cb = paint
    function self:paint(func, ow)
        if not("function"==type(func)) then return end
        paint_cb = ow and func or function(g)paint(g)func(g)end
    end
    comp:paint(function(g)paint_cb(g)end)

    return class or self
end
mt.new = new
setmetatable(mt, { __index = __index })

return setmetatable({}, {
    __tostring = function()return className end,
    __call = new,
})
