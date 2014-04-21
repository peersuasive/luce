
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

// LModifierKeys inheritage
const Luna<LModifierKeys>::Inheritence LModifierKeys::inherits[] = {
    {0,0}
};

const Luna<LModifierKeys>::InheritenceF LModifierKeys::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LModifierKeys>::Enum LModifierKeys::enums[] = {
    { "", {
        { "noModifiers"            , ModifierKeys::Flags::noModifiers },
        { "shiftModifier"          , ModifierKeys::Flags::shiftModifier },
        { "ctrlModifier"           , ModifierKeys::Flags::ctrlModifier },
        { "altModifier"            , ModifierKeys::Flags::altModifier },
        { "leftButtonModifier"     , ModifierKeys::Flags::leftButtonModifier },
        { "rightButtonModifier"    , ModifierKeys::Flags::rightButtonModifier },
        { "middleButtonModifier"   , ModifierKeys::Flags::middleButtonModifier },
        { "commandModifier"        , ModifierKeys::Flags::commandModifier },
        { "popupMenuClickModifier" , ModifierKeys::Flags::popupMenuClickModifier},
        { "allKeyboardModifiers"   , ModifierKeys::Flags::allKeyboardModifiers},
        { "allMouseButtonModifiers", ModifierKeys::Flags::allMouseButtonModifiers},
        { "ctrlAltCommandModifiers", ModifierKeys::Flags::ctrlAltCommandModifiers},
        //{ "allKeyboardModifiers"   , shiftModifier | ctrlModifier | altModifier | commandModifier },
        //{ "allMouseButtonModifiers", leftButtonModifier | rightButtonModifier | middleButtonModifier },
        //{ "ctrlAltCommandModifiers", ctrlModifier | altModifier | commandModifier }
    }},
    {0}
};
