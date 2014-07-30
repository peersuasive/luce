====
Luce
====
------------------------------------
A GUI Module for Lua (based on JUCE)
------------------------------------

.. image:: http://peersuasive.github.io/images/lua-inside.png


``Luce`` 0.3.2 *trust in stilts* `released ! <https://github.com/peersuasive/luce/releases/tag/v0.3.2>`__

`Downloads`_ for Linux, Windows, OS X, iOS and Android are available.

What is ``Luce`` ?
==================

``Luce`` is a `Lua <http://lua.org>`_ module for GUI programming based
on the portable, embeddable, remarkable C++ library `JUCE <http://www.juce.com>`_.

It can be used as an ordinary module for pure lua 5.1/lua 5.2/luajit 2.X
scripts or as a library for C++/Lua projects.

Although based on JUCE, Luce isn't aiming at becoming a binding for JUCE,
though the low level API free of Luce features could be used as such.

Luce has Lua in mind and will be developped for lua developpers.

Lua essence is to be "``a powerfull, fast, lightweight embeddable scripting
language.``" And so would Luce be too.

Luce is light, fast and `easily portable
<https://github.com/peersuasive/luce_embeddable>`_, thanks to Lua and JUCE
itself.

As of now, it's supported on Linux, Windows and Mac OS X, with partial support
for iOS and Android.

Getting started
===============

1. `download`_ the lua module for your environment

2. put it somewhere in your lua modules path (ex: ``/usr/local/share/lua/5.1``)

- if you're on Linux, you can also use the provided `luarock
  <https://github.com/peersuasive/luce/raw/master/luce-scm-0.rockspec>`_

- if you don't know JUCE, you should consider having a look at its
  `documentation <https://www.juce.com/api/annotated.html>`__ as Luce low level
  API matches for the most part JUCE's own API.
  
  For more explanations, see `Differences with JUCE`_ and `Luce design`_


A first app: say hello
----------------------

