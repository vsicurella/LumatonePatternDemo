/*
  ==============================================================================

    LayoutGenerator.h
    Created: 20 Jan 2020 8:29:14pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once
#include "CommonFunctions.h"
#include "Ratio.h"
#include "ScaleStructure.h"

class LayoutGenerator
{
    // Independent Properties
    int scalePeriod = 12; // total number of notes in scale
    int generator = 7; // step to generate MOS scale
	int generatorOffset = -1; // number of generators to start on

	int kbdType = 0; // the keyboard type index, determining the size of the MOS
	int scaleSize = 0; // size of MOS scale
    
	int rootKey = 129;
	bool flipScale = false;

	Array<Colour> scaleColours; // the colors chosen for the scale segments


	// Dependent Properties
    Ratio gOverP; // the proportion of the generator over the period
	ScaleStructure structure; // calculates the properties of the selected scale

	Array<int> validGenerators; // array of valid generators for scale size
	Array<Ratio> validKeyboards; // array of possible keyboard types
	Array<int> validSizes; // array of valid MOS scale sizes
	Array<PointPair<int>> pgCoords; // the coordinates of the period & generator with respect to the keyboard types

	std::unique_ptr<Array<int>> kbdScaleDegrees; // array of root-note-offsets per keyboard key number
	std::unique_ptr<Array<Array<int>>> notesByGenerators; // the notes by number of generators, with separate tiers for different colors


    bool validLayout = false;
    
    // Methods
    
    void updateValidOptions();
    
  public:
  
    LayoutGenerator(int periodIn);
    LayoutGenerator(int periodIn, int genIn);
    LayoutGenerator(int periodIn, int genIn, int kbdTypeIn, int rootIn=129);
	LayoutGenerator(const LayoutGenerator& layoutToCopy);
    ~LayoutGenerator();
	
	void mapKeysToDegree();
	void mapGeneratorsToNotes();
	void refresh();

	// Getters

    Ratio* getGenPeriodRatio();
	int getGeneratorOffset();
	int getKeyboardType();
	int getScaleSize();
	int getRootKey();
	bool isScaleFlipped();

	Array<Colour> getScaleColours();

	Array<int>* getKbdDegrees();
	int getKeyDegree(int keyNumIn);
	Array<Array<int>>* getGeneratorNotes();

    Array<int> getValidGenerators();
	Array<Ratio> getValidKeyboards();
    Array<int> getValidSizes();
	Array<PointPair<int>> getPGCoords();
	PointPair<int> getPGCoord();
	PointPair<int> getPGCoord(int kbdInd);

	Point<int> getXYSteps();
	Point<int> getXYSteps(int kbdInd);
    
    bool isValid();

	// Setters

	void setGeneratorOffset(int genOffsetIn);
	void setKeyboardType(int kbdIndexIn);
	void setRootKey(int rootKeyIn);
	void setScaleFlipped(bool doFlip);

	void addColour(Colour colorIn);
	void setColour(int index, Colour colorIn);
	void resetColours();
};
