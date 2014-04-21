/************************************************************

 LLookAndFeel.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LLOOKANDFEEL_H
#define __LUCE_LLOOKANDFEEL_H

class LLookAndFeel
    : public LBase,
      public LookAndFeel_V3
{
public:
    LLookAndFeel(lua_State*);
    ~LLookAndFeel();

    //==============================================================================
    static int s_createTabTextLayout(lua_State*);

    //==============================================================================
    int getCrossShape(lua_State*);
    int getTabButtonSpaceAroundImage(lua_State*);
    int getTreeViewIndentSize(lua_State*);
    int areScrollbarButtonsVisible(lua_State*);
    int createDocumentWindowButton(lua_State*);
    int getTickShape(lua_State*);
    int getTabButtonOverlap(lua_State*);
    int areLinesDrawnForTreeView(lua_State*);

    //==============================================================================
    int drawTabButton(lua_State*);
    int drawLinearSlider(lua_State*);
    int drawTreeviewPlusMinusBox(lua_State*);
    int drawStretchableLayoutResizerBar(lua_State*);
    int drawMenuBarBackground(lua_State*);
    int drawConcertinaPanelHeader(lua_State*);
    int drawPopupMenuBackground(lua_State*);
    int drawTextEditorOutline(lua_State*);
    int drawComboBox(lua_State*);
    int drawLinearSliderBackground(lua_State*);
    int drawKeymapChangeButton(lua_State*);
    int drawScrollbar(lua_State*);
    int drawTabAreaBehindFrontButton(lua_State*);
    int drawButtonBackground(lua_State*);
    int drawTableHeaderBackground(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LLookAndFeel>::Inheritence inherits[];
    static const Luna<LLookAndFeel>::InheritenceF inheritsF[];
    static const Luna<LLookAndFeel>::PropertyType properties[];
    static const Luna<LLookAndFeel>::FunctionType methods[];
    static const Luna<LLookAndFeel>::StaticType statics[];
    static const Luna<LLookAndFeel>::Enum enums[];

    //==============================================================================
    void drawButtonBackground (Graphics&, Button&, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;

    void drawTableHeaderBackground (Graphics&, TableHeaderComponent&) override;

    void drawTreeviewPlusMinusBox (Graphics&, const Rectangle<float>& area,
                                   Colour backgroundColour, bool isOpen, bool isMouseOver) override;

    bool areLinesDrawnForTreeView (TreeView&) override;
    int getTreeViewIndentSize (TreeView&) override;
    Button* createDocumentWindowButton (int buttonType) override;
    void drawComboBox (Graphics&, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) override;

    void drawKeymapChangeButton (Graphics&, int width, int height, 
                                        Button& button, const String& keyDescription) override;
    void drawPopupMenuBackground (Graphics&, int width, int height) override;
    void drawMenuBarBackground (Graphics&, int width, int height, bool, MenuBarComponent&) override;

    int getTabButtonOverlap (int tabDepth) override;
    int getTabButtonSpaceAroundImage() override;

    void drawTabButton (TabBarButton&, Graphics&, bool isMouseOver, bool isMouseDown) override;
    void drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, int w, int h) override;
    void drawTextEditorOutline (Graphics&, int width, int height, TextEditor&) override;

    void drawStretchableLayoutResizerBar (Graphics&, int w, int h, bool isVerticalBar, 
                                                bool isMouseOver, bool isMouseDragging) override;

    bool areScrollbarButtonsVisible() override;

    void drawScrollbar (Graphics&, ScrollBar&, int x, int y, int width, int height, bool isScrollbarVertical,
                        int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

    void drawLinearSlider (Graphics&, int x, int y, int width, int height,
                           float sliderPos, float minSliderPos, float maxSliderPos,
                           const Slider::SliderStyle, Slider&) override;

    void drawLinearSliderBackground (Graphics&, int x, int y, int width, int height,
                                     float sliderPos, float minSliderPos, float maxSliderPos,
                                     const Slider::SliderStyle, Slider&) override;

    void drawConcertinaPanelHeader (Graphics&, const Rectangle<int>& area, 
                                    bool isMouseOver, bool isMouseDown, ConcertinaPanel&, Component&) override;
    Path getTickShape (float height) override;
    Path getCrossShape (float height) override;

    static void createTabTextLayout (const TabBarButton& button, float length, 
                                                        float depth, Colour colour, TextLayout&);
private:
    Image backgroundTexture;
    Colour backgroundTextureBaseColour;


private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LLookAndFeel)
};

#endif // __LUCE_LLOOKANDFEEL_H
