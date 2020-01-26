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
KeyboardViewer::KeyboardViewer(LayoutGenerator* layoutIn)
 : layout(layoutIn)
{
	
}

KeyboardViewer::~KeyboardViewer()
{
}

void KeyboardViewer::setLayout(LayoutGenerator* layoutIn)
{
	layout = layoutIn;
}

void KeyboardViewer::setScale(Array<int> scaleIn)
{
	scale = scaleIn;
	repaint();
}

void KeyboardViewer::setMap(Array<int>* mapIn)
{
	map = mapIn;
}

void KeyboardViewer::setKeyTextShown(KeyText textTypeIn)
{
	keyTextShown = textTypeIn;
	DBG(keyTextShown);
	repaint();
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

	int scalePeriod = layout->getGenPeriodRatio().getDenominator();
	Array<Array<int>>* generatorNotes = layout->getGeneratorNotes();
	int modDegree;

	Array<Colour> ac = { Colours::mediumaquamarine, Colours::indianred, Colours::orange, Colours::yellow.darker(), Colours::green, Colours::cornflowerblue, Colours::lavenderblush, Colours::mediumslateblue };

	String keyText;

	int key = 55 * octaveNumber;
	for (int r = 0; r < octaveRows.size(); r++)
	{
		for (int k = 0; k < octaveRows[r]; k++)
		{
			hex = new Path();
			hexes.add(hex);
			hex->addPolygon(Point<float>(getWidth() * 0.015f, getHeight() * 0.11f) +
				(horizontalStep * (k + rowOffsets[r])) +
				verticalStep * r + octaveSpacing * octaveNumber, 6, getWidth() * widthMult);
			hex->applyTransform(transform);

			g.setColour(Colours::white);

			if (generatorNotes != nullptr)
			{
				modDegree = modulo(map->getUnchecked(key), scalePeriod);
				for (int t = 0; t < generatorNotes->size(); t++)
				{
					if (generatorNotes->getReference(t).contains(modDegree))
						g.setColour(ac[t]);
				}
			}

			g.fillPath(*hex);

			switch (keyTextShown)
			{
				case OctaveNumber:
					keyText = String(key % 55);
					break;
				case MidiNote:
				{
					if (map != nullptr)
						keyText = String(map->getUnchecked(key) + 60);
					else
						keyText = "-1";
					break;
				}
				case ScaleDegree:
				{
					keyText = String(map->getUnchecked(key));
					break;
				}
				default:
					keyText = String(key);
			}

			g.setColour(Colours::black);
			g.drawText(keyText, hex->getBounds(), Justification::centred);
			
			key++;
		}
	}
}

void KeyboardViewer::resized()
{

}


