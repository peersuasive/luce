/************************************************************

 LLookAndFeel.cpp

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

// TODO: think about a better way to implement LNF
//       our best option probably is an implementation
//       in LComponent so that any component can override
//       its own LNF
//       but the drawback of this approach if the impossibility
//       to set a global LNF at once... 
//       we could have both: this class and LComponent


#include "LLookAndFeel_inh.h"

const char LLookAndFeel::className[] = "LLookAndFeel";
const Luna<LLookAndFeel>::PropertyType LLookAndFeel::properties[] = {
    {0,0}
};
const Luna<LLookAndFeel>::FunctionType LLookAndFeel::methods[] = {
    method( LLookAndFeel, getCrossShape ),
    method( LLookAndFeel, getTabButtonSpaceAroundImage ),
    method( LLookAndFeel, getTreeViewIndentSize ),
    method( LLookAndFeel, areScrollbarButtonsVisible ),
    method( LLookAndFeel, createDocumentWindowButton ),
    method( LLookAndFeel, getTickShape ),
    method( LLookAndFeel, getTabButtonOverlap ),
    method( LLookAndFeel, areLinesDrawnForTreeView ),
    method( LLookAndFeel, drawTabButton ),
    method( LLookAndFeel, drawLinearSlider ),
    method( LLookAndFeel, drawTreeviewPlusMinusBox ),
    method( LLookAndFeel, drawStretchableLayoutResizerBar ),
    method( LLookAndFeel, drawMenuBarBackground ),
    method( LLookAndFeel, drawConcertinaPanelHeader ),
    method( LLookAndFeel, drawPopupMenuBackground ),
    method( LLookAndFeel, drawTextEditorOutline ),
    method( LLookAndFeel, drawComboBox ),
    method( LLookAndFeel, drawLinearSliderBackground ),
    method( LLookAndFeel, drawKeymapChangeButton ),
    method( LLookAndFeel, drawScrollbar ),
    method( LLookAndFeel, drawTabAreaBehindFrontButton ),
    method( LLookAndFeel, drawButtonBackground ),
    method( LLookAndFeel, drawTableHeaderBackground ),
    {0,0}
};

const Luna<LLookAndFeel>::StaticType LLookAndFeel::statics[] = {
    smethod( LLookAndFeel, createTabTextLayout ),
    {0,0}
};

LLookAndFeel::LLookAndFeel(lua_State *L)
    : LBase(L, "LLookAndFeel", true),
      LookAndFeel_V3()
{
}

LLookAndFeel::~LLookAndFeel() {}

static void createTabTextLayout (const TabBarButton& button, float length, 
                                                        float depth, Colour colour, TextLayout& tl)
{
    // ???
    LookAndFeel_V3::createTabTextLayout(button, length, depth, colour, tl);
}
int LLookAndFeel::s_createTabTextLayout(lua_State*) {
    // ???
    return 0;
}

void LLookAndFeel::drawButtonBackground(Graphics& g, Button& b, const Colour& backgroundColour, 
                                                            bool isMouseOverButton, bool isButtonDown) 
{
    if(hasCallback("drawButtonBackground"))
        callback("drawButtonBackground", 0, {
            new LRefBase("Graphics", &g),
            new LRefBase("Component", &b),
            new LRefBase("Colour", &backgroundColour),
            isMouseOverButton,
            isButtonDown,
        });
    else
        LookAndFeel_V3::drawButtonBackground(g, b, backgroundColour, isMouseOverButton, isButtonDown);
}
int LLookAndFeel::drawButtonBackground(lua_State*) {
    set("drawButtonBackground");
    return 0;
}

void LLookAndFeel::drawTableHeaderBackground (Graphics& g, TableHeaderComponent& thc) {
    if(hasCallback("drawTableHeaderBackground"))
        callback("drawTableHeaderBackground", 0, {
            new LRefBase("Graphics", &g),
            new LRefBase("Component", &thc)
        });
    else
        LookAndFeel_V3::drawTableHeaderBackground(g, thc);
}
int LLookAndFeel::drawTableHeaderBackground(lua_State*) {
    set("drawTableHeaderBackground");
    return 0;
}

void LLookAndFeel::drawTreeviewPlusMinusBox (Graphics& g, const Rectangle<float>& area, 
                                    Colour backgroundColour, bool isOpen, bool isMouseOver) 
{
    if(hasCallback("drawTreeviewPlusMinusBox"))
        callback("drawTreeviewPlusMinusBox");
    else
        LookAndFeel_V3::drawTreeviewPlusMinusBox(g, area, backgroundColour, isOpen, isMouseOver);
}
int LLookAndFeel::drawTreeviewPlusMinusBox(lua_State*) {
    set("drawTreeviewPlusMinusBox");
    return 0;
}

bool LLookAndFeel::areLinesDrawnForTreeView (TreeView& tv) {
    if(hasCallback("areLinesDrawnForTreeView")) {
        callback("areLinesDrawnForTreeView", 1);
        return LUA::checkAndGetBoolean(-1, false);
    }
    else
        return LookAndFeel_V3::areLinesDrawnForTreeView(tv);
}
int LLookAndFeel::areLinesDrawnForTreeView(lua_State*) {
    set("areLinesDrawnForTreeView");
    return 0;
}

int LLookAndFeel::getTreeViewIndentSize (TreeView& tv) {
    if(hasCallback("getTreeViewIndentSize")) {
        callback("getTreeViewIndentSize");
        if(!lua_isnumber(LUA::Get(), -1))
            LUCE::luce_error(lua_pushfstring(LUA::Get(), 
                "LLookAndFeel: getTreeViewIndentSize: expected returned number, got %s\n",
                lua_typename(LUA::Get(), lua_type(LUA::Get(), -1))
            ));
        return LUA::returnNumber(-1);
    }
    else
        return LookAndFeel_V3::getTreeViewIndentSize(tv);
}
int LLookAndFeel::getTreeViewIndentSize(lua_State*) {
    set("getTreeViewIndentSize");
    return 0;
}

Button* LLookAndFeel::createDocumentWindowButton (int buttonType) {
    if(hasCallback("createDocumentWindowButton"))
        callback("createDocumentWindowButton");
    else
        LookAndFeel_V3::createDocumentWindowButton(buttonType);
}
int LLookAndFeel::createDocumentWindowButton(lua_State*) {
    set("createDocumentWindowButton");
    return 0;
}

void LLookAndFeel::drawComboBox (Graphics& g, int width, int height, bool isButtonDown, 
                                int buttonX, int buttonY, int buttonW, int buttonH, ComboBox& box) 
{
    if(hasCallback("drawComboBox"))
        callback("drawComboBox");
    else
        LookAndFeel_V3::drawComboBox(g, width, height, isButtonDown, buttonX, buttonY, buttonW, buttonH, box);
}
int LLookAndFeel::drawComboBox(lua_State*) {
    set("drawComboBox");
    return 0;
}

void LLookAndFeel::drawKeymapChangeButton (Graphics& g, int width, int height, 
                                        Button& button, const String& keyDescription) 
{
    if(hasCallback("drawKeymapChangeButton"))
        callback("drawKeymapChangeButton");
    else
        LookAndFeel_V3::drawKeymapChangeButton(g, width, height, button, keyDescription);
}
int LLookAndFeel::drawKeymapChangeButton(lua_State*) {
    set("drawKeymapChangeButton");
    return 0;
}

void LLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height) {
    if(hasCallback("drawPopupMenuBackground"))
        callback("drawPopupMenuBackground");
    else
        LookAndFeel_V3::drawPopupMenuBackground(g, width, height);
}
int LLookAndFeel::drawPopupMenuBackground(lua_State*) {
    set("drawPopupMenuBackground");
    return 0;
}

void LLookAndFeel::drawMenuBarBackground (Graphics& g, int width, int height, bool unused, MenuBarComponent& mbc) 
{
    if(hasCallback("drawMenuBarBackground"))
        callback("drawMenuBarBackground");
    else
        LookAndFeel_V3::drawMenuBarBackground(g, width, height, unused, mbc);
}
int LLookAndFeel::drawMenuBarBackground(lua_State*) {
    set("drawMenuBarBackground");
    return 0;
}

int LLookAndFeel::getTabButtonOverlap (int tabDepth) {
    if(hasCallback("getTabButtonOverlap"))
        callback("getTabButtonOverlap");
    else
        LookAndFeel_V3::getTabButtonOverlap(tabDepth);
}
int LLookAndFeel::getTabButtonOverlap(lua_State*) {
    set("getTabButtonOverlap");
    return 0;
}

int LLookAndFeel::getTabButtonSpaceAroundImage() {
    if(hasCallback("getTabButtonSpaceAroundImage"))
        callback("getTabButtonSpaceAroundImage");
    else
        LookAndFeel_V3::getTabButtonSpaceAroundImage();
}
int LLookAndFeel::getTabButtonSpaceAroundImage(lua_State*) {
    set("getTabButtonSpaceAroundImage");
    return 0;
}

void LLookAndFeel::drawTabButton (TabBarButton& tbb, Graphics& g, bool isMouseOver, bool isMouseDown) {
    if(hasCallback("drawTabButton"))
        callback("drawTabButton");
    else
        LookAndFeel_V3::drawTabButton(tbb, g, isMouseOver, isMouseDown);
}
int LLookAndFeel::drawTabButton(lua_State*) {
    set("drawTabButton");
    return 0;
}

void LLookAndFeel::drawTabAreaBehindFrontButton (TabbedButtonBar& bar, Graphics& g, int w, int h) {
    if(hasCallback("drawTabAreaBehindFrontButton"))
        callback("drawTabAreaBehindFrontButton");
    else
        LookAndFeel_V3::drawTabAreaBehindFrontButton(bar, g, w, h);
}
int LLookAndFeel::drawTabAreaBehindFrontButton(lua_State*) {
    set("drawTabAreaBehindFrontButton");
    return 0;
}

void LLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& te) {
    if(hasCallback("drawTextEditorOutline"))
        callback("drawTextEditorOutline");
    else
        LookAndFeel_V3::drawTextEditorOutline(g, width, height, te);
}
int LLookAndFeel::drawTextEditorOutline(lua_State*) {
    set("drawTextEditorOutline");
    return 0;
}

void LLookAndFeel::drawStretchableLayoutResizerBar (Graphics&g, int w, int h, 
                                bool isVerticalBar, bool isMouseOver, bool isMouseDragging) 
{
    if(hasCallback("drawStretchableLayoutResizerBar"))
        callback("drawStretchableLayoutResizerBar");
    else
        LookAndFeel_V3::drawStretchableLayoutResizerBar(g, w, h, isVerticalBar, isMouseOver, isMouseDragging);
}
int LLookAndFeel::drawStretchableLayoutResizerBar(lua_State*) {
    set("drawStretchableLayoutResizerBar");
    return 0;
}

bool LLookAndFeel::areScrollbarButtonsVisible() {
    if(hasCallback("areScrollbarButtonsVisibl"))
        callback("areScrollbarButtonsVisibl");
    else
        LookAndFeel_V3::areScrollbarButtonsVisible();
}
int LLookAndFeel::areScrollbarButtonsVisible(lua_State*) {
    set("areScrollbarButtonsVisible");
    return 0;
}

void LLookAndFeel::drawScrollbar (Graphics& g, ScrollBar& sb, int x, int y, int width, 
                    int height, bool isScrollbarVertical, int thumbStartPosition, 
                    int thumbSize, bool isMouseOver, bool isMouseDown) 
{
    if(hasCallback("drawScrollbar"))
        callback("drawScrollbar");
    else
        LookAndFeel_V3::drawScrollbar(g, sb, x, y, width, height, isScrollbarVertical, 
                                        thumbStartPosition, thumbSize, isMouseOver, isMouseDown);
}
int LLookAndFeel::drawScrollbar(lua_State*) {
    set("drawScrollbar");
    return 0;
}

void LLookAndFeel::drawLinearSlider (Graphics& g, int x, int y, int width, 
            int height, float sliderPos, float minSliderPos, float maxSliderPos, 
                                        const Slider::SliderStyle style, Slider& slider) 
{
    if(hasCallback("drawLinearSlider"))
        callback("drawLinearSlider");
    else
        LookAndFeel_V3::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}
int LLookAndFeel::drawLinearSlider(lua_State*) {
    set("drawLinearSlider");
    return 0;
}

void LLookAndFeel::drawLinearSliderBackground (Graphics& g, int x, int y, int width, int height, 
                float sliderPos, float minSliderPos, float maxSliderPos, 
                            const Slider::SliderStyle style, Slider& slider) 
{
    if(hasCallback("drawLinearSliderBackground"))
        callback("drawLinearSliderBackground");
    else
        LookAndFeel_V3::drawLinearSliderBackground(g, x, y, width, height, sliderPos, 
                                                    minSliderPos, maxSliderPos, style, slider);
}
int LLookAndFeel::drawLinearSliderBackground(lua_State*) {
    set("drawLinearSliderBackground");
    return 0;
}

void LLookAndFeel::drawConcertinaPanelHeader (Graphics& g, const Rectangle<int>& area, 
                        bool isMouseOver, bool isMouseDown, ConcertinaPanel& cp, Component& comp) 
{
    if(hasCallback("drawConcertinaPanelHeader"))
        callback("drawConcertinaPanelHeader");
    else
        LookAndFeel_V3::drawConcertinaPanelHeader(g, area, isMouseOver, isMouseDown, cp, comp);
}
int LLookAndFeel::drawConcertinaPanelHeader(lua_State*) {
    set("drawConcertinaPanelHeader");
    return 0;
}

Path LLookAndFeel::getTickShape (float height) {
    if(hasCallback("getTickShape"))
        callback("getTickShape");
    else
        LookAndFeel_V3::getTickShape(height);
}
int LLookAndFeel::getTickShape(lua_State*) {
    set("getTickShape");
    return 0;
}

Path LLookAndFeel::getCrossShape (float height) {
    if(hasCallback("getCrossShape"))
        callback("getCrossShape");
    else
        LookAndFeel_V3::getCrossShape(height);
}
int LLookAndFeel::getCrossShape(lua_State*) {
    set("getCrossShape");
    return 0;
}
