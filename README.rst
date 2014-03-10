====
luce
====
-----------------------------------
A GUI Toolkit for Lua based on JUCE
-----------------------------------


What is ``Luce`` ?
==================

``Luce`` is a `Lua <http://lua.org>`_ GUI framework, based on the excellent C++
portable, embeddable libray `JUCE <http://www.juce.com>`_.

Though based on Juce, Luce must be considered a different project than
Juce as there are some differences between them and the gap will keep growing
as Luce is developping.

Luce has Lua in mind and will be developped for lua developpers.

Lua essence is to be "``a powerfull, fast, lightweight embeddable scripting
language.``" And so would Luce be too.

Luce is light, fast and easily portable, thanks to Lua and Juce itself.

    
Requirements and dependencies
=============================

* lua 5.1/lua 5.2/luajit

* C++11, GCC > 4.6 (CLANG supported)

* tested under Linux, Windows and Mac OS X

* ``JUCE`` 3.0.X (optional, to add new features)

Downloads
=========

v0.2 (alpha)
------------

* `linux (64b, lua5.1) <https://github.com/peersuasive/luce/releases/download/v0.2/luce.0.2.Linux_Windows.zip>`_

* `win32 (32b, lua5.2) <https://github.com/peersuasive/luce/releases/download/v0.2/luce.0.2.Linux_Windows.zip>`_


What's implemented so far ?
===========================

some of the most common widgets and components are already there

* Colour
* Component
* Font
* GlyphArrangement
* Graphics
* HyperlinkButton
* Image
* JUCEApplication
* Label
* ListBox
* Path
* PositionedGlyph
* SourceDetails
* StretchableLayoutManager
* StretchableLayoutResizerBar
* TextButton
* TextEditor
* Timer
* ToggleButton
* TreeView / TreeViewItem
* and growing...

some of the special classes are also there

* MouseListener
* TooltipWindow
* Look And Feel (only C++ at the moment)
* KeyPress
* MouseEvent
* ModifierKeys
* and so on...

and some components are implemented in pure lua

* Rectangle
* RectangleList
* Line
* Point
* AffineTransform


Luce design
===========

All Luce classes start with a ``L``.

Luce design is close to Juce's, but has less options as most of them are not
required with Lua.

For the general GUI design, see Juce.

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

For the most part, ``Luce`` uses the same methods than ``JUCE``, but they can
sometimes have different calling arguments or small behavior differences.

For instance, ``Luce`` doesn't provide any listener class directly (and
probably won't) but instead wraps the listeners, where relevant, on the C++
side; as such, there's no point in having ``addListener`` and
``removeListener`` functions taking a listener class as argument; but one would
be able to enable or disable such listeners so these methods still exist in
``Luce`` though they just activate/deactivate the wrapped Listener. 

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


How to use ?
============

For simplicity and reference, ``luce`` usually uses the same method names than 
``JUCE``. However, where ``JUCE`` uses getters/setters, Luce offers a direct
value attribution, whenever possible and obvious, that is. For instance,
``setName("...")`` and ``getName()`` would be replaced with ``name [=
"..."]``, though set/get methods are still accessible.

So Juce documentation is applicable for most of the Luce components.

Example:
--------

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
    luce:start_manual( mainWindow, function(...)
        -- do some stuff, like zmq:poll(), for instance
        return stop_now
    end )


    luce:shutdown() -- in any case, call this to close cleanly

Adding new classes to ``Luce``
==============================

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

``Luce`` is still very young just but is growing fast -- at least as fast as
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
