/*
  ==============================================================================

    Ratio.h
    Created: 11 Aug 2019 2:33:27am
    Author:  Kevin Bloom

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"

class Ratio
{
public:
    
    Ratio(bool doCf=false);
    
    Ratio(int numeratorIn, int denominatorIn, bool doCf=true);
    
    Ratio(double ratioIn, bool doCf=true);
    
    Ratio(const Ratio& rcopy);
    
    //==============================================================================
    
    void setNumerator(int numeratorIn, bool doCf=true);
    
    void setDenominator(int denominatorIn, bool doCf=true);
    
    double getNumerator() const;
    
    int getDenominator() const;
    
    Array<Ratio> getConvergents() const;
    
    Array<Ratio> getApproximations() const;
    
    Array<Ratio> getApproximations(bool n);

    
    //==============================================================================
    
    /*
     Returns the reciprocal of this ratio.
     */
    Ratio reciprocal(bool doCf=true) const;
    
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
     Returns a ratio approximating this ratio.
     */
    Ratio getApproximation(int iteration);
    
    /*
     Returns the best ratio approximating this ratio within a certain prime limit
     with the lowest cents error.
     */
    Ratio getApproximation(int primeLimit, const int* primes, size_t primesSize, double centsError=5.0, int maxInt=2000);
    
    /*
     Returns the best ratio approximating this ratio within the depth of continued fraction calculated.
     */
    Ratio getClosestApproximation();
    
    
    /*
     Returns a vector representing the prime factorization of the ratio.
     */
    Array<int> getMonzo();
    
    /*
     Calculates and returns a vector representing the prime factorization of the ratio.
     */
    Array<int> getMonzo(const int* primes, size_t primeSize);
    
    /*
     Returns the highest prime number in the ratio's factorization.
     */
    int getPrimeLimit(const int* primes, size_t primesSize);
    
    /*
     Returns an array of ints representing the primes that the ratio consists of.
     */
    Array<int> getSubgroup(const int* primes, size_t primesSize);
    
    /*
     Recalculate the continued fraction and approximations
     */
    void recalculate(int cfDepth=12);
    
    /*
     Recalculate the continued fraction, pproximations, and monzo
     */
    void recalculate(const int* primes, size_t primesSize, int cfDepth=12);
    
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
     Returns a string representing the prime limit of this ratio
     */
    String getLimitString(const int* primes, size_t primesSize);
    
    /*
     Returns a string representing this ratio
     */
    String getRatioString();
    
    /*
     Returns a string representing this ratio and the continued fraction and approximates
     */
    String toString();
    
    /*
     Returns a string representing this ratio and the continued fraction, approximates,
     the monzo, and the prime limit.
     */
    String toString(const int* primes, size_t primesSize, int approximations=0);

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
    
    void calculateConvergents();

    
    double numerator = 1;
    int denominator = 1;
    
    Array<int> cf;
    Array<Ratio> convergents;
    Array<Ratio> approximations;
    
    Array<int> monzo;
};
