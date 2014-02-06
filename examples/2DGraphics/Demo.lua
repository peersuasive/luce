#!/usr/bin/env psm
local debug
if arg and arg[1] and arg[1]:match("^[Dd]") then
    debug = true
end
local luce = require"luce"(debug)

local mainWindow = luce:JUCEApplication()
local dw = luce:DocumentWindow("Document Window")
local mc = luce:MainComponent("Main Component")
mc:setSize{1,1}

local demo = "GlyphDemo"
local demo = "LineDemo"

local demoHolder = require"DemoHolder"(demo)

demoHolder.animations.animateRotation = true
demoHolder.animations.animatePosition = true
demoHolder.animations.animateShear    = true
demoHolder.animations.animateSize     = true

mc:resized(function()
    demoHolder:setBounds( luce:Rectangle(mc:getLocalBounds()) )
end)

mainWindow:initialise(function(...)
    mc:addAndMakeVisible( demoHolder )
    demoHolder:setBounds{ 0, 0, 800, 600 }
    demoHolder:startDemo()
    dw:setContentOwned( mc, true )
    dw:centreWithSize{800, 600}
    dw:setVisible(true)
    return dw
end)

mainWindow:systemRequestedQuit(function(...)
    mainWindow:shutdown()
    mainWindow:quit()
end)
luce:start(mainWindow)
luce:shutdown()
