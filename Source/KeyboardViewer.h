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


//==============================================================================
/*
*/
class KeyboardViewer    : public Component
{
public:
    KeyboardViewer();
    ~KeyboardViewer();

    void paint (Graphics&) override;
    void resized() override;
    
    void drawOctave(Graphics& g, int octaveNumber);

private:
   
	OwnedArray<Path> hexes;

	float widthMult = 0.015;
	float spacing = 0.1;

	Array<int> octaveRows = { 2, 5, 6, 6, 6, 6, 6, 6, 6, 5, 1 };
	Array<int> rowOffsets = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 6, 10 };

	Array<int> notes = { 77, 78, 79, 112, 113, 114, 2, 4, 6, 8, 10 };

	Array<int> scale;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewer)
};
