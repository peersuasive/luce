/************************************************************

 MyLookAndFeel.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#ifndef __PSV_LOOK_AND_FEEL_H
#define __PSV_LOOK_AND_FEEL_H

#include "JuceHeader.h"

class MyLookAndFeel : public LookAndFeel_V3
{
public:
    MyLookAndFeel();
    ~MyLookAndFeel();

    // resize bar between right and left panels
    void drawStretchableLayoutResizerBar (Graphics&, int w, int h, 
            bool isVerticalBar, bool isMouseOver, bool isMouseDragging) override;

    // tooltip background
    void drawTooltip (Graphics&, const String& text, int width, int height);


private:
};

#endif // __PSV_LOOK_AND_FEEL_H
