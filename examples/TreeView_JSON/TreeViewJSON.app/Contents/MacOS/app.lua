#!/usr/bin/env luajit
--[[----------------------------------------------------------------------------

  Luce Simple JSON TreeView Demo

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

---
-- create a default Luce Application
---

local title = "JSON TreeView Demo"
local app, luce = require"luce.LApplication"("LUCE App", ...)

local function MainWindow(params)
    local app, luce = app or _G.app, luce or _G.luce
    local size = { 800 , 600 } -- our window size

    -- create a Document, that is the window that'll be put on Desktop, with borders, title, etc.
    local dw = luce:Document(title)

    --- create a Main Component, that is a container for all widgets
    local mc = luce:MainComponent(title)

    --- load the JSON module
    local json = io.open(app:getRes("assets/json_sample.json")):read("*a")

    --- load our custom class to render JSON items
    local LJSONTreeViewItem = require"LJSONTreeViewItem"

    --- load the Tree View class that'll receive JSON items
    local tv = luce:TreeView("Tree View")

    --- set a sad colour to look more serious
    tv:setColour( tv.ColourIds.backgroundColourId, "dimgrey" )

    --- tell the TreeView class we want to have visible open/close buttons
    --  on items having sub-items (that's the default)
    tv:setOpenCloseButtonsVisible(true)

    --- tell the TreeView class we don't want to see the root node
    tv:setRootItemVisible( false )

    --- tell the TreeView class we want to be able to select many nodes 
    tv:setMultiSelectEnabled( true )

    --- create an instance of our JSON items renderer
    local tvi = LJSONTreeViewItem(nil, require"json".decode(json), tv)

    --- set the root node of the TreeView class so we can see the rendered items
    tv:setRootItem( tvi )

    --- this is called by the item itself to render
    --- sub-components when a node is double-clicked
    -- note: in production, you wouldn't like such a design
    -- this is just to demonstrate how simple it is with Luce
    -- to pass functions as callbacks wherever and however you want
    -- (thanks to lua functions being first class value, of course)
    function tv:refresh(...)
        -- create sub-items (in fact, recreate the whole tree stating items openness)
        local tvi = LJSONTreeViewItem("nil", require"json".decode(json), self)
        -- to keep things simple, reset the whole root
        -- thanks to JUCE and lua velocity together, this costs just a little
        self:setRootItem(tvi)
    end

    --- finish class our window implementation 
    --- and send for display

    mc:setSize( size )                  -- set our main component size within the Document
                                        -- we'll use all the space here
    mc:addAndMakeVisible( tv )          -- add components to the main component
    tv:setBounds{ 50, 50, 600, 500 }    -- position our TreeView within the main component

    dw:setContentOwned( mc, true )      -- add our main component to be displayed 
                                        -- and set to true to have it fully managed by the app

    dw:centreWithSize( size )           -- centre window on screen with our size
    dw:setVisible(true)
    return dw                           -- send the Document Window to our App
end

return app:start(MainWindow)
