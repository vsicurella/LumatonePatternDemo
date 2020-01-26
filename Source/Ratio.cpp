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

void Ratio::setNumerator(int numeratorIn, bool doCf)
{
    numerator = numeratorIn;
    
    if (doCf)
        recalculate();
}

void Ratio::setDenominator(int denominatorIn, bool doCf)
{
    denominator = denominatorIn;
    
    if (doCf)
        recalculate();
}

double Ratio::getNumerator() const
{
    return numerator;
}

int Ratio::getDenominator() const
{
    return denominator;
}


Array<Ratio> Ratio::getConvergents() const
{
    return convergents;
}

Array<Ratio> Ratio::getApproximations() const
{
    return approximations;
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
    if (cf.size() < 1 || cf.size() != cfDepth)
    {
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
        
        calculateConvergents();
    }
    
    return cf;
}

void Ratio::calculateConvergents()
{
    Ratio conv, semiConv, nextConv, prevConv;
    
    convergents.clear();
    approximations.clear();
    
    // get convergents
    for (int i = 0; i < cf.size(); i++)
    {
        conv = Ratio(cf[i], 1, false);
        
        for (int j = i; j > 0; j--)
        {
            conv = conv.reciprocal(false);
            conv.setNumerator(
                (cf[j-i] * conv.getDenominator()) + conv.getNumerator(), false);
        }
        
        convergents.add(conv);
    }
    
    // find and add semiconvergents
    int nextNum, nextDen;
    
    int startIndex = 1;
    
    if (convergents.getReference(0).getNumerator() != 0)
        approximations.add(convergents[0]);
    else
        startIndex = 2;
    
    for (int i = startIndex; i < cf.size() - 1; i++)
    {
        prevConv = convergents[i - 1];
        conv = convergents[i];
        approximations.add(conv);

        nextConv = convergents[i + 1];
        
        nextNum = prevConv.getNumerator() + conv.getNumerator();
        nextDen = prevConv.getDenominator() + conv.getDenominator();
        
        while(nextNum < nextConv.getNumerator() ||
              nextDen < nextConv.getDenominator())
        {
            semiConv = Ratio(nextNum, nextDen, false);
            approximations.add(semiConv);
            
            nextNum = conv.getNumerator() + semiConv.getNumerator();
            nextDen = conv.getDenominator() + semiConv.getDenominator();
        }
    }
    
    approximations.add(nextConv);
}

Array<Ratio> Ratio::getApproximations(bool n)
{
    approximations.clear();
    
    Array<int> nums;
    Array<int> dens;
    
    int size = cf.size();
    int cfDigit;
    int num, den, tmp;
    int scNum, scDen;
    
    Array<int> convInd;
    
    for (int d = 0; d < size; d++)
    {
        cfDigit = cf[d];
        
        num = cfDigit;
        den = 1;
        
        // calculate the convergent
        for (int i = d; i > 0; i--)
        {
            tmp = den;
            den = num;
            num = tmp;
            num += den * cf[i - 1];
        }
        
        // if there are semiconvergents available, calculate them first
        // before adding the new convergent
        if (cfDigit > 1 && d > 1)
        {
            // the first one uses the penultimate convergent
            // and the for-loop uses the last convergent
            scNum = nums[convInd[d-1]] + nums[convInd[d-2]];
            scDen = dens[convInd[d-1]] + dens[convInd[d-2]];
            
            nums.add(scNum);
            dens.add(scDen);
            approximations.add(Ratio(scNum, scDen));
            
            for (int i = 1; i < cfDigit - 1; i++)
            {
                scNum += nums[convInd[d-1]];
                scDen += dens[convInd[d-1]];
                
                nums.add(scNum);
                dens.add(scDen);
                approximations.add(Ratio(scNum, scDen));
            }
        }
        
        convInd.add(nums.size());

        nums.add(num);
        dens.add(den);
        
        approximations.add(Ratio(num, den));
    }
    
    return approximations;
}

/*
 Returns a ratio approximating this ratio.
 */
Ratio Ratio::getApproximation(int iteration)
{
    if (iteration >= approximations.size())
        iteration = approximations.size() - 1;
    
    else if (iteration < 0)
        iteration = 0;
    
    return approximations[iteration];
}

/*
 Returns the best ratio approximating this ratio within a certain prime limit
 with the lowest cents error.
 */

