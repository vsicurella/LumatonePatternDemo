/*
  ==============================================================================

    CommonFunctions.h
    Created: 21 Jan 2020 9:54:26pm
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

#define PI 3.14159265359f

static Array<int> octaveRowSizes = { 2, 5, 6, 6, 6, 6, 6, 6, 6, 5, 1 };

static Array<int> octaveRowSpacings = {  2, 6, 6,  7,  6,  7,  6,  7,  5,  2 };
static Array<int> octaveRowLeads =   {0, 2, 7, 13, 19, 25, 31, 37, 43, 49, 54};

static Array<Array<int>> downRightBorder = { Array<int>({ 18, 30, 42, 53 }), Array<int>({ 7, 19, 31, 43 }) };
static Array<Array<int>> rightBorder = { Array<int>({ 12, 18, 24, 30, 36, 42, 48, 53, 54 }), Array<int>({ 0, 2, 7, 13, 19, 25, 31, 37, 43 }) };

static Array<int> upLeftEdge = { 0, 1, 4, 5, 6 };
static Array<int> downRightEdge = { 43, 49, 50, 51, 54 };

static Array<int> leftEdge = { 49, 54 };
static Array<int> rightEdge = { 1, 6 };

template <class T>
struct PointPair
{
	Point<T> x, y;

	PointPair() {}
	PointPair(Point<T> xIn, Point<T> yIn)
	{
		x = xIn;
		y = yIn;
	};
	PointPair(T x1, T y1, T x2, T y2)
	{
		x = Point<T>(x1, y1);
		y = Point<T>(x2, y2);
	}
};

static int modulo(int numIn, int mod)
{
	int val = 0;

	if (mod != 0)
		val = ((numIn % mod) + mod) % mod;

	return val;
}

static int getLCM(int num1, int num2)
{
	int L = jmax(num1, num2);
	int s = jmin(num1, num2);

	if (s != 0)
	{
		if (L % s == 0)
			return L / s;

		float q = L / (float)s;
		while (q == (int)q)
		{
			L = q;
		}
	}
	return L * s;
}

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

static void toHexXY(int noteNumber, int& octaveNum, Point<int>& hexxy)
{
	// TODO: error detection
	octaveNum = noteNumber / 55;
	int key = noteNumber % 55;

	int sum = 0;
	for (int r = 0; r < octaveRowSizes.size(); r++)
	{
		for (int c = 0; c < octaveRowSizes[r]; c++)
		{
			if (sum == key)
			{
				hexxy = Point<int>(c, r);
				return;
			}

			sum++;
		}
	}
}

static int fromHexXY(int octaveNum, Point<int> hexxy)
{
	// TODO: error detection

	int sum = 0;
	for (int r = 0; r < hexxy.y; r++)
	{
		for (int c = 0; c < octaveRowSizes[r]; c++)
		{
			sum++;
		}
	}

	return octaveNum * 55 + sum;
}

static int kbdDownRight(int kbdNumIn, int numSteps)
{
	if (numSteps < 1)
		return kbdNumIn;

	int octaveNum = kbdNumIn / 55;
	int octaveKey = kbdNumIn % 55;

	if (downRightEdge.contains(octaveKey))
	{
		DBG("Off the keyboard");
		return -1;
	}

	int ind = downRightBorder.getReference(0).indexOf(octaveKey);
	int kbdNumOut;

	if (ind > -1)
	{
		if (octaveNum == 4)
		{
			DBG("Off the keyboard");
			return -1;
		}
		else
		{
			kbdNumOut = downRightBorder[1][ind] + ++octaveNum * 55;
		}
	}
	else
	{
		int rowNum;
		for (int i = 1; i < octaveRowLeads.size(); i++)
		{
			if (octaveRowLeads[i] < octaveKey)
				continue;
			else if (octaveRowLeads[i] > octaveKey)
			{
				rowNum = i - 1;
				break;
			}
			else
			{
				rowNum = i;
				break;
			}
		}

		kbdNumOut = (octaveKey + octaveRowSpacings[rowNum]) + octaveNum * 55;
	}

	return kbdDownRight(kbdNumOut, --numSteps);
}

static int kbdUpLeft(int kbdNumIn, int numSteps)
{
	if (numSteps < 1)
		return kbdNumIn;

	int octaveNum = kbdNumIn / 55;
	int octaveKey = kbdNumIn % 55;

	if (upLeftEdge.contains(octaveKey))
	{
		DBG("Off the keyboard");
		return -1;
	}

	int ind = downRightBorder.getReference(1).indexOf(octaveKey);
	int kbdNumOut;

	if (ind > -1)
	{
		if (octaveNum == 0)
		{
			DBG("Off the keyboard");
			return -1;
		}
		else
		{
			kbdNumOut = downRightBorder[0][ind] + --octaveNum * 55;
		}
	}
	else
	{
		int rowNum;
		for (int i = 2; i < octaveRowLeads.size(); i++)
		{
			if (octaveRowLeads[i] < octaveKey)
				continue;
			else if (octaveRowLeads[i] > octaveKey)
			{
				rowNum = i - 1;
				break;
			}
			else
			{
				rowNum = i;
				break;
			}
		}

		kbdNumOut = (octaveKey - octaveRowSpacings[rowNum - 1]) + octaveNum * 55;
	}

	return kbdUpLeft(kbdNumOut, --numSteps);
}

static int kbdRight(int kbdNumIn, int numSteps)
{
	if (numSteps < 1)
		return kbdNumIn;

	int octaveNum = kbdNumIn / 55;
	int octaveKey = kbdNumIn % 55;

	if (rightEdge.contains(octaveKey))
	{
		DBG("Off the keyboard");
		return -1;
	}

	int ind = rightBorder.getReference(0).indexOf(octaveKey);
	int kbdNumOut;

	if (ind > -1)
	{
		if (octaveNum == 4)
		{
			DBG("Off the keyboard");
			return -1;
		}
		else
		{
			kbdNumOut = rightBorder[1][ind] + ++octaveNum * 55;
		}
	}
	else
	{
		kbdNumOut = (octaveKey + 1) + octaveNum * 55;
	}

	return kbdRight(kbdNumOut, --numSteps);
}

static int kbdLeft(int kbdNumIn, int numSteps)
{
	if (numSteps < 1)
		return kbdNumIn;

	int octaveNum = kbdNumIn / 55;
	int octaveKey = kbdNumIn % 55;

	if (leftEdge.contains(octaveKey))
	{
		DBG("Off the keyboard");
		return -1;
	}

	int ind = rightBorder.getReference(1).indexOf(octaveKey);
	int kbdNumOut;

	if (ind > -1)
	{
		if (octaveNum == 0)
		{
			DBG("Off the keyboard");
			return -1;
		}
		else
		{
			kbdNumOut = rightBorder[0][ind] + --octaveNum * 55;
		}
	}
	else
	{
		kbdNumOut = (octaveKey - 1) + octaveNum * 55;
	}

	return kbdLeft(kbdNumOut, --numSteps);
}

static int kbdMove(int kbdNumIn, Point<int> hexxy)
{
	int kbdNumOut = kbdNumIn;
	Point<int> ogpt = hexxy;

	if (hexxy.x > 0)
		kbdNumOut = kbdDownRight(kbdNumIn, hexxy.x);
	else if (hexxy.x < 0)
		kbdNumOut = kbdUpLeft(kbdNumIn, hexxy.x);

	if (hexxy.y > 0)
		kbdNumOut = kbdRight(kbdNumOut, hexxy.y);
	else if (hexxy.y < 0)
		kbdNumOut = kbdLeft(kbdNumOut, hexxy.y);

	DBG("Moved " + String(kbdNumIn) + "\tby (" + ogpt.toString() + ") -> (" + hexxy.toString() + ")\tto " + String(kbdNumOut));
	return kbdNumOut;
}

static Array<int> kbdScalePattern(int rootKbdKey, Point<int> periodHXY, Point<int> genHXY, int scaleSize, int genOffset=0)
{
	Array<int> kbdKeysOut;
	Array<int> roots;
	int octaveKeyNum = rootKbdKey % 55;
	int periodKey = kbdMove(octaveKeyNum, periodHXY);
	int generatorKey = kbdMove(octaveKeyNum, genHXY);

	if (periodKey > -1 && generatorKey > -1)
	{
		Point<int> nextMove = Point<int>(genHXY.x * genOffset, genHXY.y * genOffset);

		for (int n = 0; n < scaleSize; n++)
		{
			Point<int> opgt = nextMove;
			if (nextMove.y < 0)
			{
				int f = jmax(abs(nextMove.x) / periodHXY.x, abs(nextMove.y) / periodHXY.y) + 1;
				nextMove += (periodHXY * f);
			}
			DBG("nextMove = ("+opgt.toString()+") -> (" + nextMove.toString() + ")");

			if (nextMove == periodHXY)
				nextMove.setXY(0, 0);
			//else if (nextMove.x > periodHXY.x || nextMove.y > periodHXY.y )
			else if (nextMove.x + nextMove.y > scaleSize)
			{
				// divide by zero possible
				bool xp = (nextMove.x % periodHXY.x == 0  && nextMove.x / periodHXY.x >= 2) ? true : false;
				bool yp = nextMove.y % periodHXY.y == 0 ? true : false;

				nextMove.setXY(nextMove.x % periodHXY.x, nextMove.y % periodHXY.y);

				if (xp) nextMove.setX(periodHXY.x);
				//if (yp) nextMove.setY(periodHXY.y);
			}
			
			//if (nextMove.x < 0 || nextMove.y < 0)
			//{
			//	int f = jmax(abs(nextMove.x) / periodHXY.x, abs(nextMove.y) / periodHXY.y);
			//	nextMove = Point<int>(nextMove.x + periodHXY.x * f, nextMove.y + periodHXY.y * f);
			//}

			//if (nextMove.x > periodHXY.x)
			//{
			//	nextMove = Point<int>(nextMove.x % periodHXY.x, nextMove.y % periodHXY.y);
			//	if (nextMove.x == 0)
			//		nextMove.setX(periodHXY.x);

			//}
			//else if (nextMove.y > periodHXY.y)
			//{
			//	nextMove = Point<int>(nextMove.x % periodHXY.x, nextMove.y % periodHXY.y);
			//	if (nextMove.y == 0)
			//		nextMove.setY(periodHXY.y);
			//}

			int keyOut = kbdMove(rootKbdKey, nextMove);				
			kbdKeysOut.add(keyOut);

			nextMove += genHXY;
		}

		kbdKeysOut.add(kbdMove(rootKbdKey, periodHXY));

		for (int oct = 1; oct < 5; oct++)
		{

		}
	}

	return kbdKeysOut;
}