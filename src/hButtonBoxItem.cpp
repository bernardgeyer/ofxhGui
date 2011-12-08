
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

#include "hButtonBoxItem.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hButtonBoxItem::hButtonBoxItem(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hListItem(name, parent, dispMode, xx, yy, width, s)
{
	data->type = "button_box_item";
    lineNum = 0; //lineNum is the line# in the parent buttonBox
    altLineCols = false; // if true, draw fillColor or fillColor2 depending on odd or even line
}

//--------------------------------------------------------------

void hButtonBoxItem::draw(void)
// Small changes to hListItem::draw(void)
{
    hGui * gui = hGui::getInstance();

    if(!data->selected) {
        if(altLineCols == false)
            hSetHexColor(gui->fillColor);
        else {
            if(lineNum % 2)
                 hSetHexColor(gui->altFillColor);
            else hSetHexColor(gui->fillColor);
        }

		hPaintRect(x, y, w, h);
		hSetHexColor(gui->textColor2);

    }
	else {
        if(data->selectColor != -1)
             hSetHexColor(data->selectColor);
        else hSetHexColor(gui->itemSelColor);

		hPaintRect(x, y, w, h);
	}

    if(data->disabled == false)
        hSetHexColor(gui->textColor);
    else hSetHexColor(gui->disableColor);

    string displayStr;
    if(data->indexDisplayFlag == true) {
            displayStr += ofToString(data->index) + " ";

        if(data->label.size() > 0)
            displayStr += data->label;

        if(displayStr.size() > 0) {
            if(data->index >= 100) {
				hDrawString(gui->font, displayStr, x+data->indexShift100+3, y+gui->textHeight+2);
            }
            else if(data->index >= 10){
				hDrawString(gui->font, displayStr, x+data->indexShift10+3,  y+gui->textHeight+2);
            }
            else {
				hDrawString(gui->font, displayStr, x+data->indexShift1+3,   y+gui->textHeight+2);
            }
        }
    } // <- if(indexDisplayFlag == true)
    else {
        if(data->label.size() > 0)
            hDrawString(gui->font, data->label, x+3,   y+gui->textHeight+2);
    }

    hWidget::draw();
}

//--------------------------------------------------------------
