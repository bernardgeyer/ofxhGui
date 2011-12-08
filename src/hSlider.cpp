
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

#include "hSlider.h"
#include "hLabel.h"
#include "hNumberBox.h"
#include "hGui.h"
#include "hEvents.h"

#include "ofxXmlSettings.h"

//--------------------------------------------------------------

hSlider::hSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size)
	: hWidget(name, parent, dispMode, xx, yy, size, hGui::getInstance()->sliderSize)
{
	data->type = "slider";
	position     = 0;
	min = 0; max = 100;
	data->value = 0.0;
	precision    = 2;
	owningLabel = false;

    table = NULL;

    linkedLabel = NULL;
    linkedNumberBox = NULL;
}

//--------------------------------------------------------------

void hSlider::setRange(double mmin, double mmax, int xprecision)
{
	min = mmin;
	max = mmax;
	precision = xprecision;
}

void hSlider::setValue(double val)
{
	double pRange = w - 2;

    if(table == NULL) {
        if(val < min) val = min;
        else if(val > max) val = max;

        data->value = val;

        double vRange = max - min;
        position = ((data->value - min) * pRange) / vRange;
    }
    else {
        double tMin = table->getMinValue();
        double tMax = table->getMaxValue();

        if(val < tMin) val = tMin;
        else if(val > tMax) val = tMax;

        data->value = val;

        double vRange = tMax - tMin;
        position = ((data->value - tMin) * pRange) / vRange;
    }

	syncVar(); // synchronize the eventual used variable with the state of the widget
	
    setLinkedValues();
}

//--------------------------------------------------------------

void hSlider::setTable(hTable * _table)
{
    if(_table != NULL) table = _table;
}

//--------------------------------------------------------------

void hSlider::setLinkedLabel(hLabel * labelWidget, bool owningFlag)
{
	linkedLabel = labelWidget;
	owningLabel = owningFlag;
}

void hSlider::setLinkedNumberBox(hNumberBox * numberBoxWidget)
{
	linkedNumberBox = numberBoxWidget;
}

//--------------------------------------------------------------

void hSlider::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void hSlider::setMessage(string s)
{
	data->message = s;
}

void hSlider::bang(void)
{
	if(varType != HGUI_NO_VAR) syncVar();

	if(data->message.size() > 0) {
        hEvents::getInstance()->sendEvent(data->message, data->value, data->index);
	}
}

//--------------------------------------------------------------

void hSlider::draw(void)
{
    hGui * gui = hGui::getInstance();
	
	if(varType != HGUI_NO_VAR) {
		syncWithVar();
		
        if(data->value < min) data->value = min;
        else if(data->value > max) data->value = max;
		
		double pRange = w - 2;
        double vRange = max - min;
        position = ((data->value - min) * pRange) / vRange;
	}
	
    hWidget::draw();
	
	if(data->selectColor != -1)
		hSetHexColor(data->selectColor);
	else hSetHexColor(gui->sliderColor);
	
	hPaintRect(x+1, y+1, position, h-2);
	
	hSetHexColor(hGui::getInstance()->borderColor);
	hLine (x+position+1, y+1, x+position+1, y+h);
	
    if(owningLabel == true) {
        if(linkedLabel != NULL)
            linkedLabel->draw();
	}
}

void hSlider::mousePressed(int xx, int yy, int btn)
{
	mouseDragged(xx, yy, btn); // same routine...
}

void hSlider::mouseDragged(int xx, int yy, int btn)
{
	position = xx - x;

	if(position < 0) position = 0;
	else if(position > (w-2)) position = w-2;

    double pRange = w - 2;
    double val = 0;

    if(table == NULL) {
        double vRange = max - min;
        val = min + ((position * vRange) / pRange);
        // cout << "vRange = " << vRange << ", ";
        // cout << "val = " << val << endl;
    }
    else {
        double tMin = table->getMinValue();
        double tMax = table->getMaxValue();
        double vRange = tMax - tMin;
        double submitedValue = tMin + ((position * vRange) / pRange);
        val = table->getNearestValue(submitedValue);
        // cout << "vRange = " << vRange << ", ";
        // cout << "submitedValue = " << submitedValue << ", ";
        // cout << "val = " << val << endl;
    }

	data->value = val;
    setLinkedValues();

	bang();
}

//--------------------------------------------------------------

void hSlider::saveSettings(ofxXmlSettings * xml)
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

void hSlider::setLinkedValues(void)
{
	if(linkedLabel != NULL) {
	    string s;
	    if(precision < 1)
             s = ofToString((int)data->value);
        else s = ofToString((double)data->value, precision);

        linkedLabel->setLabel(s);

        if(owningLabel == true) {
            linkedLabel->moveTo(
                (position + x) - 2,
                y - (hGui::getInstance()->sliderSize - 2));
        }
	}

    if(linkedNumberBox != NULL) {
        linkedNumberBox->setValue(data->value, false, true); // <- false: we don't want to send to ourselves
    }
}

//--------------------------------------------------------------
