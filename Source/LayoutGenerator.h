/*
  ==============================================================================

    LayoutGenerator.h
    Created: 20 Jan 2020 8:29:14pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once
#include "ScaleStructure.h"

class LayoutHelper
{
    // Independent Properties   
	int rootKey = 129;
	bool flipScale = false;
	bool negateX = false;
	bool negateY = false;

	Array<Colour>* scaleColours; // the colors chosen for the scale segments

	// Dependent Properties
	const ScaleStructure* structure; // calculates the properties of the selected scale

	std::unique_ptr<Array<int>> kbdScaleDegrees; // array of root-note-offsets per keyboard key number
	std::unique_ptr<Array<Array<int>>> notesByGenerators; // the notes by number of generators, with separate tiers for different colors
    
  public:
  
    LayoutHelper(const ScaleStructure* scaleStructureIn, int rootIn=129);
	LayoutHelper(const LayoutHelper& layoutToCopy);
    ~LayoutHelper();
	
	void mapKeysToDegree();
	void refresh();

	// Getters
    
    int getPeriod();
    int getGenerator();
    int getSize();

	int getRootKey();
	bool isScaleFlipped();

	Array<Colour>* getScaleColours();

	Array<int>* getKbdDegrees();
	int getKeyDegree(int keyNumIn);
    
    Array<Array<int>> getDegreeGroupings();

	// Setters

	void setRootKey(int rootKeyIn);
	void setNegateX(bool doNegate);
	void setNegateY(bool doNegate);
	void setScaleFlipped(bool doFlip);

	void addColour(Colour colorIn);
	void setColour(int index, Colour colorIn);
	void setColours(Array<Colour>* coloursIn);
};
