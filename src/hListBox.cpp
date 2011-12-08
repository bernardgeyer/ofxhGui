
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

#include "hListBox.h"
#include "hPanel.h"
#include "hListItem.h"
#include "hScrollBar.h"
#include "hScrollButton.h"

#include "hGui.h"

#include "ofxXmlSettings.h"
#include <typeinfo>

//--------------------------------------------------------------

hListBox::hListBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width)
	: hPanel(name, parent, dispMode, xx, yy, width, hGui::getInstance()->buttonHeight, true)
{
	data->type = "list_box";
    // Default index display parameters:
    indexDisplayFlag = false; // false by default
    indexShift1 = 6; indexShift10 = 0, indexShift100 = 0;
	sendWhenReleasedFlag = false;

    startIndex = 1;
    defSelectColor = -1;
    defBackgroundColor = -1;
    startLine = 0;

    incButton = NULL;
    decButton = NULL;
    scrollBar = NULL;

	x -= 2; // little correction
}

//--------------------------------------------------------------

void hListBox::clear(void)
{
    hGui * gui = hGui::getInstance();

    int wsize = widgets.size();
    for(int i = 0; i < wsize; ++i) {
		gui->removeWidget(widgets[i]);
		delete widgets[i];
	}
    widgets.clear();

    int dsize = data_buffer.size();
    for(int i = 0; i < dsize; ++i)
		delete data_buffer[i];
    data_buffer.clear();
}

void hListBox::addItems(int numItems, string label)
{
    hGui * gui = hGui::getInstance();

	string name = data->name;
	string itemName;
	int offset, index;

    int xx = 0, yy = 0;

    if(numItems > 0) {
        for(int i = 0; i < numItems; ++i) {
			offset = data_buffer.size();
			index  = offset + startIndex;
			itemName = name + "_" + ofToString(index);
			// cout << itemName << endl;

			hListItem *item = new hListItem(itemName, this, HGUI_ABSOLUTE_POSITION, x+xx, y+yy, w, label);
			item->getData()->index  = index;
			item->getData()->offset = offset;
			item->setSelectColor(defSelectColor);

			item->displayIndex(indexDisplayFlag);
            item->setIndexShift(indexShift1, indexShift10, indexShift100);
            item->sendWhenReleased(sendWhenReleasedFlag);

            yy += gui->buttonHeight-1;
        }

		// Adapt the size of the panel to the size of all items inside
		int heightOfWidgets = yy+1;
		if(heightOfWidgets > h) h = heightOfWidgets;

    	// Remove the last values of maxX and maxY
#if defined( __WIN32__ ) || defined( _WIN32 )
		addMaxXY(-(gui->scrollBarSize+1), - (gui->buttonHeight-6));
#else
		addMaxXY(-(gui->scrollBarSize+1), - (gui->buttonHeight-5));
#endif
		// Set the new values of maxX and maxY
		addMaxXY((w+gui->scrollBarSize), (h));
	}
}

void hListBox::addData(std::string label)
{
	int offset = data_buffer.size();
	int index  = offset + startIndex;
	string itemName = data->name + ofToString(index);

    hGuiData * newData = new hGuiData;
	data_buffer.push_back(newData);

	newData->name   = data->name + "_" + ofToString(index);
    newData->index  = index;
    newData->offset = offset;

    newData->label = label;

    newData->value  = 0;
    newData->value2 = 0;

    newData->radioEnabled = true;
    newData->selectable = true;
    newData->selected = false;
    newData->disabled = false;

    newData->selectColor = defSelectColor;
    newData->indexDisplayFlag = indexDisplayFlag;
    newData->indexShift1   = indexShift1;
    newData->indexShift10  = indexShift10;
    newData->indexShift100 = indexShift100;

    newData->message = "";

	if(data_buffer.size() > widgets.size())
        addScrollBar(); // We add it only here because we need the real size of h

//  cout << "hListBox::addData " << newData->index << endl;
}

//--------------------------------------------------------------

hGuiData * hListBox::findElement(std::string label)
{
	hGuiData *foundData = NULL;

    int size = data_buffer.size();
    for(int i = size - 1; i >= 0; i--) {
        hGuiData *data = data_buffer[i];
        if(label == data->label) {
            foundData = data;
            break;
        }
    }

	return foundData;
}

