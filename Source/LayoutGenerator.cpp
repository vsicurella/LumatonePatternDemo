/*
  ==============================================================================

    LayoutGenerator.cpp
    Created: 20 Jan 2020 8:29:14pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#include "LayoutGenerator.h"


LayoutGenerator::LayoutGenerator(int periodIn)
{
    // TODO: add validity checks
    scalePeriod = periodIn;
    
    updateValidOptions();
}

LayoutGenerator::LayoutGenerator(int periodIn, int genIn)
{
    
    // TODO: add validity checks

    scalePeriod = periodIn;
    generator = genIn;
    
    updateValidOptions();
}

LayoutGenerator::LayoutGenerator(int periodIn, int genIn, int sizeIn)
{
    // TODO: add validity checks

    scalePeriod = periodIn;
    generator = genIn;
    scaleSize = sizeIn;
    
    updateValidOptions();
}

LayoutGenerator::~LayoutGenerator()
{
    
}
  
void LayoutGenerator::updateValidOptions()
{
    validGenerators = getCoprimes(scalePeriod);
    
    if (!validGenerators.contains(generator))
    {
        DBG("Error: invalid generator size");
        validLayout = false;
        return;
    }
    
    gOverP = Ratio(generator, scalePeriod);
    validKeyboards = gOverP.getApproximations(true);
    
    validSizes.clear();
    for (auto r : validKeyboards)
    {
        validSizes.add(r.getDenominator());
    }
    
    if (validSizes.contains(scaleSize))
    {
        validLayout = true;
    }
    else
    {
        DBG("ERROR: invalid scale size");
        //TODO: implement size error handling
        validLayout = true;
    }
}

Ratio LayoutGenerator::getGenPeriodRatio()
{
    return gOverP;
}

Array<Colour> LayoutGenerator::getScaleColours()
{
    return Array<Colour>();
}

Array<int> LayoutGenerator::getValidGenerators()
{
    return validGenerators;

}

Array<int> LayoutGenerator::getValidSizes()
{
    return validSizes;

}

Array<Ratio> LayoutGenerator::getValidKeyboards()
{
    return validKeyboards;
}

bool LayoutGenerator::isValid()
{
    return validLayout;
}
