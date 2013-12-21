====
luce
====
-----------------------------------
A GUI Toolkit for Lua based on JUCE
-----------------------------------


What is ``LUCE`` ?
==================

    ``LUCE`` is a `Lua <http://lua.org>`_ binding/wrapper to `JUCE <http://www.juce.com>`_.
        
    ``JUCE`` is "``an extensive, mature, cross-platform C++ toolkit``". 
    
    It has a clean, neat and smart C++ interface for GUI development with very
    interesting low level features. It is light, fully embeddable, well coded
    and can be very easily extended with fancy components and visual effects
    thanks to its low level API.

    For more information on ``JUCE``, see `Raw Material Software Ltd. official website
    <http://www.juce.com>`_.

    ``LUCE`` is at the very first stage of development and implements just the bare
    minimum as a demonstrator, though the core itself is well advanced.
    
    The goal of ``LUCE`` is not to write a 1 to 1 binding for ``JUCE`` but
    rather aims at creating a native GUI toolkit for Lua *based* on ``JUCE``,
    that is, with a programming interface more on the Lua spirit than the C++
    spirit.
    Therefore, something closer 
    to `tekUI <http://tekui.neoscientists.org>`_ 
    than `wxLua <http://wxlua.sourceforge.net>`_ 
    or `QtLua <http://www.nongnu.org/libqtlua>`_.

    Lua essence is to be "``a powerfull, fast, lightweight embeddable scripting language.``"
    And so would ``Luce`` be too.

    
Requirements and dependencies
=============================

    * lua 5.1/luajit (untested with 5.2)

    * C++11, GCC > 4.6 (should work with CLANG too)

    * Linux (untested with any other OS but shouldn't need a lot of work, if
      any at all, thanks to ``JUCE``)

    * ``JUCE`` 3.0 (optional, to add new features)