//--------------------------------------------------------------

void hListBox::selectElement(int element)
{
	if(element > 0) {
		if(element <= data_buffer.size()) {
			hGuiData *data = data_buffer[element-1];

			if(data->disabled   == true)  return;
			if(data->selectable == false) return;

			// cout << "selectElement " << data->name << endl;
			// cout << "radioEnabled == " << data->radioEnabled << endl;

			if(data->radioEnabled == true) {
				if(selectedRadio != NULL) {
					// cout << "selectedRadio == " << selectedRadio->name << endl;
					unselectLastRadioElement();
				}
				// else cout << "selectedRadio == NULL" << endl;
			}
			data->selected = true;

			if(data->radioEnabled == true)
				selectedRadio = data;
		}
	}
}

void hListBox::selectElement(std::string label)
{
    hGuiData * foundData = findElement(label);

    if(foundData != NULL)
		selectElement(foundData->offset+1);
}

void hListBox::unselectElement(int element)
{
	if(element > 0) {
		if(element <= data_buffer.size()) {
			hGuiData *data = data_buffer[element-1];

			if(data->disabled   == true)  return;
			if(data->selectable == false) return;

			// cout << "unselectElement " << data->name << endl;
			data->selected = false;

			if(data->radioEnabled == true)
				if(data == selectedRadio)
					unselectLastRadioElement();
		}
	}
}

void hListBox::elementSetSelected(int element, bool flag)
{
	if(flag == true)
		 selectElement(element);
	else unselectElement(element);
}

void hListBox::unselectLastRadioElement(void)
{
    if(selectedRadio != NULL) {
		// cout << "unselectLastRadioElement " << selectedRadio->name << endl;
        selectedRadio->selected = false;
        selectedRadio = NULL;
    }
}

//--------------------------------------------------------------

void hListBox::selectItem(int item)					{ selectElement(item); }
void hListBox::unselectItem(int item)				{ unselectElement(item); }
void hListBox::itemSetSelected(int item, bool flag) { elementSetSelected(item,flag); }
void hListBox::unselectLastRadioItem(void)			{ unselectLastRadioElement(); }

//--------------------------------------------------------------

void hListBox::clearLabels(void)
{
    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->label.clear();
}


void hListBox::setElementLabel(int element, string s)
{
	if(element > 0)
		if(element <= data_buffer.size())
			data_buffer[element-1]->label = s;
}

void hListBox::setRadioEnabled(bool radioFlag)
{
    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->radioEnabled = radioFlag;
}


//--------------------------------------------------------------

void hListBox::setElementRadioEnabled(int element, bool radioFlag)
{
	if(element > 0)
		if(element <= data_buffer.size()) {
			data_buffer[element-1]->radioEnabled = radioFlag;
		}
}

void hListBox::setAllElementsDisabled(bool disableFlag)
{
    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->disabled = disableFlag;
}


//--------------------------------------------------------------

void hListBox::setElementDisabled(int element, bool disableFlag)
{
	if(element > 0)
		if(element <= data_buffer.size()) {
			data_buffer[element-1]->disabled = disableFlag;
		}
}

//--------------------------------------------------------------

void hListBox::setBackgroundColor(int color)
{
	defBackgroundColor = color;
}

void hListBox::setSelectColor(int color)
{
	defSelectColor = color;
}

void hListBox::setElementSelectColor(int element, int color)
{
	if(element > 0)
		if(element <= data_buffer.size()) {
			data_buffer[element-1]->selectColor = color;
		}
}

//--------------------------------------------------------------

void hListBox::displayIndexes(bool dispFlag)
{
    indexDisplayFlag = dispFlag;
}

void hListBox::displayAllIndexes(bool dispFlag)
{
    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->indexDisplayFlag = dispFlag;
}

void hListBox::displayElementIndex(int element, bool dispFlag)
{
	if(element > 0)
		if(element <= data_buffer.size()) {
			data_buffer[element-1]->indexDisplayFlag = dispFlag;
		}
}

//--------------------------------------------------------------

void hListBox::setIndexShift(int shift1, int shift10, int shift100)
{
    indexShift1   = shift1;
    indexShift10  = shift10;
    indexShift100 = shift100;
}

