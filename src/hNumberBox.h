
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

#ifndef _HNUMBERBOX
#define _HNUMBERBOX

#include "hTextBox.h"

//--------------------------------------------------------

class hSlider;
class hListBox;

class hNumberBox: public hTextBox{
public:
    hNumberBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);

    void setRange(double mmin, double mmax, int xprecision=0);
	// Set the range of values that can take the numberbox
	// precision: how many decimal digits to display

	void setValue(double val);
	// Set a new value to the numberbox
	
	void setValue(double val, bool sliderLinkFlag, bool listBoxLinkFlag);
	// !!! Only for internal use of the gui library
	// Set a new value to the numberbox
	// if sliderLinkFlag == true, updates also the linked slider (if used)
	// if listBoxLinkFlag == true, updates also the linked listBox (if used)

	void addValue(double val);
	// Add a value to the actual value

	void addValue(double val, bool sliderLinkFlag, bool listBoxLinkFlag);
	// !!! Only for internal use of the gui library
	// Add a value to the actual value

	void setLinkedSlider(hSlider * slider);
	// Link this object to a slider object: when this object is updated, the slider will be too

	void setLinkedListBox(hListBox * listBox);
	// Link this object to a list box: when this object is updated, the list box item corresponding to the value wil be selected
	// Works also with hButtonBox

	//	void setIndex(int index); // defined in "hTextBox.h"
	// Set the index used to identify the widget
	
	// void setMessage(std::string s); // defined in "hTextBox.h"
	// Set the message that will be send when the widget state change

	void bang(void);
	// Send the message

	//--------------------------------------------------------
	
	// Methods called by event listeners:

    void draw();
	void keyPressed(int key);

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void saveSettings(ofxXmlSettings * xml);
	// Save the state of the widget to the open xml file
	
	//--------------------------------------------------------

protected:
	double min, max;
	int precision;

    hSlider * linkedSlider;
    hListBox * linkedListBox;
};

//--------------------------------------------------------
#endif // _HNUMBERBOX
