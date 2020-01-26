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
	scaleBreakdown();
}

ScaleStructure::ScaleStructure(int periodIn, int generatorIn)
{
	// TODO: valid input checking
	period = periodIn;
	generator = generatorIn;
	scaleBreakdown();
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

Point<int> ScaleStructure::getXYSteps(int kbdTypeIn)
{
	Point<int> xyOut;
	Point<int> periodHXY = pgCoords[kbdTypeIn].x;
	Point<int> generatorHXY = pgCoords[kbdTypeIn].y;

	int gMult;
	int pMult;

	// find delta x
	int lcmy = getLCM(periodHXY.y, generatorHXY.y);
	gMult = (lcmy / generatorHXY.y) * generator;
	pMult = (lcmy / periodHXY.y) * period;
	xyOut.setX(jmax(pMult, gMult) - jmin(pMult, gMult));

	// find delta y
	int lcmx = getLCM(periodHXY.x, generatorHXY.x);
	gMult = (lcmx / generatorHXY.x) * generator;
	pMult = (lcmx / periodHXY.x) * period;
	xyOut.setY(jmax(pMult, gMult) - jmin(pMult, gMult));

	return xyOut;
}

void ScaleStructure::scaleBreakdown()
{
	Ratio gOverP = Ratio(generator, period);
	Array<int> cf = gOverP.continuedFraction();
	
	DBG("P = " + String(period) + ", G = " + String(generator));
	String cfstr = "[";
	for (auto d : cf)
		cfstr += String(d) + ", ";
	cfstr += "]";
	DBG("CF = " + cfstr);

	// the seed
	scaleSizes.add(1);
	keyboardTypes.add(Ratio(1, 1));
	pgCoords.add(PointPair<int>(1, 0, 0, 1));

	// should just use Points instead
	Ratio parent1 = Ratio(0, 1);
	Ratio parent2 = Ratio(1, 0);

	int cfInd = 1;
	int digit = 0;
	int kbdInd = 0;

	DBG(String(cf[0]) + ": " + parent1.toString() + " + " + parent2.toString() + " = " + keyboardTypes[kbdInd].toString());
	String dbgstr;

	// find keyboard types, and their period/generator coordinates
	while (cfInd <= cf.size())
	{
		digit = cf[cfInd];
		dbgstr = String(digit) + ": ";

		for (int d = 0; d < digit; d++)
		{
			// if previous continued fraction index is even,
			// set parent2 to previous result
			if ((cfInd - 1) % 2 == 0)
			{
				parent2 = keyboardTypes[kbdInd];
			}
			else // if odd, set parent1 to previous result
			{
				parent1 = keyboardTypes[kbdInd];
			}

			keyboardTypes.add(parent1.mediant(parent2));
			pgCoords.add(PointPair<int>(parent1.getDenominator(), parent2.getDenominator(), parent1.getNumerator(), parent2.getNumerator()));
			kbdInd++;
			scaleSizes.add(keyboardTypes[kbdInd].getDenominator());

			dbgstr += parent1.toString() + " + " + parent2.toString() + " = " + keyboardTypes[kbdInd].toString() + "\n   ";		
		}

		cfInd++;
		DBG(dbgstr.upToLastOccurrenceOf("\n", false, true));
	}
}