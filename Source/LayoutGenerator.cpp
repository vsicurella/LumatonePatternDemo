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


	// Find the bottom left corner, key 43

	int kbdNote, nextNote = rootKey;
	Point<int> stepsFromRoot;

	while (nextNote != 49)
	{

		// Handle edges
		if (nextNote == -1)
		{
			// backtrack
			stepsFromRoot.setY(stepsFromRoot.y + 1);

			// Find out if we hit bottom edge or left edge
			int nextTry = kbdUpLeft(kbdNote, 1);

			// True if bottom edge
			if (nextTry != -1 && kbdLeft(nextTry, 1) != -1)
			{
				nextNote = nextTry;
				// y change is actually a correction
				stepsFromRoot.setX(stepsFromRoot.x - 1);
			}

			else 
			{	
				nextTry = kbdDownRight(kbdNote, 2);

				if (nextTry != -1)
				{
					// Move down two rows
					nextNote = nextTry;
					// y change is actually a correction
					stepsFromRoot.setX(stepsFromRoot.x + 2);
				}
				// True if we're on key 43
				else
				{
					nextNote = 49;
					stepsFromRoot.setXY(stepsFromRoot.x + 1, stepsFromRoot.y - 1);
				}
			}

			DBG("Next row: " + String(nextNote) + "\tSteps: " + stepsFromRoot.toString());
		}
		else
		{
			kbdNote = nextNote;
			nextNote = kbdLeft(nextNote, 1);

			DBG("\ton " + String(kbdNote) + " Steps: " + stepsFromRoot.toString());

			stepsFromRoot.setY(stepsFromRoot.y - 1);
		}
	}

	DBG("Key 49 found. Steps from root: " + stepsFromRoot.toString());

	fillStartingFromNote(49, stepsFromRoot);

	// fill in last key 43
	kbdScaleDegrees.set(43, (stepsFromRoot.x - 1) * stepSizes.x + (stepsFromRoot.y - 1) * stepSizes.y);
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