.. code:: lua

    local title = "Hello World!"

    local app, luce = require"luce.LApplication"(title, ...) -- create a basic Application
                                                             -- with command line parameters

    local timer = luce:Timer() -- a timer for the animation

    local function MainWindow(args)  -- our main component class
                                     -- will receive command line arguments or starting events

        local app, luce = app, luce    -- just to put these in the local environment
        local Colours   = luce.Colours -- id.
        local wsize     = {800,600}    -- the size of our window
        local isPaused  = false        -- holds the animation state

        local mc = luce:MainComponent("MainComponent") -- our main component
        local documentWindow = luce:Document(title)    -- create a document window to hold the main component

        local button = luce:TextButton("quit")  -- a button to close the app
        button.buttonText = "Quit"              -- visible text of the button
        button:setLookAndFeel(4)                -- change look-and-feel
        button.bounds     = { 10, 10, 100, 20 } -- and position it (x,y,w,h)

        ---
        -- set some action on button click
        ---
        button:buttonClicked(function()
            app:quit()
        end)

        ---
        -- say hello to the world with a simple animation
        ---

        -- just a dumb function to increase font size and pick a predefined colour
        local currentSize, baseSize, maxSize = 12.0, 12.0, 32.0
        local colours    = { Colours.black, Colours.red, Colours.yellow, Colours.green, Colours.blue }
        local currentCol = 1
        local function changeSize()
            currentSize = (currentSize<maxSize) and currentSize+0.5 or baseSize
            currentCol  = (currentCol>#colours) and 1 or currentCol+1
            return currentSize, colours[currentCol]
        end

        -- draw the message
        mc:paint(function(g)
            -- draw a background
            g:fillCheckerBoard( luce:Rectangle(mc:getBounds()), 48, 48, Colours.lightgrey, Colours.white) 
            -- get new font size and colour
            local size, colour = changeSize()
            -- draw text
            g:setFont(size)
            g:setColour(luce:Colour(colour))
            g:drawText("Hello World!", mc:getLocalBounds(), luce.JustificationType.centred, true);
        end)

        -- animate it a bit via the timer callback
        timer:timerCallback(function()
            if(mc:isShowing() and not(isPaused))then
                mc:repaint()
            end
        end)
        timer:startTimer (1000/60)

        ---
        -- add some key shortcuts
        ---
        local K  = string.byte 
        local kc = setmetatable( 
            luce.KeyPress.KeyCodes, { __index = function()return 0 end } ) -- just a little trick to always get a valid keycode
                                                                           -- see https://www.juce.com/api/classKeyPress.html for
                                                                           -- available key-codes
        documentWindow:keyPressed(function(k)
            local k, m = k:getKeyCode(), k:getModifiers() -- get current key-code and modifiers status
            if (k==K"Q" or k==K"q") 
                    and (m:isCommandDown() or not(app.os.osx)) then -- if Q is pressed or, on OS X, cmd+Q
                app:exit(0)     -- close the application with an normal exit state (0 by default)

            elseif (k==K"w" or k==K"W") and (m:isCommandDown() ) then -- if cmd/ctrl + W is pressed
                documentWindow:closeWindow() -- close the window
                                             -- on Linux and Windows, this has the effect of closing the application too,
                                             -- but on OS X, only the active window is closed by default
                                             -- however, if true is passed to closeWindow()
                                             -- and this is the last remaining Document
                                             -- the app will close the window and quit the application
            elseif (k==kc.spaceKey) then
                -- toggle rendering pause
                isPaused = not(isPaused)
            else
                return false -- don't consume key
                             -- returning false, nil or not returning anything
                             -- has the same effect
            end
            return true     -- tell the OS we have consumed this key
        end)

        ---
        -- add all components and display
        ---

        mc:setSize(wsize)
        mc:addAndMakeVisible(button)                -- add the component to our main component
        documentWindow:setContentOwned( mc, true )  -- add the main component to the document window
 
        ---
        documentWindow:closeButtonPressed(function() -- the user asked to close the current window...
            documentWindow:closeWindow()             -- so let's close it our way
                                                     -- if this action's not taken, it'll close the app by default
        end)
        documentWindow:setSize(wsize)   -- set dimensions for the window
                                        -- on iOS and Android, it'll just set a fullscreen
        documentWindow:setVisible(true) -- display the document
        return documentWindow           -- return it for the application to actually display it
    end

    local manual      = false       -- set true if you want to add your own process running along with the main loop
    local osx_delayed = false       -- set true if you don't want your app to display a window immediatly on OS X
                                    -- but wait for user input before, like providing a file,...
    local poller      = function()  -- the callback you want to run in manual mode
        print "I'm in a loop!"
    end
    return app:start( MainWindow, manual and {poller,100}, osx_delayed,  ) -- returns the exit state


A more complete example using only the low level API
----------------------------------------------------

.. code:: lua
   
    local luce = require"luce"()
   
    ---
    --- create a default JUCEApplication
    ---
    local mainWindow = luce:JUCEApplication("My App")

    ---
    --- create a DocumentWindow with name "Document Window"
    ---
    local dw = luce:DocumentWindow("Document Window")
    -- rename it
    dw.name = "Luce Example Application"

    ---
    --- create a MainComponent, to be hosted by the Document Window
    ---
    local mc = luce:MainComponent("The Main Component")

    ---
    --- create a button named "TheButton" with text "a button"
    ---
    local button = luce:TextButton("TheButton")
    button:setButtonText( "a button" ) -- or button.buttonText = "a button", like button2 below

    --- add a callback for when button is clicked
    button:buttonClicked(function(...)
        print("button clicked !!")
    end)

    --- change component look and feel
    local button2 = luce:TextButton("TheButton2")
    button2.buttonText = "button with a different look and feel"

    --- add a callback for when button is clicked
    button2:buttonClicked(function(...)
        print("button 2 clicked !!")
    end)

    --- set a different look and feel for button2
    button2:setLookAndFeel(3)

    ---
    --- create a Label
    ---
    local label = luce:Label("A Label")

    --- Label's setText has an optional parameter to send a notification when its content's changed
    --- by default, it sends nothing:
    label.text = "a bit of content" -- default to dontSendNotification

    --- set a callback for label text changes
    label:labelTextChanged(function(...)
        print("Label text has changed: ", label:getText()) -- or label.text
    end)
    --- but we could use one of the three notification methods accepted:
    --- sendNotification, sendNotificationSync or sendNotificationAsync
    --- by using the setText method:
    local notif = luce.NotificationType.sendNotification
    label:setText( "another content", notif )

    --- set label editable
    label:setEditable(false, true, true) -- edit on single click, edit on double click, 
                                         -- cancel changes when losing focus
    --- we can attach the label to the button too                                     
    label:attachToComponent( button, true ) -- component, true: onLeft/false: above (default)
    print( "is attached on left ?", label:isAttachedOnLeft())


    --- set a colour for background and align text to the right
    local label2 = luce:Label("Another Label")
    label2.text = "(left aligned)"
    label2:setColour( label2.ColourIds.backgroundColourId, luce.Colours.yellow )
    label2:setJustificationType( luce.JustificationType.right )

    --- centre text
    local label3 = luce:Label("(left aligned text)")
    label3.text = "(centered)"
    label3:setColour( label3.ColourIds.backgroundColourId, luce.Colours.red )
    label3:setJustificationType( luce.JustificationType.centred )

    ---
    --- create a TextEditor
    ---
    local te = luce:TextEditor("Text Editor")

    --- directly set bounds for this component
    te.bounds = { 200, 250, 200, 200 } -- x, y, w, h
    -- or
    -- te.setBounds{ 200, 250, 200, 200 }

    --- add our Document Window and components to our main JUCE application
    mainWindow:initialise(function(...)
        mc:setSize{800,600}
        mc:addAndMakeVisible( button ) -- add the button to the main component
        button:setBounds{ 200, 20, 200, 200 } -- give the button some dimensions
        mc:addAndMakeVisible( label ) -- add the label          
        --label:setBounds{ 20, 250, 100, 100 } -- don't set bounds to the label
                                               -- if you want it attached to button

        mc:addAndMakeVisible(te) -- add the Text Editor

        mc:addAndMakeVisible( button2 ) -- add the second button with the different lnf
        button2:setBounds{ 410, 20, 200, 200 }

        mc:addAndMakeVisible(label2)
        label2:setBounds{ 410, 230, 150, 30 }

        mc:addAndMakeVisible(label3)
        label3:setBounds{ 410, 270, 150, 30 }

        --mc:setBounds{ 0, 0, 800, 600 } -- set the component bounds
                                         -- as this is the last component before
                                         -- DocumentWindow, it'll set the window size
                                         -- too, unless dw sets one
        dw:setContentOwned( mc, true )

        dw:centreWithSize{800, 600} -- centre window on screen with size 800x600
        --dw:setCentrePosition{ 0, 0 } -- move it to the top left corner
    
        --dw:setBounds{ 100, 100, 800,600 } -- sets the window bounds
                                            -- as dw is a TopWindow and, as such, the very 1st component,
                                            -- it'll be positionned
                                            -- on screen directly, so that's another way of
                                            -- doing centreWithSize/setCentrePosition
        --dw:setSize{ 800,600 } -- just show the window, top left corner
        dw:setVisible(true)

        return dw -- return the Document Window so the JUCE Application can take it
    end)

    --- callback on DocumentWindow :closeButtonPressed
    dw:closeButtonPressed(function(...)
        print("*** DocumentWindow close button pressed")
    end)

    --- callback used when quit is asked
    local stop_now = false
    mainWindow:systemRequestedQuit(function(...)
        print("** MainWindow system requested quit")
        stop_now = true
        mainWindow:shutdown()
        mainWindow:quit()
    end)

    --- main loop

    --- there are two implementations of the main loop
    --- one is the JUCE's native wrapped one
    --- and the other one gives control over the loop
    --- so actions can be taken during the process execution

    -- luce:start( mainWindow ) -- the simplest one, everything's under 
                                -- JUCE control

    --- and the non automatic one
    --- the function's executed in a loop within a thread,
    --- so there's no need to loop here
    --- it is set with the same rate than the JUCE's loop (1ms by default)
    luce:start_manual( mainWindow, 1, function(...)
        -- do some stuff, like zmq:poll(), for instance
        return stop_now
    end )


More examples
-------------

For more examples, see the `examples
<https://github.com/peersuasive/luce/tree/master/examples>`__ folder of the
repository.



Requirements and dependencies
=============================

To simply use Luce as a module,

* lua 5.1 / lua 5.2 / luajit 2.X

to compile the module and for C++ projects
------------------------------------------

* C++11
  
* GCC 4.6+ / CLANG 3.3+

To extend with new JUCE classes 
-------------------------------

* ``JUCE`` 3.0.6+


.. _download:

Downloads
=========

As of v0.3.1, modules are available for both lua5.1/luajit2.X and lua5.2.

To use with lua scripts as a module, pick the module download.

If you want to contribute and help debugging, get the debug version of the
module also.

And if you want to use `Luce/Embedded
<https://github.com/peersuasive/luce_embeddable>`_ or develop with C++, get the
static library (or use the module as a shared library, if you prefer to).

For iOS, only the static library is available as Apple policies wouldn't allow
a shared version but if you'd like to deploy on jailbroken devices, just ask,
I'll provide it with the next release.

For Android, at the opposite, only the shared library/module is available, as a
static library wouldn't really make sense, but feel free to ask also.


v0.3.2 (alpha)
--------------

Linux64 5.1
~~~~~~~~~~~

* `Linux/64/2.13 (lua 5.1 module) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.linux64-5.1.zip>`__
* `Linux/64/2.13 (lua 5.1 module/debug) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.linux64-5.1_dbg.zip>`__
* `Linux/64/2.13 (static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.Linux64-5.1_static.zip>`__

Linux64 5.2
~~~~~~~~~~~
* `Linux/64/2.13 (lua 5.2 module) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.linux64-5.2.zip>`__
* `Linux/64/2.13 (lua 5.2 module/debug) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.linux64-5.2_dbg.zip>`__
* `Linux/64/2.13 (static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.Linux64-5.2_static.zip>`__

Win32 5.1
~~~~~~~~~

* `Windows/32 (lua 5.1 module) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.1.zip>`__
* `Windows/32 (lua 5.1 module/debug) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.1_dbg.zip>`__
* `Windows/32 (static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.1_static.zip>`__

Win32 5.2
~~~~~~~~~

* `Windows/32 (lua 5.2 module) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.2.zip>`__
* `Windows/32 (lua 5.2 module/debug) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.2_dbg.zip>`__
* `Windows/32 (static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.win32-5.2_static.zip>`__

OS X 5.1
~~~~~~~~

* `Mac OS X/64/10.8 (lua 5.1 module) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.osx64-5.1.zip>`__
* `Mac OS X/64/10.8 (lua 5.1 module/debug) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.osx64-5.1_dbg.zip>`__
* `Mac OS X/64/10.8 (static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.osx64-5.1_static.zip>`__

iOS 6.1 5.1
~~~~~~~~~~~

* `iOS/5.1 (lua 5.1 static) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.ios61-5.1.zip>`__

Android 4.4 5.1
~~~~~~~~~~~~~~~

* `Android/4.X (lua 5.1 shared) <https://github.com/peersuasive/luce/releases/download/v0.3.2/luce.v0.3.2.android44-5.1.zip>`__



What's implemented so far ?
===========================

Basically, most of the core components are implemented, as well as OpenGL.

Most of the Graphics painting operations are also implemented, as well as the
most usefull math/geometry classes.

Some components you might find usefull may be missing, so don't hesitate to ask
for adding (or fork the repo and follow the guide `Adding new
classes to Luce`_ then send a *pull request*).

Luce design
===========

All Luce classes start with a ``L``.

Luce design is close to JUCE's, but often simplfied when it doesn't make sense
in lua to keep some if its behaviour or features.

For the general GUI design, see JUCE.

All widgets are derived from Juce's Component class and Luce's LComponent
class. All non-widgets classes are derived from LBase. LComponent itself is
derived from LBase. LBase offers the required link to Lua while LComponent
offers the required links to Juce.

Most of the callbacks existing in Juce also exist in Luce; in the same manner
they need to be overriden in Juce to take effect, they also need to be
overriden in Luce, that is, as for Luce, that a lua function needs to be
provided for the callback to be effective. If no callback is provided, the
default Juce action is called, if any.

All L* classes map their Juce equivalent or are specific to Luce (like LBase).

All L* classes are overridable within lua code, like any pure lua modules, and
most of them are partly implemented in Lua. This is particularly useful for
callback declarations or to add actions to native methods or simply to
specialise a component with new functionnalities.  This is the mechanism we use
to implement C++ classes directly in Lua.

There's a limitation, though, unless it's a callback, as it's not possible to
reimplement a native method in lua -- hence the use of a lua class wrapping the
native one.

Differences with ``JUCE``
=========================

For simplicity and reference, ``Luce`` usually uses the same method names than
``JUCE``. However, where ``JUCE`` uses getters/setters, Luce offers a direct
value attribution, whenever possible and obvious, that is. For instance,
``setName("...")`` and ``getName()`` would be replaced with ``name [= "..."]``,
though set/get methods are still accessible.

Another different is for JUCE's overloaded methods for both; wherever a more
compact form exists that can be substituted with tables, Luce will always
implement this compact form, leaving the detailed one.

For instance, if a method can accept both a Rectangle and four number x,y,w,h,
Luce will accept either a LRectangle or the table {x,y,w,h} but not the four
numbers.

So JUCE documentation is applicable for most of the Luce's low level components.

``Luce`` doesn't provide any listener class directly (and probably won't) but
instead wraps the listeners, where relevant, on the C++ side; as such, there's
no point in having ``addListener`` and ``removeListener`` functions taking a
listener class as argument; but one would be able to enable or disable such
listeners so these methods still exist in ``Luce`` though they just
activate/deactivate the wrapped Listener. 

