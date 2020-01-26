/*
  ==============================================================================

    Ratio.h
    Created: 11 Aug 2019 2:33:27am
    Author:  Kevin Bloom

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "CommonFunctions.h"

class Ratio
{
public:
    
    Ratio(bool doCf=false);
    
    Ratio(int numeratorIn, int denominatorIn, bool doCf=false);
    
    Ratio(double ratioIn, bool doCf=false);
    
    Ratio(const Ratio& rcopy);
    
    //==============================================================================
     
    double getNumerator() const;
    
    int getDenominator() const;
        
    //==============================================================================
    
    /*
     Returns the reciprocal of this ratio.
     */
    Ratio reciprocal(bool doCf=false) const;
    
    /*
     Returns decimal representation of ratio.
     */
    double fraction() const;
    
    /*
     Returns cents value of the ratio, based on 1200 cents in 2/1
     */
    double cents() const;
    
    /*
     Returns the logarithm of the ratio given a base.
     */
    double log(int base) const;

    //==============================================================================
    
    /*
     Calculates or returns a list of integers that represent the continued fraction form of
     this ratio. Also calculates a series of rational fractions that converge to this ratio.
     */
    Array<int> continuedFraction(int cfDepth=12, double roundingError = 10e-6);
    
	/*
     Calculates if necessary and returns a vector representing the prime factorization of the ratio.
     */
    Array<int> getMonzo();
    
    /*
     Recalculate the continued fraction and monzo
     */
    void recalculate(int cfDepth=12, double roundingError = 10e-6);
    
    //==============================================================================

	Ratio operator*(const Ratio& ratioIn);
	Ratio operator/(const Ratio& ratioIn);

	Ratio mediant(const Ratio& ratioIn);

	//==============================================================================


    /*
     Returns a string representing the continued fraction.
     */
    String getCFString();
    
    /*
     Returns a string representing the monzo
     */
    String getMonzoString(const int* primes, size_t primesSize);
    
    /*
     Returns a string representing this ratio
     */
    String toString();
    
	/*
	 Returns the ratio as a point. A/B -> Point(A, B)
	*/
	Point<int> toPoint();
    
    //==============================================================================

    /*
     Returns the cents difference between two ratios.
     */
    static double compareCents(Ratio& original, Ratio& approx);
    
    /*
     Prints an array of Ratios
     */
    static void DBGRatios(Array<Ratio>& array);
    
    //==============================================================================

private:
    
    double numerator = 1;
    int denominator = 1;
    
    Array<int> cf;
    Array<Ratio> convergents;
    Array<Ratio> approximations;
    
    Array<int> monzo;
};
