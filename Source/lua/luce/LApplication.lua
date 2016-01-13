--[[----------------------------------------------------------------------------

LApplication.lua

Create a Luce Application adapted to the host/target OS

Usage: 

    local app, luce = require"luce.LApplication"(app_name)

Provides the following methods and parameters:

 At instanciation, LApplication returns the instanciated class and the luce class
 and sets the *global* variables LDEBUG, App and Luce.

 parameters:
       args: command line or event parameters
         os: OS on which the app is running: unix, linux, osx, android, ios or win

    methods:
      start: the method starting the main loop
              parameters:
                  manual: bool      (false)  gives control over the main loop (not supported by iOS and Android a.t.m.)
             osx_delayed: bool      (false)  if we want OS X app to start with a window or wait for user actions, like dropping a file, etc.
                callback: function  (nil)    a callback to provide controlled loop with

       exit: quit the application
              parameters:
                  status: number    (0)      exit code

        log: write to log in system's temp folder
   logError: write an error to log and exit with status 1
   logDebug: write a debug trace to log


    @alias meta

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 

(c) 2014, Peersuasive Technologies

------------------------------------------------------------------------------]]

local LDEBUG = _G.LDEBUG
local luce   = nil

local className = "LApplication"

local mt = {}
mt.__index = mt

