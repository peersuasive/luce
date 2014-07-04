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

-- add some key mappings
local K = string.byte
local kc = setmetatable( luce.KeyPress.KeyCodes, { __index = function()return 0 end })
dw:keyPressed(function(k)
    local k, m = k:getKeyCode(), k:getModifiers()
    if (k==K"Q" or k==K"q") and m:isCommandDown() then
        mainWindow:quit()
        return true -- consume key
    end
    return false -- don't consume key
                 -- not returning anything 
                 -- has the same effect
end)

---
--- create a MainComponent, to be hosted by the Document Window
---
local mc = luce:MainComponent("Main Component")

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
label2:setColour( luce.Label.ColourIds.backgroundColourId, "yellow" )
label2:setJustificationType( luce.JustificationType.right )

--- centre text
local label3 = luce:Label("(left aligned text)")
label3.text = "(centered)"
label3:setColour( luce.Label.ColourIds.backgroundColourId, "red" )
label3:setJustificationType( luce.JustificationType.centred )

local slm = luce:StretchableLayoutManager("unmanaged slm")

local lb = luce:Label("unmanaged label")

---
--- create a TextEditor
---
local te = luce:TextEditor("Text Editor")
te.multiLine = true

--- directly set bounds for this component
te.bounds = { 200, 250, 200, 200 } -- x, y, w, h
-- or
-- te.setBounds{ 200, 250, 200, 200 }

local combo = luce:ComboBox("Combo Box")
combo:setLookAndFeel(3)
combo:setEditableText(true)
combo.tooltip = "click me !"
combo:addItem( "new item 1", 1)
combo:addSeparator()
combo:addItem( "new item 2", 2)
combo:addItemList({"item 3", "item 4"}, 3)

combo:labelTextChanged(function(text)
    print("new combo text:", text)
end)

combo:setSelectedId(3)
--print("num items:", combo:getNumItems())


local customItem = luce:TextButton("customItem")
customItem.buttonText = "custom item"
-- sync menu callback
local menu = luce:Label("popup menu")
menu.text = "right click on me for a sync menu!"
menu:mouseDown(function(mouseEvent)
    if(mouseEvent.mods.isPopupMenu())then
        local m = luce:PopupMenu()
        m:addItem(1, "item 1")
        m:addItem(2, "item 2")
        m:addCustomItem(3, customItem, 50, 20, true)
        m:setLookAndFeel(4)
        local id = m:show()
        print(string.format("sync item %s was clicked", id))
    end
end)
-- async menu callback
local menu_async = luce:Label("async popup menu_async")
menu_async.text = "right click on me for an async menu!"
menu_async:setLookAndFeel(3)
local m = luce:PopupMenu()
m:addItem(1, "item 1")
m:addItem(2, "item 2")
m:setLookAndFeel(4)
m:menuInvocationCallback(function(id, popupMenuRef)
    print(string.format("id %s was clicked", id))
end)
menu_async:mouseDown(function(mouseEvent)
    if(mouseEvent.mods.isPopupMenu())then
        m:showMenuAsync( luce.PopupMenu.Options() )
    end
end)

-- slider
local slider = luce:Slider("a slider")
slider:setRange( 1.0, 100.0, 0.5 )
local cw, ch = slider:getTextBoxWidth(), slider:getTextBoxHeight()
slider:setTextBoxStyle( luce.Slider.TextEntryBoxPosition.TextBoxRight, false, cw/1.5, ch )

slider:valueChanged(function()
    print(string.format("slider value: %s", slider.value ))
end)

slider:stoppedDragging(function()
    print(string.format("slider last value: %s", slider.value))
end)


local imgButton = luce:ImageButton("ImageButton")
local img = luce.Image:getFromFile("logo.png")
imgButton:setImages(true, true, true, 
                        img, 0.7, luce:Colour(luce.Colours.white):withAlpha(0.0),
                        img, 1.0, luce:Colour(luce.Colours.red):withAlpha(0.5),
                        img, 1.0, luce:Colour(luce.Colours.blue):withAlpha(0.8),
                        0.5)

imgButton:buttonClicked(function()
    print("imgButton clicked!")
end)
--- add our Document Window and components to our main JUCE application
mainWindow:initialise(function(...)
    mc:setSize{800,600}
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

    mc:addAndMakeVisible(combo)
    combo:setBounds{ 410, 310, 200, 25 }

    mc:addAndMakeVisible(menu)
    menu:setBounds{ 410, 345, 200, 25 }

    mc:addAndMakeVisible(menu_async)
    menu_async:setBounds{ 410, 375, 200, 25 }

    mc:addAndMakeVisible(slider)
    slider:setBounds{ 410, 415, 200, 50 }

    mc:addAndMakeVisible(imgButton)
    imgButton:setBounds{ 10, 450, 200, 50 }

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
local stop_now = false
mainWindow:systemRequestedQuit(function(...)
    print("** MainWindow system requested quit")
    stop_now = true
    mainWindow:quit()
end)

--- main loop

--- there are two implementations of the main loop
--- one is the JUCE's native wrapped one
--- and the other one gives control over the loop
--- so actions can be taken during the process execution

-- luce:start( mainWindow ) -- the simplest one, everything's under 
                            -- Luce control

--- and the non automatic one
--- the function's executed in a loop within a thread,
--- so there's no need to loop here
--- it is set with a a rate of 1ms by default
--- note: not yet supported by iOS and Android
luce:start_manual( mainWindow, function(...)
    return stop_now
end)
