/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
    : layoutGen(12, 7, 7)
{
        
    gui.reset(new MainWindow(layoutGen));
    gui->setOpaque(false);
    gui->toFront(true);
    addAndMakeVisible(gui.get());
    
    setSize (900, 600);

//    LayoutGenerator lg(84, 19);
//
//    DBG("The period is: " + String(lg.getGenPeriodRatio().getDenominator()));
//    String vs = "";
//    for (auto i : lg.getValidGenerators())
//    {
//        vs += String(i) + ", ";
//    }
//    DBG("Valid generators are: " + vs);
//
//    DBG("Generator Selected: " + String(lg.getGenPeriodRatio().getNumerator()));
//
//    DBG("Possible Keyboards:");
//    for (auto i : lg.getValidKeyboards())
//    {
//        DBG(String(i.getNumerator()) + "/" + String(i.getDenominator()));
//    }
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    gui->repaint();
    
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    gui->setBounds(getLocalBounds());
}
