#!/usr/bin/env luajit

--[[
LUCE TreeView XML Example

(c) 2014, Peersuasive Technologies
--]]

local dump = require"pl.pretty".dump

local args = { unpack(arg or {}) }

local strip = function(s)
    return s:gsub("^xs:","")
end
local t = {}
function memoize(s)
    if not ("string"==type(s)) then return s end
    if t[s] then return t[s] else
        t[s] = s:gsub("^xs:","") return t[s] end
end

local debug
if args and args[1] and args[1]:match("^[Dd]") then
    debug = true
    table.remove(args, 1)
end
local luce = require"luce"(debug)

local mainWindow = luce:JUCEApplication("LJUCEApplication")
local dw = luce:DocumentWindow("Document Window")
local mc = luce:MainComponent("Main Component")
mc.size = {1,1}

local XMLTreeViewItem = require"XMLTreeViewItem"(luce)

local data = require"XmlParser":ParseXmlFile(assert(args[1], "Missing input file"))
local doc = { Attributes = data.Attributes, Name = data.Name }
doc.Attributes.fo = nil
doc.Attributes.dlg = nil
doc.Attributes.dxf = nil

data = data.ChildNodes
local openness = args[2] and ((args[2]==1) or (args[2]=="true")) or false
local hasBeenOpened = openness
local filter = args[3]

dw.name = doc.Name and "Document Type: ["..doc.Name.."]" or dw.name

local tv = luce:TreeView("TreeView")
tv:setColour( tv.ColourIds.backgroundColourId, "grey" )
tv.openCloseButtonsVisible = true
tv.multiSelectEnabled = true
tv.rootItemVisible = false
tv.defaultOpenness = openness

local tvi = XMLTreeViewItem(nil, data, tv, filter, 0)
tv.rootItem = tvi
tvi:sortSubItems()

local function recur(t, state)
    if not t then return end
    if ( t:mightContainSubItems() ) then --and not( t:isOpen() == state ) ) then
        t.open = state
    end
    for i=0, t.numSubItems - 1 do
        recur(t:getSubItem(i), state)
    end
end

local function testPattern(str, p)
    local s, r = pcall(string.match, str, p)
    if not s then return true end
    return r
end

