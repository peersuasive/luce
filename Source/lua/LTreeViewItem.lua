--[[
LUCE TreeViewItem for JSON

(c) 2014, Peersuasive Technologies
--]]

if arg and arg[1] and arg[1]:match("^[Dd]") then
    print"DEBUG"
    package.cpath = "debug/?.so;"..package.cpath
else
    package.cpath = "./build/?.so;"..package.cpath
end
local luce = require"luce"

local new -- pre-declaration

--
-- private methods
--
local function getProperties(self)
    local field;
    local value;
    local istop = false;
    field = self.name
    if ( self.json and not ( field and ("table"==type(self.json)) ) ) then
        if ( field and not("table"==type(self.json)) ) then
            field = field..":"
        end

        if not field and ("table"==type(self.json)) then
            value = "[Array]"
        else
            value = self.json
        end
    else
        istop = true
    end
    return {
        field = field,
        value = value,
        top = istop
    }
end

local function createItemComponent(self)
    local item = nil
    local values = getProperties(self);
    local id = values.field
    local val = values.value
    local istop = values.top
 
    item = require"LItem"( id, val, istop, function(...)self.itemDoubleClicked(self, ...)end )
    do return item end

    local field = luce:Label():new(id or "<root>")
    field.text = id or "<root>"
    field:setMinimumHorizontalScale( 100.0 );
    field:setJustificationType( field.JustificationType.centredLeft );
     
    if (istop) then
        item = field
    else
        local value = luce:Label():new(val or "<empty>")
        value.text = val or "<empty>"
        local comp = luce:Label():new("container")
        comp:setColour( comp.ColourIds.backgroundColourId, "red" )
        value:setMinimumHorizontalScale( 100.0 );
        value:setJustificationType( field.JustificationType.centredLeft );
        value:setColour( value.ColourIds.backgroundColourId, "blue" )
        --field:attachToComponent( value, true )
        value:toFront(false)
        value:setSize{ comp:getWidth(), comp:getHeight() }
        value:setVisible( true )

        comp:addAndMakeVisible( value )
        item = comp
    end
    return item
end

local function isArray(t)
    if ( t and ("table"==type(t)) ) then
        if ( #t>0 ) then
            return true
        end
        local count = false
        for _,v in next, t do
            count = true
            break
        end
        return count and t[1] or false -- indices = array, else = map
    end
    return false
end

local function itemOpennessChanged(self, isNowOpen)
    if (isNowOpen) then
        if ( self:getNumSubItems() == 0 ) then
            if ( isArray(self.json) ) then
                for i, child in next, self.json do
                    local id = child.userid
                    local item = new({}, id, child )
                    self:addSubItem( item )
                end
            else
                for id, child in next, self.json do
                    if not ( id == "userid" ) then
                        local item = new({}, id, child )
                        self:addSubItem( item )
                    end
                end
            end
        end
    end
end

new = function(self, name, json)
    local self = self or {}
    self.name = name
    self.json = json

    local tvi = luce:TreeViewItem():new()
    self.__self = tvi.__self
    for _,v in next, tvi.methods do
        self[v] = function(self,...)
            return tvi[v](self,...)
        end
    end
    -- remove or override some callbacks and internal methods
    -- ... mightContainSubItems...
    -- may have a table for callbacks and methods instead of just one for methods
    self["mightContainSubItems"] = nil
    self["itemOpennessChanged"] = nil

    function self:setUniqueName(name)
        self.name = name
    end
    function self:getUniqueName(...)
        return self.name
    end
    tvi:getUniqueName(function(...)
        return self.name
    end)
    tvi:mightContainSubItems(function(...)
        --print("*** mightContainSubItems", self.name or "<root>", ("table"==type(self.json)))
        return ("table"==type(self.json))
    end)

    tvi:itemOpennessChanged(function(isNowOpen)
        --print("** openness changed", isNowOpen)
        return itemOpennessChanged(self, isNowOpen)
    end)

    -- use
    -- tvi:paint(function(...)
    -- end)
    -- or
    -- tvi:createItemComponent(function(...)
    -- end)
    -- or none at all

    tvi:createItemComponent(function(...)
        return createItemComponent(self)
    end)

    --local mt = tvi.methods
    --require"pl.pretty".dump( tvi.methods )
    --return setmetatable(self, { __index = self } )
    return self
end

local mt = {}
mt.__index = mt
local xmeta = setmetatable( {}, {
    __call = new,
    __tostring = function()return"LTreeViewItem"end
})

module(...)
return xmeta 
