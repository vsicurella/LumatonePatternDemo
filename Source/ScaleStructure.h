/*
  ==============================================================================

    ScaleStructure.h
    Created: 25 Jan 2020 5:12:32pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "CommonFunctions.h"
#include "Ratio.h"


class ScaleStructure
{
	int period;
	int generator;

	Array<int> scaleSizes;
	Array<Ratio> keyboardTypes;
	Array<PointPair<int>> pgCoords;

	// calculates all the necessary things in one big swoop
	void scaleBreakdown();

public:

	ScaleStructure() {};
	ScaleStructure(Ratio generatorOverPeriod);
	ScaleStructure(int periodIn, int generatorIn);

	Array<int> getScaleSizes();
	int getScaleSize(int ind);

	Array<Ratio> getKeyboardTypes();
	Ratio getKeyboardType(int ind);

	Array<PointPair<int>> getPGCoords();
	PointPair<int> getPGCoord(int ind);

	Point<int> getXYSteps(int kbdTypeIn);
};