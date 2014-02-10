--[[
LUCE TreeViewItem for JSON

(c) 2014, Peersuasive Technologies
--]]

-- pre-declarations
local luce, LItem
local new        

-- a default value for unnamed items, that is the root item
local ROOT = "ROOT"

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
 
    -- we're creating a new item (@see LItem for details)
    -- the first method just activate the TreeViewItem default action
    -- when left double-click happens
    -- the second function will open the whole tree by changing TreeView openness
    -- and refreshing the rootItem
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
        return (#t~=0)
    end
    return false
end

-- isNowOpen is a boolean provided by the callback
-- if we have an indexed array, then it's a root item
-- otherwise, if we have a table, it contains the fields with values
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
        end
    else
        -- we can clean hidden items to save some memort
        -- but we don't want to remove the top items
        -- ROOT is the root item, containing all the children
        if not(self.name == ROOT) then
            self:clearSubItems()
        end
    end
end


--
-- new instanciation method
--
new = function(self, name, json, parent)
    local self = {}
    self.name = name or ROOT
    self.json = json
    self.parent = parent
    self.childs = setmetatable({}, {__mode="v"})

    local tvi = luce:TreeViewItem()

    -- methods can be locally overriden 
    -- or reimplemented
    -- for a quicker access
    function self:getUniqueName(...)
        return self.name
    end

    -- callbacks are directly implemented
    tvi:getUniqueName(function(...)
        return self.name
    end)

    tvi:mightContainSubItems(function(...)
        return ("table"==type(self.json))
    end)

    tvi:itemOpennessChanged(function(isNowOpen)
        return itemOpennessChanged(self, isNowOpen)
    end)

    tvi:compareElements(function(a, b)
        return (string.lower(a) < string.lower(b)) and -1 or 1
    end)

    -- to render items, use
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

    -- or none at all, which defaults to paintItem, using getUniqueName

    return setmetatable(self, {
        -- we're reusing tvi's index but we could also
        -- loop at the beginning of new and put all methods
        -- in self -- not really sure there'll be a great performance
        -- gain, however
        __index = function(self,k)
            return tvi[k]
        end,
        __tostring = function(self)return "LJSONTreeViewItem("..self.name..")"end
    })
end

-- takes luce instanciation as a required argument, but we could just simply
-- load it from there
-- this is just to avoid having to select between debug or release
local xmeta = setmetatable( {}, {
    __call = function(self,core, ...)
        local self = self or {}
        luce = assert(core, "Missing luce core instance")
        LItem = require"LItem"(core)
        self = setmetatable({}, {
            __call = new,
            __tostring = function()return"LJSONTreeViewItem"end,
        })
        return self
    end,
})

return xmeta
