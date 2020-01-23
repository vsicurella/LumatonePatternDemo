/*
  ==============================================================================

    CommonFunctions.h
    Created: 21 Jan 2020 9:54:26pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define PI = 3.14159265359

static Array<int> getCoprimes(int numIn)
{
    Array<int> coprimes = {1};
    int m, d, t;
    for (int i = 2; i < numIn - 1; i++)
    {
        m = numIn;
        d = i;
        while (d > 1)
        {
            m %= d;
            t = d;
            d = m;
            m = t;
        }
        
        if (d > 0)
            coprimes.add(i);
    }
    
    coprimes.add(numIn-1);
    
    return coprimes;
}

static Array<int> getFactors(int numIn)
{
    Array<int> factors;
    
    for (int i = 2; i < numIn / 2; i++)
    {
        if (numIn % i == 0)
            factors.add(i);
    }
    
    return factors;
}
