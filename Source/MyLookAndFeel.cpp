/************************************************************

 MyLookAndFeel.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2013, Peersuasive Technologies

*************************************************************/

#include "MyLookAndFeel.h"

// see juce_LookAndFeel_V2.cpp
namespace LookAndFeelHelpers
{
    // this is used by button, menu, combobox and slider
    static Colour createBaseColour (Colour buttonColour,
                                    bool hasKeyboardFocus,
                                    bool isMouseOverButton,
                                    bool isButtonDown) noexcept
    {
        const float sat = hasKeyboardFocus ? 1.3f : 0.9f;
        const Colour baseColour (buttonColour.withMultipliedSaturation (sat));

        if (isButtonDown)      return baseColour.contrasting (0.2f);
        if (isMouseOverButton) return baseColour.contrasting (0.1f);

        return baseColour;
    }

    static TextLayout layoutTooltipText (const String& text, Colour colour) noexcept
    {
        const float tooltipFontSize = 13.0f;
        const int maxToolTipWidth = 400;

        AttributedString s;
        s.setJustification (Justification::centred);
        s.append (text, Font (tooltipFontSize, Font::bold), colour);

        TextLayout tl;
        tl.createLayoutWithBalancedLineLengths (s, (float) maxToolTipWidth);
        return tl;
    }
}



MyLookAndFeel::MyLookAndFeel()
{
    setColour (TreeView::selectedItemBackgroundColourId, Colours::transparentWhite.withAlpha( 0.6f ));
}

MyLookAndFeel::~MyLookAndFeel() {}

// resize bar between right and left panels
void MyLookAndFeel::drawStretchableLayoutResizerBar (Graphics& g, int w, int h, bool /*isVerticalBar*/,
                                                      bool isMouseOver, bool isMouseDragging)
{

    float alpha = 0.5f;

    if (isMouseOver || isMouseDragging)
    {
        g.fillAll (Colours::grey.withAlpha (0.8f));
        //g.fillAll (Colour (0x190000ff));
        alpha = 1.0f;
    }

    const float cx = w * 0.5f;
    const float cy = h * 0.5f;
    const float cr = jmin (w, h) * 0.4f;

    g.setGradientFill (ColourGradient (Colours::white.withAlpha (alpha), cx + cr * 0.1f, cy + cr,
                                       Colours::black.withAlpha (alpha), cx, cy - cr * 4.0f,
                                       true));

    g.fillEllipse (cx - cr, cy - cr, cr * 2.0f, cr * 2.0f);

    /*
    if (isMouseOver || isMouseDragging)
        g.fillAll (Colours::grey.withAlpha (1.0f));
    else
        g.fillAll (Colours::grey.withAlpha (0.4f));
    */

}

// tooltips
void MyLookAndFeel::drawTooltip (Graphics& g, const String& text, int width, int height)
{
    //g.fillAll (findColour (TooltipWindow::backgroundColourId));
    g.fillAll( Colours::transparentWhite.withAlpha( 0.6f ) );

#if ! JUCE_MAC // The mac windows already have a non-optional 1 pix outline, so don't double it here..
    g.setColour (findColour (TooltipWindow::outlineColourId));
    g.drawRect (0, 0, width, height, 1);
#endif

    LookAndFeelHelpers::layoutTooltipText (text, findColour (TooltipWindow::textColourId))
        .draw (g, Rectangle<float> ((float) width, (float) height));
}