Some future use cases may reveal the need for such an availability but at the
moment, we haven't found any.

Another difference is with Rectangle and Point objects, for which we didn't
find any use to provide natively. These classes are provided as pure lua
indexed tables and recreated wherever needed. So where a ``JUCE`` method needs
a ``Rectangle`` or ``Point`` object, a table containing the values must be
provided instead. Order is always x, y [, w, h ]. In general speaking, it
respects the order declared in the class constructor. Later on, there'll probably
be a lua implementation of these classes, to offer some of their most useful
methods, like ``:reduce()``.

Adding new classes to Luce
==========================

There are two kinds of classes in ``Luce``: *full* classes and *wrapper* classes.

Full classes are just ``JUCE`` classes extended to be integrated with ``Luce``,
while wrapper classes are there to create some kind of inheritence between
``Luce`` components.

For the 1st one, see ``LLabel``, ``LTextEditor`` or ``LTextButton``, while
the only example for the 2nd kind is ``LComponent``.

``LLabel``, ``LTextEditor`` and ``LTextButton`` extend their respective
``JUCE`` component while inheriting ``LComponent``, which in turn wraps all
``JUCE``'s ``Component`` base class methods.

This allows simulating inheritence in ``Luce`` components, as it wouldn't be
possible in a simple way otherwise. Like previously said, we're not aiming
at a 1 to 1 binding to ``JUCE``, so more complex mechanisms would be oversized
here (unless someone knows a simple way to achieve this, of course !).

