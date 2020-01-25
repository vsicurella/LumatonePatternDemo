/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainWindow.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow (LayoutGenerator& layoutToUse)
    : layout(layoutToUse)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    keyboardView.reset (new KeyboardViewer());
    addAndMakeVisible (keyboardView.get());
    keyboardView->setName ("new component");

    editPeriod.reset (new Slider ("new slider"));
    addAndMakeVisible (editPeriod.get());
    editPeriod->setRange (1, 400, 1);
    editPeriod->setSliderStyle (Slider::IncDecButtons);
    editPeriod->setTextBoxStyle (Slider::TextBoxLeft, false, 60, 20);
    editPeriod->addListener (this);

    editGenerator.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (editGenerator.get());
    editGenerator->setEditableText (false);
    editGenerator->setJustificationType (Justification::centredLeft);
    editGenerator->setTextWhenNothingSelected (String());
    editGenerator->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    editGenerator->addListener (this);

    editKeyboard.reset (new ComboBox ("new combo box"));
    addAndMakeVisible (editKeyboard.get());
    editKeyboard->setEditableText (false);
    editKeyboard->setJustificationType (Justification::centredLeft);
    editKeyboard->setTextWhenNothingSelected (String());
    editKeyboard->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    editKeyboard->addListener (this);

    editColorLayout.reset (new Component());
    addAndMakeVisible (editColorLayout.get());
    editColorLayout->setName ("new component");

    editShowKeyNumber.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editShowKeyNumber.get());
    editShowKeyNumber->setButtonText (TRANS("Full Keyboard Number"));
    editShowKeyNumber->setRadioGroupId (10);
    editShowKeyNumber->addListener (this);
    editShowKeyNumber->setToggleState (true, dontSendNotification);

    editShowOctaveNum.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editShowOctaveNum.get());
    editShowOctaveNum->setButtonText (TRANS("Octave Number"));
    editShowOctaveNum->setRadioGroupId (10);
    editShowOctaveNum->addListener (this);

    editShowMidiNote.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editShowMidiNote.get());
    editShowMidiNote->setButtonText (TRANS("MIDI Note"));
    editShowMidiNote->setRadioGroupId (10);
    editShowMidiNote->addListener (this);

    editShowScaleDegree.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editShowScaleDegree.get());
    editShowScaleDegree->setButtonText (TRANS("Scale Degree"));
    editShowScaleDegree->setRadioGroupId (10);
    editShowScaleDegree->addListener (this);


    //[UserPreSize]
    editPeriod->setValue(12);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    refresh();
    editGenerator->setSelectedId(7);
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    keyboardView = nullptr;
    editPeriod = nullptr;
    editGenerator = nullptr;
    editKeyboard = nullptr;
    editColorLayout = nullptr;
    editShowKeyNumber = nullptr;
    editShowOctaveNum = nullptr;
    editShowMidiNote = nullptr;
    editShowScaleDegree = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    keyboardView->setBounds (proportionOfWidth (0.0076f), proportionOfHeight (0.0226f), proportionOfWidth (0.9838f), proportionOfHeight (0.6632f));
    editPeriod->setBounds (proportionOfWidth (0.1128f), proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0690f), 120, 24);
    editGenerator->setBounds (proportionOfWidth (0.1128f), proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.1724f), 112, 24);
    editKeyboard->setBounds (proportionOfWidth (0.1128f), proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.2759f), 112, 24);
    editColorLayout->setBounds (proportionOfWidth (0.3102f), proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0690f), 240, 120);
    editShowKeyNumber->setBounds (proportionOfWidth (0.3102f) + roundToInt (240 * 1.5458f), proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0726f), 176, 24);
    editShowOctaveNum->setBounds ((proportionOfWidth (0.3102f) + roundToInt (240 * 1.5458f)) + 0, (proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0726f)) + roundToInt (24 * 1.3333f), 176, 24);
    editShowMidiNote->setBounds ((proportionOfWidth (0.3102f) + roundToInt (240 * 1.5458f)) + 0, ((proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0726f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f), 176, 24);
    editShowScaleDegree->setBounds ((proportionOfWidth (0.3102f) + roundToInt (240 * 1.5458f)) + 0, (((proportionOfHeight (0.0226f) + roundToInt (proportionOfHeight (0.6632f) * 1.0726f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f), 176, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainWindow::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == editPeriod.get())
    {
        //[UserSliderCode_editPeriod] -- add your slider handling code here..
        DBG("Period box has changed");
        layout = LayoutGenerator((int)editPeriod->getValue());
        refresh();
        //[/UserSliderCode_editPeriod]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void MainWindow::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == editGenerator.get())
    {
        //[UserComboBoxCode_editGenerator] -- add your combo box handling code here..
        DBG("Generator box has changed");
        layout = LayoutGenerator((int)editPeriod->getValue(), editGenerator->getSelectedId());
        refresh(false);
        //[/UserComboBoxCode_editGenerator]
    }
    else if (comboBoxThatHasChanged == editKeyboard.get())
    {
        //[UserComboBoxCode_editKeyboard] -- add your combo box handling code here..
        DBG("Keyboard box has changed");
        //[/UserComboBoxCode_editKeyboard]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void MainWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == editShowKeyNumber.get())
    {
        //[UserButtonCode_editShowKeyNumber] -- add your button handler code here..
        //[/UserButtonCode_editShowKeyNumber]
    }
    else if (buttonThatWasClicked == editShowOctaveNum.get())
    {
        //[UserButtonCode_editShowOctaveNum] -- add your button handler code here..
        //[/UserButtonCode_editShowOctaveNum]
    }
    else if (buttonThatWasClicked == editShowMidiNote.get())
    {
        //[UserButtonCode_editShowMidiNote] -- add your button handler code here..
        //[/UserButtonCode_editShowMidiNote]
    }
    else if (buttonThatWasClicked == editShowScaleDegree.get())
    {
        //[UserButtonCode_editShowScaleDegree] -- add your button handler code here..
        //[/UserButtonCode_editShowScaleDegree]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainWindow::refresh(bool recalculateGenerators)
{
    if (recalculateGenerators)
    {
        editGenerator->clear();

        for (auto g : layout.getValidGenerators())
        {
            editGenerator->addItem(String(g), g);
        }
    }

    editKeyboard->clear();

    if (layout.isValid())
    {
        int i = 1;
        for (auto kbd : layout.getValidKeyboards())
        {
            editKeyboard->addItem(String(kbd.getNumerator()) + "/" + String(kbd.getDenominator()), i++);
        }
    }
    else
    {
        editKeyboard->addItem("Invalid Generator", 1);
    }

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component" constructorParams="LayoutGenerator&amp; layoutToUse"
                 variableInitialisers="layout(layoutToUse)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="new component" id="f8a4a0ba2169ed5d" memberName="keyboardView"
                    virtualName="" explicitFocusOrder="0" pos="0.763% 2.256% 98.379% 66.316%"
                    class="KeyboardViewer" params=""/>
  <SLIDER name="new slider" id="c9338955361b5253" memberName="editPeriod"
          virtualName="" explicitFocusOrder="0" pos="11.249% 106.803% 120 24"
          posRelativeY="f8a4a0ba2169ed5d" min="1.0" max="400.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="d2fccf87f53946cd" memberName="editGenerator"
            virtualName="" explicitFocusOrder="0" pos="11.249% 117.234% 112 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="363a9dc4b5eb4f63" memberName="editKeyboard"
            virtualName="" explicitFocusOrder="0" pos="11.249% 127.664% 112 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="new component" id="80741f8eece04bb7" memberName="editColorLayout"
                    virtualName="" explicitFocusOrder="0" pos="30.982% 106.803% 240 120"
                    posRelativeY="f8a4a0ba2169ed5d" class="Component" params=""/>
  <TOGGLEBUTTON name="new toggle button" id="3fefe6b79e2bbe21" memberName="editShowKeyNumber"
                virtualName="" explicitFocusOrder="0" pos="154.583% 107.256% 176 24"
                posRelativeX="80741f8eece04bb7" posRelativeY="f8a4a0ba2169ed5d"
                buttonText="Full Keyboard Number" connectedEdges="0" needsCallback="1"
                radioGroupId="10" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d5902f532f1a13b4" memberName="editShowOctaveNum"
                virtualName="" explicitFocusOrder="0" pos="0 133.333% 176 24"
                posRelativeX="3fefe6b79e2bbe21" posRelativeY="3fefe6b79e2bbe21"
                buttonText="Octave Number" connectedEdges="0" needsCallback="1"
                radioGroupId="10" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="cd8f1afc15d93282" memberName="editShowMidiNote"
                virtualName="" explicitFocusOrder="0" pos="0 133.333% 176 24"
                posRelativeX="3fefe6b79e2bbe21" posRelativeY="d5902f532f1a13b4"
                buttonText="MIDI Note" connectedEdges="0" needsCallback="1" radioGroupId="10"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="90354e3468042d3e" memberName="editShowScaleDegree"
                virtualName="" explicitFocusOrder="0" pos="0 133.333% 176 24"
                posRelativeX="3fefe6b79e2bbe21" posRelativeY="cd8f1afc15d93282"
                buttonText="Scale Degree" connectedEdges="0" needsCallback="1"
                radioGroupId="10" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

