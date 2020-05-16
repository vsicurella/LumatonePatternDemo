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

    editPeriod.reset (new Slider ("editPeriod"));
    addAndMakeVisible (editPeriod.get());
    editPeriod->setRange (3, 400, 1);
    editPeriod->setSliderStyle (Slider::IncDecButtons);
    editPeriod->setTextBoxStyle (Slider::TextBoxLeft, false, 50, 20);
    editPeriod->addListener (this);

    editGenerator.reset (new ComboBox ("editGenerator"));
    addAndMakeVisible (editGenerator.get());
    editGenerator->setEditableText (false);
    editGenerator->setJustificationType (Justification::centredLeft);
    editGenerator->setTextWhenNothingSelected (String());
    editGenerator->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    editGenerator->addListener (this);

    editKeyboard.reset (new ComboBox ("editKeyboard"));
    addAndMakeVisible (editKeyboard.get());
    editKeyboard->setEditableText (false);
    editKeyboard->setJustificationType (Justification::centredLeft);
    editKeyboard->setTextWhenNothingSelected (String());
    editKeyboard->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    editKeyboard->addListener (this);

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

    editGeneratorOffset.reset (new Slider ("editGeneratorOffset"));
    addAndMakeVisible (editGeneratorOffset.get());
    editGeneratorOffset->setRange (-6, 6, 1);
    editGeneratorOffset->setSliderStyle (Slider::IncDecButtons);
    editGeneratorOffset->setTextBoxStyle (Slider::TextBoxLeft, false, 50, 20);
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

    genLbl->setBounds (-80, 0, 88, 24);

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

    modMosDegreeBox.reset (new ComboBox ("modMosDegreeBox"));
    addAndMakeVisible (modMosDegreeBox.get());
    modMosDegreeBox->setEditableText (false);
    modMosDegreeBox->setJustificationType (Justification::centredLeft);
    modMosDegreeBox->setTextWhenNothingSelected (String());
    modMosDegreeBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    modMosDegreeBox->addListener (this);

    numPeriodsLabel.reset (new Label ("numPeriodsLabel",
                                      TRANS("Num Periods:")));
    addAndMakeVisible (numPeriodsLabel.get());
    numPeriodsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    numPeriodsLabel->setJustificationType (Justification::centredLeft);
    numPeriodsLabel->setEditable (false, false, false);
    numPeriodsLabel->setColour (TextEditor::textColourId, Colours::black);
    numPeriodsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    modMosDegreeLbl.reset (new Label ("modMosDegreeLbl",
                                      TRANS("MODMOS Degree Selector")));
    addAndMakeVisible (modMosDegreeLbl.get());
    modMosDegreeLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    modMosDegreeLbl->setJustificationType (Justification::centredLeft);
    modMosDegreeLbl->setEditable (false, false, false);
    modMosDegreeLbl->setColour (TextEditor::textColourId, Colours::black);
    modMosDegreeLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    modMosChromaSld.reset (new Slider ("modMosChromaSld"));
    addAndMakeVisible (modMosChromaSld.get());
    modMosChromaSld->setRange (-10, 10, 1);
    modMosChromaSld->setSliderStyle (Slider::IncDecButtons);
    modMosChromaSld->setTextBoxStyle (Slider::TextBoxLeft, false, 50, 20);
    modMosChromaSld->addListener (this);

    modMosChromaLbl.reset (new Label ("modMosChromaLbl",
                                      TRANS("MODMOS Chroma Amount")));
    addAndMakeVisible (modMosChromaLbl.get());
    modMosChromaLbl->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    modMosChromaLbl->setJustificationType (Justification::centredLeft);
    modMosChromaLbl->setEditable (false, false, false);
    modMosChromaLbl->setColour (TextEditor::textColourId, Colours::black);
    modMosChromaLbl->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    generatorLabel.reset (new Label ("generatorLabel",
                                     TRANS("Generator: ")));
    addAndMakeVisible (generatorLabel.get());
    generatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    generatorLabel->setJustificationType (Justification::centredLeft);
    generatorLabel->setEditable (false, false, false);
    generatorLabel->setColour (TextEditor::textColourId, Colours::black);
    generatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    numPeriodBox.reset (new ComboBox ("numPeriodBox"));
    addAndMakeVisible (numPeriodBox.get());
    numPeriodBox->setEditableText (false);
    numPeriodBox->setJustificationType (Justification::centredLeft);
    numPeriodBox->setTextWhenNothingSelected (String());
    numPeriodBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    numPeriodBox->addListener (this);


    //[UserPreSize]
	colourTableModel->setListBoxComponent(editColorLayout.get());
	editColorLayout->updateContent();
	DBG("MAIN WINDOW: Setting size...");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	DBG("MAIN WINDOW: Constructed! Refreshing options...");
    //refresh();

	DBG("MAIN WINDOW: Setting default values...");
	// Default values
	editRootSld->setValue(135);
	editPeriod->setValue(12, sendNotificationSync);
	editGeneratorOffset->setValue(1);
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
    colorSelectionLbl = nullptr;
    editScaleFlip = nullptr;
    editBlankKeys = nullptr;
    negateXBtn = nullptr;
    negateYBtn = nullptr;
    modMosDegreeBox = nullptr;
    numPeriodsLabel = nullptr;
    modMosDegreeLbl = nullptr;
    modMosChromaSld = nullptr;
    modMosChromaLbl = nullptr;
    generatorLabel = nullptr;
    numPeriodBox = nullptr;


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

    keyboardView->setBounds (proportionOfWidth (0.0090f), proportionOfHeight (0.0228f), proportionOfWidth (0.9835f), proportionOfHeight (0.6640f));
    editPeriod->setBounds (proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -21, proportionOfWidth (0.1036f), 24);
    editGenerator->setBounds (proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -61, proportionOfWidth (0.1036f), 24);
    editKeyboard->setBounds (proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -101, proportionOfWidth (0.1036f), 24);
    editColorLayout->setBounds (proportionOfWidth (0.6731f) - ((roundToInt (proportionOfWidth (0.9835f) * 0.1183f)) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -36, roundToInt (proportionOfWidth (0.9835f) * 0.1183f), 136);
    editShowKeyNumber->setBounds (proportionOfWidth (0.8709f) - (176 / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -24, 176, 24);
    editShowOctaveNum->setBounds ((proportionOfWidth (0.8709f) - (176 / 2)) + 0, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -24) + 27, 176, 24);
    editShowMidiNote->setBounds ((proportionOfWidth (0.8709f) - (176 / 2)) + 0, ((proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -24) + 27) + 27, 176, 24);
    editShowScaleDegree->setBounds ((proportionOfWidth (0.8709f) - (176 / 2)) + 0, (((proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -24) + 27) + 27) + 27, 176, 24);
    editGeneratorOffset->setBounds (proportionOfWidth (0.3348f) - (proportionOfWidth (0.1036f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -60, proportionOfWidth (0.1036f), 24);
    periodLbl->setBounds ((proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2)) + -55, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -21) + 0, 64, 24);
    offsetLbl->setBounds ((proportionOfWidth (0.3348f) - (proportionOfWidth (0.1036f) / 2)) + -56, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -60) + 0, 64, 24);
    ScaleSize->setBounds ((proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2)) + -82, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -101) + 0, 88, 24);
    editRootSld->setBounds (proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -141, proportionOfWidth (0.1036f), 24);
    rootLbl->setBounds ((proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2)) + -75, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -141) + 0, 80, 24);
    colorSelectionLbl->setBounds ((proportionOfWidth (0.6731f) - ((roundToInt (proportionOfWidth (0.9835f) * 0.1183f)) / 2)) + (roundToInt (proportionOfWidth (0.9835f) * 0.1183f)) / 2 - (112 / 2), (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -36) + -24, 112, 24);
    editScaleFlip->setBounds (((proportionOfWidth (0.2853f) - (88 / 2)) + roundToInt (88 * 0.0000f)) + 0, ((proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -96) + roundToInt (24 * 1.1667f)) + 28, roundToInt (proportionOfWidth (0.9835f) * 0.0702f), 24);
    editBlankKeys->setBounds ((proportionOfWidth (0.8709f) - (176 / 2)) + 0, ((((proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -24) + 27) + 27) + 27) + 27, 176, 24);
    negateXBtn->setBounds (proportionOfWidth (0.2853f) - (88 / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -96, 88, 24);
    negateYBtn->setBounds ((proportionOfWidth (0.2853f) - (88 / 2)) + roundToInt (88 * 0.0000f), (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -96) + roundToInt (24 * 1.1667f), 88, 24);
    modMosDegreeBox->setBounds (proportionOfWidth (0.5000f) - (proportionOfWidth (0.0886f) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -45, proportionOfWidth (0.0886f), 24);
    numPeriodsLabel->setBounds (proportionOfWidth (0.2342f), ((proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -21) + 0) + 0, proportionOfWidth (0.0706f), 24);
    modMosDegreeLbl->setBounds ((proportionOfWidth (0.5000f) - (proportionOfWidth (0.0886f) / 2)) + proportionOfWidth (0.0886f) / 2 - (176 / 2), (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -45) + 24 - 56, 176, 24);
    modMosChromaSld->setBounds (proportionOfWidth (0.4985f) - ((roundToInt (proportionOfWidth (0.9835f) * 0.1038f)) / 2), proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -109, roundToInt (proportionOfWidth (0.9835f) * 0.1038f), 24);
    modMosChromaLbl->setBounds ((proportionOfWidth (0.4985f) - ((roundToInt (proportionOfWidth (0.9835f) * 0.1038f)) / 2)) + (roundToInt (proportionOfWidth (0.9835f) * 0.1038f)) / 2 - (176 / 2), (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -109) + -32, 176, 24);
    generatorLabel->setBounds ((proportionOfWidth (0.1764f) - (proportionOfWidth (0.1036f) / 2)) + -78, (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -61) + 0, 80, 24);
    numPeriodBox->setBounds (proportionOfWidth (0.3120f), (proportionOfHeight (0.0228f) + proportionOfHeight (0.6640f) - -21) + 24 / 2 - (24 / 2), proportionOfWidth (0.0846f), 24);
    //[UserResized] Add your own custom resize handling here..

	// update color box row heights
	int idealHeight = editColorLayout->getHeight() / colourTableModel->getNumRows() * colourTableModel->getNumRows();
	editColorLayout->setSize(editColorLayout->getWidth(), idealHeight);
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
		scaleStructure->resetToPeriod(period);
		/*layout->setColours(&scaleColours);
		colourTableModel->setColours(&scaleColours);*/
		onPeriodChange();
        //[/UserSliderCode_editPeriod]
    }
    else if (sliderThatWasMoved == editGeneratorOffset.get())
    {
        //[UserSliderCode_editGeneratorOffset] -- add your slider handling code here..
		genOffset = editGeneratorOffset->getValue();
		scaleStructure->setGeneratorOffset(genOffset);
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
    else if (sliderThatWasMoved == modMosChromaSld.get())
    {
        //[UserSliderCode_modMosChromaSld] -- add your slider handling code here..
		int naturalDegree = modMosDegreeBox->getSelectedId() - 1;
		scaleStructure->setAlterationofDegree(naturalDegree, modMosChromaSld->getValue());
        //[/UserSliderCode_modMosChromaSld]
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
		genIndex = editGenerator->getSelectedId() - 1;
		scaleStructure->setGeneratorIndex(genIndex);
		onGeneratorChange();
        //[/UserComboBoxCode_editGenerator]
    }
    else if (comboBoxThatHasChanged == editKeyboard.get())
    {
        //[UserComboBoxCode_editKeyboard] -- add your combo box handling code here..
		sizeIndex = jmax(1, editKeyboard->getSelectedId() - 1);
		DBG("SIZE BOX INDEX SET TO " + String(sizeIndex));
		scaleStructure->setSizeIndex(sizeIndex);
		onSizeChange();
		refreshKeyboardView();
        //[/UserComboBoxCode_editKeyboard]
    }
    else if (comboBoxThatHasChanged == modMosDegreeBox.get())
    {
        //[UserComboBoxCode_modMosDegreeBox] -- add your combo box handling code here..
		modMosChromaSld->setValue(scaleStructure->getAlterationOfDegree(modMosDegreeBox->getSelectedId() - 1), dontSendNotification);
		refreshKeyboardView();
        //[/UserComboBoxCode_modMosDegreeBox]
    }
    else if (comboBoxThatHasChanged == numPeriodBox.get())
    {
        //[UserComboBoxCode_numPeriodBox] -- add your combo box handling code here..
		periodFactorIndex = numPeriodBox->getSelectedId() - 1;
		onPeriodFactorChange();
        //[/UserComboBoxCode_numPeriodBox]
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainWindow::onPeriodChange()
{
	DBG("Period has changed to " + String(period));
	// Set up period factors
	periodFactors = scaleStructure->getPeriodFactors();
	numPeriodBox->clear(dontSendNotification);
	for (int i = 0; i < periodFactors.size(); i++)
		numPeriodBox->addItem(String(periodFactors[i]), i + 1);
	numPeriodBox->setSelectedId(1, sendNotificationSync);

	modMosChromaSld->setRange(-period, period, 1);
}

void MainWindow::onPeriodFactorChange()
{
	scaleStructure->setAll(period, -1, -1, editGeneratorOffset->getValue(), numPeriodBox->getSelectedId() - 1);
	DBG("Period factor has changed, fractional period is " + String(scaleStructure->getPeriod(true)));

	refreshGenerators(false);
	refreshSizes(false);

	sizeIndex = scaleStructure->getScaleSizeIndex();
	onSizeChange();
	refreshKeyboardView();
}

void MainWindow::onGeneratorChange()
{
	DBG("Generator box has changed, generator is " + String(scaleStructure->getGenerator()));
	refreshSizes();
}

void MainWindow::onSizeChange()
{
	if (scaleStructure->getScaleSize() > 1)
	{
		editGeneratorOffset->setEnabled(true);
		editGeneratorOffset->setRange(0, scaleStructure->getScaleSize() - 1, 1);
	}
	else
		editGeneratorOffset->setEnabled(false);

	// Update modmos degree box to have 'size' amount of degrees
	modMosDegreeBox->clear(dontSendNotification);
	for (int i = 0; i < scaleStructure->getScaleSize() * scaleStructure->getPeriodFactor(); i++)
	{
		modMosDegreeBox->addItem(String(i + 1), i + 1);
	}
	modMosDegreeBox->setSelectedId(1);

	DBG("Step sizes: " + scaleStructure->getStepSize().toString());
}

void MainWindow::refreshGenerators(bool updateControl)
{
	// Update generators
	validGenerators = scaleStructure->getValidGenerators();
	editGenerator->clear(dontSendNotification);
	for (int i = 0; i < validGenerators.size(); i++)
	{
		editGenerator->addItem(String(validGenerators[i]), i + 1);
	}

	NotificationType notify = updateControl ? sendNotificationSync : dontSendNotification;
	editGenerator->setSelectedId(scaleStructure->getSuggestedGeneratorIndex() + 1, notify);
}

void MainWindow::refreshSizes(bool updateControl)
{
	// update keyboard options
	validSizes = scaleStructure->getScaleSizes();
	editKeyboard->clear(dontSendNotification);
	for (int i = 1; i < validSizes.size(); i++)
	{
		editKeyboard->addItem(String(validSizes[i] * scaleStructure->getPeriodFactor()), i + 1);
	}

	NotificationType notify = updateControl ? sendNotificationSync : dontSendNotification;
	editKeyboard->setSelectedId(scaleStructure->getSuggestedSizeIndex() + 1, notify);
}


void MainWindow::refreshKeyboardView()
{
	layout->refresh();
	keyboardView->repaint();
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
                    virtualName="" explicitFocusOrder="0" pos="0.846% 2.311% 98.307% 66.367%"
                    class="KeyboardViewer" params="layout.get()"/>
  <SLIDER name="editPeriod" id="c9338955361b5253" memberName="editPeriod"
          virtualName="" explicitFocusOrder="0" pos="17.654%c -21R 10.399% 24"
          posRelativeY="f8a4a0ba2169ed5d" min="3.0" max="400.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <COMBOBOX name="editGenerator" id="d2fccf87f53946cd" memberName="editGenerator"
            virtualName="" explicitFocusOrder="0" pos="17.654%c -61R 10.399% 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="editKeyboard" id="363a9dc4b5eb4f63" memberName="editKeyboard"
            virtualName="" explicitFocusOrder="0" pos="17.654%c -101R 10.399% 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <GENERICCOMPONENT name="new component" id="80741f8eece04bb7" memberName="editColorLayout"
                    virtualName="" explicitFocusOrder="0" pos="67.231%c -36R 11.808% 136"
                    posRelativeY="f8a4a0ba2169ed5d" posRelativeW="f8a4a0ba2169ed5d"
                    class="ListBox" params="&quot;Colour Selector&quot;, colourTableModel.get()"/>
  <TOGGLEBUTTON name="new toggle button" id="3fefe6b79e2bbe21" memberName="editShowKeyNumber"
                virtualName="" explicitFocusOrder="0" pos="87.062%c -24R 176 24"
                posRelativeY="f8a4a0ba2169ed5d" buttonText="Full Keyboard Number"
                connectedEdges="0" needsCallback="1" radioGroupId="10" state="1"/>
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
  <SLIDER name="editGeneratorOffset" id="cf8ed030b390dba8" memberName="editGeneratorOffset"
          virtualName="" explicitFocusOrder="0" pos="33.495%c -60R 10.399% 24"
          posRelativeY="f8a4a0ba2169ed5d" min="-6.0" max="6.0" int="1.0"
          style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="50" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="new label" id="8b29c2f0ff851665" memberName="periodLbl"
         virtualName="" explicitFocusOrder="0" pos="-55 0 64 24" posRelativeX="c9338955361b5253"
         posRelativeY="c9338955361b5253" edTextCol="ff000000" edBkgCol="0"
         labelText="Period:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3e88e9cd29d6aede" memberName="genLbl" virtualName=""
         explicitFocusOrder="0" pos="-80 0 88 24" posRelativeX="47c080d0f31dbabc"
         posRelativeY="47c080d0f31dbabc" edTextCol="ff000000" edBkgCol="0"
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
  <SLIDER name="editRootSld" id="c486bd0e1ff65df1" memberName="editRootSld"
          virtualName="" explicitFocusOrder="0" pos="17.654%c -141R 10.399% 24"
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
                virtualName="" explicitFocusOrder="0" pos="0 28 7.011% 24" posRelativeX="91bd59afec743d5b"
                posRelativeY="91bd59afec743d5b" posRelativeW="f8a4a0ba2169ed5d"
                buttonText="Flip" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="eb5b9b780ba3f90c" memberName="editBlankKeys"
                virtualName="" explicitFocusOrder="0" pos="0 27 176 24" posRelativeX="3fefe6b79e2bbe21"
                posRelativeY="90354e3468042d3e" buttonText="Blank" connectedEdges="0"
                needsCallback="1" radioGroupId="10" state="0"/>
  <TOGGLEBUTTON name="negateXBtn" id="fe6ffcda9917ff6" memberName="negateXBtn"
                virtualName="" explicitFocusOrder="0" pos="28.537%c -96R 88 24"
                posRelativeY="f8a4a0ba2169ed5d" buttonText="Negate X" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="negateYBtn" id="91bd59afec743d5b" memberName="negateYBtn"
                virtualName="" explicitFocusOrder="0" pos="0% 116.667% 88 24"
                posRelativeX="fe6ffcda9917ff6" posRelativeY="fe6ffcda9917ff6"
                buttonText="Negate Y" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <COMBOBOX name="modMosDegreeBox" id="5a7f5a9b8eb8c2f2" memberName="modMosDegreeBox"
            virtualName="" explicitFocusOrder="0" pos="50%c -45R 8.827% 24"
            posRelativeY="f8a4a0ba2169ed5d" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="numPeriodsLabel" id="f9ca9fdac9632f8f" memberName="numPeriodsLabel"
         virtualName="" explicitFocusOrder="0" pos="23.458% 0 7.013% 24"
         posRelativeY="8b29c2f0ff851665" edTextCol="ff000000" edBkgCol="0"
         labelText="Num Periods:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="modMosDegreeLbl" id="e42659cd84f0c6e5" memberName="modMosDegreeLbl"
         virtualName="" explicitFocusOrder="0" pos="0Cc 56R 176 24" posRelativeX="5a7f5a9b8eb8c2f2"
         posRelativeY="5a7f5a9b8eb8c2f2" edTextCol="ff000000" edBkgCol="0"
         labelText="MODMOS Degree Selector" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="modMosChromaSld" id="8eb8c5b5ca62ad94" memberName="modMosChromaSld"
          virtualName="" explicitFocusOrder="0" pos="49.698%c -109R 10.332% 24"
          posRelativeY="f8a4a0ba2169ed5d" posRelativeW="f8a4a0ba2169ed5d"
          min="-10.0" max="10.0" int="1.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="modMosChromaLbl" id="b7f7c7d3b2836124" memberName="modMosChromaLbl"
         virtualName="" explicitFocusOrder="0" pos="0Cc -32 176 24" posRelativeX="8eb8c5b5ca62ad94"
         posRelativeY="8eb8c5b5ca62ad94" edTextCol="ff000000" edBkgCol="0"
         labelText="MODMOS Chroma Amount" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="generatorLabel" id="92df2825c7c52295" memberName="generatorLabel"
         virtualName="" explicitFocusOrder="0" pos="-78 0 80 24" posRelativeX="d2fccf87f53946cd"
         posRelativeY="d2fccf87f53946cd" edTextCol="ff000000" edBkgCol="0"
         labelText="Generator: " editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="numPeriodBox" id="17fa8b0b6c0af0b" memberName="numPeriodBox"
            virtualName="" explicitFocusOrder="0" pos="31.197% 0Cc 8.464% 24"
            posRelativeY="c9338955361b5253" editable="0" layout="33" items=""
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

