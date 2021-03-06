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
KeyboardViewer::KeyboardViewer(LayoutHelper* layoutIn)
 : layout(layoutIn)
{
	
}

KeyboardViewer::~KeyboardViewer()
{
}

void KeyboardViewer::setLayout(LayoutHelper* layoutIn)
{
	layout = layoutIn;
	repaint();
}

void KeyboardViewer::setKeyTextShown(KeyText textTypeIn)
{
	keyTextShown = textTypeIn;
	repaint();
}

void KeyboardViewer::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

	scalePeriod = layout->getPeriod();
	for (int i = 0; i < 5; i++)
		drawOctave(g, i);
}

void KeyboardViewer::drawOctave(Graphics& g, int octaveNumber)
{
	hexes.clear();
	Path* hex;

	Array<int>* map = layout->getKbdDegrees();
	Array<Array<int>> generatorNotes = layout->getDegreeGroupings();
	int modDegree;

	String keyText;

	int key = 55 * octaveNumber;
	for (int r = 0; r < octaveRowSizes.size(); r++)
	{
		for (int k = 0; k < octaveRowSizes[r]; k++)
		{
			hex = new Path();
			hexes.add(hex);
			hex->addPolygon(Point<float>(getWidth() * 0.015f, getHeight() * 0.11f) +
				(horizontalStep * (k + octaveRowOffsets[r])) +
				verticalStep * r + octaveSpacing * octaveNumber, 6, getWidth() * widthMult);
			hex->applyTransform(transform);

			Colour keyColour = Colours::white;

			if (generatorNotes.size() > 0)
			{
				modDegree = modulo(map->getUnchecked(key), scalePeriod);
				for (int t = 0; t < generatorNotes.size(); t++)
				{
					if (generatorNotes.getReference(t).contains(modDegree))
						keyColour = (*layout->getScaleColours())[t];
				}
			}

			g.setColour(keyColour);
			g.fillPath(*hex);

			if (keyTextShown != Blank)
			{
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

				g.setColour(keyColour.contrasting(1));
				g.drawText(keyText, hex->getBounds(), Justification::centred);
			}

			key++;
		}
	}
}

void KeyboardViewer::resized()
{
	horizontalStep = Point<float>(getWidth() * widthMult * 2 + spacing, 0);
	horizontalStep.rotatedAboutOrigin(0.2f);

	verticalStep = Point<float>(getWidth() * widthMult + spacing, getWidth() * widthMult * 1.66667f) - horizontalStep;

	octaveSpacing = horizontalStep * 7 + verticalStep * 2;
}
