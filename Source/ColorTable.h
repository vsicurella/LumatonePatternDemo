/*
  ==============================================================================

    ColorTable.h
    Created: 28 Jan 2020 9:29:49pm
    Author:  Vincenzo

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class ColourTableModel : public ListBoxModel,
							private ChangeListener
{
	Array<Colour>* colourPalette;
	ListBox* theBox;

public:

	ColourTableModel(Array<Colour>* colourPaletteIn);
	~ColourTableModel();

	void setColours(Array<Colour>* colourPaletteIn);

	void setListBoxComponent(ListBox* listBoxIn);

	int getNumRows() override;

	void paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;

	Component* refreshComponentForRow(int rowNumber, bool isRowSelected, Component* existingComponentToUpdate) override;

	void listBoxItemClicked(int row, const MouseEvent& e) override;

	void changeListenerCallback(ChangeBroadcaster* broadcaster) override;
};