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
}

KeyboardViewer::~KeyboardViewer()
{
}

void KeyboardViewer::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

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

	Array<Colour> ac = { Colours::red, Colours::orange, Colours::yellow, Colours::green, Colours::cornflowerblue };

	int key = 55 * octaveNumber;
	for (int r = 0; r < octaveRows.size(); r++)
	{
		for (int k = 0; k < octaveRows[r]; k++)
		{
			hex = new Path();
			hexes.add(hex);
			hex->addPolygon(Point<float>(getWidth()*0.015f, getHeight()*0.11f) + 
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

}
