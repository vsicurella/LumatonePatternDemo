/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

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
MainWindow::MainWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    scaleStructure.reset(new ScaleStructure(12));
	layout.reset(new LayoutHelper(scaleStructure.get()));
	layout->setColours(&scaleColours);
	colourTableModel.reset(new ColourTableModel(layout->getScaleColours()));
    //[/Constructor_pre]

    keyboardView.reset (new KeyboardViewer (layout.get()));
    addAndMakeVisible (keyboardView.get());
    keyboardView->setName ("new component");

    editColorLayout.reset (new ListBox ("Colour Selector", colourTableModel.get()));
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

    genLbl.reset (new Label ("new label",
                             TRANS("Generator:")));
    addAndMakeVisible (genLbl.get());
    genLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    genLbl->setJustificationType (Justification::centredLeft);
    genLbl->setEditable (false, false, false);
    genLbl->setColour (TextEditor::textColourId, Colours::black);
    genLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    genLbl->setBounds (-80, 0, 88, 24);

    editRootSld.reset (new Slider ("editRootSld"));
    addAndMakeVisible (editRootSld.get());
    editRootSld->setRange (0, 274, 1);
    editRootSld->setSliderStyle (Slider::IncDecButtons);
    editRootSld->setTextBoxStyle (Slider::TextBoxLeft, false, 50, 20);
    editRootSld->addListener (this);

    rootLbl.reset (new Label ("new label",
                              TRANS("Root Key: ")));
    addAndMakeVisible (rootLbl.get());
    rootLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rootLbl->setJustificationType (Justification::centredLeft);
    rootLbl->setEditable (false, false, false);
    rootLbl->setColour (TextEditor::textColourId, Colours::black);
    rootLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    colorSelectionLbl.reset (new Label ("colorSelectionLbl",
                                        TRANS("Color Selection\n")));
    addAndMakeVisible (colorSelectionLbl.get());
    colorSelectionLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    colorSelectionLbl->setJustificationType (Justification::centredLeft);
    colorSelectionLbl->setEditable (false, false, false);
    colorSelectionLbl->setColour (TextEditor::textColourId, Colours::black);
    colorSelectionLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    editScaleFlip.reset (new ToggleButton ("editScaleFlip"));
    addAndMakeVisible (editScaleFlip.get());
    editScaleFlip->setButtonText (TRANS("Flip"));
    editScaleFlip->addListener (this);

    editBlankKeys.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editBlankKeys.get());
    editBlankKeys->setButtonText (TRANS("Blank"));
    editBlankKeys->setRadioGroupId (10);
    editBlankKeys->addListener (this);

    negateXBtn.reset (new ToggleButton ("negateXBtn"));
    addAndMakeVisible (negateXBtn.get());
    negateXBtn->setButtonText (TRANS("Negate X"));
    negateXBtn->addListener (this);

    negateYBtn.reset (new ToggleButton ("negateYBtn"));
    addAndMakeVisible (negateYBtn.get());
    negateYBtn->setButtonText (TRANS("Negate Y"));
    negateYBtn->addListener (this);

    scaleStructureComponent.reset (new ScaleStructureComponent (*scaleStructure.get(), scaleColours));
    addAndMakeVisible (scaleStructureComponent.get());
    scaleStructureComponent->setName ("scaleStructureComponent");


    //[UserPreSize]
	colourTableModel->setListBoxComponent(editColorLayout.get());
	editColorLayout->updateContent();
	DBG("MAIN WINDOW: Setting size...");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	scaleStructureComponent->addChangeListener(this);
	DBG("MAIN WINDOW: Setting default values...");
	// Default values
	editRootSld->setValue(135);
	DBG("MAIN WINDOW: Done. Moving on.");
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    keyboardView = nullptr;
    editColorLayout = nullptr;
    editShowKeyNumber = nullptr;
    editShowOctaveNum = nullptr;
    editShowMidiNote = nullptr;
    editShowScaleDegree = nullptr;
    genLbl = nullptr;
    editRootSld = nullptr;
    rootLbl = nullptr;
    colorSelectionLbl = nullptr;
    editScaleFlip = nullptr;
    editBlankKeys = nullptr;
    negateXBtn = nullptr;
    negateYBtn = nullptr;
    scaleStructureComponent = nullptr;


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
	g.drawRect(editColorLayout->getBoundsInParent().expanded(3), 3.0f);
    //[/UserPaint]
}

void MainWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    keyboardView->setBounds (10, proportionOfHeight (0.0283f), proportionOfWidth (0.5803f), proportionOfHeight (0.5406f));
    editColorLayout->setBounds (proportionOfWidth (0.7868f) - (proportionOfWidth (0.3724f) / 2), proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -30, proportionOfWidth (0.3724f), 136);
    editShowKeyNumber->setBounds (20, proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -54, 176, 24);
    editShowOctaveNum->setBounds (20 + 0, (proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -54) + 27, 176, 24);
    editShowMidiNote->setBounds (20 + 0, ((proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -54) + 27) + 27, 176, 24);
    editShowScaleDegree->setBounds (20 + 0, (((proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -54) + 27) + 27) + 27, 176, 24);
    editRootSld->setBounds (90, proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -14, proportionOfWidth (0.1036f), 24);
    rootLbl->setBounds (90 + -75, (proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -14) + 0, 80, 24);
    colorSelectionLbl->setBounds ((proportionOfWidth (0.7868f) - (proportionOfWidth (0.3724f) / 2)) + proportionOfWidth (0.3724f) / 2 - (112 / 2), (proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -30) + -24, 112, 24);
    editScaleFlip->setBounds (((proportionOfWidth (0.3163f) - (proportionOfWidth (0.0990f) / 2)) + roundToInt (proportionOfWidth (0.0990f) * 1.1591f)) + 91, ((proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -14) + roundToInt (24 * 0.0000f)) + 0, roundToInt (proportionOfWidth (0.5803f) * 0.1680f), 24);
    editBlankKeys->setBounds (20 + 0, ((((proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -54) + 27) + 27) + 27) + 27, 176, 24);
    negateXBtn->setBounds (proportionOfWidth (0.3163f) - (proportionOfWidth (0.0990f) / 2), proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -14, proportionOfWidth (0.0990f), 24);
    negateYBtn->setBounds ((proportionOfWidth (0.3163f) - (proportionOfWidth (0.0990f) / 2)) + roundToInt (proportionOfWidth (0.0990f) * 1.1591f), (proportionOfHeight (0.0283f) + proportionOfHeight (0.5406f) - -14) + roundToInt (24 * 0.0000f), proportionOfWidth (0.1006f), 24);
    scaleStructureComponent->setBounds (10 + proportionOfWidth (0.5803f) - -23, proportionOfHeight (0.0283f) + 0, 504, roundToInt (proportionOfHeight (0.5406f) * 1.0000f));
    //[UserResized] Add your own custom resize handling here..

	// update color box row heights
	int idealHeight = editColorLayout->getHeight() / colourTableModel->getNumRows() * colourTableModel->getNumRows();
	editColorLayout->setSize(editColorLayout->getWidth(), idealHeight);
	scaleStructureComponent->setSize(scaleStructureComponent->getHeight(), scaleStructureComponent->getHeight());
    //[/UserResized]
}

void MainWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == editShowKeyNumber.get())
    {
        //[UserButtonCode_editShowKeyNumber] -- add your button handler code here..
		keyboardView->setKeyTextShown(KeyboardViewer::KeyText::KeyNumber);
        //[/UserButtonCode_editShowKeyNumber]
    }
    else if (buttonThatWasClicked == editShowOctaveNum.get())
    {
        //[UserButtonCode_editShowOctaveNum] -- add your button handler code here..
		keyboardView->setKeyTextShown(KeyboardViewer::KeyText::OctaveNumber);
        //[/UserButtonCode_editShowOctaveNum]
    }
    else if (buttonThatWasClicked == editShowMidiNote.get())
    {
        //[UserButtonCode_editShowMidiNote] -- add your button handler code here..
		keyboardView->setKeyTextShown(KeyboardViewer::KeyText::MidiNote);
        //[/UserButtonCode_editShowMidiNote]
    }
    else if (buttonThatWasClicked == editShowScaleDegree.get())
    {
        //[UserButtonCode_editShowScaleDegree] -- add your button handler code here..
		keyboardView->setKeyTextShown(KeyboardViewer::KeyText::ScaleDegree);
        //[/UserButtonCode_editShowScaleDegree]
    }
    else if (buttonThatWasClicked == editScaleFlip.get())
    {
        //[UserButtonCode_editScaleFlip] -- add your button handler code here..
		layout->setScaleFlipped(editScaleFlip->getToggleState());
        //[/UserButtonCode_editScaleFlip]
    }
    else if (buttonThatWasClicked == editBlankKeys.get())
    {
        //[UserButtonCode_editBlankKeys] -- add your button handler code here..
		keyboardView->setKeyTextShown(KeyboardViewer::KeyText::Blank);
        //[/UserButtonCode_editBlankKeys]
    }
    else if (buttonThatWasClicked == negateXBtn.get())
    {
        //[UserButtonCode_negateXBtn] -- add your button handler code here..
		layout->setNegateX(negateXBtn->getToggleState());
        //[/UserButtonCode_negateXBtn]
    }
    else if (buttonThatWasClicked == negateYBtn.get())
    {
        //[UserButtonCode_negateYBtn] -- add your button handler code here..
		layout->setNegateY(negateYBtn->getToggleState());
        //[/UserButtonCode_negateYBtn]
    }

    //[UserbuttonClicked_Post]
	keyboardView->repaint();
    //[/UserbuttonClicked_Post]
}

void MainWindow::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == editRootSld.get())
    {
        //[UserSliderCode_editRootSld] -- add your slider handling code here..
		rootKey = editRootSld->getValue();
		layout->setRootKey(rootKey);
		refreshKeyboardView();
        //[/UserSliderCode_editRootSld]
    }

    //[UsersliderValueChanged_Post]

    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainWindow::refreshKeyboardView()
{
	layout->refresh();
	//keyboardView->repaint();
}

