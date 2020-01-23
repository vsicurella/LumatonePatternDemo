/*
  ==============================================================================

    KeyboardViewer.cpp
    Created: 22 Jan 2020 12:06:39am
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KeyboardViewer.h"

//==============================================================================
KeyboardViewer::KeyboardViewer()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    hex.addPolygon(Point<float>(), 6, 0);
}

KeyboardViewer::~KeyboardViewer()
{
}

void KeyboardViewer::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("KeyboardViewer", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
    
    g.setColour(Colours::red);
    g.fillPath(hex);
    
}

void KeyboardViewer::drawOctave(int octaveNumber)
{
//    float widthMult = 0.05;
//    float spacing = 0;
//    Point<float> horizontalStep = ;
//    Point<float> verticalStep;
}

void KeyboardViewer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    hex.clear();
    hex.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * 0.04);
    AffineTransform transform = AffineTransform::translation(-getWidth() / 2.0f, -getHeight() / 2.0f);
    transform = transform.rotated(-0.2f);
    transform = transform.translated(getWidth() / 2.0f, getHeight() / 2.0f);
    hex.applyTransform(transform);
}
