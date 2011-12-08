
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

#include "hSliderBox.h"
#include "hSlider.h"
#include "hLabel.h"
#include "hGui.h"

#include "ofxXmlSettings.h"
#include <typeinfo>

//--------------------------------------------------------------

hSliderBox::hSliderBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width)
	: hPanel(name, parent, dispMode, xx, yy, width, hGui::getInstance()->sliderSize, false)
{
    startIndex = 1;
}

void hSliderBox::addSliders(int numSliders)
{
	data->type = "slider_box";
    hGui * gui = hGui::getInstance();

	string name = data->name;
	string itemName;
	int index;
	
    int xx = 0, yy = 0;
	
    if(numSliders > 0) {
        for(int i = 0; i < numSliders; ++i) {
			index = widgets.size() + startIndex;
			itemName = name + "_" + ofToString(index);
			// cout << itemName << endl;
			
			hSlider * slider = new hSlider(itemName, this, HGUI_ABSOLUTE_POSITION, x+xx, y+yy, w);
			slider->getData()->index = index; // starts with 1
			// cout << "hSliderBox::addSliders " << widgets.size() << " " << id + i << endl;
			slider->setLinkedLabel(new hLabel("", NULL, HGUI_ABSOLUTE_POSITION, x, y, ""), true);
			slider->setValue(0);
            yy += gui->sliderBoxStep;
        }

		// Adapt the size of the panel to the size of all items inside
		int heigtOfWidgets = yy - (gui->sliderSize - 2);
		if(heigtOfWidgets > h) h = heigtOfWidgets;
    }
}

void hSliderBox::setBackgroundColor(int color)
{
	// cout << "hSliderBox::setBackgroundColor:" << color << endl;
	
    int size = widgets.size();
    for(int i = 0; i < size; ++i) {
        widgets[i]->setBackgroundColor(color);
		widgets[i]->setVisibleBackground(true);
	}
}

void hSliderBox::setRange(double mmin, double mmax, int xprecision)
{
	int size = widgets.size();
    for(int i = 0; i < size; ++i) {
        hSlider * slider = dynamic_cast<hSlider *>(widgets[i]);
        if(slider != NULL)
                slider->setRange(mmin, mmax, xprecision);
        else cout << "hSliderBox::setRange - dynamic_cast failed with " << typeid(widgets[i]).name() << endl;
    }
}

void hSliderBox::setValue(double val, bool labelLinkFlag)
{
	int size = widgets.size();
    for(int i = 0; i < size; ++i) {
        hSlider * slider = dynamic_cast<hSlider *>(widgets[i]);
        if(slider != NULL)
                slider->setValue(val);
        else cout << "hSliderBox::setValue - dynamic_cast failed with " << typeid(widgets[i]).name() << endl;
    }
}

void hSliderBox::setSliderValue(int slider, double val, bool labelLinkFlag)
{
	if(slider > 0)
		if(slider <= widgets.size()) {
            hSlider * sliderPtr = dynamic_cast<hSlider *>(widgets[slider-1]);
            if(sliderPtr != NULL)
                 sliderPtr->setValue(val);
            else cout << "hSliderBox::setSliderValue - dynamic_cast failed with " << typeid(widgets[slider-1]).name() << endl;

		}
}

//--------------------------------------------------------------

void hSliderBox::setStartIndex(int index)
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

void hSliderBox::setMessage(string s)
// Set the same message to all items of the list box
{
	int size = data_buffer.size();
    for(int i = 0; i < size; ++i)
        data_buffer[i]->message = s;
}

//--------------------------------------------------------------

void hSliderBox::saveSettings(ofxXmlSettings * xml)
{
	int size = data_buffer.size();
	
	for(int i = 0; i < size; ++i) {
		hGuiData * dataPtr = data_buffer[i];
		
		if(dataPtr->name.size() > 0) {
			int tag = xml->addTag(dataPtr->type);
			xml->pushTag(dataPtr->type, tag);
			
			xml->addValue("name", dataPtr->name);
			
			double dValue = dataPtr->value;
			int nValue = (int) dataPtr->value; // truncated value
			
			if(dValue == (double)nValue) // same ? don't show decimal digits
				xml->addValue("value", nValue);
			else xml->addValue("value", dValue);
			
			xml->popTag();
		}
	}
}

//--------------------------------------------------------------
