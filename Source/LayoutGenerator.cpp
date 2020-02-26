/*
  ==============================================================================

    LayoutGenerator.cpp
    Created: 20 Jan 2020 8:29:14pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#include "LayoutGenerator.h"

LayoutHelper::LayoutHelper(const ScaleStructure* structureIn, int rootIn)
	: structure(structureIn)
{
	rootKey = rootIn;

	refresh();
	DBG("LAYOUT: Finished constructing.");
}

LayoutHelper::LayoutHelper(const LayoutHelper& layoutToCopy)
	: structure(layoutToCopy.structure)
{
	rootKey = layoutToCopy.rootKey;

	scaleColours = layoutToCopy.scaleColours;

	refresh();
	DBG("LAYOUT: Finished constructing.");
}

LayoutHelper::~LayoutHelper()
{
    
}

void LayoutHelper::refresh()
{
	DBG("LAYOUT: Refreshing...");
	mapKeysToDegree();
}

int LayoutHelper::getPeriod()
{
    return structure->getPeriod();
}

int LayoutHelper::getGenerator()
{
    return structure->getGenerator(structure->getGeneratorIndex());
}

int LayoutHelper::getSize()
{
    return structure->getScaleSize(structure->getSizeIndex());
}

void LayoutHelper::mapKeysToDegree()
{
	kbdScaleDegrees.reset(new Array<int>());
	kbdScaleDegrees->resize(275);
	kbdScaleDegrees->fill(-1);
	
	if (!structure->isValid())
	{
		DBG("ERROR: not a valid layout :(");
		return;
	}

	Point<int> steps = structure->getCurrentStepSize();

	if (flipScale)
	{
		steps.setXY(steps.y, steps.x);
	}

	int xSteps = 0;
	int ySteps = 0;

	int nextRow = rootKey;
	int nextNote;

	/// temporary algorithm that gets most keys

	//DBG("moving right and getting upleft/downright rows");
	// start moving right and getting upleft/downright rows
	while (nextRow > 0)
	{
		xSteps = 0;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdScaleDegrees->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;

		}
		nextNote = nextRow;
		xSteps = 0;
		while (nextNote > -1)
		{
			//DBG("RIGHT Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdScaleDegrees->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdDownRight(nextNote, 1);
			xSteps++;

		}

		nextRow = kbdRight(nextRow, 1);
		ySteps++;
	}

	//DBG("moving left and get upleft/downright rows");
	// moving left and get upleft/downright rows
	ySteps = -1;
	nextRow = kbdLeft(rootKey, 1);
	while (nextRow > 0)
	{
		xSteps = 0;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("LEFT Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdScaleDegrees->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;
		}
		xSteps = 0;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdScaleDegrees->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdDownRight(nextNote, 1);
			xSteps++;
		}

		nextRow = kbdLeft(nextRow, 1);
		ySteps--;
	}
}

int LayoutHelper::getRootKey()
{
	return rootKey;
}

Array<Colour>* LayoutHelper::getScaleColours()
{
	return scaleColours;
}

bool LayoutHelper::isScaleFlipped()
{
	return flipScale;
}

void LayoutHelper::setScaleFlipped(bool doFlip)
{
	DBG("Flipping scale");
	flipScale = doFlip;
	refresh();
}

Array<int>* LayoutHelper::getKbdDegrees()
{
	return kbdScaleDegrees.get();
}

int LayoutHelper::getKeyDegree(int keyNumIn)
{
	return kbdScaleDegrees->getUnchecked(keyNumIn);
}

Array<Array<int>> LayoutHelper::getDegreeGroupings()
{
    return structure->getDegreeGroupings();
}

void LayoutHelper::setRootKey(int rootKeyIn)
{
	rootKey = rootKeyIn;
	mapKeysToDegree();
}

void LayoutHelper::addColour(Colour colorIn)
{
	scaleColours->add(colorIn);
}

void LayoutHelper::setColour(int index, Colour colorIn)
{
	scaleColours->set(index, colorIn);
}

void LayoutHelper::setColours(Array<Colour>* coloursIn)
{
	scaleColours = coloursIn;
}
