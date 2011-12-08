
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

#include "hNumberBox.h"
#include "hTextBox.h"
#include "hLabel.h"
#include "hSlider.h"
#include "hListBox.h"
#include "hGui.h"
#include "hEvents.h"

#include "ofxXmlSettings.h"

using namespace std;

//--------------------------------------------------------------

hNumberBox::hNumberBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hTextBox(name, parent, dispMode, xx, yy, width, s)
{
	data->type = "number_box";
    focusSendFlag = true;
    linkedSlider = NULL;
    linkedListBox = NULL;
}

//--------------------------------------------------------------

void hNumberBox::setRange(double mmin, double mmax, int xprecision)
{
	min = mmin;
	max = mmax;
	precision = xprecision;
}

void hNumberBox::setValue(double val)
{
    setValue(val, false, false);
}

void hNumberBox::setValue(double val, bool sliderLinkFlag, bool listBoxLinkFlag)
{
    if(val < min) val = min;
    else if(val > max) val = max;
	// cout << "val = " << val << endl;

	string val_label;

    if(precision < 1)
         val_label = ofToString((int)val);
    else val_label = ofToString(val, precision);
	setLabel(val_label);
    // cout << "valLabel = " << val_label << endl;
	
    // data->value = ofToFloat(data->label); // round the numerical value too
	data->value = atof(data->label.c_str()); // kind of ofToDouble

   // cout << "rounded label = " << data->label << endl;
   // cout << "rounded value = " << data->value << " precision = " << precision << endl;

	syncVar(); // synchronize the eventual used variable with the state of the widget

    if(linkedLabel != NULL)
        linkedLabel->setLabel(data->label);

    if(sliderLinkFlag == true) {
        if(linkedSlider != NULL)
            linkedSlider->setValue(data->value);
    }

    if(listBoxLinkFlag == true) {
        if(linkedListBox != NULL) {
            linkedListBox->selectElement(data->value);
            // cout << "linkedListBox->selectElement" << endl;
        }
     }
}

void hNumberBox::addValue(double val)
{
    setValue(data->value + val, false, false);
}

void hNumberBox::addValue(double val, bool sliderLinkFlag, bool listBoxLinkFlag)
{
    setValue(data->value + val, sliderLinkFlag, listBoxLinkFlag);
}

//--------------------------------------------------------------

void hNumberBox::setLinkedSlider(hSlider * slider)
{
	linkedSlider = slider;
}

void hNumberBox::setLinkedListBox(hListBox * listBox)
{
	linkedListBox = listBox;
}

//--------------------------------------------------------------

void hNumberBox::bang(void)
{
	if(varType != HGUI_NO_VAR) syncVar();

		if(data->message.size() > 0) {
        hEvents::getInstance()->sendEvent(data->message, data->value, data->index);
	}
}

//--------------------------------------------------------------

void hNumberBox::draw()
{
	if(varType != HGUI_NO_VAR) {
		hWidget * textObj = hPanel::getSelectedTextObj();
		if(textObj != this) { // number boxes can not sync with variable during editing
			syncWithVar();
			
			if(data->value < min) data->value = min;
			else if(data->value > max) data->value = max;
			
			if(precision < 1)
				setLabel(ofToString((int)data->value));
			else setLabel(ofToString(data->value, precision));
		}
	}
	
	hTextBox::draw();
}

void hNumberBox::keyPressed(int key)
{
    string s = data->label;

    if((key == 10) || (key == 13)) { // RETURN
		double value;
		// value = ofToFloat(data->label); // round the numerical value too
		value = atof(data->label.c_str()); // kind of ofToDouble

        setValue(value, true, true);
        bang();
    }
    else if((key == 8) || (key == 127)) { // BACKSPACE
        if(s.size() > 0)
            setLabel(s.substr(0, s.length() - 1));
    }
    else if((key >= 32) && (key <= 255)) { // NORMAL KEY
        s += (char)key;
        setLabel(s);
    }
}

//--------------------------------------------------------------

void hNumberBox::saveSettings(ofxXmlSettings * xml)
{
	if(data->name.size() > 0) {
		int tag = xml->addTag(data->type);
		xml->pushTag(data->type, tag);
		
		xml->addValue("name", data->name);
		
		double dValue = data->value;
		int nValue = (int) data->value; // truncated value
		
		if(dValue == (double)nValue) // same ? don't show decimal digits
			xml->addValue("value", nValue);
		else xml->addValue("value", dValue);
		
		xml->popTag();
	}
}

//--------------------------------------------------------------
