--[[
LUCE TreeViewItem for JSON

(c) 2014, Peersuasive Technologies
--]]

local luce = _G.Luce
local LItem = require"LItem"
local new
local className = "XMLTreeViewItem"

local memo = memoize
local ROOT = "ROOT"

local function getProperties(self)
    local field;
    local value;
    local istop = false;
    field = self.name
    if ( self.value and not ( field and ("table"==type(self.value)) ) ) then
        if ( field and not("table"==type(self.value)) ) then
            field = field..":"
        end

        if not field and ("table"==type(self.value)) then
            value = "[Array]"
        else
            value = self.value
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
                --self.parent:setDefaultOpenness( not(self.parent:areItemsOpenByDefault()) )
                self.parent:refresh()
            end 
        end
    )
    return item
end

local function isArray(t)
    return ("table"==type(t)) and (#t~=0)
end
local function isMixed(t)
    if ("table"==type(t)) then
        local count = 0
        for _,v in next, t do
            count=count+1
        end
        if (count==0) then return false,0,0 end -- empty
        if (#t~=0) and (count~=#t) then return true, #t, (count-#t) end
        return false, #t, (count>0 and count-#t or 0)
    end
    return false, 0, 0
end
local function isMap(t)
    local _,_,c = isMixed(t)
    return (c~=0)
end
local function isArrayEmpty(t)
    if ("table"==type(t)) then 
        for _,_ in next,t do return false end
    end
    return true
end

local function testPattern(str, p)
    local s, r = pcall(string.match, str, p)
    if not s then return true end
    return r
end

local _id = { true, "(", true, ")" }
local function itemOpennessChanged(self, isNowOpen)
    if (isNowOpen) then
        if ( self.numSubItems == 0 ) then
            if ( isArray(self.value) ) then
                local i = 0
                for xid, child in next, self.value do
                    i = i+1
                    if not(isArrayEmpty(child)) then
                        local xid = _id
                        xid[1] = child.Attributes.name or ""
                        xid[3] = memo(child.Name)
                        local id = table.concat(xid)
                        if ( (not(self.filter) and true) or testPattern(id, self.filter) ) then 
                            local attr = {Value=memo(child.Value), name=nil}
                            for k, v in next, child.Attributes do
                                attr[k] = memo(v)
                            end
                            for k,v in next, child.ChildNodes do
                                attr[k] = v
                            end
                            attr.name = nil
                            local item = new(_, id, attr, self.parent,_, self.level+i)
                            self:addSubItemSorted(item)
                        end
                    else
                        local item = new(_, xid, child, self.parent,_,self.level+i)
                        self:addSubItemSorted(item)
                    end
                end
            else
                if not isArrayEmpty(self.value) then
                    local i = 1
                    for id, value in next, self.value do
                        local value = memo(value)
                        i = i+1
                        local item = new(_, id, value, self.parent,_,self.level+i)
                        self:addSubItemSorted(item)
                    end
                end
            end
        end
    else
        if self.name~=ROOT then
            self:clearSubItems()
        end
    end
end

local function recurState(t, state)
    t.open = state
    for i=0, t.numSubItems-1 do
        recurState(t:getSubItem(i), state)
    end
end

new = function(_, name, value, parent, filter, level)
    local self = {}
    self.name = name or ROOT
    self.value = value
    self.parent = parent
    self.filter = filter
    self.level = level+1

    local tvi = luce:TreeViewItem()
    tvi:getUniqueName(function(...)
        return self.name
    end)
    tvi:mightContainSubItems(function(...)
        return ( not(isArrayEmpty(self.value)) )
    end)

    tvi:compareElements(function(a, b)
        local a = a:getUniqueName()
        local a_ = a:gsub("^s*",""):sub(1,1)
        a = a:gsub("^(", "")
        local b = b:getUniqueName()
        local b_ = b:gsub("^s*",""):sub(1,1)
        b = b:gsub("^(", "")
        if ( ( (a_ == "(") and ( a_ == b_ ) ) ) then
            return (string.lower(a) < string.lower(b)) and -1 or 1
        elseif ( a_ ~= "(" and b_ ~= "(" ) then
            return (string.lower(a) < string.lower(b)) and -1 or 1
        elseif ( a_ == "(" ) then
            return 1
        else
            return -1
        end
        return 0
    end)

    tvi:itemOpennessChanged(function(isNowOpen)
        return itemOpennessChanged(self, isNowOpen)
    end)

    tvi:itemDoubleClicked(function(mouseEvent)
        if ( mouseEvent.mods:isLeftButtonDown() ) then
            if not(isArrayEmpty(self.value)) then
                tvi.open = not(tvi.open)
            end
        else
            if(not(isArrayEmpty(self.value))) then
                recurState(tvi, not(tvi.open))
            end
        end
    end)

    ---[[
    tvi:paintItem(function(...)
        local field = self.name
        local value;
        local istop = false;
        if ( self.value and not ( field and ("table"==type(self.value)) ) ) then
            if ( field and not("table"==type(self.value)) ) then
                field = field..":"
            end

            if not field and ("table"==type(self.value)) then
                value = "[Array]"
            else
                value = self.value
            end
        else
            istop = true
        end
        return field..(value or"")
    end)
    --]]
    --[[
    tvi:createItemComponent(function(...)
        return createItemComponent(self)
    end)
    --]]
 
    return setmetatable(self, {
        __index = function(self,k) return tvi[k] end,
        __tostring = function(self)return "XMLTreeViewItem("..self.name..")"end
    })
end

return setmetatable({}, {
    __call = new,
    __tostring = function()return className end,
})