void hListBox::setElementIndexShift(int element, int shift1, int shift10, int shift100)
{
	if(element > 0)
		if(element <= data_buffer.size()) {
			data_buffer[element-1]->indexShift1   = shift1;
			data_buffer[element-1]->indexShift10  = shift10;
			data_buffer[element-1]->indexShift100 = shift100;
		}
}

void hListBox::sendWhenReleased(bool flag)
{
    sendWhenReleasedFlag = flag;
}

//--------------------------------------------------------------

void hListBox::setStartIndex(int index)
// Normally, the indexes of the items start with #1
// Here we can modify that.
// Warning : It is necessary to do this before adding items and data

// TEST : try to do that before and after
// WORKS, can we do the same for the others ?
{
    startIndex = index;

    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->index = i + startIndex;
}

//--------------------------------------------------------------

void hListBox::setLinkedLabel(hLabel * label)
{
    int size = widgets.size();
    for(int i = 0; i < size; ++i) {
        hListItem * item = dynamic_cast<hListItem *>(widgets[i]);
        if(item != NULL)
            item->setLinkedLabel(label);
//          else cout << "hListBox::setLinkedLabel - dynamic_cast failed with " << widgets[i]->getTypeName()
//                    << " at [" << i << "]" << endl;
    }
}

void hListBox::setLinkedNumberBox(hNumberBox * numberBoxWidget)
{
    int size = widgets.size();
    for(int i = 0; i < size; ++i) {
        hListItem * item = dynamic_cast<hListItem *>(widgets[i]);
        if(item != NULL)
            item->setLinkedNumberBox(numberBoxWidget);
//          else cout << "hListBox::setLinkedNumberBox - dynamic_cast failed with " << widgets[i]->getTypeName()
//                    << " at [" << i << "]" << endl;
    }
}

//--------------------------------------------------------------

void hListBox::setMessage(string s)
{
    int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->message = s;
}

//--------------------------------------------------------
//							Helper methods:
//							Should not be called directly
//--------------------------------------------------------------

void hListBox::addScrollBar(void)
{
    if(parentPanel == NULL) return;

	if(scrollBar == NULL) {
        hGui * gui = hGui::getInstance();
        // Add the scrollBar widget:
	    scrollBar = new hScrollBar("", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, (y+gui->scrollButtonHeight)-1,
								   gui->scrollBarSize, (h - (gui->scrollButtonHeight*2)+1) );
	    scrollBar->setLinkedListBox(this);

        // Add the dec button widget (up):
        decButton = new hScrollButton("", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, y, 0, "");
        decButton->setDirection(false);
	    decButton->setLinkedListBox(this);

        // Add the inc button widget (down):
        incButton = new hScrollButton("", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, ((y + h) - gui->scrollButtonHeight)-1, 0, "");
        incButton->setHeight(gui->scrollButtonHeight+1);
        incButton->setDirection(true);
	    incButton->setLinkedListBox(this);
    }
}

//--------------------------------------------------------------

void hListBox::scrollItems(int startItem)
{
    int numItems = widgets.size();
    int numData  = data_buffer.size();
    if(numItems == numData) return; // nothing to do (there are at least the same number of data  that items)

    if((startItem >= 0) && (startItem <= (numData - numItems))) {
        // Move the data pointers to show the new data to the widgets:
        for(int i = 0; i < numItems; ++i) {
            hWidget  * widget  = widgets[i];
            hGuiData * dataPtr = data_buffer[i+startItem];
            widget->setData(dataPtr);
        }

        startLine = startItem; // We need to remember this
    }
}

int hListBox::getScrollPosition(void)
{
    return startLine;
}

void hListBox::setScrollBarPosition(int start_item)
{
    int numItems = getNumWidgets();
    int numData  = getNumData();
    if(numData == numItems) return; // nothing to scroll

    scrollBar->setPosition(start_item);
}

//--------------------------------------------------------------

void hListBox::saveSettings(ofxXmlSettings * xml)
{
	if(data->name.size() > 0) {
		int tag = xml->addTag(data->type);
		xml->pushTag(data->type, tag);

		xml->addValue("name", data->name);

		if(selectedRadio != NULL)
			xml->addValue("selection", selectedRadio->offset+1);

		xml->popTag();
	}
}

//--------------------------------------------------------------

