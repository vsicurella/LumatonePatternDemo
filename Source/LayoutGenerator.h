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

class LayoutGenerator
{
    // Attributes
    
    int scalePeriod = 0; // total number of notes in scale
    int generator = 0; // step to generate MOS scale
    int scaleSize = 0; // size of MOS scale
    
    Ratio gOverP; // the proportion of the generator over the period
    Array<Colour> scaleColors; // the colors chosen for the scale segments
    
    Array<Ratio> validKeyboards; // array of possible keyboard types
    Array<int> validGenerators; // array of valid generators for scale size
    Array<int> validSizes; // array of valid MOS scale sizes
    
    bool validLayout = false;
    
    // Methods
    
    void updateValidOptions();
    
    
  public:
  
    LayoutGenerator(int periodIn);
    LayoutGenerator(int periodIn, int genIn);
    LayoutGenerator(int periodIn, int genIn, int sizeIn);
    
    ~LayoutGenerator();
        
    Ratio getGenPeriodRatio();
    
    Array<Colour> getScaleColours();
    Array<int> getValidGenerators();
    Array<int> getValidSizes();
    Array<Ratio> getValidKeyboards();
    
    bool isValid();
    
};
