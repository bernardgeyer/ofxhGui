
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

#ifndef _H2DSLIDER
#define _H2DSLIDER

#include "hWidget.h"

//--------------------------------------------------------

class h2DSlider: public hWidget{
public:
    h2DSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size);

	void setRange(double mmin, double mmax, int xprecision=0);
	// Set the range of values that can take the 2DSlider
	// precision: this parameter is actually ignored

	void setXY(double xVal, double yVal);
	// Set the 2 values (x and y) of the 2DSlider
	
	void setIndex(int index);
	// The index of a 2DSlider can be used as an additional  parameter
	// Usefull when we have a few 2DSliders that do similar things
	
	void setMessage(std::string s);
	// Set the message that will be send when the widget state change
	
	void bang(void);
	// Send the message
		
	//--------------------------------------------------------
	
	// Methods called by event listeners:

    void draw(void);
	
    void mousePressed(int xx, int yy, int btn);
    void mouseDragged(int xx, int yy, int btn);

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void saveSettings(ofxXmlSettings * xml);
	// Save the state of the widget to the open xml file

	//--------------------------------------------------------
	
protected:
	int xPosition, yPosition;
	double min, max;
	int precision;
};

//--------------------------------------------------------
#endif // _H2DSLIDER
