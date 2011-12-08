
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

#ifndef _HSLIDER
#define _HSLIDER

#include "hWidget.h"
#include "hTable.h"

//--------------------------------------------------------

class hLabel;
class hNumberBox;

class hSlider: public hWidget{
public:
    hSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size);

	void setRange(double mmin, double mmax, int xprecision=0);
	// Set the range of values that can take the slider
	// precision: used for the linked object: how many decimal digits to display

	void setValue(double val);
	// Set a new value to the slider

	void setTable(hTable *_table);
	// If the slider uses a table:
	// When the slider is moved by the user
	// the values of the table are used instead of the values [min .. max]
	// and the slider's linked objects receive this value too
	// Warning : the values of the table have to be entered in ascending order
	
	void setLinkedLabel(hLabel * labelWidget, bool owningFlag);
	// Link this object to a label object: when this object is updated, the label will be too
	// owningFlag == true means that the label will be displayed and move with the slider

	void setLinkedNumberBox(hNumberBox * numberBoxWidget);
	// Link this object to a numberBox object: when this object is updated, the numberBox will be too

	void setIndex(int index);
	// The index of a slider can be used as an additional  parameter
	// Usefull when we have a few sliders that do similar things

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change
	
	void bang(void);
	// Send the message
	
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

private:
	void setLinkedValues(void);
	// Helper method: send 'data->value' to the linked object

protected:
	int position;
	double min, max;
	int precision;
	hTable * table;

	bool owningLabel;
    hLabel * linkedLabel;
    hNumberBox * linkedNumberBox;
};

//--------------------------------------------------------
#endif // _HSLIDER
