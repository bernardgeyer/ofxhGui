
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

#ifndef _HSLIDERBOX
#define _HSLIDERBOX

#include "hPanel.h"

//-----------------------------------------------------------------------

// A SliderBox is a group of sliders with labels displayed on top of it


class hSliderBox: public hPanel{
public:
    hSliderBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	// 'width' is the width of the sliders, height is automatically calculated

	void addSliders(int numSliders);
	
	void setBackgroundColor(int color);
	// Set the same backgroud color to all sliders
	// Warning : It is necessary to do this AFTER adding items

	void setRange(double mmin, double mmax, int xprecision);
	// Set the same range to all sliders of the slider box

	void setValue(double val, bool labelLinkFlag);
	// Set the same value to all sliders of the slider box
	// if labelLinkFlag == true, updates also the linked label or number box

	void setSliderValue(int slider, double val, bool labelLinkFlag);
	// 'slider' is the slider number to modify (starting with 1)
	// if labelLinkFlag == true, updates also the linked label or number box

	void setStartIndex(int index);
	// Normally, the indexes of the items start with #1
	// Here we can modify that.
	// Warning : It is necessary to do this BEFORE adding items
	
	void setMessage(std::string s);
	// Set the same message to all items of the slider box

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void saveSettings(ofxXmlSettings * xml);
	// Save the state of the widget to the open xml file
	
protected:
    int startIndex;
};

//--------------------------------------------------------
#endif // _HSLIDERBOX
