
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

#include "hAlert.h"
#include "hAlertLabel.h"
#include "hGui.h"
#include "ofMain.h"

//--------------------------------------------------------------

hAlert::hAlert(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hDialog(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "alert";
    hGui * gui = hGui::getInstance();
	dialogColor = gui->alertColor;

    addTools(50, 1, "Yes", "No");
    alertLabel = new hAlertLabel("", this, HGUI_ABSOLUTE_POSITION, x, y, "");
}

//--------------------------------------------------------------

void hAlert::clear(void)
{
    alertLabel->setLabel("");
}

//--------------------------------------------------------------

void hAlert::display(std::string str)
{
    hGui * gui = hGui::getInstance();

    if(! isOpen()) {
        clear(); open();
    }

    int y0 = y - gui->checkBoxSize;
    int centerX = x + (w/2);
    int centerY = y0 + (h/2);
    int strWidth  = gui->afont->stringWidth(str);
    int strHeight = gui->afont->stringHeight(str);

    int x1 = centerX - (strWidth/2);
    int y1 = centerY - (strHeight/2);

    alertLabel->moveTo(x1, y1);
    alertLabel->setLabel(str);
}

//--------------------------------------------------------------

int hAlert::waitAnswer(void)
{
    while(result == 0) {
        ofSleepMillis(100);
    }
	
    return result;
}

//--------------------------------------------------------------
