
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

#include "hTabBox.h"
#include "hTabBoxItem.h"
#include "hGui.h"

#include "ofxXmlSettings.h"
#include <typeinfo>

//--------------------------------------------------------------

int ofGetWidth(); int ofGetHeight();

hTabBox::hTabBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width)
	: hListBox(name, parent, dispMode, xx, yy, width)
{
	data->type = "tab_box";
    hGui * gui = hGui::getInstance();

    mainTabSelectionPanel =
    new hPanel("", this, HGUI_ABSOLUTE_POSITION, x, y+gui->tabHeight+1, w, (ofGetHeight() - gui->tabHeight)-3, false);
	mainTabSelectionPanel->getData()->name = name + "_panel";

    curTabSelectionPanel = NULL;

    setSelectColor(gui->tabBoxSelColor);

	x += 2; // little correction
}

//--------------------------------------------------------------

void hTabBox::addItems(int numItems)
{
	string name = data->name;
	string itemName;
	int offset, index;

    int xx = 0, yy = 0;
    hTabBoxItem *item = NULL;

    if(numItems > 0) {
        int itemWidth = w / numItems;
        for(int i = 0; i < numItems; ++i) {
			offset = widgets.size();
			index  = (offset + startIndex) - 1; // -1: don't count the linked panel
			itemName = name + ofToString(index);
			// cout << itemName << endl;

            if(i == 0)
                 item = new hTabBoxItem(itemName, this, HGUI_ABSOLUTE_POSITION, x+xx,   y+yy, itemWidth,   "");
			else item = new hTabBoxItem(itemName, this, HGUI_ABSOLUTE_POSITION, x+xx-1, y+yy, itemWidth+1, "");

			item->getData()->index  = index;
			item->getData()->offset = offset;
 			item->setSelectColor(defSelectColor);

			item->displayIndex(indexDisplayFlag);
            item->setIndexShift(indexShift1, indexShift10, indexShift100);

            xx += itemWidth;
        }

        // Add rounding error to last tab:
        if(item != NULL) {
            int remainingWidth = w - (itemWidth * numItems);
            item->incWidth(remainingWidth);
        }
    }
}

//--------------------------------------------------------------

void hTabBox::setItemLabel(int item, string s)
{
	if(item > 0) // item #0 is used by the selection panel
		if(item < widgets.size()) {
            hTabBoxItem * itemPtr = dynamic_cast<hTabBoxItem *>(widgets[item]);
            if(itemPtr != NULL)
                itemPtr->setLabel(s);
            else cout << "hTabBox::setItemLabel - dynamic_cast failed with " << typeid(widgets[item]).name() << endl;
		}
}

void hTabBox::setItemPanel(int item, hPanel * panel)
{
	if(item > 0) // item #0 is used by the selection panel
		if(item < widgets.size()) {
            hTabBoxItem * itemPtr = dynamic_cast<hTabBoxItem *>(widgets[item]);
            if(itemPtr != NULL) {
                itemPtr->setLinkedPanel(panel);
            }
            else cout << "hTabBox::setItemPanel - dynamic_cast failed with " << typeid(widgets[item]).name() << endl;
		}
}

//--------------------------------------------------------------

void hTabBox::selectItem(int item)
// Uses only items, not just data elements (not scrollable)
{
	if(item > 0)
		if(item <= widgets.size()) {
            hTabBoxItem * itemPtr = dynamic_cast<hTabBoxItem *>(widgets[item]);
            if(itemPtr != NULL) {
                hPanel * linkedPanel = itemPtr->getLinkedPanel();
                if(linkedPanel != NULL)
                    storeItemPanel(linkedPanel);

                itemPtr->setSelected(true);

                hGuiData * dataPtr = itemPtr->getData();
                if(dataPtr->radioEnabled) {
                    if(selectedRadio != NULL) {
                        selectedRadio->selected = false;
                    } // <- if(selectedRadio != NULL)
                    selectedRadio = dataPtr;
                    selectedRadio->selected = true; // NEW
                } // <- radioEnabled
            }
            else cout << "hTabBox::selectItemPanel - dynamic_cast failed with " << typeid(widgets[item]).name() << endl;
        }
}

//--------------------------------------------------------------

void hTabBox::mousePressed(int xx, int yy, int btn)
// Some differences with hPanel's mousePressed
// (added functionality)
{
    // cout << "hTabBox::mousePressed" << endl;
    switch(btn) {
        case 0:
        hWidget *widget = findWidget(xx, yy);
        if(widget == NULL) return;

        hTabBoxItem * itemPtr = dynamic_cast<hTabBoxItem *>(widget);
        if(itemPtr != NULL) {
            // cout << "it's a hTabBoxItem: " << itemPtr << endl;
            hPanel * linkedPanel = itemPtr->getLinkedPanel();
            if(linkedPanel != NULL) {
                storeItemPanel(linkedPanel);

            // Remove last radio selection and set the new one:
            hGuiData * dataPtr = widget->getData();
            if(dataPtr->radioEnabled) {
                if(selectedRadio != NULL) {
                    selectedRadio->selected = false;
                } // <- if(selectedRadio != NULL)
                selectedRadio = dataPtr;
                selectedRadio->selected = true; // NEW
            } // <- radioEnabled
        } // <- if(item->getLinkedPanel() != NULL)
    } // <- if(item != NULL)
    else {
        hPanel * panel = dynamic_cast<hPanel *>(widget);
        if(panel != NULL)
            widget->mousePressed(xx, yy, btn);
    }

    clickedWidget = widget; // will be null if no widget found (necessary for drag)
    break;
    }
}

//--------------------------------------------------------
//						Helper methods:
//						Should not be called directly
//--------------------------------------------------------

void hTabBox::storeItemPanel(hPanel * linkedPanel)
{
    if(parentPanel == NULL) { // It's the root tab box
        mainTabSelectionPanel->clearWidgets(); // remove content of tab selection panel (can only have one anyway)
        mainTabSelectionPanel->addWidgetPtr(linkedPanel); // add set the new content instead
    }
    else {
        if(curTabSelectionPanel != NULL) {
            int index = parentPanel->findWidgetIndex(curTabSelectionPanel);
            // cout << "findWidgetIndex = " << index << endl;
            if(index > -1) parentPanel->removeWidgetPtrAt(index);
        }
        parentPanel->addWidgetPtr(linkedPanel);
        curTabSelectionPanel = linkedPanel;
    }
}

//--------------------------------------------------------------
