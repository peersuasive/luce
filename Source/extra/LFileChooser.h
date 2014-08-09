/************************************************************

 LFileChooser.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LFILECHOOSER_H
#define __LUCE_LFILECHOOSER_H

class LFileChooser
    : public LBase,
      public FileChooser
{
public:
    LFileChooser(lua_State*);
    LFileChooser(lua_State*, const String&, 
            const File init = File::nonexistent, const String &pat = String::empty,
            bool native = true);

    static int lnew(lua_State*);
    ~LFileChooser();

    //==============================================================================
    int getResults(lua_State*);
    int getResult(lua_State*);
    int browseForMultipleFilesOrDirectories(lua_State*);
    int browseForFileToOpen(lua_State*);
    int showDialog(lua_State*);
    int browseForFileToSave(lua_State*);
    int browseForDirectory(lua_State*);
    int browseForMultipleFilesToOpen(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LFileChooser>::Inheritence inherits[];
    static const Luna<LFileChooser>::InheritenceF inheritsF[];
    static const Luna<LFileChooser>::PropertyType properties[];
    static const Luna<LFileChooser>::FunctionType methods[];
    static const Luna<LFileChooser>::StaticType statics[];
    static const Luna<LFileChooser>::Enum enums[];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFileChooser)
};

#endif // __LUCE_LFILECHOOSER_H