How to use ?
============

    For simplicity and reference, ``luce`` uses the same method names than
    ``JUCE``'s. However, where ``JUCE`` uses getters/setters, we'll prefer a direct
    access interface instead, whenever possible and obvious, that is. For instance,
    ``setName("...")`` and ``getName()`` would be replaced with ``name [=
    "..."]``

    At the current stage of development, ``luce`` follows the ``JUCE`` general
    rules for creating GUI applications: a ``JUCEApplication`` object hosts a
    ``TopLevelWindow`` object which in turn hosts some components.

    ``JUCE`` uses callbacks and only the most relevant ones are implemented as of now.
    They are accessed like any normal function in lua, except they're evaluated
    by the C++ code not the lua interpreter.

    Porting ``JUCE``'s messaging system (``ActionBroadcaster``/``MessageManager``/``...``) to
    ``LUCE`` will be the next step after the core minimum features were
    implemented, along with a Lua alternative to ``JUCE``'s ``var`` generic
    container (in short, it'll be implemented with tables and callbacks).

Example
-------

.. code:: lua
   
    local luce = require"luce"
   
    ---
    --- create a default JUCEApplication
    ---
    local mainWindow = luce:JUCEApplication()
    local mainWindow = mainWindow:new()
   
    ---
    --- create a DocumentWindow with name "Document Window"
    ---
    local dw = luce:DocumentWindow():new("Document Window")
    -- rename it
    dw.name = "LUCE Example Application"
   
    ---
    --- create a MainComponent, to be hosted by the Document Window
    ---
    local mc = luce:MainComponent():new()
   
    ---
    --- create a button named "TheButton" with text "a button"
    ---
    local button = luce:TextButton():new("TheButton")
    button:setButtonText( "a button")
    
    --- add a callback on button clicks
    button:buttonClicked(function(...)
        print("button clicked !!")
    end)
   
    ---
    --- create a Label
    ---
    local label = luce:Label():new("A Label")
   
    --- Label's setText has an optional parameter to send a notification when its content's changed
    --- by default, it sends nothing:
    label.text = "a bit of content" -- defaults to dontSendNotification
   
    --- but we could use one of the three notification methods accepted:
    --- sendNotification, sendNotificationSync or sendNotificationAsync
    --- by using the setText method:
    --- set a callback for label text changes
    label:labelTextChanged(function(...)
        print("Label text has changed: ", label:getText())
    end)

    local notif = luce.NotificationType.sendNotification
    label:setText( "another content", notif ) -- will print "another content" on the terminal output
   
    --- set label editable
    label:setEditable(false, true, true) -- don't edit on single click, edit on double click, 
                                         -- cancel changes when losing focus
   
    --- we can attach the label to the button too                                     
    label:attachToComponent( button, true ) -- attach to button, on left (default: above)
    print( "is attached on left ?", label:isAttachedOnLeft())
   
    ---
    --- create a TextEditor
    ---
    local te = luce:TextEditor():new("Text Editor")
   
    --- directly set bounds for this component
    te.bounds = { 200, 250, 200, 200 } -- x, y, w, h
    -- or
    -- te.setBounds{ 200, 250, 200, 200 }
   
    --- add our Document Window and components to our main JUCE application
    mainWindow:initialise(function(...)

        mc:addAndMakeVisible( button ) -- add the button to the main component
        button:setBounds{ 200, 20, 200, 200 } -- give the button some dimensions
        mc:addAndMakeVisible( label ) -- add the label          
        --label:setBounds{ 20, 250, 100, 100 } -- don't set bounds for the label
                                               -- if you want it attached to button
        mc:addAndMakeVisible(te) -- add the Text Editor

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
    local keep_going = true
    mainWindow:systemRequestedQuit(function(...)
        print("** MainWindow system requested quit")
        keep_going = false
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
    luce:start_manual( mainWindow, function(...) 
        local status = true
        if ( not keep_going ) then
            status = false
        end
        return status
    end )
    
    
    luce:shutdown() -- in any case, call this to close cleanly


Adding new ``JUCE`` classes
===========================

    There are two kinds of classes in ``LUCE``: *full* classes and *wrapper* classes.
    
    Full classes are just ``JUCE`` classes extended to be integrated with ``LUCE``,
    while wrapper classes are there to create some kind of inheritence between
    ``LUCE`` components.

    For the 1st one, see ``LLabel``, ``LTextEditor`` or ``LTextButton``, while
    the only example for the 2nd kind is ``LComponent``.

    ``LLabel``, ``LTextEditor`` and ``LTextButton`` extend their respective
    ``JUCE`` component while inheriting ``LComponent``, which in turn wraps all
    ``JUCE``'s ``Component`` base class methods.
    
    This allows simulating inheritence in ``LUCE`` components, as it wouldn't be
    possible in a simple way otherwise. Like previously said, we're not aiming
    at a 1 to 1 binding to ``JUCE``, so more complex mechanisms would be oversized
    here (unless someone knows a simple way to achieve this, of course !).

    There is a helper script, ``microparser``, which greatly simplify the job
    of creating new classes for ``LUCE``. It won't generate a new "ready to use"
    class but gives a great help by generating the class template and headers
    with all available methods and callbacks and pre-implementing them.
    The most obvious ones are fully generated.

    To add pseudo-inheritence, use the script ``create_inh.sh``:

    .. code:: sh

        create_inh.sh <LUCE_CLASS_BASE_NAME>


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

 

``Luce`` development stage and future
=====================================

    ``LUCE`` is just a few days old and not really useful as it is for more
    than a demonstrator but it'll become more and more interesting while
    growing. Any help would be the most welcome so if you have C++, Lua or
    documenting skills or are just simply interested, don't hesitate to fork and
    contribute :)

    The roadmap at the moment is to add more base components and develop a
    clean, lua-like, API.

    You may also want to have a look at ``luz``, a simple demonstrator on
    remotely and dynamically creating a ``Luce`` application, a small *avant
    goût* of the forthcoming Peersuasive's smart-data oriented architecture
    ``gadokai`` (yet to be announced).


License.
========

    For open source projects, ``LUCE`` is licensed under the term of the `GPLv3
    <http://www.gnu.org/licenses/gpl-3.0.html>`_ with some parts being `AGPLv3
    <http://www.gnu.org/licenses/agpl-3.0.html>`_.
    
    For commercial projects and professional support, please contact us at

    ``contact``

    ``_at``

    ``peersuasive.com``.


.. vim:syntax=rst:filetype=rst:spelllang=en
