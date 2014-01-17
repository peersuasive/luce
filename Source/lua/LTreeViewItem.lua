--[[
LUCE TreeViewItem for JSON

(c) 2014, Peersuasive Technologies
--]]

local luce, LItem
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
 
    item = LItem( id, val, istop,
        function(...)self.itemDoubleClicked(self, ...)end,
        function(...)
            if(self.parent)then 
                self.parent:setDefaultOpenness( not(self.parent:areItemsOpenByDefault()) )
                self.parent:refresh()
            end 
        end
    )
    return item
    --[[
    item = require"LItem"( id, val, istop, 
        function(...)self.itemDoubleClicked(self, ...)end,
        function(...)
            if(self.parent)then 
                self.parent:setDefaultOpenness( not(self.parent:areItemsOpenByDefault()) )
                self.parent:refresh()
            end 
        end
    )
    return item
    --]]
end

local function isArrayxx(t)
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

local function isArray(t)
    return ("table"==type(t)) and (#t~=0)
end
local function isTable(t)
    if ("table"==type(t)) then
        local count = false
        for _,v in next, t do
            count=true
            return true
        end
        --return (t~=0) or (count~=0), #t, (count>0 and count-#t or 0)
        return (#t~=0)
        --[[
        if (count==0) then return false,0,0 end -- empty
        if (#t~=0) and (count~=#t) then return true, #t, (count-#t) end
        return false, #t, (count>0 and count-#t or 0)
        --]]
    end
    return false, 0, 0
end

local function itemOpennessChanged(self, isNowOpen)
    if (isNowOpen) then
        if ( self:getNumSubItems() == 0 ) then
            if ( isArray(self.json) ) then
                for i, child in next, self.json do
                    local id = child.userid
                    local item = new({}, id, child, self.parent )
                    self:addSubItem( item )
                end
            else
                if ( isTable(self.json) ) then
                    for id, child in next, self.json do
                        if not ( id == "userid" ) then
                            local item = new({}, id, child, self.parent )
                            self:addSubItem( item )
                        end
                    end
                end
            end
            items = {}
        end
    else
        if not(self.name == "nil") then
            self:clearSubItems()
        end
    end
end

new = function(self, name, json, parent)
    --local self = self or setmetatable({}, {__mode="v"})
    local self = {}
    self.name = name
    self.json = json
    self.parent = parent
    self.childs = setmetatable({}, {__mode="v"})

    local tvi = luce:TreeViewItem()
    --tvi:isManaged( true )
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
    --function self:addSubItem(item)
    --    self.childs[#self.childs+1] = item
    --    tvi:addSubItem(item)
    --end
    --function self:addSubItemSorted(item)
    --    tvi:addSubItem(item)
    --end
    --function self:clearSubItems()
    --    tvi:clearSubItems()
    --    self.childs = setmetatable({}, {__mode="v"})
    --    collectgarbage()
    --end
    --function self:getUniqueName(...)
        tvi:getUniqueName(function(...)
            return self.name
        end)
    --end
    tvi:mightContainSubItems(function(...)
        return ("table"==type(self.json))
    end)

    tvi:itemOpennessChanged(function(isNowOpen)
        return itemOpennessChanged(self, isNowOpen)
    end)

    tvi:compareElements(function(a, b)
        return (string.lower(a) < string.lower(b)) and -1 or 1
    end)
    -- use
    --[[
    tvi:paintItem(function(...)
       local field = self.name
       local value;
       if ( self.json and not ( field and ("table"==type(self.json)) ) ) then
           if ( field and not("table"==type(self.json)) ) then
               field = field..":"
           end
           if not field and ("table"==type(self.json)) then
               value = "[Array]"
           else
               value = self.json
           end
       end
       return field..(value or"")
    end)
    --]]

    -- or
    
    ---[[
    tvi:createItemComponent(function(...)
        return createItemComponent(self)
    end)
    --]]

    -- or none at all

    --local mt = tvi.methods
    --require"pl.pretty".dump( tvi.methods )
    ---[[
    local self = setmetatable(self, {
        __index = tvi.__index
    })
    return self
    --]]
    --return self
end

local mt = {}
mt.__index = mt
local xmeta = setmetatable( {}, {
    __call = function(self,debug, ...)
        local self = self or {}
        luce = require(debug and"luce_debug"or"luce")
        LItem = require"LItem"(debug)
        self = setmetatable({}, {
            __call = new,
            __tostring = function()return"LTreeViewItem"end,
        })
        return self
    end,
    --__tostring = function()return"LTreeViewItem"end,
    --[[
    __gc = function(t)
        t.tvi:isManaged(false)
    end
    --]]
})

module(...)
return xmeta
