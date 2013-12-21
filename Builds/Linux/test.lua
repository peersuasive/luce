#!/usr/bin/env luajit

package.cpath = "./build/?.so;"..package.cpath

local luce = require"luce"

--do return end

---
--- create a default JUCEApplication
---
local mainWindow = luce:JUCEApplication()
local mainWindow = mainWindow:new()

---
--- create a DocumentWindow with name "Document Window"
---
local dw = luce:DocumentWindow():new("Document Window")
-- rename it
dw.name = "LUCE Example Application"

---
--- create a MainComponent, to be hosted by the Document Window
---
local mc = luce:MainComponent():new()

---
--- create a button named "TheButton" with text "a button"
---
local button = luce:TextButton():new("TheButton")
button:setButtonText( "a button")

--- add a callback for when button is clicked
button:buttonClicked(function(...)
    print("button clicked !!")
end)

---
--- create a Label
---
local label = luce:Label():new("A Label")

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

---
--- create a TextEditor
---
local te = luce:TextEditor():new("Text Editor")

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
