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
MainWindow::MainWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..
	layout.reset(new LayoutGenerator(12));
    //[/Constructor_pre]

    keyboardView.reset (new KeyboardViewer (layout.get()));
    addAndMakeVisible (keyboardView.get());
    keyboardView->setName ("new component");

    editPeriod.reset (new Slider ("new slider"));
    addAndMakeVisible (editPeriod.get());
    editPeriod->setRange (3, 400, 1);
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

    editGeneratorOffset.reset (new Slider ("new slider"));
    addAndMakeVisible (editGeneratorOffset.get());
    editGeneratorOffset->setRange (-6, 6, 1);
    editGeneratorOffset->setSliderStyle (Slider::IncDecButtons);
    editGeneratorOffset->setTextBoxStyle (Slider::TextBoxLeft, false, 60, 20);
    editGeneratorOffset->addListener (this);

    periodLbl.reset (new Label ("new label",
                                TRANS("Period:")));
    addAndMakeVisible (periodLbl.get());
    periodLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    periodLbl->setJustificationType (Justification::centredLeft);
    periodLbl->setEditable (false, false, false);
    periodLbl->setColour (TextEditor::textColourId, Colours::black);
    periodLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    genLbl.reset (new Label ("new label",
                             TRANS("Generator:")));
    addAndMakeVisible (genLbl.get());
    genLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    genLbl->setJustificationType (Justification::centredLeft);
    genLbl->setEditable (false, false, false);
    genLbl->setColour (TextEditor::textColourId, Colours::black);
    genLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    offsetLbl.reset (new Label ("new label",
                                TRANS("Offset:")));
    addAndMakeVisible (offsetLbl.get());
    offsetLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    offsetLbl->setJustificationType (Justification::centredLeft);
    offsetLbl->setEditable (false, false, false);
    offsetLbl->setColour (TextEditor::textColourId, Colours::black);
    offsetLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    ScaleSize.reset (new Label ("new label",
                                TRANS("Scale Size:")));
    addAndMakeVisible (ScaleSize.get());
    ScaleSize->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    ScaleSize->setJustificationType (Justification::centredLeft);
    ScaleSize->setEditable (false, false, false);
    ScaleSize->setColour (TextEditor::textColourId, Colours::black);
    ScaleSize->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    editRootSld.reset (new Slider ("new slider"));
    addAndMakeVisible (editRootSld.get());
    editRootSld->setRange (0, 274, 1);
    editRootSld->setSliderStyle (Slider::IncDecButtons);
    editRootSld->setTextBoxStyle (Slider::TextBoxLeft, false, 60, 20);
    editRootSld->addListener (this);

    rootLbl.reset (new Label ("new label",
                              TRANS("Root Key: ")));
    addAndMakeVisible (rootLbl.get());
    rootLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    rootLbl->setJustificationType (Justification::centredLeft);
    rootLbl->setEditable (false, false, false);
    rootLbl->setColour (TextEditor::textColourId, Colours::black);
    rootLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label.reset (new Label ("new label",
                            TRANS("Color Selection:")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    editScaleFlip.reset (new ToggleButton ("new toggle button"));
    addAndMakeVisible (editScaleFlip.get());
    editScaleFlip->setButtonText (TRANS("Flip"));
    editScaleFlip->addListener (this);


    //[UserPreSize]
	DBG("MAIN WINDOW: Setting size...");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	DBG("MAIN WINDOW: Constructed! Refreshing options...");
    //refresh();

	DBG("MAIN WINDOW: Setting default values...");
	// Default values
	editRootSld->setValue(129);
	editPeriod->setValue(12);
	editGeneratorOffset->setValue(-1);
	editGenerator->setSelectedId(7);
	//editKeyboard->setSelectedId(7);

	DBG("MAIN WINDOW: Done. Moving on.");
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
    editGeneratorOffset = nullptr;
    periodLbl = nullptr;
    genLbl = nullptr;
    offsetLbl = nullptr;
    ScaleSize = nullptr;
    editRootSld = nullptr;
    rootLbl = nullptr;
    label = nullptr;
    editScaleFlip = nullptr;


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

    keyboardView->setBounds (proportionOfWidth (0.0078f), proportionOfHeight (0.0222f), proportionOfWidth (0.9839f), proportionOfHeight (0.6630f));
    editPeriod->setBounds (proportionOfWidth (0.1391f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0684f), 120, 24);
    editGenerator->setBounds (proportionOfWidth (0.1401f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.1453f), 112, 24);
    editKeyboard->setBounds (proportionOfWidth (0.1401f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.2905f), 112, 24);
    editColorLayout->setBounds (proportionOfWidth (0.3594f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0726f), roundToInt (proportionOfWidth (0.9839f) * 0.3324f), 154);
    editShowKeyNumber->setBounds (proportionOfWidth (0.0078f) + roundToInt (proportionOfWidth (0.9839f) * 0.7200f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0908f), 176, 24);
    editShowOctaveNum->setBounds ((proportionOfWidth (0.0078f) + roundToInt (proportionOfWidth (0.9839f) * 0.7200f)) + 0, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0908f)) + roundToInt (24 * 1.3333f), 176, 24);
    editShowMidiNote->setBounds ((proportionOfWidth (0.0078f) + roundToInt (proportionOfWidth (0.9839f) * 0.7200f)) + 0, ((proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0908f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f), 176, 24);
    editShowScaleDegree->setBounds ((proportionOfWidth (0.0078f) + roundToInt (proportionOfWidth (0.9839f) * 0.7200f)) + 0, (((proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0908f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f)) + roundToInt (24 * 1.3333f), 176, 24);
    editGeneratorOffset->setBounds (proportionOfWidth (0.1401f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.2179f), 120, 24);
    periodLbl->setBounds (proportionOfWidth (0.1391f) + -55, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0684f)) + 0, 64, 24);
    genLbl->setBounds (proportionOfWidth (0.1401f) + -81, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.1453f)) + 0, 88, 24);
    offsetLbl->setBounds (proportionOfWidth (0.1401f) + -56, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.2179f)) + 0, 64, 24);
    ScaleSize->setBounds (proportionOfWidth (0.1401f) + -82, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.2905f)) + 0, 88, 24);
    editRootSld->setBounds (proportionOfWidth (0.1401f), proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.3645f), 120, 24);
    rootLbl->setBounds (proportionOfWidth (0.1401f) + -75, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.3645f)) + 0, 80, 24);
    label->setBounds (proportionOfWidth (0.3594f) + (roundToInt (proportionOfWidth (0.9839f) * 0.3324f)) / 2 - (112 / 2), (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.0726f)) + -22, 112, 24);
    editScaleFlip->setBounds (proportionOfWidth (0.1401f) + 120 - -6, (proportionOfHeight (0.0222f) + roundToInt (proportionOfHeight (0.6630f) * 1.2179f)) + 0, roundToInt (proportionOfWidth (0.9839f) * 0.0699f), 24);
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
		period = editPeriod->getValue();
		DBG("Period box has changed to " + String(period));
		layout.reset(new LayoutGenerator(period));
		refreshSelections();
        //[/UserSliderCode_editPeriod]
    }
    else if (sliderThatWasMoved == editGeneratorOffset.get())
    {
        //[UserSliderCode_editGeneratorOffset] -- add your slider handling code here..
		genOffset = editGeneratorOffset->getValue();
		layout->setGeneratorOffset(genOffset);
		layout->refresh();
		refreshKeyboardView();
		//keyboardView->setScale(kbdScalePattern(129, periodHXY, genHXY, size, genOffset));
        //[/UserSliderCode_editGeneratorOffset]
    }
    else if (sliderThatWasMoved == editRootSld.get())
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

