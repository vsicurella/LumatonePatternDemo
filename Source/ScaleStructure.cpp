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
	fractionalPeriods = getFactors(period);
	fractionalPeriodSelected = 0;

	validGenerators = getCoprimes(period / fractionalPeriods[fractionalPeriodSelected]);
}

ScaleStructure::ScaleStructure(int periodIn, int generatorIndex, int sizeIndex, Array<int> degreeGroups)
{
	period = periodIn;
	fractionalPeriods = getFactors(period);
	fractionalPeriodSelected = 0;

	validGenerators = getCoprimes(period / fractionalPeriods[fractionalPeriodSelected]);
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

Array<int> ScaleStructure::getFractionalPeriods() const
{
	return fractionalPeriods;
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
	fractionalPeriods = getFactors(period);
	fractionalPeriodSelected = 0;
	validGenerators = getCoprimes(period / fractionalPeriods[fractionalPeriodSelected]);
	generator = -1;
	currentSizeSelected = -1;

	scaleSizes.clear();
	keyboardTypes.clear();
	pgCoords.clear();
	stepSizes.clear();
}

void ScaleStructure::setFractionalPeriodIndex(int index)
{
	fractionalPeriodSelected = index;
	validGenerators = getCoprimes(period / fractionalPeriods[fractionalPeriodSelected]);
	calculateProperties();
}

void ScaleStructure::setGeneratorIndex(int index)
{
    generator = index;
	calculateProperties();
}

void ScaleStructure::setSizeIndex(int index)
{
	currentSizeSelected = index;
	useSuggestedSizeGrouping();
}

void ScaleStructure::setGeneratorOffset(int offsetIn)
{
	generatorOffset = offsetIn;
	useSuggestedSizeGrouping();
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

    Array<int> cf = getContinuedFraction((double)validGenerators[generator] / (period / fractionalPeriods[fractionalPeriodSelected]));

	// seed the sequence
	Point<int> parent1 = Point<int>(-1 + cf[0], 1);
	Point<int> parent2 = Point<int>(1, 0);
	Point<int> gp = Point<int>(cf[0], 1);

	Array<Point<int>> packet = { gp, parent2, gp + parent2 }; // makes for cleaner code
	pgCoords.add(PointPair<int>(packet[0], packet[1]));
	keyboardTypes.add(packet[2]);
	scaleSizes.add(packet[2].y);

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

	String dbgstr = "";
	for (auto s : keyboardTypes)
	{
		dbgstr += "(" + s.toString() + "), ";
	}

	DBG("Sizes available: " + dbgstr);

	calculateStepSizes();
	calculateGeneratorChain();
}

void ScaleStructure::calculateStepSizes()
{
	stepSizes.clear();

	Point<int> stepSizesOut;
	Point<int> periodCoordinate;
	Point<int> generatorCoordinate;

	int fPeriod = period / fractionalPeriods[fractionalPeriodSelected];
    
    int gen = validGenerators[generator];

	for (int i = 0; i < scaleSizes.size(); i++)
	{
		generatorCoordinate = Point<int>(pgCoords[i].x.x, pgCoords[i].y.x);
		periodCoordinate = Point<int>(pgCoords[i].x.y, pgCoords[i].y.y);

		// find horiztonal step size (X)
		if (periodCoordinate.y == generatorCoordinate.y)
			stepSizesOut.setX(fPeriod - gen);
		else if (periodCoordinate.y == 0)
			stepSizesOut.setX(fPeriod);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(gen);
		else
			stepSizesOut.setX(fPeriod * generatorCoordinate.y - gen * periodCoordinate.y);

		// find upward right step size (Y)
		if (periodCoordinate.x == generatorCoordinate.x)
			stepSizesOut.setY(fPeriod - gen);
		else if (periodCoordinate.x == 0)
			stepSizesOut.setX(fPeriod);
		else if (generatorCoordinate.y == 0)
			stepSizesOut.setX(gen);
		else
			stepSizesOut.setY(gen * periodCoordinate.x - fPeriod * generatorCoordinate.x);

		stepSizes.add(stepSizesOut);
	}
}

void ScaleStructure::calculateGeneratorChain()
{
	Array<int> chain;
    int gen = validGenerators[generator];
	int fractionalPeriod = period / fractionalPeriods[fractionalPeriodSelected];

	for (int i = 0; i < fractionalPeriod; i++)
	{
		chain.add(modulo(i * gen, fractionalPeriod));
	}
	
	generatorChain.clear();
	for (int i = 0; i < fractionalPeriods.size(); i++)
	{
		for (auto d : chain)
			generatorChain.add(d + fractionalPeriod * i);
	}
}

void ScaleStructure::fillDegreeGroupings()
{
	degreeGroupings.clear();

	Array<int> grouping;

	for (int i = 0; i < fractionalPeriods[fractionalPeriodSelected]; i++)
	{
		grouping.addArray(sizeGroupings);
	}

    degreeGroupings.resize(grouping.size());

    // Fill degree groups symmetrically

    int indexForward = generatorOffset;
    int indexBackwards = period - 1 + generatorOffset;
    int indexOffset;
    
    for (int t = 0; t < grouping.size(); t++)
    {
        for (int n = 0; n < scaleSizes[grouping[t]]; n++)
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
	for (int i = 0; i < grouping.size(); i++) {
		size = scaleSizes[grouping[i]];
		dbgstr += String(size) + ", ";
		sum += size;
	}
	dbgstr += " = " + String(sum);
	DBG("Using this size grouping: " + dbgstr);

	dbgstr = "";
	for (int group = 0; group < grouping.size(); group++)
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

void ScaleStructure::fillGroupingsSymmetrically()
{
	degreeGroupings.clear();

	Array<int> grouping;
	for (int i = 0; i < fractionalPeriods[fractionalPeriodSelected]; i++)
	{
		grouping.addArray(sizeGroupings);
	}

	degreeGroupings.resize(grouping.size());

	// Fill degree groups symmetrically

	int indexOffset = modulo(generatorOffset, period);

	for (int t = 0; t < grouping.size(); t++)
	{
		for (int n = 0; n < scaleSizes[grouping[t]]; n++)
		{
			degreeGroupings.getReference(t).add(generatorChain[indexOffset]);
			indexOffset = modulo(indexOffset + 1, period);
		}
	}

	String dbgstr = "";
	int size, sum = 0;
	for (int i = 0; i < grouping.size(); i++) {
		size = scaleSizes[grouping[i]];
		dbgstr += String(size) + ", ";
		sum += size;
	}
	dbgstr += " = " + String(sum);
	DBG("Using this size grouping: " + dbgstr);

	dbgstr = "";
	for (int group = 0; group < grouping.size(); group++)
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
	int fractionalPeriod = fractionalPeriods[fractionalPeriodSelected];
	float interval = 1200 / period / fractionalPeriod;
	int suggestedCents = 700 / fractionalPeriod;

	for (int i = 1; i < validGenerators.size(); i++)
	{
		dif1 = abs(suggestedCents - interval * validGenerators[i]);

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

Array<int> ScaleStructure::getNestedSizeGrouping()
{
	int scaleSize = scaleSizes[currentSizeSelected];
	Array<int> grouping = { currentSizeSelected };

	int notesLeft = (period / fractionalPeriods[fractionalPeriodSelected]) - scaleSize;
	int subSizeInd = currentSizeSelected;
	int subSize = scaleSize;

	while (notesLeft > 0)
	{
		int q = notesLeft / subSize;

		if (notesLeft <= subSize && scaleSizes.contains(notesLeft))
		{
			grouping.add(scaleSizes.indexOf(notesLeft));
			notesLeft = 0;
		}
		else if (q >= 2)
		{
			int numToAdd = notesLeft % subSize == 0 ? q : q - (q % 2);
			for (int n = 0; n < numToAdd; n++)
			{
				grouping.add(subSizeInd);
				notesLeft -= subSize;

				// check if notesLeft can be divided equally by next size
				if (subSizeInd > 0)
				{
					int stagedSubInd = subSizeInd - 1;
					int stagedSubSize = scaleSizes[stagedSubInd];
					int q2 = notesLeft / stagedSubSize;

					if (notesLeft % stagedSubSize == 0)
					{
						// extra check for symmetry
						if (q2 % 2 == 0)
						{
							for (int qn = 0; qn < q2; qn++)
							{
								grouping.add(stagedSubInd);
								notesLeft -= stagedSubSize;
							}

							break;
						}
					}
				}
			}
		}

		subSize = scaleSizes[--subSizeInd];
	}

	DBG("Nested group:");
	String dbgstr = "";
	for (int i = 0; i < grouping.size(); i++)
		dbgstr += String(scaleSizes[grouping[i]]) + ", ";
	DBG(dbgstr);

	return grouping;
}

// TODO: possibility for improving large scales groupings.
// When checking the "staged" sizes, there could be an additional check to see if
// a different configuration of those two sizes produce a smaller grouping
// ex. with this algorithm, "Schismatic" 69/118 scale gives (7 * 4) + (5 * 18) or 22 groups
// but this could be reduced to (7 * 14) + (5 * 4) for 18 groups
Array<int> ScaleStructure::getComplimentarySizeGrouping()
{
	int scaleSize = scaleSizes[currentSizeSelected];
	Array<int> grouping = { currentSizeSelected };

	int notesLeft = (period / fractionalPeriods[fractionalPeriodSelected]) - scaleSize;
	int subSizeInd = currentSizeSelected;
	int subSize = scaleSize;

	int q = notesLeft / subSize;
	int numToAdd = notesLeft % subSize == 0 ? q : q - (q % 2);
	int num = 0;

	while (notesLeft > 0)
	{
		// check if notesLeft can be divided equally by next size
		if (subSizeInd > 0)
		{
			int stagedSubInd = subSizeInd - 1;
			int stagedSubSize = scaleSizes[stagedSubInd];
			int q2 = notesLeft / stagedSubSize;

			if (notesLeft % stagedSubSize == 0)
			{
				// extra check for symmetry
				int groupSize = grouping.size() - 1;
				if (groupSize == 0 || q2 % 2 == 0)
				{
					for (int qn = 0; qn < q2; qn++)
					{
						grouping.add(stagedSubInd);
						notesLeft -= stagedSubSize;
					}

					break;
				}
			}
		}

		if (notesLeft <= subSize && scaleSizes.contains(notesLeft))
		{
			grouping.add(scaleSizes.indexOf(notesLeft));
			notesLeft = 0;
		}
		else if (q >= 0 && num < numToAdd)
		{
			grouping.add(subSizeInd);
			notesLeft -= subSize;
			num++;
		}
		else if (notesLeft > 0)
		{
			subSize = scaleSizes[--subSizeInd];
			q = notesLeft / subSize;
			numToAdd = notesLeft % subSize == 0 ? q : q - (q % 2);
			num = 0;
		}
	}

	DBG("Complimentary group:");
	String dbgstr = "";
	for (int i = 0; i < grouping.size(); i++)
		dbgstr += String(scaleSizes[grouping[i]]) + ", ";
	DBG(dbgstr);

	return grouping;
}

void ScaleStructure::useSuggestedSizeGrouping()
{
	Array<Array<int>> groupings;
	groupings.add(getNestedSizeGrouping());
	groupings.add(getComplimentarySizeGrouping());

	Array<float> groupingScores;

	// create score by averaging range and length of group
	for (auto g : groupings)
	{
		int range = g[0] - g[g.size() - 1];
		groupingScores.add((range + g.size()) / (float) groupings.size());
	}

	// find lowest score and return respective group
	int index = 0;
	for (int s = 0; s < groupings.size(); s++)
	{
		if (groupingScores[s] < groupingScores[index])
			index = s;
	}

	// make symmetric and fill degree groupings
	sizeGroupings = arrangeSymmetrically(groupings[index]);

	DBG("Symmetric group:");
	String dbgstr = "";
	for (int i = 0; i < sizeGroupings.size(); i++)
		dbgstr += String(scaleSizes[sizeGroupings[i]]) + ", ";
	DBG(dbgstr);

	fillGroupingsSymmetrically();
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
		sum += scaleSizes[sizeGroupings[s]] * fractionalPeriods[fractionalPeriodSelected];
	}
	
	if (sum != period)
	{
		DBG("Invalid scale groupings");
		valid = false;
	}

	return valid;
}
