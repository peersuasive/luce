#!/usr/bin/env lua

package	= 'luce'
version	= 'scm52-0'
source	= {
	url	= 'git://github.com/peersuasive/luce.git'
}
description	= {
	summary	= "GUI toolkit for Lua based on JUCE.",
	detailed	= '',
	homepage	= 'https://peersuasive.com/luce',
	license	= 'GPLv3',
}
dependencies = {
    "lua = 5.2",
}

build	= {
	type	= 'command',
    platforms = {
        linux = {
            build_command = "cd Builds/Linux && make CONFIG=Release AUDIO=0 LUA_V=52",
            install = {
                lib = { ["luce.core"] = "Builds/Linux/build52/core.so" },
            },
        },
        mingw32 = {
            build_command = "cd Builds/MingW && ./wrapper-52 CONFIG=Release AUDIO=0",
            install = {
                lib = { ["luce.core"] = "Builds/MingW/build52/core.dll" },
            },
        },
    },

    install = {
        lua = { 
            luce = "Source/lua/luce.lua",
            ["luce.init"] = "Source/lua/luce/init.lua",
            ["luce.LClass"] = "Source/lua/luce/LClass.lua",
            ["luce.LRectangle"] = "Source/lua/luce/LRectangle.lua",
            ["luce.LAffineTransform"] = "Source/lua/luce/LAffineTransform.lua",
            ["luce.LAnimatedPosition"] = "Source/lua/luce/LAnimatedPosition.lua",
            ["luce.LApplication"] = "Source/lua/luce/LApplication.lua",
            ["luce.LClass"] = "Source/lua/luce/LClass.lua",
            ["luce.LCommon"] = "Source/lua/luce/LCommon.lua",
            ["luce.LDocument"] = "Source/lua/luce/LDocument.lua",
            ["luce.LEventCentral"] = "Source/lua/luce/LEventCentral.lua",
            ["luce.LImageComponent"] = "Source/lua/luce/LImageComponent.lua",
            ["luce.LLine"] = "Source/lua/luce/LLine.lua",
            ["luce.LPoint"] = "Source/lua/luce/LPoint.lua",
            ["luce.LRange"] = "Source/lua/luce/LRange.lua",
            ["luce.LRectangle"] = "Source/lua/luce/LRectangle.lua",
            ["luce.LRectangleList"] = "Source/lua/luce/LRectangleList.lua",
            ["luce.LRectanglePlacement"] = "Source/lua/luce/LRectanglePlacement.lua",
            ["luce.deepcopy"] = "Source/lua/luce/deepcopy.lua"
        },
    },

    copy_directories = { "examples" },
}
