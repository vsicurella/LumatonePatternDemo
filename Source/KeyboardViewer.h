/*
  ==============================================================================

    KeyboardViewer.h
    Created: 22 Jan 2020 12:06:39am
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CommonFunctions.h"
#include "LayoutGenerator.h"


//==============================================================================
/*
*/
class KeyboardViewer    : public Component
{
public:

	enum KeyText
	{
		KeyNumber = 0,
		OctaveNumber,
		MidiNote,
		ScaleDegree,
		Blank
	};

    KeyboardViewer(LayoutHelper* layoutIn);
    ~KeyboardViewer();

    void paint (Graphics&) override;
    void resized() override;
    
    void drawOctave(Graphics& g, int octaveNumber);

	void setLayout(LayoutHelper* layoutIn);
	void setKeyTextShown(KeyText textTypeIn);

private:
   
	// Functionality Attributes
	OwnedArray<Path> hexes;
	LayoutHelper* layout;

	Point<float> horizontalStep;
	Point<float> verticalStep;
	Point<float> octaveSpacing;
	AffineTransform transform = AffineTransform::rotation(-0.2f);

	float widthMult = 0.015;
	float spacing = 0.1;

	// Independent Attributes
	int scalePeriod = 12;
	int keyTextShown = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewer)
};
