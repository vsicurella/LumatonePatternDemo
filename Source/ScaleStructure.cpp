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


void ScaleStructure::setGeneratorIndex(int index)
{
    generator = index;
	calculateProperties();
}

void ScaleStructure::setSizeIndex(int index)
{
	currentSizeSelected = index;
    useSimpleSizeStructure();
}

void ScaleStructure::setGeneratorOffset(int offsetIn)
{
	generatorOffset = offsetIn;
    useSimpleSizeStructure();
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
			stepSizesOut.setX(abs(period * generatorCoordinate.y - gen * periodCoordinate.y));

		// find upward right step size (Y)
		if (periodCoordinate.x == generatorCoordinate.x)
			stepSizesOut.setY(period - gen);
		else if (periodCoordinate.x == 0)
			stepSizesOut.setX(period);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(gen);
		else
			stepSizesOut.setY(abs(period * generatorCoordinate.x - gen * periodCoordinate.x));

		stepSizes.add(stepSizesOut);
	}
}

void ScaleStructure::calculateGeneratorChain()
{
	generatorChain.clear();
    int gen = validGenerators[generator];
	for (int i = 0; i < period; i++)
	{
		generatorChain.add(i * gen);
	}
}

void ScaleStructure::fillDegreeGroupings()
{
	degreeGroupings.clear();
    degreeGroupings.resize(sizeGroupings.size());

    // Fill degree groups symmetrically

    int indexForward = generatorOffset;
    int indexBackwards = period - 1 - generatorOffset;
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
}

int ScaleStructure::useSuggestedGeneratorIndex()
{
	// suggest the coprime scale degree nearest to a "perfect fifth"
	int genSug = round(period * (0.6));
	int genDif = 0;
	int sugDif = 10e4;
	int ind = 0;

	for (int g = 0; g < validGenerators.size(); g++)
	{
		genDif = genSug - validGenerators[g];
		if (abs(genDif) < sugDif)
		{
			ind = g;
			sugDif = genDif;
		}
	}

    generator = ind;
	calculateProperties();

	return ind;
}

int ScaleStructure::useSuggestedSizeIndex()
{
	int ind = -1;
	int size = 0;
	Array<int> suggestedSizes = { 7, 5, 6, 8, 9, 10 };
	while (ind < 0 && size < scaleSizes.size())
	{
		ind = scaleSizes.indexOf(suggestedSizes[size]);
		size++;
	}

	int s = 4;
	while (ind < 0 && s > 0)
	{
		ind = scaleSizes.indexOf(s--);
	}

	// all scales should at *least* have sizes of 1 or 2
	jassert(ind >= 0);

	currentSizeSelected = ind;
    useSimpleSizeStructure();
    
	return ind;
}

void ScaleStructure::useSimpleSizeStructure()
{
	// Find out how many notes each color tier will have
	// Can be made to be customized
	int scaleSize = scaleSizes[currentSizeSelected];

	Array<int> noteSegments = { scaleSize };

	int notesLeft = period - scaleSize;
	int subSizeIdx = currentSizeSelected - 1;
	int subSize = scaleSizes[subSizeIdx];

	while (subSize > notesLeft && subSizeIdx > 0)
		subSize = scaleSizes[--subSizeIdx];

	if (subSizeIdx <= 0)
	{
		DBG("ERROR: Bad note segmenting");
		return;
	}

	int f = notesLeft / subSize;
	for (int i = 0; i < f; i++)
	{
		noteSegments.add(subSize);
	}

	int remainder = notesLeft % subSize;
	if (remainder > 0)
		noteSegments.add(remainder);
    
    fillDegreeGroupings();
}

void ScaleStructure::useCascadingSizeStructure()
{
    // TODO
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
