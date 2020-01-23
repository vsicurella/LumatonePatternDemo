/*
  ==============================================================================

    Shapes.h
    Created: 22 Jan 2020 12:07:15am
    Author:  Vincenzo Sicurella

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#define PI = 3.14159265359

class Polygon : public DrawableShape
{
    Rectangle<float> bounds;
    int numSides = 6;
    double rotation = 0;
    
public:
    
    Polygon(Rectangle<float> boundsIn, int numSidesIn, double rotationIn=0);
    ~Polygon() override;
    
    void setBounds(Rectangle<float> boundsIn);
    
    std::unique_ptr<Drawable> createCopy() const override;

    Path getOutlineAsPath() const override;
    
    Rectangle<float> getDrawableBounds() const override;
};
