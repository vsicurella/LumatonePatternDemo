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

static Array<int> octaveRowSpacings = { 2, 6, 6, 7, 6, 7, 6, 7, 5, 2 };
static Array<int> octaveRowLeads = {0, 2, 7, 13, 19, 25, 31, 37, 43, 49, 54};

static Array<Array<int>> downRightBorder = { Array<int>({ 18, 30, 42, 53 }), Array<int>({ 7, 19, 31, 43 }) };
static Array<Array<int>> rightBorder = { Array<int>({ 12, 18, 30, 36, 42, 48, 53, 54 }), Array<int>({ 0, 2, 7, 13, 19, 25, 31, 37, 43 }) };

static Array<int> upLeftEdge = { 0, 1, 4, 5, 6 };
static Array<int> downRightEdge = { 43, 49, 50, 51, 54 };

static Array<int> leftEdge = { 49, 54 };
static Array<int> rightEdge = { 1, 6 };


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
			kbdNumOut = downRightBorder[1][ind] + octaveNum * 55;
		}
	}
	else
	{
		int rowNum;
		for (int i = 1; i < octaveRowLeads.size() - 1; i++)
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
			kbdNumOut = downRightBorder[0][ind] + octaveNum * 55;
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
			kbdNumOut = rightBorder[1][ind] + octaveNum * 55;
		}
	}
	else
	{
		kbdNumOut = (kbdNumIn + 1) + octaveNum * 55;
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
			kbdNumOut = rightBorder[0][ind] + octaveNum * 55;
		}
	}
	else
	{
		kbdNumOut = (kbdNumIn - 1) + octaveNum * 55;
	}

	return kbdLeft(kbdNumOut, --numSteps);
}

static int kbdMove(int kbdNumIn, Point<int> hexxy)
{
	int kbdNumOut = -1;

	if (hexxy.x > 0)
		kbdNumOut = kbdDownRight(kbdNumIn, hexxy.x);
	else if (hexxy.x < 0)
		kbdNumOut = kbdUpLeft(kbdNumIn, hexxy.x);

	if (hexxy.y > 0)
		kbdNumOut = kbdRight(kbdNumOut, hexxy.y);
	else if (hexxy.y < 0)
		kbdNumOut = kbdLeft(kbdNumOut, hexxy.y);

	return kbdNumOut;
}

static Array<int> kbdScalePattern(Point<int> periodHXY, Point<int> genHXY, int scaleSize, int rootKbdKey)
{
	Array<int> kbdKeysOut;
	int octaveKeyNum = rootKbdKey % 55;
	int periodKey = kbdMove(octaveKeyNum, periodHXY);
	int generatorKey = kbdMove(octaveKeyNum, genHXY);

	Point<int> nextMove;
	if (periodKey > -1 && generatorKey > -1)
	{
		for (int n = 0; n < scaleSize; n++)
		{
			nextMove = Point<int>(genHXY.x * n % periodHXY.x, genHXY.y * n % periodHXY.y);
			kbdKeysOut.add(kbdMove(rootKbdKey, nextMove));
		}

		for (int oct = 1; oct < 5; oct++)
		{
			for (int key = 0; key < scaleSize; key++)
			{
				kbdKeysOut.add(kbdKeysOut[key] + oct * 55);
			}
		}
	}

	return kbdKeysOut;
}