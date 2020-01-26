/*
  ==============================================================================

    LayoutGenerator.cpp
    Created: 20 Jan 2020 8:29:14pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#include "LayoutGenerator.h"


LayoutGenerator::LayoutGenerator(int periodIn)
{
    // TODO: add validity checks
    scalePeriod = periodIn;
    
    updateValidOptions();
}

LayoutGenerator::LayoutGenerator(int periodIn, int genIn)
{
    
    // TODO: add validity checks

    scalePeriod = periodIn;
    generator = genIn;
    
    updateValidOptions();
}

LayoutGenerator::LayoutGenerator(int periodIn, int genIn, int kbdTypeIn, int rootIn)
{
    // TODO: add validity checks

    scalePeriod = periodIn;
    generator = genIn;
    
    updateValidOptions();

	kbdType = kbdTypeIn;
	scaleSize = validKeyboards[kbdType].getDenominator();
	rootKey = rootIn;

	refresh();
}

LayoutGenerator::LayoutGenerator(const LayoutGenerator& layoutToCopy)
{
	scalePeriod = layoutToCopy.scalePeriod;
	generator = layoutToCopy.generator;

	updateValidOptions();

	kbdType = layoutToCopy.kbdType;
	scaleSize = layoutToCopy.scaleSize;
	rootKey = layoutToCopy.rootKey;

	scaleColors = layoutToCopy.scaleColors;

	refresh();
}

LayoutGenerator::~LayoutGenerator()
{
    
}

void LayoutGenerator::refresh()
{
	mapKeysToDistance();
	mapGeneratorsToNotes();
}
  
void LayoutGenerator::updateValidOptions()
{
    validGenerators = getCoprimes(scalePeriod);
    
    if (!validGenerators.contains(generator))
    {
        DBG("Error: invalid generator size");
        validLayout = false;
        return;
    }
    
	structure = ScaleStructure(scalePeriod, generator);
    gOverP = Ratio(generator, scalePeriod);

	validKeyboards = structure.getKeyboardTypes();
	validSizes = structure.getScaleSizes();
	pgCoords = structure.getPGCoords();
    
    if (validSizes.contains(scaleSize))
    {
        validLayout = true;
    }
    else
    {
        DBG("ERROR: invalid scale size");
        //TODO: implement size error handling
        validLayout = true;
    }
}

void LayoutGenerator::mapKeysToDistance()
{
	kbdNoteMap.reset(new Array<int>());
	kbdNoteMap->resize(275);
	kbdNoteMap->fill(-1);
	
	if (pgCoords[kbdType].x.x * pgCoords[kbdType].x.y * pgCoords[kbdType].y.x * pgCoords[kbdType].y.y <= 0)
		return;

	Point<int> steps = getXYSteps();

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
			kbdNoteMap->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;

		}
		nextNote = nextRow;
		xSteps = 0;
		while (nextNote > -1)
		{
			//DBG("RIGHT Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdNoteMap->set(nextNote, xSteps * steps.x + ySteps * steps.y);
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
			kbdNoteMap->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdUpLeft(nextNote, 1);
			xSteps--;
		}
		xSteps = 0;
		nextNote = nextRow;
		while (nextNote > -1)
		{
			//DBG("Mapping note " + String(nextNote) + " to " + String(xSteps * steps.x + ySteps * steps.y));
			kbdNoteMap->set(nextNote, xSteps * steps.x + ySteps * steps.y);
			nextNote = kbdDownRight(nextNote, 1);
			xSteps++;
		}

		nextRow = kbdLeft(nextRow, 1);
		ySteps--;
	}
}

void LayoutGenerator::mapGeneratorsToNotes()
{
	if (scaleSize < 1)
	{
		DBG("ERROR: Scale size less than 1.");
		return;
	}
	DBG("Period: " + String(scalePeriod) + "\tGen: " + String(generator) + " " + String(generatorOffset) + "\tSize: " + String(scaleSize)); 
	// Find out how many notes each color tier will have
	// Can be made to be customized
	Array<int> noteSegments = { scaleSize };
	
	int noteLeft = scalePeriod - scaleSize;
	int subSizeIdx = kbdType - 1;
	int subSize = validSizes[subSizeIdx];

	while (subSize > noteLeft && subSizeIdx > 0)
		subSize = validSizes[--subSizeIdx];

	if (subSizeIdx <= 0)
	{
		DBG("ERROR: Bad note segmenting");
		return;
	}

	int f = noteLeft / subSize;
	for (int i = 0; i < f; i++)
	{
		noteSegments.add(subSize);
	}

	int remainder = noteLeft % subSize;
	if (remainder > 0)
		noteSegments.add(remainder);

	notesByGenerators.reset(new Array<Array<int>>());
	// Cycle through the scale by generators and 
	// separate the tiers symmetrically

	int degreeForward = modulo(generator * generatorOffset, scalePeriod);
	int degreeBackward = degreeForward;
	int index;
	for (int t = 0; t < noteSegments.size(); t++)
	{
		notesByGenerators->add(Array<int>());
		for (int n = 0; n < noteSegments[t]; n++)
		{
			if (t % 2 == 0)
			{
				if (degreeForward < 0 || degreeForward >= scalePeriod)
					degreeForward = modulo(degreeForward, scalePeriod);

				notesByGenerators->getReference(t).add(degreeForward);
				degreeForward += generator;
			}
			else
			{
				degreeBackward -= generator;
				if (degreeBackward < 0 || degreeBackward >= scalePeriod)
					degreeBackward = modulo(degreeBackward, scalePeriod);

				notesByGenerators->getReference(t).add(degreeBackward);
			}
		}
	}

	DBG("Scale created: ");
	for (int t = 0; t < notesByGenerators->size(); t++)
	{
		String notes;
		for (auto n : notesByGenerators->getReference(t))
		{
			notes += String(n) + ", ";
		}
		DBG("Tier " + String(t + 1) +":\t" + notes);
	}
}

Ratio LayoutGenerator::getGenPeriodRatio()
{
    return gOverP;
}

int LayoutGenerator::getScaleSize()
{
	return scaleSize;
}

int LayoutGenerator::getRootKey()
{
	return rootKey;
}

Array<int>* LayoutGenerator::getNoteMap()
{
	return kbdNoteMap.get();
}

Array<Array<int>>* LayoutGenerator::getGeneratorNotes()
{
	return notesByGenerators.get();
}

int LayoutGenerator::getKeyNote(int keyNumIn)
{
	return kbdNoteMap->getUnchecked(keyNumIn);
}

Array<Colour> LayoutGenerator::getScaleColours()
{
    return Array<Colour>();
}

Array<int> LayoutGenerator::getValidGenerators()
{
    return validGenerators;

}

Array<int> LayoutGenerator::getValidSizes()
{
    return validSizes;

}

Array<Ratio> LayoutGenerator::getValidKeyboards()
{
    return validKeyboards;
}

Array<PointPair<int>> LayoutGenerator::getPGCoords()
{
	return pgCoords;
}

PointPair<int> LayoutGenerator::getPGCoord()
{
	return pgCoords[kbdType];
}

PointPair<int> LayoutGenerator::getPGCoord(int kbdInd)
{
	return pgCoords[kbdInd];
}

Point<int> LayoutGenerator::getXYSteps()
{
	return structure.getXYSteps(kbdType);
}
Point<int> LayoutGenerator::getXYSteps(int kbdInd)
{
	return structure.getXYSteps(kbdInd);
}

bool LayoutGenerator::isValid()
{
    return validLayout;
}

void LayoutGenerator::setKeyboardType(int kbdIndexIn)
{
	kbdType = kbdIndexIn;
	scaleSize = validKeyboards[kbdType].getDenominator();
}

void LayoutGenerator::setRootKey(int rootKeyIn)
{
	rootKey = rootKeyIn;
	mapKeysToDistance();
}

void LayoutGenerator::setGeneratorOffset(int genOffsetIn)
{
	generatorOffset = genOffsetIn;
	refresh();
}
