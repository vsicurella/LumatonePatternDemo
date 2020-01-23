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
    
	for (int i = 0; i < 5; i++)
		drawOctave(g, i);
}

void KeyboardViewer::drawOctave(Graphics& g, int octaveNumber)
{
	Point<float> horizontalStep = Point<float>(getWidth() * widthMult * 2 + spacing, 0);
	horizontalStep.rotatedAboutOrigin(0.2f);
	
	Point<float> verticalStep = Point<float>(getWidth() * widthMult + spacing, getWidth() * widthMult * 1.66667f) - horizontalStep;

	AffineTransform transform = AffineTransform::rotation(-0.2f);
	//transform = transform.rotated(-0.2f);

	Point<float> octaveSpacing = horizontalStep * 7 + verticalStep * 2;

	hexes.clear();
	Path* hex;

	Array<Colour> ac = { Colours::red, Colours::orange, Colours::yellow, Colours::green, Colours::blue };

	int key = 55 * octaveNumber;
	for (int r = 0; r < octaveRows.size(); r++)
	{
		for (int k = 0; k < octaveRows[r]; k++)
		{
			hex = new Path();
			hexes.add(hex);
			hex->addPolygon(Point<float>(getWidth()*0.02f, getHeight()*0.1f) + 
							(horizontalStep * (k + rowOffsets[r])) + 
							verticalStep * r + octaveSpacing * octaveNumber, 6, getWidth() * widthMult);
			hex->applyTransform(transform);
			
			g.setColour(ac[octaveNumber]);
			g.fillPath(*hex);

			g.setColour(Colours::black);
			g.drawText(String(key), hex->getBounds(), Justification::centred);
			
			key++;
		}
	}
}

void KeyboardViewer::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //hex.clear();
    //hex.addPolygon(getLocalBounds().getCentre().toFloat(), 6, getWidth() * widthMult);
    //AffineTransform transform = AffineTransform::translation(-getWidth() / 2.0f, -getHeight() / 2.0f);
    //transform = transform.rotated(-0.2f);
    //transform = transform.translated(getWidth() / 2.0f, getHeight() / 2.0f);
    //hex.applyTransform(transform);
}