local rootItems = {}
local prev_filter = nil
local filtering = false
function tv:refresh(filter_)
    local reg = filter_ and filter_:match("^r:")
    local filter_ = filter_ and (reg and filter_:sub(3) or filter_:lower())
    filter_ = filter_ and ( (filter_~="") and filter_ or "." )

    if ( filter_ and filter_~=prev_filter) then
        prev_filter = filter_
        tv.defaultOpenness = false
        local pending = {}
        for i=#rootItems, 1, -1 do
            local t = rootItems[i]
            local un = t.uniqueName
            if (
                not(reg) and un:lower():match(filter_) 
                or (reg and testPattern(un, filter_))
            ) then
                pending[#pending+1] = t
                rootItems[i] = nil
            end
        end
        for i=tvi.numSubItems-1, 0, -1 do
            local un = tvi:getSubItem(i).uniqueName
            if not (
                not(reg) and un:lower():match(filter_) 
                or (reg and testPattern(un, filter_))
            ) then
                rootItems[#rootItems+1] = tvi:getSubItem(i)
                tvi:removeSubItem(i, false)
            end
        end
        for _,t in next, pending do tvi:addSubItemSorted(t) end pending = nil

    elseif(filter_) then
        return
    else
        local state = not(tv.defaultOpenness)
        if ( state ) then
            for i=0, tvi.numSubItems-1 do
                local t = tvi:getSubItem(i)
                recur( tvi:getSubItem(i), state )
            end
        else
            for i=0, tvi:getNumSubItems()-1 do
                local t = tvi:getSubItem(i)
                if ( t and t:mightContainSubItems() ) then
                    t.open = state
                end
            end
        end
        tv.defaultOpenness = state
    end
end
--
local filterBox = luce:TextEditor("filterBox")
filterBox:setSize{1,1}
filterBox.text = filter or ""

-- credits to https://github.com/lua-nucleo/lua-nucleo
local escape_lua_pattern
do
  local matches =
  {
    ["^"] = "%^";
    ["$"] = "%$";
    ["("] = "%(";
    [")"] = "%)";
    ["%"] = "%%";
    ["."] = "%.";
    ["["] = "%[";
    ["]"] = "%]";
    ["*"] = "%*";
    ["+"] = "%+";
    ["-"] = "%-";
    ["?"] = "%?";
    ["\0"] = "%z";
  }

  escape_lua_pattern = function(s)
    return (s:gsub(".", matches))
  end
end

filterBox:textEditorTextChanged(function(...)
    if not(filterBox.text:match("^r:")) then
        filter = escape_lua_pattern(filterBox.text)
        filter = (filter=="") and "." or filter
        tv:refresh(filter)
    else
        filter = filterBox.text--:sub(3)
        tv:refresh(filter)
    end
end)

filterBox:textEditorReturnKeyPressed(function(...)
    if ( filterBox.text:match("^r:") ) then
        filter = filterBox.text --:sub(3)
        tv:refresh(filter)
    end
end)

filterBox:textEditorEscapeKeyPressed(function(...)
    filterBox:setText("", true)
    mc:unfocusAllComponents()
    filter="."
    tv:refresh(filter)
end)

local propBox = luce:TextEditor("Property Box")
propBox:setSize{1,1}
propBox:removeListener()
propBox.scrollbarsShown = true
propBox:setMultiLine( true, false )
propBox.readOnly = true
propBox.caretVisible = false
propBox.popupMenuEnabled = false

for k, v in next, doc.Attributes do
    propBox.text = propBox.text .. string.format("%s: %s\n", k,v)
end

propBox:setColour( propBox.ColourIds.backgroundColourId, "grey" )

local slm = luce:StretchableLayoutManager("left")

local slr = luce:StretchableLayoutResizerBar( "resizer", slm, 1, true )
slr:mouseDoubleClick(function(mouseEvent)
    local bounds = luce:Rectangle(mc:getLocalBounds()):reduced(5)
    local next_x;
    if (slr.hidden) then
        next_x = (slr.hidden * -1)
        slr.hidden = nil
    else
        local b = luce:Rectangle( slr:getBounds() )
        next_x = bounds.w
        slr.hidden = bounds.w - (b.x + b.w)
    end
    local e = mouseEvent:withNewPosition( { next_x, mouseEvent.y } )
    slr:mouseDrag( e )
end)

slm:setItemLayout( 0, {100, -1.0, -0.7} );
slm:setItemLayout( 1, {1, 10, 10} );
slm:setItemLayout( 2, {1, -0.6, 250} );

mc:resized(function(...)
    local bounds = luce:Rectangle(mc:getLocalBounds()):reduced(5)
    slm:layOutComponents( {"", slr, ""}, { bounds.x, bounds.y, bounds.w, bounds.h }, false, true)
    local props = bounds:withTrimmedLeft(5)
    props.x = slr:getX() + slr:getWidth()
    props.w = bounds.w - slr:getX() - 5
    bounds.w = slr:getX() -5

    local lbounds = bounds:removeFromTop(30):withTrimmedBottom(5)
    filterBox:setBounds( lbounds )
    tv:setBounds( bounds )

    propBox:setBounds( props )
end)

-- initialise callback, where components are displayed
mainWindow:initialise(function(...)
    filterBox:setSize{1,1}
    propBox:setSize{1,1}
    mc:addAndMakeVisible( filterBox )
    mc:addAndMakeVisible( propBox )
    mc:addAndMakeVisible( tv )
    tv:setBounds { 0, 0, 800, 600 }
    mc:addAndMakeVisible( slr )
    dw:setContentOwned( mc, true )
    dw:centreWithSize{800, 600}
    dw:setLookAndFeel(4);
    dw:setVisible(true)
    return dw
end)

--- callback used when quit is asked
local stop_now = false
mainWindow:systemRequestedQuit(function(...)
    stop_now = true
    mainWindow:shutdown()
    mainWindow:quit()
end)

--- main loop
--luce:start( mainWindow )
---[[
luce:start_manual( mainWindow, function(...)
    return stop_now
end )
--]]

luce:shutdown() -- in any case, call this to close cleanly
