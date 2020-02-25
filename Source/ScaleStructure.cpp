/*
  ==============================================================================

    ScaleStructure.cpp
    Created: 25 Jan 2020 5:12:32pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "ScaleStructure.h"

ScaleStructure::ScaleStructure(Ratio generatorOverPeriod)
{
	period = generatorOverPeriod.getDenominator();
	generator = generatorOverPeriod.getNumerator();
	calculateProperties();
}

ScaleStructure::ScaleStructure(int periodIn, int generatorIn)
{
	// TODO: valid input checking
	period = periodIn;
	generator = generatorIn;
	calculateProperties();
}

Array<int> ScaleStructure::getScaleSizes()
{
	return scaleSizes;
}

int ScaleStructure::getScaleSize(int ind)
{
	return scaleSizes[ind];
}

Array<Ratio> ScaleStructure::getKeyboardTypes()
{
	return keyboardTypes;
}

Ratio ScaleStructure::getKeyboardType(int ind)
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

Point<int> ScaleStructure::getStepSizes(int kbdTypeIn)
{
	Point<int> stepSizesOut;
	Point<int> periodCoordinate = pgCoords[kbdTypeIn].x;
	Point<int> generatorCoordinate = pgCoords[kbdTypeIn].y;

	generatorCoordinate = Point<int>(pgCoords[kbdTypeIn].x.x, pgCoords[kbdTypeIn].y.x);
	periodCoordinate = Point<int>(pgCoords[kbdTypeIn].x.y, pgCoords[kbdTypeIn].y.y);

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

	return stepSizesOut;
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
			keyboardTypes.add(Ratio(packet[2]));
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
}