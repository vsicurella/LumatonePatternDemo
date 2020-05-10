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
    return structure->getGenerator();
}

int LayoutHelper::getSize()
{
	return structure->getScaleSize();
}

void LayoutHelper::mapKeysToDegree()
{
	kbdScaleDegrees.clear();
	kbdScaleDegrees.resize(275);
	kbdScaleDegrees.fill(INT_MIN);
	
	if (!structure->isValid())
	{
		DBG("ERROR: not a valid layout :(");
		return;
	}

	stepSizes = structure->getStepSize();

	if (negateX)
		stepSizes.setX(-stepSizes.x);
	if (negateY)
		stepSizes.setY(-stepSizes.y);
	if (flipScale)
		stepSizes.setXY(stepSizes.y, stepSizes.x);

	fillStartingFromNote(rootKey);
	fixErrors();
}

void LayoutHelper::fillStartingFromNote(int kbdNoteNum, Point<int> startingSteps)
{
	int xSteps, ySteps = startingSteps.y;

	int nextRow = kbdNoteNum;
	int nextNote;

	/// temporary algorithm that gets most keys

	//DBG("moving right and getting upleft/downright rows");
	// start moving right and getting upleft/downright rows
	while (nextRow > 0)
	{
		xSteps = startingSteps.x;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("Mapping note " + String(nextNote) + " to " + String(xSteps * stepSizes.x + ySteps * stepSizes.y));
			kbdScaleDegrees.set(nextNote, xSteps * stepSizes.x + ySteps * stepSizes.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;

		}
		nextNote = nextRow;
		xSteps = startingSteps.x;
		while (nextNote > -1)
		{
			//DBG("RIGHT Mapping note " + String(nextNote) + " to " + String(xSteps * stepSizes.x + ySteps * stepSizes.y));
			kbdScaleDegrees.set(nextNote, xSteps * stepSizes.x + ySteps * stepSizes.y);
			nextNote = kbdDownRight(nextNote, 1);
			xSteps++;

		}

		nextRow = kbdRight(nextRow, 1);
		ySteps++;
	}

	//DBG("moving left and get upleft/downright rows");
	// moving left and get upleft/downright rows
	ySteps = startingSteps.y - 1;
	nextRow = kbdLeft(kbdNoteNum, 1);
	while (nextRow > 0)
	{
		xSteps = startingSteps.x;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("LEFT Mapping note " + String(nextNote) + " to " + String(xSteps * stepSizes.x + ySteps * stepSizes.y));
			kbdScaleDegrees.set(nextNote, xSteps * stepSizes.x + ySteps * stepSizes.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;
		}
		xSteps = startingSteps.x;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("Mapping note " + String(nextNote) + " to " + String(xSteps * stepSizes.x + ySteps * stepSizes.y));
			kbdScaleDegrees.set(nextNote, xSteps * stepSizes.x + ySteps * stepSizes.y);
			nextNote = kbdDownRight(nextNote, 1);
			xSteps++;
		}

		nextRow = kbdLeft(nextRow, 1);
		ySteps--;
	}
}

void LayoutHelper::fixErrors()
{
	// Start from bottom left corner, look for consecutive -1's

	int negativeErrors = 0;
	int kbdNote = 43;
	int nextNote = kbdRight(kbdNote, 1);
	DBG("CHECK ERROR: Bottom Left.");
	while (nextNote < 221)
	{
		if (kbdScaleDegrees[kbdNote] == INT_MIN)
			negativeErrors++;
		else
		{
			// break if corner is valid
			DBG("No errors found.");
			break;
		}
		
		
		// find first non-negative-one value
		if (negativeErrors >= 2 && kbdScaleDegrees[nextNote] != INT_MIN)
		{
			// fill
			DBG("Found nonnegative key: Key " + String(nextNote) + "\tDegree " + String(kbdScaleDegrees[nextNote]));
			fillStartingFromNote(nextNote, findStepsFromRoot(nextNote));
			break;
		}

		kbdNote = nextNote;
		nextNote = kbdRight(nextNote, 1);
	}

	// Start from top right corner, look for consecutive -1's 
	negativeErrors = 0;
	kbdNote = 226;
	nextNote = kbdLeft(kbdNote, 1);
	DBG("CHECK ERROR: Top Right.");
	while (nextNote > 49)
	{
		if (kbdScaleDegrees[kbdNote] == INT_MIN)
			negativeErrors++;

		// break if there aren't consecutive negative values
		if (negativeErrors == 0 && kbdNote == 47)
		{
			DBG("No errors found.");
			break;
		}

		// find first non-negative-one value
		else if (negativeErrors >= 2 && kbdScaleDegrees[nextNote] != INT_MIN)
		{
			// fill

			fillStartingFromNote(nextNote, findStepsFromRoot(nextNote));
			break;
		}

		kbdNote = nextNote;
		nextNote = kbdLeft(nextNote, 1);
	}
}

Point<int> LayoutHelper::findStepsFromRoot(int kbdNoteNum)
{
	// TODO:
	// Figure out how many x and y steps it takes to get from root note to given note
	return Point<int>();
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



void LayoutHelper::setNegateX(bool doNegate)
{
	negateX = doNegate;
	refresh();
}

void LayoutHelper::setNegateY(bool doNegate)
{
	negateY = doNegate;
	refresh();
}

void LayoutHelper::setScaleFlipped(bool doFlip)
{
	flipScale = doFlip;
	refresh();
}

Array<int>* LayoutHelper::getKbdDegrees()
{
	return &kbdScaleDegrees;
}

int LayoutHelper::getKeyDegree(int keyNumIn)
{
	return kbdScaleDegrees[keyNumIn];
}

Array<Array<int>> LayoutHelper::getDegreeGroupings()
{
    return structure->getDegreeGroupings();
}

void LayoutHelper::setRootKey(int rootKeyIn)
{
	rootKey = rootKeyIn;
	refresh();
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
