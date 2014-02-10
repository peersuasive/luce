--[[----------------------------------------------------------------------------

DemoHolder.lua

JUCE Graphics Demo Holder

components holder

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

--[[ REQUIREMENTS ]]------------------------------------------------------------

local luce = require"luce"()
local className = "DemoHolder"

local new_vars = setmetatable({}, {
    __call = function()
        return setmetatable({}, {
            __newindex = function(self,k,v)
                rawset(self, k, function(...) if(...)then v[k]=... else return v[k] end end)
            end
        })
    end
})

local function new(demoComp)
    -- init
    local self = {}
    self.name = name or className
    self.demoComp = demoComp or "GlyphDemo"

    -- class main component
    local comp = luce:Component("DemoHolder")
    comp:setOpaque(true)

    local timer = luce:Timer()

    local demo = require(self.demoComp)
    comp:addAndMakeVisible(demo)

    comp:resized(function(...)
        demo:setBounds( luce:Rectangle(comp:getLocalBounds()) )
    end)

    local lightgrey = luce.Colours.lightgrey
    local white = luce.Colours.white
    comp:paint(function(g)
        g:fillCheckerBoard( luce:Rectangle(comp:getBounds()), 48, 48, lightgrey, white) 
    end)

    timer:timerCallback(function()
        demo:repaint()
    end)

    function self:startDemo()
        local fps = 60
        timer:startTimer (1000 / fps)
        comp:resized()
    end

    local __vars = new_vars()
    __vars.animations = demo
    
    -- internal
    self.__self = comp.__self
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
    })
end

--module(...)
return new
