/*
  ==============================================================================

    KeyboardViewer.h
    Created: 22 Jan 2020 12:06:39am
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Shapes.h"

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
    
    void drawOctave(int octaveNumber);

private:
    
    //Polygon hex;
    Path hex;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewer)
};