There is a helper script, ``microparser``, which greatly simplify the job
of creating new classes for ``Luce``. It won't generate a new "ready to use"
class but gives a great help by generating the class template and headers
with all available methods and callbacks and pre-implementing them.
The most obvious ones are fully generated.

To add pseudo-inheritence, use the script ``create_inh.sh``:

.. code:: sh

    ./create_inh.sh <Luce_CLASS_BASE_NAME>


which generates the ``LCLASS_inh.h`` header to be included in the class.

Once the class is created, include it in ``luce.cpp``, ``luce.h`` and reference it in ``Main.cpp``:

.. code:: c++

    int l_NewClass(lua_State *L) {
        Luna<LNewClass>::Register(L);
        return 1;
    }

    static const luaL_reg luce_lib [] = {
        { "NewClass", l_NewClass },
        [...]
        {NULL, NULL}
    };

 

``Luce`` Roadmap
================

``Luce`` is still very young but growing fast -- at least as fast as
our needs for it. Most of the basic widgets are aleady there and it's already
possible to build full applications with it.
Performances are there too, even if there isn't any optimisation done yet.

Next big steps are:

* implementating a high level API (porcelaine) to simplify the process of
  creating new applications and reduce the number of required calls and methods
  to the native (JUCE) API

* more low level binding, like box2d, to be able to create our own fancy widgets

