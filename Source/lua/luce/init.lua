--[[
LUCE Loader

(c) 2014, Peersuasive Technologies
--]]

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
    "Rectangle",
    "RectangleList",
    "AffineTransform",
    "Point",
    "Line",
    "RectanglePlacement",
    "ImageComponent",
}

local xmeta = setmetatable({
        new = function(self, dbg)
            local luce = dbg and require"luce.core_d" or require"luce.core"
            return load_luce(_, luce)
        end
    }, 
    {
    __call = function(self, dbg)
        local luce = dbg and require"luce.core_d" or require"luce.core"
        if(dbg)then LDEBUG=true end
        
        local luce_m = load_luce(_, luce)
        -- load lua modules
        for _,m in next, LModules do
            local mm = require("luce.L"..m)( luce )
            --luce_m[m] = function(self,...) return mm(...) end
            local mt = getmetatable(mm)
            mt.__call = function(self,...) return mm(...) end
            luce_m[m] = setmetatable(mm, mt)
        end
        -- bitwise
        luce_m.bit = bit or bit32 or require"luce.bit.numberlua"
        -- deepcopy, goes to table.deepcopy
        require"luce.deepcopy"

        return luce_m
        --return(load_luce(_, luce))

    end,
})

--module(...)
return xmeta
