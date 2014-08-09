/************************************************************

 LFileChooser_inh.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LFILECHOOSER_INH_H
#define __LUCE_LFILECHOOSER_INH_H

// LBase inheritage
const Luna<LFileChooser>::Inheritence LFileChooser::inherits[] = {
    {0,0}
};

const Luna<LFileChooser>::InheritenceF LFileChooser::inheritsF[] = {
    method( LBase, light),
    method( LBase, unlight),
    {0,0}
};

const Luna<LFileChooser>::Enum LFileChooser::enums[] = {
    { "Flags", {
        { "openMode", FileBrowserComponent::FileChooserFlags::openMode },
        { "saveMode", FileBrowserComponent::FileChooserFlags::saveMode },
        { "canSelectFiles", FileBrowserComponent::FileChooserFlags::canSelectFiles },
        { "canSelectDirectories", FileBrowserComponent::FileChooserFlags::canSelectDirectories },
        { "canSelectMultipleItems", FileBrowserComponent::FileChooserFlags::canSelectMultipleItems },
        { "useTreeView", FileBrowserComponent::FileChooserFlags::useTreeView },
        { "filenameBoxIsReadOnly", FileBrowserComponent::FileChooserFlags::filenameBoxIsReadOnly },
        { "warnAboutOverwriting", FileBrowserComponent::FileChooserFlags::warnAboutOverwriting }
    }},
    {0}
};
#endif // __LUCE_LFILECHOOSER_INH_H
