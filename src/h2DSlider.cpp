
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

#include "h2DSlider.h"
#include "hGui.h"
#include "hEvents.h"

#include "ofxXmlSettings.h"

//--------------------------------------------------------------

h2DSlider::h2DSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size)
	: hWidget(name, parent, dispMode, xx, yy, size, size)
{
	data->type = "slider2D";
	xPosition    = size/2;
	yPosition    = size/2;
	min = -1.0; max = 1.0;
	data->value  = 0.0;
	data->value2 = 0.0;
	precision    = 2;
}

//--------------------------------------------------------------

void h2DSlider::setRange(double mmin, double mmax, int xprecision)
{
	min = mmin;
	max = mmax;
	precision = xprecision;
}

void h2DSlider::setXY(double xVal, double yVal)
{
    if(xVal < min) xVal = min; else if(xVal > max) xVal = max; data->value = xVal;
    if(yVal < min) yVal = min; else if(yVal > max) yVal = max; data->value2 = yVal;

	double vRange = max - min;
	double xpRange = w - 2;
	double ypRange = h - 3; // h has normally to be the same dimension than w ... but ... ?

	xPosition = ((data->value - min) * xpRange) / vRange;
	yPosition = ((data->value2 - min) * ypRange) / vRange;
}

//--------------------------------------------------------------

void h2DSlider::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void h2DSlider::setMessage(string s)
{
	data->message = s;
}

void h2DSlider::bang(void)
{
	if(data->message.size() > 0) {
        hEvents::getInstance()->sendEvent(data->message, data->value, data->value2, data->index);
	}
}

//--------------------------------------------------------------

void h2DSlider::draw(void)
{
    hWidget::draw();
	
	hSetHexColor(hGui::getInstance()->twoDSliderColor);
	
	const int size = 8;
	int x1 = x+xPosition-size;
	int x2 = x+xPosition;
	int x3 = x+xPosition+size;
	
	int y1 = y+yPosition-size;
	int y2 = y+yPosition;
	int y3 = y+yPosition+size;
	
	hLine (x1+1, y2+2, x3+1, y2+2);
	hLine (x2+1, y1+2, x2+1, y3+2);
}

void h2DSlider::mousePressed(int xx, int yy, int btn)
{
	mouseDragged(xx, yy, btn); // same routine...
}

void h2DSlider::mouseDragged(int xx, int yy, int btn)
{
	xPosition = xx - x;
	yPosition = yy - y;

	if(xPosition < 0) xPosition = 0; else if(xPosition > (w-2)) xPosition = w-2;
	if(yPosition < 0) yPosition = 0; else if(yPosition > (w-3)) yPosition = w-3;

	double vRange = max - min;
	double xpRange = w - 2;
	double ypRange = h - 3; // h has normally to be the same dimension than w ... but ... ?

	data->value = min + ((xPosition * vRange) / xpRange);
	data->value2 = min + ((yPosition * vRange) / ypRange);


	bang();
}

//--------------------------------------------------------------

void h2DSlider::saveSettings(ofxXmlSettings * xml)
{
	if(data->name.size() > 0) {
		int tag = xml->addTag(data->type);
		xml->pushTag(data->type, tag);
		
		xml->addValue("name", data->name);
		
		double dValue; int nValue;
		
		// store x value
		dValue = data->value;
		nValue = (int) data->value; // truncated value
		
		if(dValue == (double)nValue) // same ? don't show decimal digits
			xml->addValue("x", nValue);
		else xml->addValue("x", dValue);
		
		// store y value
		dValue = data->value2;
		nValue = (int) data->value2; // truncated value
		
		if(dValue == (double)nValue) // same ? don't show decimal digits
			xml->addValue("y", nValue);
		else xml->addValue("y", dValue);
		
		xml->popTag();
	}
}

//--------------------------------------------------------------
