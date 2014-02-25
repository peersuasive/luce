-- TODO: move these methods to a common class

-- only the main component (comp) is exposed by default
-- to expose sub-components methods, use new_vars
-- Usage: __vars.METHOD_TO_EXPOSE = LCOMPONENT_METHOD_BELONGS_TO
-- 
-- ex: 
-- local textEditor = luce:TextEditor()
-- __vars.setText = textEditor
--
local new_vars = setmetatable({}, {
    __call = function()
        return setmetatable({}, {
            __newindex = function(self,k,v)
                rawset(self, k, function(...) if(...)then v[k]=... else return v[k] end end)
            end
        })
    end
})

-- int_index is used to store nil's, so that __index don't call comp.__index
-- it belongs to self
local newint_index = function() return { __unlocal = function(t,k) int_index[k] = nil end } end

-- create a new self with relevant metamethods
local new_class_self = function(mt, comp, name)
    local mt = mt or { className = "LClass" }
    local __vars = new_vars()
    local int_index = newint_index()
    local comp = comp or {}
    local self = setmetatable({ 
        name = name or mt.className, 
        __self = comp.__self 
    }, {
        __newindex = function(t,k,v)
            int_index[k] = true
            rawset(t,k,v)
        end
    })
    return self, setmetatable({}, {
        __self = comp.__self,
        __index = function(x, k)
            if(rawget(self,k))then return rawget(self,k) -- self
            elseif(int_index[k]) then return nil         -- also self
            elseif(mt[k]) then return mt[k]          -- upper self
            elseif(__vars[k])then return __vars[k]() -- sub components or specifics, may override comp
            else return comp[k] end                  -- comp
        end,
        __newindex = function(t,k,v)
            if(__vars[k])then __vars[k](v)
            elseif(comp.__exists(k))then comp[k] = v
            else rawset(self,k,v) end
        end,
        __tostring = function(self)return mt.className.."("..self.name..")"end,
        __export   = function(f,c) __vars[f] = c end,
        __unexport = function(f) __vars[f] = nil end,
        __unlocal  = function(_,k) int_index[k] = nil rawset(self,k,nil) end,
    })
end

local new_comp_self = function(comp)
    local comp = comp
    local mt = getmetatable(comp)
    local _ind = mt.__index
    local _nind = mt.__newindex
    local lmt = mt
    lmt.__index = function(t,v)
        return rawget(comp,v) or _ind(comp,v)
    end
    lmt.__newindex = function(t,k,v)
        -- ignore fields, just override functions
        if("function"==type(v) and (rawget(comp,k) or comp[k])) then
            rawset(t,k,v)
        else
            -- FIXME: à débugger, ça peut venir d'ici, avec une confusion                                                            
            -- dans les mt, puisque celle de comp est modifiée ou bien                                                               
            -- de luce_m, ou de luce lui-même            
            _nind(comp,k,v)
        end
    end
    return setmetatable({}, lmt)
end
local function export(self, f, c)
    getmetatable(self).__export(f, c)
end
local function unexport(self, f, c)
    getmetatable(self).__unexport(f, c)
end
local function unlocal(self, f, c)
    getmetatable(self).__unlocal(f, c)
end

return { 
    comp = {
        self = new_comp_self,
        export = export,
        unexport = unexport,
        unlocal = unlocal,
    },
    class = {
        self = new_class_self,
        export = export,
    }
}
