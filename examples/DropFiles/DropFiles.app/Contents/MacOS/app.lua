#!/usr/bin/env luajit

local title = "Drop Files"
local app, luce = require"luce.LApplication"(title, ...)

local function MainWindow(args)
    local app, luce = app or _G.App, luce or _G.Luce
    local Colours = luce.Colours
    local wsize     = {240,120}
    local mc = luce:MainComponent("MainComponent")
    local dw = luce:Document(title)

    local dropTarget = luce:ListBox("dropTarget")
    dropTarget.bounds = {0,0,240,120}

    local bg = luce:Colour(Colours.white):withAlpha(0.0)
    local active = luce:Colour(Colours.yellow):withAlpha(0.5)
    dropTarget:setColour( dropTarget.ColourIds.backgroundColourId, bg )

    -- file drop callbacks
    dropTarget:isInterestedInFileDrag(function(files)
        return #files>0
    end)
    dropTarget:filesDropped(function(files, x, y)
        print"DROPPED FILES:"
        for i,f in next,files do print(i, f) end
        dropTarget:setColour( dropTarget.ColourIds.backgroundColourId, bg )
    end)
    dropTarget:fileDragEnter(function(files, x, y)
        dropTarget:setColour( dropTarget.ColourIds.backgroundColourId, active )
    end)
    dropTarget:fileDragExit(function(files, x, y)
        dropTarget:setColour( dropTarget.ColourIds.backgroundColourId, bg )
    end)

    --
    -- Luce Initialisation
    app:initialised(function()
    end)

    local bgText = luce:Colour(Colours.black):withAlpha(0.5)
    mc:paint(function(g)
        g:setFont(24.0)
        g:setColour( bgText )
        g:drawText("Drop a file here!", mc:getLocalBounds(), luce.JustificationType.centred, true);
    end)

    --
    -- set components visible
    mc:setSize(wsize)
    mc:addAndMakeVisible(dropTarget)

    dw:setBackgroundColour( luce.Colours.peru )
    dw:setContentOwned( mc, true )

    ---
    dw:setSize(wsize)
    dw:setVisible(true)
    dw.nativeTitleBar = false
    dw:setResizable(false,false)
    return dw
end

return app:start(MainWindow)
