
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

#include "hLabel.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hLabel::hLabel(std::string name, hPanel * parent, int dispMode, int xx, int yy, string s)
	: hWidget(name, parent, dispMode, xx, yy, 100, hGui::getInstance()->buttonHeight)
{
	data->type = "label";
    hGui * gui = hGui::getInstance();

	textWidth  = gui->font->stringWidth(s);
    w = textWidth; h = gui->textHeight+5;

	data->label = s;
	fixedMode = false;
}

void hLabel::draw(void)
{
    hGui * gui = hGui::getInstance();

	if(data->label.size() > 0) {
		hSetHexColor(gui->textColor);
        if(fixedMode == false)
             hDrawString(gui->font,  data->label, x+1, y+gui->textHeight);
        else hDrawString(gui->ffont, data->label, x+1, y+gui->ftextHeight);

		if(data->selected) {
			hSetHexColor(gui->labelSelColor);
			hFrameRect(x, y, w, h);
		}
    }
}

//--------------------------------------------------------------

void hLabel::setLabel(string s)
{
	data->label = s;
}

std::string hLabel::getLabel(void)
{
    return data->label;
}

void hLabel::setFixedMode(bool fixed)
{
    hGui * gui = hGui::getInstance();

    fixedMode = fixed;

    if(fixed == false) {
        textWidth  = gui->font->stringWidth(data->label);
        w = textWidth; h = gui->textHeight+5;
    }
    else {
        textWidth  = gui->ffont->stringWidth(data->label);
        w = textWidth; h = gui->ftextHeight+5;
    }
}

void hLabel::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void hLabel::setMessage(string s)
{
	data->message = s;
}

void hLabel::bang(void)
{
	if(data->label.size() > 0)
		if(data->message.size() > 0) {
            hEvents::getInstance()->sendEvent(data->message, data->label, data->index);
		}
}

//--------------------------------------------------------------

void hLabel::mousePressed(int xx, int yy, int btn)
{
	if(data->selectable) {
		data->selected = !data->selected;
		bang();
	}
}

//--------------------------------------------------------------
