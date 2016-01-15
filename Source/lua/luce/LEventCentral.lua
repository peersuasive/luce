--[[----------------------------------------------------------------------------

 EventCentral.lua

 A (quite) naive (possibly asynchronous) message broadcaster

    TODO: see https://github.com/Salmito/leda for a possible implementation
              or adapt with gadokai

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014-2016, Peersuasive Technologies

------------------------------------------------------------------------------]]

--[[
example:

local ec = luce:EventCentral()
ec:register("greetings", function(...) print("Hello", ...) end)

...

local ec = luce:EventCentral()
ec:broadcast("greetings", "John Doe")


If app is started with a controlled loop, events will be broadcasted asynchronously by the loop,
otherwise, they'll be broacasted synchronously

--]]

-- TODO: when using with LLC, try to unregister first...

local app, luce = _G.App, _G.Luce
local className = "LEventCentral"
local ec = {}
-- LLIVE
if(LUCE_LIVE_CODING)then
    if not(app.EventCentral)then
        app.EventCentral = { clear = _G.LDEBUG and function()ec={}end or function()end }
    end
end
-- LLIVE

local mt = {
    broadcast = function(event,...)
        if not ec[event] then return nil, "Event not registered" end
        for l in next, ec[event] or {} do
            if(app.ControlEvent)then
                app.ControlEvent:attachEvent(l,'default',...)
            else
                l(...)
            end
        end
        return true
    end,
    register = function(event, cb)
        if not("function"==type(cb))then return nil, "Callback not found or not a function" end
        local l = ec[event] or {}
        -- debug
        if _G.LDEBUG then if(l[cb])then print "WARNING: already registered" end end
        l[cb] = true
        ec[event] = l
        return true
    end,
    unregister = function(event, cb)
        if(ec[event])then
            ec[event][cb] = nil
        end
    end,

    isRegistered = function(event)
        return ec[event] and true or false
    end,
}
local function new()
    app = app or _G.App
    return setmetatable({}, {
        __index = mt,
        __self = className,
    })
end
return setmetatable({}, {
    __call = new,
    __tostring = function()return className end,
})