* an equivalent to JUCE's message broadcasting, between C++/Lua but also between
  any components (gadokai? pure ømq?)

* a var/Value equivalent usable within lua, even out of any JUCE context (gadokai? ømq?)

* some minor tasks like overriding LookAndFeel lua side

* optimisation, if required (there's a looooot of room for optimisation, no worry at all on this side)

API documentation will come later as Juce's one is still fully relevant.

You may also want to have a look at `luz <https://github.com/peersuasive/luz>`_,
a simple demonstrator on remotely and dynamically creating a ``Luce``
application, a small *avant goût* of the forthcoming Peersuasive's smart-data
oriented architecture ``gadokai`` (yet to be announced).



Related Projects
================

`Luce Embeddable <https://github.com/peersuasive/luce_embeddable>`_, to create standalone or bundled applications.

`Luce Squishable <https://github.com/peersuasive/luce_squishable>`_, to concatenate Luce's lua classes to one, portable file.


License.
========

For open source projects, ``Luce`` is licensed under the terms of the `GPLv3
<http://www.gnu.org/licenses/gpl-3.0.html>`_ with some parts being `AGPLv3
<http://www.gnu.org/licenses/agpl-3.0.html>`_.

For commercial projects and professional support, please contact us at

``contact``

``_at``

``peersuasive.com``.


.. vim:syntax=rst:filetype=rst:spelllang=en
