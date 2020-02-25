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
	generator = validGenerators[generatorIndex];

	// TODO: check for valid input
	calculateProperties();

	currentSizeSelected = sizeIndex;
	sizeGroupings = degreeGroups;
}

Array<int> ScaleStructure::getScaleSizes()
{
	return scaleSizes;
}

int ScaleStructure::getScaleSize(int ind)
{
	return scaleSizes[ind];
}

Array<Point<int>> ScaleStructure::getKeyboardTypes()
{
	return keyboardTypes;
}

Point<int> ScaleStructure::getKeyboardType(int ind)
{
	return keyboardTypes[ind];
}

Array<PointPair<int>> ScaleStructure::getPGCoords()
{
	return pgCoords;
}

PointPair<int> ScaleStructure::getPGCoord(int ind)
{
	return pgCoords[ind];
}



int ScaleStructure::getGroupOfDegree(int scaleDegreeIn)
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
	generator = validGenerators[index];
	calculateProperties();
}

void ScaleStructure::setSizeIndex(int index)
{
	currentSizeSelected = index;
	// TODO: recalculate degree groups
}

void ScaleStructure::setGeneratorOffset(int offsetIn)
{
	generatorOffset = offsetIn;
	// TODO: recalculate degree groups
}

Point<int> ScaleStructure::getStepSizes(int kbdTypeIn)
{
	return stepSizes[kbdTypeIn];
}

void ScaleStructure::calculateProperties()
{
	scaleSizes.clear();
	keyboardTypes.clear();
	pgCoords.clear();

	Ratio goverp = Ratio(generator, period);

	Array<int> cf = goverp.continuedFraction();

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

	for (int i = 0; i < scaleSizes.size(); i++)
	{
		generatorCoordinate = Point<int>(pgCoords[i].x.x, pgCoords[i].y.x);
		periodCoordinate = Point<int>(pgCoords[i].x.y, pgCoords[i].y.y);

		// find horiztonal step size (X)
		if (periodCoordinate.y == generatorCoordinate.y)
			stepSizesOut.setX(period - generator);
		else if (periodCoordinate.y == 0)
			stepSizesOut.setX(period);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(generator);
		else
			stepSizesOut.setX(abs(period * generatorCoordinate.y - generator * periodCoordinate.y));

		// find upward right step size (Y)
		if (periodCoordinate.x == generatorCoordinate.x)
			stepSizesOut.setY(period - generator);
		else if (periodCoordinate.x == 0)
			stepSizesOut.setX(period);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(generator);
		else
			stepSizesOut.setY(abs(period * generatorCoordinate.x - generator * periodCoordinate.x));

		stepSizes.add(stepSizesOut);
	}
}

void ScaleStructure::calculateGeneratorChain()
{
	generatorChain.clear();

	for (int i = 0; i < period; i++)
	{
		generatorChain.add(i * generator);
	}
}

void ScaleStructure::fillDegreeGroupings()
{
	degreeGroupings.clear();
	degreeGroupings.resize(sizeGroupings.size());
	int indexOffset;

	for (int g = 0; g < sizeGroupings.size(); g++)
	{
		int groupSize = scaleSizes[sizeGroupings[g]];
		for (int s = 0; s < groupSize; s++)
		{
			indexOffset = modulo(groupSize + s + generatorOffset, period);
			degreeGroupings.getReference(g).add(generatorChain[indexOffset]);
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

	generator = validGenerators[ind];
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

	return ind;
}

void ScaleStructure::useSimpleSizeStructure()
{

}

void ScaleStructure::useCascadingSizeStructure()
{

}