void MainWindow::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == editGenerator.get())
    {
        //[UserComboBoxCode_editGenerator] -- add your combo box handling code here..
		generator = editGenerator->getSelectedId();
		DBG("Generator box has changed, generator is " + String(generator));
		layout->setGenerator(generator);

		refreshSelections(false);

		int suggestedKbd = layout->suggestedScaleSize();
		DBG("Suggested scale size: " + String(layout->getValidSizes()[suggestedKbd]));
		editKeyboard->setSelectedId(suggestedKbd + 1, dontSendNotification);
        //[/UserComboBoxCode_editGenerator]
    }
    else if (comboBoxThatHasChanged == editKeyboard.get())
    {
        //[UserComboBoxCode_editKeyboard] -- add your combo box handling code here..
		DBG("Keyboard box has changed");
        //[/UserComboBoxCode_editKeyboard]
    }

    //[UsercomboBoxChanged_Post]

	int ind = editKeyboard->getSelectedId() - 1;
	layout->setKeyboardType(ind);
	size = layout->getScaleSize();
	periodHXY = layout->getPGCoord().x;
	genHXY = layout->getPGCoord().y;

	// quick crash prevention, bad solution
	if (periodHXY.x * periodHXY.y * genHXY.x * genHXY.y > 0)
	{
		DBG("Delta coordinates are: (" + layout->getXYSteps(ind).toString() + ")");
	}
	else
	{
		DBG("ERROR: 0 is in either Period: (" + periodHXY.toString() + ") or Gen: (" + genHXY.toString() + "). FIX ME!");
	}

	layout->refresh();
	keyboardView->setLayout(layout.get());
    //[/UsercomboBoxChanged_Post]
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

    //[UserbuttonClicked_Post]
	keyboardView->repaint();
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainWindow::refreshSelections(bool recalculateGenerators)
{
    if (recalculateGenerators)
    {
        editGenerator->clear(dontSendNotification);

        for (auto g : layout->getValidGenerators())
        {
            editGenerator->addItem(String(g), g);
        }

		generator = layout->getValidGenerators()[layout->suggestedGenerator()];
		DBG("Suggested generator: " + String(generator));
		editGenerator->setSelectedId(generator);
		DBG("MAIN WINDOW: finished recalulating generators");
		// gets called again when generator is set
		return;
    }

    editKeyboard->clear(dontSendNotification);

    if (layout->isValid())
    {
		DBG("Updating Generator Offsets and Keyboard Sizes");
		// update gen offset range
		if (editGenerator->getSelectedId() > 0)
			editGeneratorOffset->setRange(-(editGenerator->getSelectedId()), editGenerator->getSelectedId(), 1);

		// update keyboard options
        for (int i = 0; i < layout->getValidKeyboards().size() - 2; i++)
        {
            editKeyboard->addItem(String(layout->getValidSizes()[i]), i+1);
        }
    }
    else
    {
        editKeyboard->addItem("Invalid Generator", 1);
    }
}

