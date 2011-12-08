
/*****************************************************************************
 
 Copyright (C) 2011 by Bernard Geyer
 
 http://bernardgeyer.com/
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 *****************************************************************************/

#ifndef _HLISTBOX
#define _HLISTBOX

#include "hPanel.h"

//--------------------------------------------------------

class hLabel;
class hNumberBox;
class hScrollBar;
class hScrollButton;

class hListBox: public hPanel{
public:
    hListBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	// 'width' is the width of the text items, height is automatically calculated
	// 'buttonHight' is just a default hight before items are add

    void clear(void);
	// remove the whole content (items and data) of a listBox

	virtual void addItems(int numItems, std::string label);
	// 'items' are the visible hListItem objects in the listbox
	// 'elements' are the total number of data objects (made visible by a scrollbar)

    void addData(std::string label);
	// Add a new data element to a listBox
	// radioFlag is true by default

    hGuiData * findElement(std::string label);
	// Find an element by label
	

    void selectElement(int element);
	// Select an element
	// Warning: first element = #1

    void selectElement(std::string label);
	// Select an element by label

    void unselectElement(int element);
	// Unselect an element
	// Warning: first element = #1
	
    void elementSetSelected(int element, bool flag);
	// Select/unselect an element depending on flag
	// Warning: first element = #1
	
    void unselectLastRadioElement(void);
	// Unselect the last selected element
	// Only used by radio-enabled elements
	

	void selectItem(int item);
	// Same than selectElement, used for non-scrollable widgets
	
    void unselectItem(int item);
	// Same than unselectElement, used for non-scrollable widgets
	
    void itemSetSelected(int item, bool flag);
	// Same than elementSetSelected, used for non-scrollable widgets 

    void unselectLastRadioItem(void);
	// Same than unselectLastRadioElement, used for non-scrollable widgets 
	
    void clearLabels(void);
	// Clear the label of every element in the list box

	void setElementLabel(int element, std::string s);
	// 'element' is the element number to modify (starting with 1)

    void setRadioEnabled(bool radioFlag);
	// WARNING : It is necessary to do this AFTER adding items and data
	// Modify the radio mode of all elements of the listBox
	// Radio mode is true by default
	// Radio mode off means that it is possible to select more than one item

    void setElementRadioEnabled(int element, bool radioFlag);
	// 'element' is the element number to modify (starting with 1)
	// Note: Normally there is no need to modify the radio mode of only a few elements

    void setAllElementsDisabled(bool disableFlag);
	// Disable all elements of the listBox
	// Warning : It is necessary to do this AFTER adding items and data
	
    void setElementDisabled(int element, bool disableFlag);
	// 'element' is the element number to modify (starting with 1)

	void setBackgroundColor(int color);
	// Set the same background color for all elements
	// Warning : It is necessary to do this BEFORE adding items and data

	void setSelectColor(int color);
	// Set the same select color for all elements
	// Warning : It is necessary to do this BEFORE adding items and data

    void setElementSelectColor(int element, int color);
	// 'element' is the element number to modify (starting with 1)
	// Important: to attribute the same color to all elements
	// call setSelectColor BEFORE adding items and data
	
    void displayIndexes(bool dispFlag);
	// display the index of each item before the label if true
	// Warning : It is necessary to do this BEFORE adding items and data

    void displayAllIndexes(bool dispFlag);
	// set or remove the display of all indexes
	// Warning : It is necessary to do this AFTER adding items and data

    void displayElementIndex(int element, bool dispFlag);
	// 'element' is the element number to modify (starting with 1)
	// Important: to attribute the same index to all elements
	// call displayIndexes BEFORE adding items and data
	
    void setIndexShift(int shift1, int shift10, int shift100);
	// set the x shift of each item for the values 0..9, 10..99, >= 100
	// Warning : It is necessary to do this BEFORE adding items and data

    void setElementIndexShift(int element, int shift1, int shift10, int shift100);
	// 'element' is the element number to modify (starting with 1)
	// Important: to attribute the same index shifts to all elements
	// call setIndexShift BEFORE adding items and data

    void sendWhenReleased(bool flag);
	// Ask to send the message when a list item is realised instead of when it is pushed.
	// Do this when the message needs a lenghty processing
	// Warning : It is necessary to do this BEFORE adding items and data
	
    void setStartIndex(int index);
	// Normally, the indexes of the items start with #1
	// Here we can modify that.
	// Warning : It is necessary to do this BEFORE adding items and data
		
    void setLinkedLabel(hLabel * label);
	// Set the same linked label to all items of the list box
	// Has to be done after all items are defined

    void setLinkedNumberBox(hNumberBox * numberBoxWidget);
	// Set the same linked label to all items of the list box
	// Has to be done after all items are defined

	void setMessage(std::string s);
	// Set the same message to all elements of the list box
	// Has to be done after all elements are defined

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
    void addScrollBar(void);
	// Add a scrollbar to a listBox (automatically done)

    void scrollItems(int startItem);
	// Used by the scrollBar and the scroll buttons

    int getScrollPosition(void);
	// Needed by the scroll buttons

    void setScrollBarPosition(int start_item);
	// Move the scrollBar to a certain position
	// Needed when the content of the list box has been modified
	// (generally move to position 0)
	
	//--------------------------------------------------------

	void saveSettings(ofxXmlSettings * xml);
	// Save the state of the widget to the open xml file
	
	//--------------------------------------------------------
	
protected:
friend class hScrollBar;
friend class hScrollButton;

    int defSelectColor;
    int defBackgroundColor;
    int indexDisplayFlag;
    int indexShift1, indexShift10, indexShift100;
    bool sendWhenReleasedFlag;

    int startIndex;
    int startLine; // First line to display (used by the scrollBar)

	hScrollBar * scrollBar;
    hScrollButton * incButton, * decButton;
};

//--------------------------------------------------------
#endif // _HLISTBOX
