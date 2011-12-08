
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

#include "hCheckBox.h"
#include "hGui.h"
#include "hEvents.h"

#include "ofxXmlSettings.h"

//--------------------------------------------------------------

hCheckBox::hCheckBox(std::string name, hPanel * parent, int dispMode, int xx, int yy)
	: hWidget(name, parent, dispMode, xx, yy, hGui::getInstance()->checkBoxSize, hGui::getInstance()->checkBoxSize)
{
	data->type = "check_box";
	data->selectable = true;
}

//--------------------------------------------------------------

void hCheckBox::setLabelExtension(string s)
{
	x_extension = hGui::getInstance()->font->stringWidth(s);
}

void hCheckBox::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void hCheckBox::setMessage(string s)
{
	data->message = s;
}

void hCheckBox::setMessage2(std::string s)
{
    data->message2 = s;
}

void hCheckBox::bang(void)
{
	if(varType != HGUI_NO_VAR) syncVar();

	if(data->message.size() > 0) {
	    if((data->selected == true) || (data->message2.size() == 0))
             hEvents::getInstance()->sendEvent(data->message,  data->index, data->selected);
        else hEvents::getInstance()->sendEvent(data->message2, data->index, data->selected);
	}
}

//--------------------------------------------------------------

void hCheckBox::draw(void)
{
	if(varType != HGUI_NO_VAR)
		syncWithVar();
	
    hGui * gui = hGui::getInstance();
	
    ofFill();
    if(backgroundColor != -1)
		hSetHexColor(backgroundColor);
    else hSetHexColor(gui->fillColor);
    ofRect(x, y, w, h);
	
    if(data->selected) {
        if(data->selectColor != -1)
			hSetHexColor(data->selectColor);
        else hSetHexColor(gui->checkBoxColor);
		ofRect(x, y, w, h);
    }
	
    hWidget::draw();
}

//--------------------------------------------------------------

void hCheckBox::mousePressed(int xx, int yy, int btn)
{
    toggleSelection();
	bang();
}

//--------------------------------------------------------------

void hCheckBox::saveSettings(ofxXmlSettings * xml)
{
	if(data->name.size() > 0) {
		int tag = xml->addTag(data->type);
		xml->pushTag(data->type, tag);
		
		xml->addValue("name", data->name);
		
		if(data->selected)
			xml->addValue("selected", "true");
		else xml->addValue("selected", "false");
		
		xml->popTag();
	}
}

//--------------------------------------------------------------