void MainWindow::refreshKeyboardView()
{
	keyboardView->setLayout(layout.get());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GENERICCOMPONENT name="new component" id="f8a4a0ba2169ed5d" memberName="keyboardView"
                    virtualName="" explicitFocusOrder="0" pos="0.807% 2.256% 98.385% 66.316%"
                    class="KeyboardViewer" params="layout.get()"/>
  <SLIDER name="new slider" id="c9338955361b5253" memberName="editPeriod"
          virtualName="" explicitFocusOrder="0" pos="13.925% 106.803% 120 24"
          posRelativeY="f8a4a0ba2169ed5d" min="3.0" max="400.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="new combo box" id="d2fccf87f53946cd" memberName="editGenerator"
            virtualName="" explicitFocusOrder="0" pos="14.026% 114.512% 112 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="new combo box" id="363a9dc4b5eb4f63" memberName="editKeyboard"
            virtualName="" explicitFocusOrder="0" pos="14.026% 129.025% 112 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="new component" id="80741f8eece04bb7" memberName="editColorLayout"
                    virtualName="" explicitFocusOrder="0" pos="35.923% 107.256% 33.231% 154"
                    posRelativeY="f8a4a0ba2169ed5d" posRelativeW="f8a4a0ba2169ed5d"
                    class="Component" params=""/>
  <TOGGLEBUTTON name="new toggle button" id="3fefe6b79e2bbe21" memberName="editShowKeyNumber"
                virtualName="" explicitFocusOrder="0" pos="72% 109.07% 176 24"
                posRelativeX="f8a4a0ba2169ed5d" posRelativeY="f8a4a0ba2169ed5d"
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
  <SLIDER name="new slider" id="cf8ed030b390dba8" memberName="editGeneratorOffset"
          virtualName="" explicitFocusOrder="0" pos="14.026% 121.769% 120 24"
          posRelativeY="f8a4a0ba2169ed5d" min="-6.0" max="6.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="8b29c2f0ff851665" memberName="periodLbl"
         virtualName="" explicitFocusOrder="0" pos="-55 0 64 24" posRelativeX="c9338955361b5253"
         posRelativeY="c9338955361b5253" edTextCol="ff000000" edBkgCol="0"
         labelText="Period:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3e88e9cd29d6aede" memberName="genLbl" virtualName=""
         explicitFocusOrder="0" pos="-81 0 88 24" posRelativeX="d2fccf87f53946cd"
         posRelativeY="d2fccf87f53946cd" edTextCol="ff000000" edBkgCol="0"
         labelText="Generator:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="dc6aebf5407d47e5" memberName="offsetLbl"
         virtualName="" explicitFocusOrder="0" pos="-56 0 64 24" posRelativeX="cf8ed030b390dba8"
         posRelativeY="cf8ed030b390dba8" edTextCol="ff000000" edBkgCol="0"
         labelText="Offset:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2f4e8da9f66b9c12" memberName="ScaleSize"
         virtualName="" explicitFocusOrder="0" pos="-82 0 88 24" posRelativeX="363a9dc4b5eb4f63"
         posRelativeY="363a9dc4b5eb4f63" edTextCol="ff000000" edBkgCol="0"
         labelText="Scale Size:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="c486bd0e1ff65df1" memberName="editRootSld"
          virtualName="" explicitFocusOrder="0" pos="14.026% 136.508% 120 24"
          posRelativeY="f8a4a0ba2169ed5d" min="0.0" max="274.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="60" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="c3f7dd0f5b81a1e9" memberName="rootLbl" virtualName=""
         explicitFocusOrder="0" pos="-75 0 80 24" posRelativeX="c486bd0e1ff65df1"
         posRelativeY="c486bd0e1ff65df1" edTextCol="ff000000" edBkgCol="0"
         labelText="Root Key: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9c0e28f4dfed6909" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0Cc -22 112 24" posRelativeX="80741f8eece04bb7"
         posRelativeY="80741f8eece04bb7" edTextCol="ff000000" edBkgCol="0"
         labelText="Color Selection:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TOGGLEBUTTON name="new toggle button" id="f9e862554b787aca" memberName="editScaleFlip"
                virtualName="" explicitFocusOrder="0" pos="-6R 0 6.974% 24" posRelativeX="cf8ed030b390dba8"
                posRelativeY="cf8ed030b390dba8" posRelativeW="f8a4a0ba2169ed5d"
                buttonText="Flip" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