void MainWindow::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == scaleStructureComponent.get())
	{
		refreshKeyboardView();
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
                 parentClasses="public Component, public ChangeListener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="new component" id="f8a4a0ba2169ed5d" memberName="keyboardView"
                    virtualName="" explicitFocusOrder="0" pos="10 2.847% 58.033% 54.1%"
                    class="KeyboardViewer" params="layout.get()"/>
  <GENERICCOMPONENT name="new component" id="80741f8eece04bb7" memberName="editColorLayout"
                    virtualName="" explicitFocusOrder="0" pos="78.679%c -30R 37.237% 136"
                    posRelativeY="f8a4a0ba2169ed5d" class="ListBox" params="&quot;Colour Selector&quot;, colourTableModel.get()"/>
  <TOGGLEBUTTON name="new toggle button" id="3fefe6b79e2bbe21" memberName="editShowKeyNumber"
                virtualName="" explicitFocusOrder="0" pos="20 -54R 176 24" posRelativeY="f8a4a0ba2169ed5d"
                buttonText="Full Keyboard Number" connectedEdges="0" needsCallback="1"
                radioGroupId="10" state="1"/>
  <TOGGLEBUTTON name="new toggle button" id="d5902f532f1a13b4" memberName="editShowOctaveNum"
                virtualName="" explicitFocusOrder="0" pos="0 27 176 24" posRelativeX="3fefe6b79e2bbe21"
                posRelativeY="3fefe6b79e2bbe21" buttonText="Octave Number" connectedEdges="0"
                needsCallback="1" radioGroupId="10" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="cd8f1afc15d93282" memberName="editShowMidiNote"
                virtualName="" explicitFocusOrder="0" pos="0 27 176 24" posRelativeX="3fefe6b79e2bbe21"
                posRelativeY="d5902f532f1a13b4" buttonText="MIDI Note" connectedEdges="0"
                needsCallback="1" radioGroupId="10" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="90354e3468042d3e" memberName="editShowScaleDegree"
                virtualName="" explicitFocusOrder="0" pos="0 27 176 24" posRelativeX="3fefe6b79e2bbe21"
                posRelativeY="cd8f1afc15d93282" buttonText="Scale Degree" connectedEdges="0"
                needsCallback="1" radioGroupId="10" state="0"/>
  <LABEL name="new label" id="3e88e9cd29d6aede" memberName="genLbl" virtualName=""
         explicitFocusOrder="0" pos="-80 0 88 24" posRelativeX="47c080d0f31dbabc"
         posRelativeY="47c080d0f31dbabc" edTextCol="ff000000" edBkgCol="0"
         labelText="Generator:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="editRootSld" id="c486bd0e1ff65df1" memberName="editRootSld"
          virtualName="" explicitFocusOrder="0" pos="90 -14R 10.36% 24"
          posRelativeY="f8a4a0ba2169ed5d" min="0.0" max="274.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="c3f7dd0f5b81a1e9" memberName="rootLbl" virtualName=""
         explicitFocusOrder="0" pos="-75 0 80 24" posRelativeX="c486bd0e1ff65df1"
         posRelativeY="c486bd0e1ff65df1" edTextCol="ff000000" edBkgCol="0"
         labelText="Root Key: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="colorSelectionLbl" id="9c0e28f4dfed6909" memberName="colorSelectionLbl"
         virtualName="" explicitFocusOrder="0" pos="0Cc -24 112 24" posRelativeX="80741f8eece04bb7"
         posRelativeY="80741f8eece04bb7" edTextCol="ff000000" edBkgCol="0"
         labelText="Color Selection&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="editScaleFlip" id="f9e862554b787aca" memberName="editScaleFlip"
                virtualName="" explicitFocusOrder="0" pos="91 0 16.818% 24" posRelativeX="91bd59afec743d5b"
                posRelativeY="91bd59afec743d5b" posRelativeW="f8a4a0ba2169ed5d"
                buttonText="Flip" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="eb5b9b780ba3f90c" memberName="editBlankKeys"
                virtualName="" explicitFocusOrder="0" pos="0 27 176 24" posRelativeX="3fefe6b79e2bbe21"
                posRelativeY="90354e3468042d3e" buttonText="Blank" connectedEdges="0"
                needsCallback="1" radioGroupId="10" state="0"/>
  <TOGGLEBUTTON name="negateXBtn" id="fe6ffcda9917ff6" memberName="negateXBtn"
                virtualName="" explicitFocusOrder="0" pos="31.607%c -14R 9.91% 24"
                posRelativeY="f8a4a0ba2169ed5d" buttonText="Negate X" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="negateYBtn" id="91bd59afec743d5b" memberName="negateYBtn"
                virtualName="" explicitFocusOrder="0" pos="115.909% 0% 10.06% 24"
                posRelativeX="fe6ffcda9917ff6" posRelativeY="fe6ffcda9917ff6"
                buttonText="Negate Y" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <GENERICCOMPONENT name="scaleStructureComponent" id="b43f58850a822163" memberName="scaleStructureComponent"
                    virtualName="" explicitFocusOrder="0" pos="-23R 0 504 100%" posRelativeX="f8a4a0ba2169ed5d"
                    posRelativeY="f8a4a0ba2169ed5d" posRelativeH="f8a4a0ba2169ed5d"
                    class="ScaleStructureComponent" params="*scaleStructure.get(), scaleColours"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

