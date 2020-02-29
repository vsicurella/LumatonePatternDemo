/*
  ==============================================================================

    ScaleStructure.cpp
    Created: 25 Jan 2020 5:12:32pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "ScaleStructure.h"

ScaleStructure::ScaleStructure(int periodIn)
{
	period = periodIn;
	validGenerators = getCoprimes(period);
}

ScaleStructure::ScaleStructure(int periodIn, int generatorIndex, int sizeIndex, Array<int> degreeGroups)
{
	period = periodIn;
	validGenerators = getCoprimes(period);
	generator = generatorIndex;

	// TODO: check for valid input
	calculateProperties();

	currentSizeSelected = sizeIndex;
	sizeGroupings = degreeGroups;
}

int ScaleStructure::getPeriod() const
{
    return period;
}

Array<int> ScaleStructure::getValidGenerators() const
{
    return validGenerators;
}

int ScaleStructure::getGenerator(int genIndex) const
{
    return validGenerators[genIndex];
}

Array<int> ScaleStructure::getScaleSizes() const
{
	return scaleSizes;
}

int ScaleStructure::getScaleSize(int ind) const
{
	return scaleSizes[ind];
}

Array<Point<int>> ScaleStructure::getKeyboardTypes() const
{
	return keyboardTypes;
}

Point<int> ScaleStructure::getKeyboardType(int ind) const
{
	return keyboardTypes[ind];
}

Array<PointPair<int>> ScaleStructure::getPGCoords() const
{
	return pgCoords;
}

PointPair<int> ScaleStructure::getPGCoord(int ind) const
{
	return pgCoords[ind];
}

int ScaleStructure::getGroupOfDegree(int scaleDegreeIn) const
{
	for (int g = 0; g < sizeGroupings.size(); g++)
	{
		if (degreeGroupings.getReference(g).contains(scaleDegreeIn))
			return g;
	}

	return -1;
}

void ScaleStructure::resetToPeriod(int periodIn)
{
	period = periodIn;
	validGenerators = getCoprimes(period);
	generator = -1;
	currentSizeSelected = -1;

	scaleSizes.clear();
	keyboardTypes.clear();
	pgCoords.clear();
	stepSizes.clear();
}

void ScaleStructure::setGeneratorIndex(int index)
{
    generator = index;
	calculateProperties();
}

void ScaleStructure::setSizeIndex(int index)
{
	currentSizeSelected = index;
    //useSimpleSizeStructure();
	useCascadingSizeStructure();
}

void ScaleStructure::setGeneratorOffset(int offsetIn)
{
	generatorOffset = offsetIn;
	//useSimpleSizeStructure();
	useCascadingSizeStructure();
}

Point<int> ScaleStructure::getStepSizes(int kbdTypeIn) const
{
	return stepSizes[kbdTypeIn];
}

Array<int> ScaleStructure::getSizeGrouping() const
{
	return sizeGroupings;
}

Array<Array<int>> ScaleStructure::getDegreeGroupings() const
{
    return degreeGroupings;
}

int ScaleStructure::getGeneratorIndex() const
{
    return generator;
}

int ScaleStructure::getSizeIndex() const
{
    return currentSizeSelected;
}

Point<int> ScaleStructure::getCurrentStepSize() const
{
	return stepSizes[currentSizeSelected];
}

void ScaleStructure::calculateProperties()
{
	scaleSizes.clear();
	keyboardTypes.clear();
	pgCoords.clear();

    Array<int> cf = getContinuedFraction((double)validGenerators[generator] / period);

	// seed the sequence
	Point<int> parent1 = Point<int>(-1 + cf[0], 1);
	Point<int> parent2 = Point<int>(1, 0);
	Point<int> gp = Point<int>(cf[0], 1);

	Array<Point<int>> packet = { gp, parent2, gp + parent2 }; // makes for cleaner code

	// find keyboard types, and their period/generator coordinates
	for (int i = 1; i < cf.size(); i++)
	{
		for (int d = 0; d < cf[i]; d++)
		{
			pgCoords.add(PointPair<int>(packet[0], packet[1]));
			keyboardTypes.add(packet[2]);
			scaleSizes.add(packet[2].y);

			parent1 = packet[0];
			parent2 = packet[1];
			gp = packet[2];

			// if previous continued fraction index is even,
			// set parent2 to previous result
			if (i % 2 == 0)
				parent1 = gp;
			else // if odd, set parent1 to previous result
				parent2 = gp;

			packet = { parent1, parent2, parent1 + parent2 };
		}
	}

	calculateStepSizes();
	calculateGeneratorChain();
}

void ScaleStructure::calculateStepSizes()
{
	stepSizes.clear();

	Point<int> stepSizesOut;
	Point<int> periodCoordinate;
	Point<int> generatorCoordinate;
    
    int gen = validGenerators[generator];

	for (int i = 0; i < scaleSizes.size(); i++)
	{
		generatorCoordinate = Point<int>(pgCoords[i].x.x, pgCoords[i].y.x);
		periodCoordinate = Point<int>(pgCoords[i].x.y, pgCoords[i].y.y);

		// find horiztonal step size (X)
		if (periodCoordinate.y == generatorCoordinate.y)
			stepSizesOut.setX(period - gen);
		else if (periodCoordinate.y == 0)
			stepSizesOut.setX(period);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(gen);
		else
			stepSizesOut.setX(period * generatorCoordinate.y - gen * periodCoordinate.y);	

		// find upward right step size (Y)
		if (periodCoordinate.x == generatorCoordinate.x)
			stepSizesOut.setY(period - gen);
		else if (periodCoordinate.x == 0)
			stepSizesOut.setX(period);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(gen);
		else
			stepSizesOut.setY(gen * periodCoordinate.x - period * generatorCoordinate.x);

		stepSizes.add(stepSizesOut);
	}
}

void ScaleStructure::calculateGeneratorChain()
{
	generatorChain.clear();
    int gen = validGenerators[generator];
	for (int i = 0; i < period; i++)
	{
		generatorChain.add(modulo(i * gen, period));
	}
}

void ScaleStructure::fillDegreeGroupings()
{
	degreeGroupings.clear();
    degreeGroupings.resize(sizeGroupings.size());

    // Fill degree groups symmetrically

    int indexForward = generatorOffset;
    int indexBackwards = period - 1 + generatorOffset;
    int indexOffset;
    
    for (int t = 0; t < sizeGroupings.size(); t++)
    {
        for (int n = 0; n < scaleSizes[sizeGroupings[t]]; n++)
        {
            if (t % 2 == 0)
            {
                indexOffset = modulo(indexForward, period);
                indexForward++;
            }
            else
            {
                indexOffset = modulo(indexBackwards, period);
                indexBackwards--;
            }
            
            degreeGroupings.getReference(t).add(generatorChain[indexOffset]);
        }
    }

	String dbgstr = "";
	int size, sum = 0;
	for (int i = 0; i < sizeGroupings.size(); i++) {
		size = scaleSizes[sizeGroupings[i]];
		dbgstr += String(size) + ", ";
		sum += size;
	}
	dbgstr += " = " + String(sum);
	DBG("Using this size grouping: " + dbgstr);

	dbgstr = "";
	for (int group = 0; group < sizeGroupings.size(); group++)
	{
		Array<int> degreeGroup = degreeGroupings[group];
		dbgstr += "Tier " + String(group) + ": ";
		for (int deg = 0; deg < degreeGroup.size(); deg++)
		{
			dbgstr += String(degreeGroup[deg]) + ", ";
		}
		dbgstr += "\n";
	}

	DBG("Degree groupings: ");
	DBG(dbgstr);
}

int ScaleStructure::getSuggestedGeneratorIndex()
{
	int index = -1;
	float dif1, dif2 = 10e6;
	float interval = 1200 / period;

	for (int i = 1; i < validGenerators.size(); i++)
	{
		dif1 = abs(700 - interval * validGenerators[i]);

		if (dif1 < dif2)
		{
			dif2 = dif1;
			index = i;
		}
	}

	return index;
}

int ScaleStructure::getSuggestedSizeIndex()
{
	int index = -1;
	int dif1, dif2 = INT_MAX;

	for (int i = 0; i < scaleSizes.size(); i++)
	{
		dif1 = abs(7 - scaleSizes[i]);

		if (dif1 < dif2)
		{
			dif2 = dif1;
			index = i;
		}
	}

	return index;
}

void ScaleStructure::useSimpleSizeStructure()
{
	// Find out how many notes each color tier will have
	// Can be made to be customized
	int scaleSize = scaleSizes[currentSizeSelected];

	sizeGroupings = { currentSizeSelected };

	int notesLeft = period - scaleSize;
	int subSizeIdx = currentSizeSelected - 1;
	int subSize = scaleSizes[subSizeIdx];

	while (notesLeft > 0)
	{
		while (subSize > notesLeft && subSizeIdx > 0)
			subSize = scaleSizes[--subSizeIdx];

		if (subSizeIdx < 0)
		{
			DBG("ERROR: Bad note segmenting");
			return;
		}

		int q = notesLeft / subSize;
		for (int i = 0; i < q; i++)
		{
			sizeGroupings.add(subSizeIdx);
		}

		notesLeft -= (q * subSize);
	}
    
    fillDegreeGroupings();
}

void ScaleStructure::useCascadingSizeStructure()
{
	int scaleSize = scaleSizes[currentSizeSelected];
	sizeGroupings = { currentSizeSelected };

	int notesLeft = period - scaleSize;
	int subSizeIdx = currentSizeSelected;
	int subSize = scaleSize;

	while (notesLeft > 0)
	{
		int q = notesLeft / subSize;
		if (notesLeft <= subSize && scaleSizes.contains(notesLeft))
		{
			sizeGroupings.add(scaleSizes.indexOf(notesLeft));
			break;
		}
		else if (q >= 2)
		{
			int iterations = notesLeft % subSize == 0 ? q : q - (q % 2);
			for (int i = 0; i < iterations; i++)
			{
				sizeGroupings.add(subSizeIdx);
				notesLeft -= subSize;
			}
		}

		subSize = scaleSizes[--subSizeIdx];
	}

    fillDegreeGroupings();
}

bool ScaleStructure::isValid() const
{	
	bool valid = true;

	if (generator < 0 || generator > validGenerators.size())
	{
		DBG("Invalid generator");
		valid = false;
	}

	if (currentSizeSelected < 0 || currentSizeSelected >= scaleSizes.size())
	{
		DBG("Invalid scale size");
		valid = false;
	}

	int sum = 0;
	for (int s = 0; s < sizeGroupings.size(); s++)
	{
		sum += scaleSizes[sizeGroupings[s]];
	}
	
	if (sum != period)
	{
		DBG("Invalid scale groupings");
		valid = false;
	}

	return valid;
}
