#!/usr/bin/env lua
local title = "Hello World!"

local app, luce = require"luce.LApplication"(title, ...) -- create a basic Application
                                                         -- with command line parameters


local timer = luce:Timer() -- a time for the animation
local function MainWindow(...)  -- our main component class
    local app, luce = app, luce -- just to put these in the local environment
    local Colours   = luce.Colours
    local wsize     = {800,600} -- the size of our window
    local isPaused  = false

    local mc = luce:MainComponent("MainComponent") -- our main component
    local documentWindow = luce:Document(title)    -- create a document window to hold the main component

    local button = luce:TextButton("quit")  -- a button to exit the app
    button.buttonText = "Quit"              -- set button text
    button:setLookAndFeel(4)                -- change look-and-feel
    button.bounds     = { 10, 10, 100, 20 } -- and position it x,y,w,h

    ---
    -- set some action on button click
    ---
    button:buttonClicked(function()
        app:quit()
    end)

    ---
    -- say hello to the world with a simple animation
    ---

    -- just a dump method to increase font size and pick a predefined colour
    local currentSize, baseSize, maxSize = 12.0, 12.0, 32.0
    local colours    = { Colours.black, Colours.red, Colours.yellow, Colours.green, Colours.blue }
    local currentCol = 1
    local function changeSize()
        currentSize = (currentSize>maxSize) and baseSize or currentSize+0.5
        currentCol  = (currentCol<#colours) and currentCol+1 or 1
        return currentSize, colours[currentCol]
    end

    -- draw the message
    mc:paint(function(g)
        -- draw a background
        g:fillCheckerBoard( luce:Rectangle(mc:getBounds()), 48, 48, Colours.lightgrey, Colours.white) 
        -- get new font size and colour
        local size, colour = changeSize()
        -- draw text
        g:setFont(size)
        g:setColour(colour)
        g:drawText("Hello World!", mc:getLocalBounds(), luce.JustificationType.centred, true);
    end)

    -- animate it a bit with the time callback
    timer:timerCallback(function()
        if(mc:isShowing() and not(isPaused))then
            mc:repaint()
        end
    end)
    timer:startTimer (1000/60)

    ---
    -- add some key shortcuts
    ---
    local K  = string.byte 
    local kc = setmetatable( 
        luce.KeyPress.KeyCodes, { __index = function()return 0 end } ) -- just a little trick to always get a valid keycode
                                                                       -- see https://www.juce.com/api/classKeyPress.html for
                                                                       -- available key-codes
    documentWindow:keyPressed(function(k)
        local k, m = k:getKeyCode(), k:getModifiers() -- get current key-code and modifiers status
        if (k==K"Q" or k==K"q") 
                and (m:isCommandDown() or not(app.os.osx)) then -- if Q is pressed or, on OS X, cmd+Q
            app:exit(0)     -- close the application with an normal exit state (0 by default)

        elseif (k==K"w" or k==K"W") and (m:isCommandDown() ) then -- if cmd/ctrl + W is pressed
            documentWindow:closeWindow() -- close the window
                                         -- on Linux and Windows, this as the effect of closing the application too,
                                         -- but on OS X, only the active window is closed by default
                                         -- however, if true is passed to closeWindow()
                                         -- and this is the last remaining Document
                                         -- the app will close the window and quit the appliation
        elseif (k==kc.spaceKey) then
            -- toggle rendering pause
            isPaused = not(isPaused)
        else
            return false -- don't consume key
                         -- returning false, nil or not returning anything
                         -- has the same effect
        end
        return true     -- tell the OS we have consumed this key
    end)

    ---
    -- add all components and display
    ---

    mc:setSize(wsize)
    mc:addAndMakeVisible(button)                -- add the component to our main component
    documentWindow:setContentOwned( mc, true )  -- add the main component to the document window

    ---
    documentWindow:closeButtonPressed(function() -- the user asked to close the current window...
        documentWindow:closeWindow()             -- so let's close it our way
                                                 -- if this action's not taken, it'll close the app by default
    end)
    documentWindow:setSize(wsize)   -- set dimensions for the window
                                    -- on iOS and Android, it'll just set a fullscreen
    documentWindow:setVisible(true) -- display the document
    return documentWindow           -- return it for the application to actually display it
end

local manual      = false       -- set true if you want to add your own process running along with the main loop
local osx_delayed = false       -- set true if you don't want your app to display a window immediatly on OS X
                                -- but wait for user input before, like providing a file,...
local poller      = function()  -- the callback you want to run in manual mode
    print "I'm in a loop!"
end
return app:start( MainWindow, manual and poller, osx_delayed ) -- returns the exit state