local function new(name, prog, ...)
    local name = name or className
    local args = {...}
    -- pre-declaration
    local self = {
        prog     = prog,
        args     = args,
        name     = name,
        log      = nil,
        logError = nil,
        logDebug = nil,
        start    = nil,
        exit     = nil,
        os       = nil,
        has_initialised = false,
    }

    ---
    -- specific useful directories and parameters
    ---
    local OS      = {
        unix      = os.getenv("HOME") and true,
        win       = os.getenv("HOMEDRIVE") and true,
        linux     = nil,
        osx       = (os.getenv("HOME") or ""):match("^/Users") and true,
        ios       = (os.getenv("HOME") or ""):match("^/var/mobile") and true,
        android   = os.getenv('ANDROID_DATA') and true,
    }
    OS.linux      = OS.unix and not(OS.osx or OS.ios or OS.android)
    OS.is_mobile  = (OS.ios or OS.android)
    OS.is_desktop = not(OS.is_mobile)
    local sep     = (OS.unix or OS.android) and "/" or "\\"
    local so      = OS.unix and "so" or "dll"
    OS.sep        = sep
    self.os       = OS

    local HOME    = luce.JUCEApplication.userHomeDirectory()
    local DOCS    = luce.JUCEApplication.userDocumentsDirectory()
    local DATA    = luce.JUCEApplication.userApplicationDataDirectory()
    local TMP     = (OS.linux or OS.osx or OS.ios) and "/tmp" or luce.JUCEApplication.tempDirectory()
    local has_stdout = (OS.linux or OS.win) and true

    -- some default path when semi-embedded
    -- look in $HOME/.luce for classes and modules first
    -- NOTE: should add ./ too
    if not(OS.win)then
    local rel_path = prog:match("(.*)/[^/]+$") or "."
    local luce_lib = rel_path.."/lib/?.so;"..rel_path.."/lib/?/?.so;"
    luce_lib       = luce_lib..HOME.."/.luce/lib/?.so;"..HOME.."/.luce/lib/?/?.so;" -- "~/.luce/lib/?.so;~/.luce/lib/?/?.so"
    luce_lib       = luce_lib..HOME.."/.luce/lib/?.dylib;"..HOME.."/.luce/lib/?/?.dylib;"
    luce_lib       = luce_lib.."./lib/?.so;./lib/?.dylib;./lib/?/?.so;./lib/?/?.dylib;"

    local luce_lua = rel_path.."/lua/?.lua;"..rel_path.."/lua/?/?.lua;"
    luce_lua       = luce_lua..rel_path.."/lua/init.lua;"..rel_path.."/lua/?/init.lua;"
    luce_lua       = luce_lua..HOME.."/.luce/lua/?.lua;"..HOME.."/.luce/lua/?/?.lua;"
    luce_lua       = luce_lua.."./lua/?.lua;./lua/?/?.lua;./lua/init.lua;./lua/?/init.lua;"

    local luce_cls = rel_path.."/classes/?.lua;"..rel_path.."/classes/?/?.lua;"
    luce_cls       = luce_cls..rel_path.."/classes/init.lua;"..rel_path.."/classes/?/init.lua;"
    luce_cls       = luce_cls.."./classes/?.lua;./classes/?/?.lua;./classes/init.lua;./classes/?/init.lua;"
    package.path   = luce_lua..package.path
    package.path   = luce_cls..package.path
    package.cpath  = luce_lib..package.cpath

    self.pre_path  = rel_path
    else -- windows... is p* us off
    local rel_path = prog:match("(.*)\\[^\\]+$") or "."
    local luce_lib = rel_path.."\\lib\\?.dll;"..rel_path.."\\lib\\?\\?.dll;"
    luce_lib       = luce_lib..HOME.."\\_luce\\lib\\?.dll;"..HOME.."\\_luce\\lib\\?\\?.dll;"
    local luce_lua = rel_path.."\\lua\\?.lua;"..rel_path.."\\lua\\?\\?.lua;"
    luce_lua       = luce_lua.."\\_luce\\lua\\?.lua;"..HOME.."\\_luce\\lua\\?\\?.lua;"
    package.path   = luce_lua..package.path
    package.cpath  = luce_lib..package.cpath

    self.pre_path  = rel_path
    end

    ---
    -- utils
    ---
    local log_file = (LDEBUG or not(has_stdout))
                        and io.open(TMP..sep.."luce."..name..".log", "wb")
                        or io.stdout
    
    -- TODO: depending on OS, choose to save in log
    --       or to display an alert window (Windows and Mac OS X, for instance)
    local function log(msg, ...)
        local msg = (msg or "").."\n"
        log_file:write(string.format(msg, ...))
        log_file:flush()
    end
    local function logError(msg, ...)
        local msg = "Error: "..(msg or "")
        log(msg, ...)
        if(self.has_initialised)then
            self:quit(1)
        else
            os.exit(1)
        end
    end
    local logDebug
    if(LDEBUG)then
        logDebug = function(msg, ...)
            local msg = "DEBUG: "..(msg or "")
            log(msg, ...)
        end
    else logDebug = function()end end

    self.log      = log
    self.logError = logError
    self.logDebug = logDebug
    _G.Log        = log
    _G.LogError   = logError
    _G.LogDebug   = logDebug

    local function shift(i)
        local i = i or 1
        local v = args[i]
        table.remove(args, i)
        return v
    end
    local _assert = assert
    local function assert(truth, ...)
        if(truth)then return truth end
        logError(...)
    end

    function self:getRes(res_path, as_bin)
        -- TODO: return content if embedded and explicitly asked
        --       or dump embedded content and return path
        return (LPATH or self.pre_path) .. OS.sep .. res_path
    end

    ---
    -- LApplication Class initialisation
    ---
    local lapp        = luce:JUCEApplication(name)
    local MainClass   = nil -- provided by start
    local backgroundColour = luce.Colours.white

    -- called once :initialise has finished and DocumentWindows is visble
    local initialised_callback = function()end
    lapp:initialised(function(...)
        if (OS.android or OS.ios) then --and not(self.initialised) then
            HOME     = luce.JUCEApplication.userHomeDirectory()
            DOCS     = luce.JUCEApplication.userDocumentsDirectory()
            DATA     = luce.JUCEApplication.userApplicationDataDirectory()
            TMP      = luce.JUCEApplication.tempDirectory():gsub(".temp$","")
            if(OS.android)then
                log_file = io.open(TMP.."/luce."..name..".log", "wb") or io.stdout
            end
        end

        TMP2 = luce.JUCEApplication.tempDirectory():gsub(".temp$","")
        logDebug("dirs: home: %s, docs: %s, data: %s, tmp2: %s",HOME, DOCS, DATA, TMP2)

        initialised_callback()
    end)

    -- provides the method for programmer as they may want to start some
    -- processes only once the application is fully initialised
    function self:initialised(func)
        if("function"==type(func))then initialised_callback = func end
    end

    -- wrapper to LUCEApplication :initialise
    local function initialise(...)
        self.has_initialised = true
        local extra = (... and not(tostring(...)=="") and {...}) or {}
        local params = {}
        for _,v in next,args  do params[#params+1] = v end
        for _,v in next,extra do params[#params+1] = v end
        return MainClass(params)
    end

    ---
    -- LApplication implementation
    ---

    -- mainly used by mobile devices
    lapp:suspended(function(...)
        logDebug("SUSPENDED")
    end)

    -- mainly used by mobile devices
    lapp:resumed(function(...)
        logDebug("RESUMED")
        -- on Android, this is called at least once, 
        -- when application is about to start
        -- on this first call, there's not display yet, so components can't be made visible,
        -- and any attempt to do so will crash the app
        -- we have to wait for initialise to be called for this
    end)

    -- mainly use by OS X
    local delayed = false
    local anotherInstanceStarted_callback = function()end
    lapp:anotherInstanceStarted(function(...)
        logDebug("ANOTHER INSTANCE STARTED")
        if (OS.osx and delayed) then
            return initialise(...)
        else
            return anotherInstanceStarted_callback()
        end
    end)

    -- 
    function self:anotherInstanceStarted(func)
        if("function"==type(func))then anotherInstanceStarted_callback = func end
    end

    -- used by all platforms
    lapp:initialise(function(...)
        logDebug("INITIALISE (general)")
        -- most of all, except osx in some cases, like when an argument, like a file, is
        -- required to start
        if not(OS.osx) or (OS.osx and not(delayed)) then
            return initialise(...)
        end
    end)
    
    -- start the main loop
    function self:start(mainClass, wants_control, wants_osx_delayed)
        local t = type(wants_control)
        local ms, cb
        if("table"==t) then
            cb, ms = wants_control[1], wants_control[2]
        else
            cb, ms = wants_control, 0
        end

        if(LUCE_LIVE_CODING)then
            return mainClass, cb, ms
        end
        if(wants_control) and not("function"==t or "table"==t)then
            return nil, 
                string.format("Control callback: expected function, got '%s'", type(wants_control))
        end
        delayed = wants_osx_delayed
        MainClass = mainClass
        if(cb) and not(OS.android or OS.ios)then
            return luce:start_manual( lapp, ms, cb )
        else
            return luce:start( lapp )
        end
    end

    -- clean up environment when the application is about to close
    local shutdown_callback = function()end
    lapp:shutdown(function()
        if(log_file)then log_file:close() end
        shutdown_callback()
    end)

    -- provides the method to programmers as they may want to clean up
    -- or save some of their stuff before leaving
    function self:shutdown(func)
        if("function"==type(func))then shutdown_callback = func end
    end

    -- quit the application
    lapp:systemRequestedQuit(function()
        logDebug("SYSTEM REQUESTED QUIT")
        self:exit()
    end)
    local is_closing = false
    function self:exit(state)
        if is_closing then return "zob" end
        is_closing = true
        lapp:quit(status)
    end
    self.quit = exit

    -- disable some methods we don't want the programmer to call directly
    self.initialise = function()end
    self.anotherInstanceStarted = function()end
    self.systemRequestedQuit = function()end

    return setmetatable(self, {
        __index    = lapp,
        __newindex = lapp,
        __tostring = function() return className.."("..name..")" end
    }), luce
end

mt.__call = function(_, name, ...)
    -- first arg is program with relative path
    --local args = {...}
    --local prog = args[1] or (arg and arg[0]) or "."; table.remove(args,1)
    -- TODO: test if that still works when embedded
    local args, prog = {...}
    if (arg) then
        prog = arg[0]
    else
        prog = args[1] or "."
        table.remove(args,1)
    end
    if LPATH then prog = LPATH end
    lDEBUG  = args[1] and args[1]:match("^[Dd]$") and table.remove(args,1) and true
    luce    = require"luce"(lDEBUG)
    _G.App  = new(name, prog, unpack(args))
    return _G.App, luce, args
end

return setmetatable(mt, mt)
