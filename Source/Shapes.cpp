/*
  ==============================================================================

    Shapes.cpp
    Created: 22 Jan 2020 12:07:15am
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#include "Shapes.h"

Polygon::Polygon(Rectangle<float> boundsIn, int numSidesIn, double rotationIn)
{
    bounds = boundsIn;
    numSides = numSidesIn;
    rotation = rotationIn;
}

Polygon::~Polygon()
{
}

void Polygon::setBounds(Rectangle<float> boundsIn)
{
    bounds = boundsIn;
}

std::unique_ptr<Drawable> Polygon::createCopy() const
{
    return std::unique_ptr<Drawable>(new Polygon(bounds, numSides, rotation));
}

Path Polygon::getOutlineAsPath() const
{
    Path outline;
    outline.addPolygon(bounds.getCentre().toFloat(), numSides, bounds.getWidth()/2);
    return outline;
}

Rectangle<float> Polygon::getDrawableBounds() const
{
    return bounds.toFloat();
}
