/*
==============================================================================

Ratio.cpp
Created: 18 Aug 2019 10:31:18am
Author:  Kevin Bloom

==============================================================================
*/

#include "Ratio.h"

Ratio::Ratio(bool doCf)
{
    numerator = 1;
    denominator = 1;
    
    if (doCf)
        continuedFraction();
}

Ratio::Ratio(int numeratorIn, int denominatorIn, bool doCf)
{
    numerator = numeratorIn;
    denominator = denominatorIn;
    
    if (doCf)
        continuedFraction();
}

Ratio::Ratio(double ratioIn, bool doCf)
{
    numerator = ratioIn;
    denominator = 1;
    
    if (doCf)
        continuedFraction();
}

Ratio::Ratio(const Ratio& rcopy)
{
    numerator = rcopy.getNumerator();
    denominator = rcopy.getDenominator();
    
}


//==============================================================================

double Ratio::getNumerator() const
{
    return numerator;
}

int Ratio::getDenominator() const
{
    return denominator;
}

//==============================================================================

Ratio Ratio::reciprocal(bool doCf) const
{
    return Ratio((int) denominator, numerator, doCf);
}

double Ratio::fraction() const
{
    return (double) numerator / denominator;
}

double Ratio::cents() const
{
    return log2(fraction()) * 1200.0;
}

double Ratio::log(int base) const
{
    return log2(fraction()) / log2(base);
}


//==============================================================================

Array<int> Ratio::continuedFraction(int cfDepth, double roundingError)
{
    if (cf.size() < 1)
    {
		if ((int)numerator == numerator)
			cfDepth = 1000; // ratio is rational, can get whole continued fraction

        cf.clear();
        int iterations = 0;
        
        double contFrac = fraction();
        int digit;
        
        while (iterations < cfDepth)
        {
            digit = (int) contFrac;
            cf.add(digit);
            
            contFrac -= (int) contFrac;
            
            if (contFrac == 0 || contFrac <= roundingError)
            {
                break;
            }
            
            contFrac = 1.0 / contFrac;
            
            iterations++;
        }        
    }
    
    return cf;
}

Array<int> Ratio::getMonzo()
{
    if (monzo.size() > 0 || numerator != (int) numerator)
        return monzo;
    
	Array<int> numfacts = getPrimeFactorization(numerator);
	Array<int> denfacts = getPrimeFactorization(denominator);
	int size = jmax(numfacts.size(), denfacts.size());

	for (int i = 0; i < size; i++)
	{
		monzo.add(0);
		if (i < numfacts.size())
			monzo.getReference(i) += numfacts[i];
		if (i < denfacts.size())
			monzo.getReference(i) -= denfacts[i];
	}

	return monzo;
}

void Ratio::recalculate(int cfDepth, double roundingError)
{
    cf.clear();
    continuedFraction(cfDepth, roundingError);
    
    monzo.clear();
	getMonzo();
}

//==============================================================================

Ratio Ratio::operator*(const Ratio& ratioIn)
{
	return Ratio(numerator * ratioIn.getNumerator(), denominator * ratioIn.getDenominator(), false);
}

Ratio Ratio::operator/(const Ratio& ratioIn)
{
	return Ratio(numerator * ratioIn.getDenominator(), denominator * ratioIn.getNumerator(), false);
}

Ratio Ratio::mediant(const Ratio& ratioIn)
{
	return Ratio(numerator + ratioIn.getNumerator(), denominator + ratioIn.getDenominator(), false);
}

//==============================================================================

String Ratio::getCFString()
{
	return arrayToString(cf, "", '[', ']');
}

String Ratio::getMonzoString(const int* primes, size_t primesSize)
{
    return arrayToString(monzo, "", '|', '>');
}

String Ratio::toString()
{
    return String(numerator) + "/" + String(denominator);
}

Point<int> Ratio::toPoint()
{
	return Point<int>(numerator, denominator);
}

double Ratio::compareCents(Ratio& original, Ratio& approx)
{
    return approx.cents() - original.cents();
}

void Ratio::DBGRatios(Array<Ratio>& array)
{
    DBG("Ratios:");
    
    for (int i = 0; i < array.size(); i++)
    {
        DBG(array.getReference(i).toString() + "\t");
        DBG(String(array.getReference(i).fraction()));
        
        if (i > 0)
        {
            DBG(" (" + String(array.getReference(i).fraction() / array.getReference(i-1).fraction()) + ")");
        }
        
        DBG('\n');
    }
    DBG('\n');
}
