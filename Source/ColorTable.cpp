/*
  ==============================================================================

    ColorTable.cpp
    Created: 28 Jan 2020 9:29:49pm
    Author:  Vincenzo

  ==============================================================================
*/

#include "ColorTable.h"

ColourTableModel::ColourTableModel(Array<Colour>* colourPaletteIn)
{
	colourPalette = colourPaletteIn;
}

ColourTableModel::~ColourTableModel()
{
	ListBoxModel::~ListBoxModel();
}

void ColourTableModel::setColours(Array<Colour>* colourPaletteIn)
{
	colourPalette = colourPaletteIn;
}

void ColourTableModel::setListBoxComponent(ListBox* listBoxIn)
{
	theBox = listBoxIn;
}

int ColourTableModel::getNumRows()
{
	// TODO: Add colour utility
	return 6;
}

void ColourTableModel::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
	g.fillAll(colourPalette->getUnchecked(rowNumber));
}

Component* ColourTableModel::refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate)
{
	return existingComponentToUpdate;
}

void ColourTableModel::listBoxItemClicked(int row, const MouseEvent& e)
{
	ColourSelector* cs = new ColourSelector();
	cs->setComponentID(String(row));
	cs->setCurrentColour(colourPalette->getUnchecked(row));
	cs->addChangeListener(this);
	cs->setSize(300, 400);

	Rectangle<int> area = theBox->getRowPosition(row, true).withPosition(theBox->getBoundsInParent().getPosition());
	CallOutBox::launchAsynchronously(cs, area, theBox->getParentComponent());
}

void ColourTableModel::changeListenerCallback(ChangeBroadcaster* broadcaster)
{
	ColourSelector* cs = dynamic_cast<ColourSelector*>(broadcaster);
	colourPalette->set(cs->getComponentID().getIntValue(), cs->getCurrentColour());
}