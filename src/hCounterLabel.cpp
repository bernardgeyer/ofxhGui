
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

#include "hCounterLabel.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hCounterLabel::hCounterLabel(std::string name, hPanel * parent, int dispMode, int xx, int yy, string s)
	: hLabel(name, parent, dispMode, xx, yy, s)
{
	data->type = "counter_label";
	
	disp_d = false;
	disp_ms = false;
}

//--------------------------------------------------------------

void hCounterLabel::display_milliseconds(bool flag)
{
	disp_ms = flag;
}

void hCounterLabel::display_days(bool flag)
{
	disp_d = flag;
}

//--------------------------------------------------------------

void hCounterLabel::setTime(double time)
{
	long long lTime = time;
	
	string str;
	int d, h, min, sec, ms;

	if(disp_d) {
		d = (lTime / 86400000);
		if(d < 10) str += "0";
		str += ofToString(d);
		str += ":";
	}
	
	h = (lTime / 3600000) % 24;
	if(h < 10) str += "0";
	str += ofToString(h);
	str += ":";

	min = (lTime / 60000)   % 60;
	if(min < 10) str += "0";
	str += ofToString(min);
	str += ":";

	sec = (lTime /  1000)   % 60;
	if(sec < 10) str += "0";
	str += ofToString(sec);
	
	if(disp_ms) {
		ms =  lTime %  1000;
		str += ":";
		if(ms < 100) str += "0";
		if(ms < 10) str += "0";
		str += ofToString(ms);
	}
	
	setLabel(str);
}

//--------------------------------------------------------------

void hCounterLabel::draw(void)
{
    hGui * gui = hGui::getInstance();
	
	if(varType != HGUI_NO_VAR) {
		syncWithVar();
		setTime(data->value);
	}
	
	if(data->label.size() > 0) {
        hSetHexColor(gui->counterColor);
		hDrawString(gui->cfont, data->label, x, y+gui->ctextHeight);
	}
}


//--------------------------------------------------------------