Ratio Ratio::getApproximation(int primeLimitIn, const int* primes, size_t primesSize, double centsError, int maxInt)
{
    Ratio ratioOut;
    Ratio approx;
    
    int primeLimit;
    double centsDelta;
    
    bool useCents = centsError > 0;
    bool useMaxInt = maxInt > 0;
    
    for (int i = 0; i < approximations.size(); i++)
    {
        approx = approximations[i];
        primeLimit = approx.getPrimeLimit(primes, primesSize);
        centsDelta = fabs(approx.cents() - cents());

        if (useCents)
        {
            if (primeLimit < primeLimitIn && centsDelta <= centsError && getNumerator() < maxInt)
                ratioOut = approx;

            if (primeLimit == primeLimitIn)
            {
                ratioOut = approx;
            }
        }

        else
        {
            if (primeLimit <= primeLimitIn && getNumerator() < maxInt)
            {
                ratioOut = approx;
                if (primeLimit == primeLimitIn)
                    break;
            }
        }
    }

    if (ratioOut.getNumerator() == 1 && ratioOut.getDenominator() == 1)
        ratioOut = getClosestApproximation();

    return ratioOut;
}

Ratio Ratio::getClosestApproximation()
{
    return approximations[approximations.size() - 1];
}

Array<int> Ratio::getMonzo()
{
    return monzo;
}

Array<int> Ratio::getMonzo(const int* primes, size_t primeSize)
{
    if (monzo.size() > 0 || numerator != (int) numerator)
        return monzo;
    
    double numFrac = numerator;
    double denFrac = denominator;
    double quotient;
    
    if (numerator == (int) numerator)
    {
        for (int i = 0; i < primeSize; i++)
        {
            if (primes[i] > numFrac)
                break;
            
            if (monzo.size() < (i+1))
            {
                monzo.add(0);
            }
            
            quotient = numFrac;
            quotient /= primes[i];
            
            while(quotient == (int) quotient)
            {
                numFrac = quotient;
                monzo.set(i, monzo[i] + 1);
                quotient /= primes[i];
            }
            
        }
        
        for (int i = 0; i < primeSize; i++)
        {
            if (primes[i] > denFrac)
                break;
            
            if (monzo.size() < (i+1))
            {
                monzo.add(0);
            }
            
            quotient = denFrac;
            quotient /= primes[i];
            
            while(quotient == (int) quotient)
            {
                denFrac = quotient;
                monzo.set(i, monzo[i] - 1);
                quotient /= primes[i];
            }
        }
    }
    
    return monzo;
}

int Ratio::getPrimeLimit(const int* primes, size_t primesSize)
{
    int index = getMonzo(primes, primesSize).size() - 1;
    
    if (index < primesSize)
        return primes[index];
    else
        return 0;
}

Array<int> Ratio::getSubgroup(const int* primes, size_t primesSize)
{
    Array<int> subgroupOut;
    getMonzo(primes, primesSize);
    
    for (int i = 0; i < monzo.size(); i++)
    {
        if (abs(monzo[i]) > 0)
        {
            subgroupOut.add(primes[i]);
        }
    }
    
    return subgroupOut;
}

void Ratio::recalculate(int cfDepth)
{
    cf.clear();
    continuedFraction(cfDepth);
    
    monzo.clear();
}

void Ratio::recalculate(const int* primes, size_t primesSize, int cfDepth)
{
    cf.clear();
    continuedFraction(cfDepth);
    
    monzo.clear();
    getMonzo(primes, primesSize);
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
    continuedFraction();
    String cfString;
    
    for (int i = 0; i < cf.size(); i++)
    {
        cfString += String(cf[i]);
        if (i < cf.size() - 1)
            cfString += ",";
    }
    
    return cfString;
}

String Ratio::getMonzoString(const int* primes, size_t primesSize)
{
    getMonzo(primes, primesSize);
    String monzoString = "| ";
    
    for (int i = 0; i < monzo.size(); i++)
    {
        monzoString += String(monzo[i]) + " ";
    }
    
    monzoString += ">";
    
    return monzoString;
}

String Ratio::getLimitString(const int* primes, size_t primesSize)
{
    return String(String(getPrimeLimit(primes, primesSize)) +  "-limit");
}

String Ratio::getRatioString()
{
    return String(numerator) + "/" + String(denominator);
}

String Ratio::toString()
{
    String out = getRatioString() + "\n";
    out += "CF: " + getCFString() + "\n";
    
    return out;
}

String Ratio::toString(const int* primes, size_t primesSize, int approximations)
{
    String out = getRatioString() + "\n";
    out += "CF: " + getCFString() + "\n";
    out += "Monzo: " + getMonzoString(primes, primesSize) + "\n";
    out += getLimitString(primes, primesSize);
    
    if (approximations > 0)
    {
        out += "\nApproximations: ";
        
        for (int i = 0; i < approximations; i++)
        {
            out += getApproximation(i).getRatioString();
            if (i < (approximations-1))
                out += ", ";
        }
    }
    
    return out;
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
        DBG(array.getReference(i).getRatioString() + "\t");
        DBG(String(array.getReference(i).fraction()));
        
        if (i > 0)
        {
            DBG(" (" + String(array.getReference(i).fraction() / array.getReference(i-1).fraction()) + ")");
        }
        
        DBG('\n');
    }
    DBG('\n');
}
