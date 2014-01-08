#!/usr/bin/env psm

--[[
LUCE Application Template

(c) 2014, Peersuasive Technologies
--]]


if arg and arg[1] and arg[1]:match("^[Dd]") then
    print"DEBUG"
    package.cpath = "debug/?.so;"..package.cpath
else
    package.cpath = "./build/?.so;"..package.cpath
end
local luce = require"luce"

---
--- create a default JUCEApplication
---
local mainWindow = luce:JUCEApplication():new()

---
--- create a DocumentWindow with name "Document Window"
---
local dw = luce:DocumentWindow():new("Document Window")

---
--- create a MainComponent, to be hosted by the Document Window
---
local mc = luce:MainComponent():new()


--
-- put components here
--

local json = io.open("json_sample.json"):read("*a")
local ltvi = require"LTreeViewItem"
local tvi = ltvi(nil, require"json".decode(json))

local tv = luce:TreeView():new("Tree View")

--tv:setColour( tv.ColourIds.backgroundColourId, "dimgrey" )

tv:setOpenCloseButtonsVisible(true)

tv:setRootItemVisible( false )
tv:setMultiSelectEnabled( true )

tv:setRootItem( tvi )

--
-- initialise callback, where components are displayed
--
mainWindow:initialise(function(...)
    mc:addAndMakeVisible( tv ) -- add components to the main component
    tv:setBounds{ 50, 50, 600, 500 }
    --mc:setBounds{ 50, 50, 800, 600 } -- set the component bounds
                                     -- as this is the last component before
                                     -- DocumentWindow, it'll set the window size
                                     -- too, unless dw sets one
    dw:setContentOwned( mc, true )

    dw:centreWithSize{800, 600} -- centre window on screen with size 800x600
    --dw:setCentrePosition{ 0, 0 } -- move it to the top left corner
    
    --dw:setBounds{ 100, 100, 800,600 } -- sets the window bounds
                                        -- as dw is a TopWindow and, as such, the very 1st component,
                                        -- it'll be positionned
                                        -- on screen directly, so that's another way of
                                        -- doing centreWithSize/setCentrePosition
    --dw:setSize{ 800,600 } -- just show the window, top left corner
    dw:setLookAndFeel(4);
    dw:setVisible(true)


    return dw -- return the Document Window so the JUCE Application can take it
end)

--- callback used when quit is asked
local keep_going = true
mainWindow:systemRequestedQuit(function(...)
    keep_going = false
    mainWindow:shutdown()
    mainWindow:quit()
end)

--- main loop

--- there are two implementations of the main loop
--- one is the JUCE's native wrapped one
--- and the other one gives control over the loop
--- so actions can be taken during the process execution

-- luce:start( mainWindow ) -- the simplest one, everything's under 
                            -- JUCE control

--- and the non automatic one
--- the function's executed in a loop within a thread,
--- so there's no need to loop here
--- it is set with the same rate than the JUCE's loop (1ms by default)
luce:start_manual( mainWindow, function(...)
    return keep_going
end )


luce:shutdown() -- in any case, call this to close cleanly
