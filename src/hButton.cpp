
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

#include "hButton.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hButton::hButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hWidget(name, parent, dispMode, xx, yy, width, hGui::getInstance()->buttonHeight)
{
	data->type = "button";
	data->label = s;

	labelXoffset = 0;
	labelYoffset = 0;

	pressed = false;
	sendWhenReleasedFlag = false;
}

//--------------------------------------------------------------

void hButton::setDisabled(bool disableFlag)
{
	data->disabled = disableFlag;
}

void hButton::setLabel(string s)
{
	data->label = s;
}

void hButton::setLabelOffset(int xOffset, int yOffset)
{
	labelXoffset = xOffset;
	labelYoffset = yOffset;
}

void hButton::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void hButton::setMessage(string s)
{
	data->message = s;
}

void hButton::sendWhenReleased(bool flag)
{
    sendWhenReleasedFlag = flag;
}

void hButton::bang(void)
// Send the message of the button
{
    if(data->message.size() > 0) {
		// cout << "hButton::sendMessage ";
		// cout << data->message << " " <<  data->index << endl;
        hEvents::getInstance()->sendEvent(data->message, data->index);
	}
}

//--------------------------------------------------------------

void hButton::draw(void)
{
	
    hGui * gui = hGui::getInstance();
	
    if(backgroundColor != -1)
        hSetHexColor(backgroundColor);
    else hSetHexColor(gui->fillColor);
	
    hPaintRect(x, y, w, h);
	hWidget::draw();

    if(!pressed) {
        if(data->label.size() > 0) {
            if(data->disabled == false)
				hSetHexColor(gui->textColor);
            else hSetHexColor(gui->disableColor);
			
			hDrawString(gui->font, data->label, x+labelXoffset+3, y+gui->textHeight+labelYoffset+2);
        }
    }
    else {
        hSetHexColor(gui->buttonShadowColor);
        hLine (x+1,     y+2, x+w,   y+2);
        hLine (x+1,     y+3, x+w,   y+3);
		
        hLine (x+1,     y+1, x+1,     y+h-1);
        hLine (x+2,     y+1, x+2,     y+h-1);
		
        if (data->label.size() > 0) {
            hSetHexColor(gui->textColor);
			
			hDrawString(gui->font, data->label, x+labelXoffset+3+2, y+gui->textHeight+labelYoffset+2+2);
        }
	}
}

void hButton::mousePressed(int xx, int yy, int btn)
{
    // cout << "hButton::mousePressed" << endl;

    if(data->disabled == true) return;

    pressed = true;

    if(sendWhenReleasedFlag == false)
        bang();
}

void hButton::mouseReleased(int xx, int yy, int btn)
{
    // cout << "hButton::mouseReleased" << endl;
    pressed = false;

    if(sendWhenReleasedFlag == true)
        bang();
}

//--------------------------------------------------------------
