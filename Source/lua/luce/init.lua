--[[----------------------------------------------------------------------------

  Luce - init.lua

  Luce Internal

  Luce module loader entry point

  Loads all lua classes and put Luce in _G environment

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local function load_luce(self, core)
    local LClass = require"luce.LClass"
    local mt = {}
    for k,v in next, core do
        if ("table"==type(v)) then
            mt[k] = v
        elseif k:match("^[A-Z]") then
            --[[
            local l = LClass( v() )
            mt[k] = function(self,...) return l(...) end
            --]]
            ---[[
            local loaded = v()
            local l = LClass( loaded )
            lmt = { new = function(self,...) return l(...) end }
            for a,b in next, loaded do lmt[a] = b end
            mt[k] = setmetatable(lmt, {
                __call = function(self,...) return l(...) end,
            })
            --]]
        else
            mt[k] = v
        end
    end

    -- pure lua modules
    --local LRectangle = require"luce.LRectangle"
    --local LRectangleList = require"luce.LRectangleList"
    --mt.Rectangle = function(self, ...) return LRectangle(...) end
    --mt.RectangleList = function(self, ...) return LRectangleList(...) end

    local xmeta = setmetatable(mt, {
        __index = mt
    })
    return xmeta
end

local LModules = {
    "Document",
    "Rectangle",
    "Range",
    "RectangleList",
    "AffineTransform",
    "Point",
    "Line",
    "RectanglePlacement",
    "ImageComponent",
    "AnimatedPosition",
    "EventCentral",
}

local function init(self,dbg)
    if(dbg)then _G.LDEBUG=true end
    local luce = dbg and require"luce.core_d" or require"luce.core"
    local luce_m = load_luce(_, luce)
    luce_m.class = require"luce.LCommon".class
    luce_m.comp = require"luce.LCommon".comp

    -- bitwise
    luce_m.bit = bit or bit32 or require"luce.bit.numberlua"
    -- deepcopy, goes to table.deepcopy
    require"luce.deepcopy"
    _G.Luce = luce_m

    -- load lua modules
    for _,m in next, LModules do
        local mm = require("luce.L"..m)
        --luce_m[m] = function(self,...) return mm(...) end
        luce_m[m] = setmetatable({}, {
            __index = getmetatable(mm).__index,
            __tostring = getmetatable(mm).__tostring,
            __call  = function(self,x,...)
                -- when using . or :
                if(luce_m==x)then return mm(...) else return mm(x,...) end
            end
        })
    end
    return luce_m
end

return setmetatable({ new = init, }, {
    __call = init
})
