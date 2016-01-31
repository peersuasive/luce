local title = "Hello World!"

local app, luce = require"luce.LApplication"(title, ...) -- create a basic Application
                                                         -- with command line parameters
local function MainWindow(...)  -- our main component class
    local app, luce = app, luce -- just to put these in the local environment
    local Colours   = luce.Colours
    local wsize     = {800,600} -- the size of our window
    local isPaused  = false

    local mc = luce:MainComponent("MainComponent") -- our main component
    local documentWindow = luce:Document(title)    -- create a document window to hold the main component

    local animateMe = luce:AnimatedPosition(luce.AnimatedPosition.ContinuousWithMomentum())
    animateMe:setLimits( luce:Range(0, 680) )
    local dragMe    = luce:Label("drag it")
    dragMe:setColour( luce.Label.ColourIds.backgroundColourId, "red" )
    dragMe:setColour( luce.Label.ColourIds.outlineColourId, "black" )
    dragMe:setJustificationType( luce.JustificationType.centred )
    dragMe.bounds   = { 50, 50, 70, 20 }
    dragMe.text     = "drag me!"

    math.randomseed(os.time()) math.random() math.random() math.random()

    local mx, my, mx2, my2
    local function moveIt(x, y)
        local x, y = x - mx, y - my
        local r = luce:Rectangle(dragMe:getBounds())
        local n = luce:Rectangle{ (r.x + x), (r.y + y), r.w, r.h }
        dragMe:setBounds( n )
    end
    dragMe:mouseDown(function(m)
        mx, my = m:getMouseDownX(), m:getMouseDownY()
        animateMe:beginDrag(_, dragMe:getY())
    end)
    dragMe:mouseDrag(function(m)
        moveIt(m.x, m.y)
    end)
    dragMe:mouseUp(function(m)
        mx2, my2 = dragMe:getX(), dragMe:getY()
        mx, my = nil, nil
        print(m:getDistanceFromDragStart())
        animateMe:drag(m:getDistanceFromDragStart())
        animateMe:endDrag()
    end)

    animateMe:positionChanged(function(pos)
        print("aMe pos", pos)
        print("  -> x,y", mx2, my2)
        dragMe:setTopLeftPosition(pos, dragMe:getY())
    end)

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
    -- draw the message
    local xpos = 0
    mc:paint(function(g)
        -- draw a background
        g:fillCheckerBoard( luce:Rectangle(mc:getBounds()), 48, 48, Colours.lightgrey, Colours.white) 
        -- draw text
        g:setFont(32.0)
        g:setColour(luce:Colour(Colours.black))
        local r = luce:Rectangle(mc:getLocalBounds()):setX(xpos)
        g:drawText("Hello World!", r, luce.JustificationType.left, true);
    end)

    local animateText = luce:AnimatedPosition(luce.AnimatedPosition.ContinuousWithMomentum())
    animateText:setLimits( luce:Range(-600, 600) )
    animateText:positionChanged(function(pos)
        xpos = pos
        mc:repaint()
    end)

    local now = luce:Time( (luce.Time:getCurrentTime():toMilliseconds() - 100) )
    app:initialised(function()
        animateText:beginDrag(now)
        animateText:drag(150)
        animateText:endDrag()

        dragMe:animateComponent( luce:Rectangle(dragMe:getBounds()):translated(220, 240):expanded(30, 20),
                             1.0,
                             1500,
                             false,
                             1.0,
                             0.2)

    end)
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
    -- add and display components
    ---
    mc:setSize(wsize)
    mc:addAndMakeVisible(button)                -- add the component to our main component
    mc:addAndMakeVisible(dragMe)
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
