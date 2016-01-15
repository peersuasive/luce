--[[----------------------------------------------------------------------------

LDocument.lua

This class wraps DocumentWindow to be portable accross supported platforms.

Usage:

    local dw = luce:Document(name)

The main usage remains the same as its JUCE equivalent.

However, it adds one new method:

    closeWindow(quit_if_last)

        closes the window and quits the application is this is the last remaining one,
        except on OS X, where it just closes the window, unless specified otherwise.

    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]
local LDEBUG = _G.LDEBUG
local luce   = _G.Luce
local app    = _G.App
local log, logError = app and app.log, app and app.logError

local className = "LDocument"

local mt = {}
mt.__index = mt

local function new(_, name, addToDesktop)
    local LDEBUG = _G.LDEBUG
    local luce   = _G.Luce
    local app    = _G.App
    local log, logError, logDebug = app.log, app.logError, app.logDebug

    local name = name or className
    -- pre-declaration
    local self = {
        name          = name,
        setFullScreen = nil,
        setSize       = nil,
        setBounds     = nil,
        closeWindow   = nil,
    }
    -- where we'll store overriden variables
    -- it's checked in self's metatable
    local override = { size = nil, bounds = nil }

    ---
    -- LDocument Class initialisation
    --
    -- we'll override some methods to have a correct behaviour
    -- on every platforms
    --
    -- for instance, there's no need to set bounds of the Document
    -- on mobile devices as we'll want it to be fullscreen anyway
    ---
    local this   = luce:DocumentWindow(name, addToDesktop)
    local bounds = {0,0,800,600}
    local size   = {800, 600}

    -- TODO: set bounds instead of size, getting current bounds if a Point
    --       is provided
    local function set_size(size, bounds)
        if not(this) then return end
        if app.os.ios or app.os.android then
            if not(this:isFullScreen()) then
                this:setFullScreen(true) -- or kiosk ?
            end
        else
            if(bounds)then
                this:setBounds(bounds)
            else
                this:centreWithSize(size)
            end
        end
    end
    function self:setFullScreen(state)
        if (app.os.ios or app.os.android) then
            return
        else
            if state == this:isKioskMode() then return end
            if("nil"==type(state))then state = not(this:isKioskMode()) end
            this:setKioskMode(state)
        end
    end

    function self:setSize(size)
        set_size(size)
    end
    override.size = function(v)
        if(v)then set_size(v)
        else return this.size end
    end
 
    function self:setBounds(b)
        bounds = b
        size = { b.w, b.h }
        set_size(size, bounds)
    end
    override.bounds = function(v)
        if(v)then set_size{v.w, v.h}
        else return this.bounds end
    end

    function self:closeWindow(quit_if_last)
        if(app.os.linux or app.os.win or quit_if_last)then
            this:closeWindow(true)
        else
            this:closeWindow(false)
        end
    end

    this:closeButtonPressed(function()
        self:closeWindow(false)
    end)
    function self:closeButtonPressed(func)
        if("function"==type(func))then
            this:closeButtonPressed(func)
        end
    end

    function self:setContentOwned(comp, resizeToFit)
        if(LUCE_LIVE_CODING)then
            this:setContentNonOwned(comp, resizeToFit)
        else
            this:setContentOwned(comp, resizeToFit)
        end
    end

    -- default shorcuts
    local K = string.byte
    this:keyPressed(function(k)
        local k, m = k:getKeyCode(), k:getModifiers()
        if not(app.os.osx) and (k==K"Q" or k==K"q") then
            app:exit()
        elseif (k==K"w" or k==K"W") and (m:isCommandDown() ) then
            self:closeWindow()
        else
            return false
        end
        return true
    end)

    self.__self = this.__self
    return setmetatable(self, {
        __self  = this.__self,
        __index = function(_,k)
            if(override[k])then return override[k]() -- look for overriden variables first
            else return this[k] end
        end,
        __newindex = function(_,k,v)
            if(override[k])then override[k](v)       -- id.
            else this[k]=v end
        end,
        __tostring = function() return className.."("..name..")" end
    })
end

return setmetatable(mt, {
    __call = new,
    __tostring = function()return className end,
})
