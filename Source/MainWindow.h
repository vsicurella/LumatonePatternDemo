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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "KeyboardViewer.h"
#include "ColorTable.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainWindow  : public Component,
                    public Slider::Listener,
                    public ComboBox::Listener,
                    public Button::Listener
{
public:
    //==============================================================================
    MainWindow ();
    ~MainWindow() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	void onPeriodChange();
	void onPeriodFactorChange();
    void onGeneratorChange();
	void onSizeChange();
	
	void refreshGenerators();
	void refreshSizes();

	void refreshKeyboardView();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<ScaleStructure> scaleStructure;
	std::unique_ptr<LayoutHelper> layout;
	std::unique_ptr<ColourTableModel> colourTableModel;

	Array<int> periodFactors;
    Array<int> validGenerators;
    Array<int> validSizes;

	int period = 12;
	int periodFactorIndex = 0;
	int genIndex = 2;
	int genOffset = -1;
	int sizeIndex = 4;
	int rootKey = 129;

	Point<int> periodHXY = Point<int>(2, 5);
	Point<int> genHXY = Point<int>(1, 3);

	// default colors
	Array<Colour> scaleColours = {
		Colours::aliceblue,
		Colours::mediumpurple,
		Colours::indianred,
		Colours::cadetblue,
		Colours::green,
		Colours::yellow.darker(),
		Colours::cornflowerblue,
		Colours::lavenderblush,
		Colours::mediumslateblue,
		Colours::mediumvioletred.withBrightness(0.8),
		Colours::indianred.withBrightness(0.8),
		Colours::orange.withBrightness(0.8),
		Colours::green.withBrightness(0.8),
		Colours::yellow.darker().withBrightness(0.8),
		Colours::cornflowerblue.withBrightness(0.8),
		Colours::lavenderblush.withBrightness(0.8),
		Colours::mediumslateblue.withBrightness(0.8)
	};
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<KeyboardViewer> keyboardView;
    std::unique_ptr<Slider> editPeriod;
    std::unique_ptr<ComboBox> editGenerator;
    std::unique_ptr<ComboBox> editKeyboard;
    std::unique_ptr<ListBox> editColorLayout;
    std::unique_ptr<ToggleButton> editShowKeyNumber;
    std::unique_ptr<ToggleButton> editShowOctaveNum;
    std::unique_ptr<ToggleButton> editShowMidiNote;
    std::unique_ptr<ToggleButton> editShowScaleDegree;
    std::unique_ptr<Slider> editGeneratorOffset;
    std::unique_ptr<Label> periodLbl;
    std::unique_ptr<Label> genLbl;
    std::unique_ptr<Label> offsetLbl;
    std::unique_ptr<Label> ScaleSize;
    std::unique_ptr<Slider> editRootSld;
    std::unique_ptr<Label> rootLbl;
    std::unique_ptr<Label> colorSelectionLbl;
    std::unique_ptr<ToggleButton> editScaleFlip;
    std::unique_ptr<ToggleButton> editBlankKeys;
    std::unique_ptr<ToggleButton> negateXBtn;
    std::unique_ptr<ToggleButton> negateYBtn;
    std::unique_ptr<ComboBox> modMosDegreeBox;
    std::unique_ptr<Label> numPeriodsLabel;
    std::unique_ptr<Label> modMosDegreeLbl;
    std::unique_ptr<Slider> modMosChromaSld;
    std::unique_ptr<Label> modMosChromaLbl;
    std::unique_ptr<Label> generatorLabel;
    std::unique_ptr<ComboBox> numPeriodBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

