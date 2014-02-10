--[[----------------------------------------------------------------------------

GraphicsDemoBase.lua

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
local className = "LLinesDemo"

local function new(self, name)
    -- init
    local self = {}
    self.name = name or className
    
    -- class main component
    local comp = require"GraphicsDemoBase"(self.name)
 
    local offset = comp.SlowerBouncingNumber()
    local positions = { nil, nil, nil, nil, nil, nil, nil, nil }
    for i=1, 8 do positions[i] = comp.SlowerBouncingNumber() end

    local function drawDemo(self, g)
        do
            local verticalLines = luce:RectangleList()
            local pos = offset:getValue()

            for x=1, comp:getWidth() do
                local y = comp:getHeight() * 0.3
                local length = y * math.abs (math.sin (x / 100.0 + 2.0 * pos))
                verticalLines:addWithoutMerging( luce:Rectangle{ x, y - length * 0.5, 1.0, length} )
            end

            g:setColour( luce.Colour(luce.Colours.blue):withAlpha( self.getAlpha() ) )
            g:fillRectList (verticalLines)
        end

        do
            local horizontalLines = luce:RectangleList()
            local pos = offset:getValue();

            for y = 1, comp:getHeight() do
                local x = comp:getWidth() * 0.3
                local length = x * math.abs (math.sin (y / 100.0 + 2.0 * pos))
                horizontalLines:addWithoutMerging( luce:Rectangle{x - length * 0.5, y, length, 1.0})
            end

            g:setColour( luce:Colour(luce.Colours.green):withAlpha( comp:getAlpha() ) )
            g:fillRectList(horizontalLines);
        end

        g:setColour( luce:Colour(luce.Colours.red):withAlpha( comp:getAlpha() ) )

        local w = comp:getWidth()
        local h = comp:getHeight()

        g:drawLine ({positions[1]:getValue() * w,
                    positions[2]:getValue() * h,
                    positions[3]:getValue() * w,
                    positions[4]:getValue() * h})

        g:drawLine ({positions[5]:getValue() * w,
                    positions[6]:getValue() * h,
                    positions[7]:getValue() * w,
                    positions[8]:getValue() * h})
    end
    self.drawDemo = drawDemo

    -- call GraphicsDemoBase paint method
    comp:paint(self)

    -- internal
    self.__self = comp.__self
    return setmetatable(self, {
        __self = comp.__self,
        __index = function(_, k)
            return comp[k]
        end,
        __newindex = function(t,k,v)
            if(comp.__exists(k))then comp[k] = v
            else rawset(t,k,v) end
        end,
    })
end

--module(...)
return new(...)
