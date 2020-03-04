/*
  ==============================================================================

    ScaleStructure.h
    Created: 25 Jan 2020 5:12:32pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once

#include "CommonFunctions.h"

class ScaleStructure
{
	int period;
	int generator = -1;

	Array<int> fractionalPeriods;
	Array<int> validGenerators;

	Array<int> scaleSizes;
	Array<Point<int>> keyboardTypes;
	Array<PointPair<int>> pgCoords;
	Array<Point<int>> stepSizes;

	Array<int> sizeGroupings;
	Array<Array<int>> degreeGroupings;
	Array<int> generatorChain;

	int fractionalPeriodSelected = 0;
	int currentSizeSelected = -1;
	int generatorOffset = 0;

	void calculateProperties();
	void calculateStepSizes();
	void calculateGeneratorChain();
	void fillDegreeGroupings();
	void fillGroupingsSymmetrically();

public:

	ScaleStructure(int periodIn);
	ScaleStructure(int periodIn, int generatorIndex, int sizeIndex, Array<int> degreeGroups=Array<int>());
	ScaleStructure(const ScaleStructure& scaleToCopy);
	ScaleStructure(ValueTree scaleStructureProperties);
    
    int getPeriod() const;
	Array<int> getFractionalPeriods() const;
    
    Array<int> getValidGenerators() const;
    int getGenerator(int genIndex) const;

	Array<int> getScaleSizes() const;
	int getScaleSize(int ind) const;

	Array<Point<int>> getKeyboardTypes() const;
	Point<int> getKeyboardType(int ind) const;

	Array<PointPair<int>> getPGCoords() const;
	PointPair<int> getPGCoord(int ind) const;

	Point<int> getStepSizes(int kbdTypeIn) const;
	int getGroupOfDegree(int scaleDegreeIn) const;

	Array<int> getSizeGrouping() const;
    Array<Array<int>> getDegreeGroupings() const;
    
    int getGeneratorIndex() const;
    int getSizeIndex() const;
	Point<int> getCurrentStepSize() const;

	bool isValid() const;

	void resetToPeriod(int periodIn);

	void setFractionalPeriodIndex(int index);
	void setGeneratorIndex(int index);
	void setSizeIndex(int index);
	void setGeneratorOffset(int offsetIn);

	// returns the index whose generator is closest to a perfect fifth
	int getSuggestedGeneratorIndex();

	// returns the index whose size is closest to 7
	int getSuggestedSizeIndex();
	int getPrefferedSizeIndex(int prefferedSize, bool preferLarger = true);

	Array<int> getNestedSizeGrouping();
	Array<int> getComplimentarySizeGrouping();
	void useSuggestedSizeGrouping();
};
