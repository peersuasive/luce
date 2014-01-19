#!/usr/bin/env lua

package	= 'luce'
version	= 'scm-0'
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
    "lua >= 5.1", "lua <= 5.2",
}

build	= {
	type	= 'command',
    platforms = {
        linux = {
            build_command = "cd Builds/Linux && make CONFIG=Release TARGET=core.so",
            install = {
                lib = { ["luce.core"] = "Builds/Linux/build/core.so" },
            },
        },
        mingw32 = {
            build_command = "cd Builds/MingW && ./wrapper CONFIG=Release TARGET=core.dll",
            install = {
                lib = { ["luce.core"] = "Builds/MingW/build/core.dll" },
            },
        },
    },

    install = {
        lua = { 
            luce = "Source/lua/luce.lua",
            ["luce.init"] = "Source/lua/luce/init.lua",
            ["luce.LClass"] = "Source/lua/luce/LClass.lua",
            ["luce.LRectangle"] = "Source/lua/luce/LRectangle.lua",
        }
    },

    copy_directories = { "examples" },
}
