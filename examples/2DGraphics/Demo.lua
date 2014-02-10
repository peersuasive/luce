#!/usr/bin/env lua

local args = {...}

local demos = {
    GlyphDemo = "GlyphDemo",
    LinesDemo  = "LinesDemo"
}
local animations = {
    rotation = true,
    position = true,
    shear    = true,
    size     = true,
}
local demo = "GlyphDemo"
local usage = function()
    print("Usage: Demo.lua [options] [demo]")
    print(" demo: one of GlypDemo, LinesDemo (default: GlyphDemo)")
    print("options:")
    print(" -d <animation> [-d ...]    disable selected animation")
    print("                can be one of rotation, position, shear, size or all (default: all enabled)")  
    print()
end
if(#args>0)then
    for i,o in next, args do
    if("-h"==o) or ("--help"==o)then
        usage()
        os.exit()
    elseif(o:match("^%-"))then
        if("-d"==o)then
            local a = args[i+1]
            if("all"==a)then
                animations.rotation = false
                animations.position = false
                animations.shear    = false
                animations.size     = false
            elseif( animations[a] ) then
                animations[a] = false
            else 
                print(string.format("unknown animation: %s, ignoring", a))
            end
            args[i+1] = ""
        else
            print(string.format("unknown option: %s\n", o))
            usage()
            os.exit(1)
        end
    else
        if not(""==o)then
        if not(demos[o])then
            print(string.format("Unknow demo '%s', using default (%s)", o, demo))
        end
        end
        demo = demos[o] or "GlyphDemo"
    end
    end
end

local luce = require"luce"()

local mainWindow = luce:JUCEApplication()
local dw = luce:DocumentWindow("Document Window")
local mc = luce:MainComponent("Main Component")
mc:setSize{1,1}


local demoHolder = require"DemoHolder"(demo)

demoHolder.animations.animateRotation = animations.rotation
demoHolder.animations.animatePosition = animations.position
demoHolder.animations.animateShear    = animations.shear
demoHolder.animations.animateSize     = animations.size

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
