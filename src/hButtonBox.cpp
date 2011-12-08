
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

#include "hButtonBox.h"
#include "hButtonBoxItem.h"
#include "hGui.h"

#include "ofxXmlSettings.h"

//--------------------------------------------------------------

hButtonBox::hButtonBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int item_width, int item_height)
                : hListBox(name, parent, dispMode, xx, yy, hGui::getInstance()->buttonHeight)
{
	data->type = "button_box";
    itemWidth  = item_width;
    itemHeight = item_height;

    xItems = 0;
    yItems = 0;

    altLineCols = false;
    // if true, draw fillColor or fillColor2 depending on odd or even line

    // Default index display parameters:
    indexDisplayFlag = false; // false by default
    indexShift1 = 12; indexShift10 = 6, indexShift100 = 0;
	
	x += 2; // Little correction
}

//--------------------------------------------------------------

void hButtonBox::addItems(int numXItems, int numYItems)
{
    if(numXItems < 1) return;
    if(numYItems < 1) return;

    xItems = numXItems;
    yItems = numYItems;

    hGui * gui = hGui::getInstance();

	string name = data->name;
	string itemName;
	int offset, index;
	
	int widthOfWidgets, heigthOfWidgets;
    int xx, yy;

    yy = 0;
    for(int j = 0; j < numYItems; ++j) {
        xx = 0;
        for(int i = 0; i < numXItems; ++i) {
			offset = widgets.size();
			index = offset + startIndex;
			itemName = name + "_" + ofToString(index);
			// cout << itemName << endl;
			
			hButtonBoxItem *item = new hButtonBoxItem(itemName, this, HGUI_ABSOLUTE_POSITION, x+xx, y+yy, w, "");

            item->setWidth(itemWidth);
            item->setHeight(itemHeight);

			item->getData()->index  = index;
			item->getData()->offset = offset;
			item->setSelectColor(defSelectColor);

            item->lineNum = j+1; // remember the line of the widget
            item->altLineCols = altLineCols; // set the line color mode of the widget

			item->displayIndex(indexDisplayFlag);
            item->setIndexShift(indexShift1, indexShift10, indexShift100);
            item->sendWhenReleased(sendWhenReleasedFlag);

            xx += itemWidth - 1;
            widthOfWidgets = xx+1;
            if(widthOfWidgets > w) w = widthOfWidgets;
        }

        yy += itemHeight - 1;
		heigthOfWidgets = yy+1;
		if(heigthOfWidgets > h) h = heigthOfWidgets;
    }
}

int hButtonBox::getXItems(void)
{
    return xItems;
}

int hButtonBox::getYItems(void)
{
    return yItems;
}

void hButtonBox::alternateLineColors(bool flag)
{
    altLineCols = flag;
}

//--------------------------------------------------------------

void hButtonBox::saveSettings(ofxXmlSettings * xml)
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
