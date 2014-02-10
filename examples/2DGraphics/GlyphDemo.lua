--[[----------------------------------------------------------------------------

GlyphDemo.lua

JUCE Graphics Demo

base component

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

--[[ REQUIREMENTS ]]------------------------------------------------------------
local luce = require"luce"()
local className = "LGlyphDemo"

local function new(self)
    local self = {}
    self.name = className
    
    -- parent class
    local comp = require"GraphicsDemoBase"(self.name)
 
    local glyphs = luce:GlyphArrangement()
    glyphs:addFittedText( luce:Font(20.0), 
                          "The Quick Brown Fox Jumped Over The Lazy Dog",
                           -120, -50, 240, 100, luce.JustificationType.centred, 2, 1.0 )

    -- =0
    local function drawDemo(self, g)
        g:setColour( luce:Colour(luce.Colours.black):withAlpha( comp:getAlpha() ) )
        glyphs:draw(g, comp:getTransform())
    end
    self.drawDemo = drawDemo

    -- call GraphicsDemoBase paint method
    comp:paint(self)

    self.__self = comp.__self
    -- internal
    return setmetatable(self, {
        __self = comp.__self,
        __index = function(_, k) return comp[k] end,
        __newindex = function(t,k,v)
            if(comp.__exists(k))then comp[k] = v
            else rawset(t,k,v) end
        end,
    })
end

--module(...)
return new(...)
