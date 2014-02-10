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
local luce, new = require"luce"()

local float_Pi = 3.14159265358979323846
local double_Pi= 3.1415926535897932384626433832795

local function round(val, n)
    return math.floor( (val * 10^n) + 0.5) / (10^n)
end

local className = "LGraphicsDemoBase"

local new_vars = setmetatable({}, {
    __call = function()
        return setmetatable({}, {
            __newindex = function(self,k,v)
                rawset(self, k, function(...) if(...)then v[k]=... else return v[k] end end)
            end
        })
    end
})

local bc_getValue = function(self)
    local v = math.fmod( self.phase + self.speed * luce.Time:getMillisecondCounterHiRes(), 2.0 )
    return (v>=1.0) and (2.0 - v) or v
end
local BouncingNumber = function()
    local self = {}
    self.speed = ( 0.0004 + 0.0007 * luce.Random:getSystemRandom():nextDouble())
    self.phase = luce.Random:getSystemRandom():nextDouble()
    self.getValue = bc_getValue
    return self
end

local SlowerBouncingNumber = function()
    local self = BouncingNumber()
    self.speed = self.speed * 0.3
    return self
end

new = function(self, name)
    -- init
    local self = {}
    self.name = name or className
    local __vars = new_vars()

    self.SlowerBouncingNumber = SlowerBouncingNumber

    local displayFont = luce:Font(
        luce.Font:getDefaultMonospacedFontName(), 12.0, luce.Font.FontStyleFlags.bold
    );
    averageTimeMs = 0
    lastRenderStartTime = 0
    averageActualFPS = 0

    -- body
    -- class main component
    local comp = luce:Component(self.name)

    local clipImage = luce:Image()

    self.animations = {
        animateRotation = true,
        animatePosition = true,
        animateShear    = true,
        animateSize     = true,
    }

    for _,v in next, {
        "offsetX", "offsetY", "rotation", "size", "shear", "alpha", "clipRectX",
        "clipRectY", "clipPathX", "clipPathY", "clipPathDepth", "clipPathAngle",
        "clipImageX", "clipImageY", "clipImageAngle", "clipImageSize"
    } do self[v] = SlowerBouncingNumber() end

    local function getTransform()
        local hw = 0.5 * comp:getWidth();
        local hh = 0.5 * comp:getHeight();
        local t = luce:AffineTransform()
        if (self.animations.animateRotation)then
            t = t:rotated (self.rotation:getValue() * float_Pi * 2.0)
        end

        if (self.animations.animateSize)then
            t = t:scaled (0.3 + self.size:getValue() * 2.0)
        end

        if (self.animations.animatePosition)then
            t = t:translated (hw + hw * (self.offsetX:getValue() - 0.5),
                              hh + hh * (self.offsetY:getValue() - 0.5))
        else
            t = t:translated (hw, hh);
        end

        if (self.animations.animateShear)then
            t = t:sheared (self.shear:getValue() * 2.0 - 1.0, 0.0)
        end
        return t;
    end
    self.getTransform = getTransform

    local function getAlpha()
        return 1.0
    end
    self.getAlpha = getAlpha

    local function drawDemo()
        local name = name or ""
        error("drawDemo is pure in GraphicsDemoBase, children '"..name.."' must implement it.")
    end
    self.drawDemo = drawDemo

    local jtopRight = luce.JustificationType.topRight
    local blackAlpha = luce:Colour(luce.Colours.black):withAlpha( getAlpha() )

    local function paint(child, g)
        local startTime = 0.0
        do
            local state = g:ScopedSaveState(g)
            g:setImageResamplingQuality ( luce.Graphics.ResamplingQuality.mediumResamplingQuality )
            startTime = luce.Time:getMillisecondCounterHiRes()
            child:drawDemo (g)
        end

        local now = luce.Time.getMillisecondCounterHiRes()
        local filtering = 0.08

        local elapsedMs = now - startTime
        averageTimeMs = averageTimeMs + ((elapsedMs - averageTimeMs) * filtering)

        local sinceLastRender = now - lastRenderStartTime
        lastRenderStartTime = now;

        local effectiveFPS = 1000.0 / averageTimeMs
        local actualFPS = (sinceLastRender>0) and (1000.0 / sinceLastRender) or 0
        averageActualFPS = averageActualFPS + ((actualFPS - averageActualFPS) * filtering)

        local ga = luce:GlyphArrangement()

        ga:addFittedText (displayFont,
                          "Time: "..string.format("%6.2f",averageTimeMs)
                            .. " ms\nEffective FPS: " .. string.format("%6.2f",effectiveFPS)
                            .. "\nActual FPS: " .. string.format("%6.2f", averageActualFPS),
                          0, 10.0, comp:getWidth() - 10.0, comp:getHeight(), luce.JustificationType.topRight, 3)
        g:setColour( luce:Colour(luce.Colours.white):withAlpha(0.5) )
        local r = luce:Rectangle( ga:getBoundingBox(0, ga:getNumGlyphs(), true) ):getSmallestIntegerContainer():expanded(4)

        g:fillRect ( r )
        g:setColour (luce.Colours.black)
        ga:draw (g)
    end
    -- children will call this method to start the demo
    -- with their own implementation of drawDemo
    self.paint = function(_, self)
        comp:paint(function(g)
            paint(self, g)
        end)
    end
    
    local function clipToRectangle(g)
        local w = comp:getWidth() / 2;
        local h = comp:getHeight() / 2;

        local x = (int) (w * self.clipRectX.getValue());
        local y = (int) (h * self.clipRectY.getValue());

        g:reduceClipRegion (x, y, w, h);
    end
    self.clipToRectangle = clipToRectangle

    local function clipToPath(g)
        local pathSize = jmin(comp:getWidth(), comp:getHeight());
        local p = luce:Path()
        p:addStar( luce:Point(self.clipPathX:getValue(),
                              self.clipPathY:getValue()) * pathSize,
                              7,
                    pathSize * (0.5 + self.clipPathDepth:getValue()),
                    pathSize * 0.5,
                    self.clipPathAngle:getValue()
        )

        g:reduceClipRegion(p, luce:AffineTransform().identity);
    end
    self.clipToPath = clipToPath

    local function clipToImage(g)
        if not(clipImage:isValid())then
            createClipImage()
        end

        local transform = luce:AffineTransform():translation(
                    clipImage:getWidth() / -2.0,
                    clipImage:getHeight() / -2.0)
                            :rotated(clipImageAngle:getValue() * float_Pi * 2.0)
                            :scaled (2.0 + clipImageSize.getValue() * 3.0)
                            :translated (getWidth() * 0.5, getHeight() * 0.5)

        g:reduceClipRegion (clipImage, transform)
    end
    self.clipToImage = clipToImage

    local function createClipImage()
        clipImage = luce:Image(luce.Image.PixelFormat.ARGB, 300, 300, true)

        local g = luce:Graphics(clipImage)

        g:setGradientFill (ColourGradient (luce.Colours.transparentBlack, 0, 0,
                                           luce.Colours.black, 0, 300, false))

        for i=1, 20 do
            g:fillRect (luce.Random:getSystemRandom():nextInt (200),
                        luce.Random:getSystemRandom():nextInt (200),
                        luce.Random:getSystemRandom():nextInt (100),
                        luce.Random:getSystemRandom():nextInt (100))
        end
    end
    self.createClipImage = createClipImage

    -- end of body
    
    -- expose some sub component methods
    -- __vars.some_method_from_a_sub_comp = sub_comp
    self.__self = comp.__self
    -- internal
    return setmetatable(self, {
        __self = comp.__self,
        __index = function(_, k)
            if(__vars[k])then return __vars[k]()
            else return comp[k] end
        end,
        __newindex = function(t,k,v)
            if(__vars[k])then __vars[k](v)
            elseif(comp.__exists(k))then comp[k] = v
            else rawset(t,k,v) end
        end,
        __tostring = function(self)return className.."("..self.name..")"end
    })
end

local xmeta = setmetatable({},{
     __call = new,
    __tostring = function()return className end,
})

--module(...)
return xmeta
