--[[
LUCE TreeViewItem item object

(c) 2014, Peersuasive Technologies
--]]

if arg and arg[1] and arg[1]:match("^[Dd]") then
    print"DEBUG"
    package.cpath = "debug/?.so;"..package.cpath
else
    package.cpath = "./build/?.so;"..package.cpath
end
local luce = require"luce"

local function new(self, id, val, istop, dblClick)
    local comp  = luce:MainComponent():new("container")
    local field = luce:Label():new(id or "<root>")
    field.text = id or "<root>"
    field:setMinimumHorizontalScale( 100.0 );
    field:setJustificationType( field.JustificationType.centredLeft );
    --field:setColour( field.ColourIds.backgroundColourId, "red" )
    comp:addAndMakeVisible( field )
    comp:addMouseListener(true)
    comp:resized(function(...)
        field:setSize{ comp:getWidth(), comp:getHeight() }
    end)

    comp:mouseDoubleClick(function(mouseEvent)
        print("** mouse dbl click", mouseEvent)
        dblClick( mouseEvent )
    end)
    return comp
end

local mt = {}
mt.__index = mt
local xmeta = setmetatable( {}, {
    __call = new,
    __tostring = function()return"LItem"end
})

module(...)
return xmeta 
