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
	int generator = 0;

	Array<int> validGenerators;

	Array<int> scaleSizes;
	Array<Point<int>> keyboardTypes;
	Array<PointPair<int>> pgCoords;
	Array<Point<int>> stepSizes;

	Array<int> degreeGroupings;
	Array<int> generatorChain;

	int currentSizeSelected = -1;
	int generatorOffset = 0;

	// calculates all the necessary things in one big swoop
	void calculateProperties();
	void calculateStepSizes();
	void calculateGeneratorChain();

public:

	ScaleStructure(int periodIn) {};
	ScaleStructure(int periodIn, int generatorIndex, int sizeIndex, Array<int> degreeGroups=Array<int>());
	ScaleStructure(const ScaleStructure& scaleToCopy);
	ScaleStructure(ValueTree scaleStructureProperties);

	Array<int> getScaleSizes();
	int getScaleSize(int ind);

	Array<Point<int>> getKeyboardTypes();
	Point<int> getKeyboardType(int ind);

	Array<PointPair<int>> getPGCoords();
	PointPair<int> getPGCoord(int ind);

	Point<int> getStepSizes(int kbdTypeIn);

	void setGeneratorIndex(int index);
	void setSizeIndex(int index);
	void setGeneratorOffset(int offsetIn);
};