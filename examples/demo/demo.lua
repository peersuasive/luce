#!/usr/bin/env luajit

local debug
if arg and arg[1] and arg[1]:match("^[Dd]") then
    debug = true
end
local luce = require"luce"(debug)

---
--- create a default JUCEApplication
---
local mainWindow = luce:JUCEApplication("JUCEApplication")

---
--- create a DocumentWindow with name "Document Window"
---
local dw = luce:DocumentWindow("Document Window")
-- rename it
dw.name = "LUCE Example Application"

---
--- create a MainComponent, to be hosted by the Document Window
---
local mc = luce:MainComponent("Main Component")
mc:setSize{1,1}
---
--- create a button named "TheButton" with text "a button"
---
local button = luce:TextButton("TheButton")
button:setButtonText( "a button")

--- add a callback for when button is clicked
button:buttonClicked(function(...)
    print("button clicked !!")
end)

--- change component look and feel
local button2 = luce:TextButton("TheButton2")
button2.buttonText = "button with a different look and feel"

--- add a callback for when button is clicked
button2:buttonClicked(function(...)
    print("button 2 clicked !!")
end)

--- set a different look and feel for button2
button2:setLookAndFeel(3)

---
--- create a Label
---
local label = luce:Label("A Label")

--- Label's setText has an optional parameter to send a notification when its content's changed
--- by default, it sends nothing:
label.text = "a bit of content" -- default to dontSendNotification

--- set a callback for label text changes
label:labelTextChanged(function(...)
    print("Label text has changed: ", label:getText())
end)
--- but we could use one of the three notification methods accepted:
--- sendNotification, sendNotificationSync or sendNotificationAsync
--- by using the setText method:
local notif = luce.NotificationType.sendNotification
label:setText( "another content", notif )

--- set label editable
label:setEditable(false, true, true) -- edit on single click, edit on double click, 
                                     -- cancel changes when losing focus
--- we can attach the label to the button too                                     
label:attachToComponent( button, true ) -- component, true: onLeft/false: above (default)
print( "is attached on left ?", label:isAttachedOnLeft())


--- set a colour for background and align text to the right
local label2 = luce:Label("Another Label")
label2.text = "(left aligned)"
label2:setColour( label2.ColourIds.backgroundColourId, "yellow" )
label2:setJustificationType( label2.JustificationType.right )

--- centre text
local label3 = luce:Label("(left aligned text)")
label3.text = "(centered)"
label3:setColour( label3.ColourIds.backgroundColourId, "red" )
label3:setJustificationType( label3.JustificationType.centred )

local slm = luce:StretchableLayoutManager("unmanaged slm")

local lb = luce:Label("unmanaged label")

---
--- create a TextEditor
---
local te = luce:TextEditor("Text Editor")

--- directly set bounds for this component
te.bounds = { 200, 250, 200, 200 } -- x, y, w, h
-- or
-- te.setBounds{ 200, 250, 200, 200 }

--- add our Document Window and components to our main JUCE application
mainWindow:initialise(function(...)

    mc:addAndMakeVisible( button ) -- add the button to the main component
    button:setBounds{ 200, 20, 200, 200 } -- give the button some dimensions
    mc:addAndMakeVisible( label ) -- add the label          
    --label:setBounds{ 20, 250, 100, 100 } -- don't set bounds to the label
                                           -- if you want it attached to button

    mc:addAndMakeVisible(te) -- add the Text Editor

    mc:addAndMakeVisible( button2 ) -- add the second button with the different lnf
    button2:setBounds{ 410, 20, 200, 200 }

    mc:addAndMakeVisible(label2)
    label2:setBounds{ 410, 230, 150, 30 }

    mc:addAndMakeVisible(label3)
    label3:setBounds{ 410, 270, 150, 30 }

    --mc:setBounds{ 0, 0, 800, 600 } -- set the component bounds
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
    dw:setVisible(true)

    return dw -- return the Document Window so the JUCE Application can take it
end)

--- callback on DocumentWindow :closeButtonPressed
dw:closeButtonPressed(function(...)
    print("*** DocumentWindow close button pressed")
end)

--- callback used when quit is asked
local keep_going = true
mainWindow:systemRequestedQuit(function(...)
    print("** MainWindow system requested quit")
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
    local status = true
    if ( not keep_going ) then
        status = false
    end
    return status
end )


luce:shutdown() -- in any case, call this to close cleanly
