/************************************************************

 LComboBox.h

    @author Christophe Berbizier (cberbizier@peersuasive.com)
    @license GPLv3
    @copyright 


(c) 2014, Peersuasive Technologies

*************************************************************/

#ifndef __LUCE_LCOMBOBOX_H
#define __LUCE_LCOMBOBOX_H

class LComboBox
    : public LComponent,
      public ComboBox,
      public ComboBox::Listener
{
public:
    LComboBox(lua_State*);
    ~LComboBox();

    //==============================================================================
    int addListener(lua_State*);
    int removeListener(lua_State*);

    //==============================================================================
    int comboBoxChanged(lua_State*);

    //==============================================================================
    int setJustificationType(lua_State*);
    int getJustificationType(lua_State*);
    int setTooltip(lua_State*);
    int getTooltip(lua_State*);
    int setTextWhenNoChoicesAvailable(lua_State*);
    int getTextWhenNoChoicesAvailable(lua_State*);
    int setTextWhenNothingSelected(lua_State*);
    int getTextWhenNothingSelected(lua_State*);
    int setSelectedId(lua_State*);
    int getSelectedId(lua_State*);
    int setText(lua_State*);
    int getText(lua_State*);
    int setSelectedItemIndex(lua_State*);
    int getSelectedItemIndex(lua_State*);
    int setItemEnabled(lua_State*);
    int isItemEnabled(lua_State*);

    //==============================================================================
    int isTextEditable(lua_State*);
    int indexOfItemId(lua_State*);
    int getItemText(lua_State*);
    int getSelectedIdAsValue(lua_State*);
    int getNumItems(lua_State*);
    int getItemId(lua_State*);

    //==============================================================================
    int setEditableText(lua_State*);
    int addSectionHeading(lua_State*);
    int valueChanged(lua_State*);
    int showPopup(lua_State*);
    int labelTextChanged(lua_State*);
    int handleAsyncUpdate(lua_State*);
    int showEditor(lua_State*);
    int changeItemText(lua_State*);
    int addItem(lua_State*);
    int addItemList(lua_State*);
    int addSeparator(lua_State*);
    int clear(lua_State*);

    //==============================================================================
    static const char className[];
    static const Luna<LComboBox>::Inheritence inherits[];
    static const Luna<LComboBox>::InheritenceF inheritsF[];
    static const Luna<LComboBox>::PropertyType properties[];
    static const Luna<LComboBox>::FunctionType methods[];
    static const Luna<LComboBox>::StaticType statics[];
    static const Luna<LComboBox>::Enum enums[];

private:
    virtual void mouseMove(const MouseEvent&) override;
    virtual void mouseEnter(const MouseEvent&) override;
    virtual void mouseExit(const MouseEvent&) override;
    virtual void mouseDown(const MouseEvent&) override;
    virtual void mouseDrag(const MouseEvent&) override;
    virtual void mouseUp(const MouseEvent&) override;
    virtual void mouseDoubleClick(const MouseEvent&) override;
    virtual void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;
    virtual void mouseMagnify(const MouseEvent&, float) override;
 
    virtual bool keyPressed(const KeyPress&) override;

    //==============================================================================
    virtual void comboBoxChanged(ComboBox *) override;
    void valueChanged (Value&) override;
    void labelTextChanged(Label*) override;

    //==============================================================================
    virtual void paint(Graphics&) override;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LComboBox)
};

#endif // __LUCE_LCOMBOBOX_H
