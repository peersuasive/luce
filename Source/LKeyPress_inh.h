
/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
  
(c) 2013-2014, Peersuasive Technologies

*/

// LBase inheritence
const Luna<LKeyPress>::Inheritence LKeyPress::inherits[] = {
    {0,0}
};

const Luna<LKeyPress>::InheritenceF LKeyPress::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LKeyPress>::Enum LKeyPress::enums[] = {
    { "KeyCodes", {
        { "spaceKey", KeyPress::spaceKey },
        { "escapeKey", KeyPress::escapeKey },
        { "returnKey", KeyPress::returnKey },
        { "tabKey", KeyPress::tabKey },
        { "deleteKey", KeyPress::deleteKey },
        { "backspaceKey", KeyPress::backspaceKey },
        { "insertKey", KeyPress::insertKey },
        { "upKey", KeyPress::upKey },
        { "downKey", KeyPress::downKey },
        { "leftKey", KeyPress::leftKey },
        { "rightKey", KeyPress::rightKey },
        { "pageUpKey", KeyPress::pageUpKey },
        { "pageDownKey", KeyPress::pageDownKey },
        { "homeKey", KeyPress::homeKey },
        { "endKey", KeyPress::endKey },
        { "F1Key", KeyPress::F1Key },
        { "F2Key", KeyPress::F2Key },
        { "F3Key", KeyPress::F3Key },
        { "F4Key", KeyPress::F4Key },
        { "F5Key", KeyPress::F5Key },
        { "F6Key", KeyPress::F6Key },
        { "F7Key", KeyPress::F7Key },
        { "F8Key", KeyPress::F8Key },
        { "F9Key", KeyPress::F9Key },
        { "F10Key", KeyPress::F10Key },
        { "F11Key", KeyPress::F11Key },
        { "F12Key", KeyPress::F12Key },
        { "F13Key", KeyPress::F13Key },
        { "F14Key", KeyPress::F14Key },
        { "F15Key", KeyPress::F15Key },
        { "F16Key", KeyPress::F16Key },
        { "numberPad0", KeyPress::numberPad0 },
        { "numberPad1", KeyPress::numberPad1 },
        { "numberPad2", KeyPress::numberPad2 },
        { "numberPad3", KeyPress::numberPad3 },
        { "numberPad4", KeyPress::numberPad4 },
        { "numberPad5", KeyPress::numberPad5 },
        { "numberPad6", KeyPress::numberPad6 },
        { "numberPad7", KeyPress::numberPad7 },
        { "numberPad8", KeyPress::numberPad8 },
        { "numberPad9", KeyPress::numberPad9 },
        { "numberPadAdd", KeyPress::numberPadAdd },
        { "numberPadSubtract", KeyPress::numberPadSubtract },
        { "numberPadMultiply", KeyPress::numberPadMultiply },
        { "numberPadDivide", KeyPress::numberPadDivide },
        { "numberPadSeparator", KeyPress::numberPadSeparator },
        { "numberPadDecimalPoint", KeyPress::numberPadDecimalPoint },
        { "numberPadEquals", KeyPress::numberPadEquals },
        { "numberPadDelete", KeyPress::numberPadDelete },
        { "playKey", KeyPress::playKey },
        { "stopKey", KeyPress::stopKey },
        { "fastForwardKey", KeyPress::fastForwardKey },
        { "rewindKey", KeyPress::rewindKey },
    }},
    {0}
};
