
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

#include "hListItem.h"
#include "hLabel.h"
#include "hNumberBox.h"
#include "hGui.h"
#include "hEvents.h"

hListItem::hListItem(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hWidget(name, parent, dispMode, xx, yy, width, hGui::getInstance()->buttonHeight)
{
	data->type = "list_item";
	data->label = s;
	data->selectable = true;
	data->radioEnabled = true; // By default
	sendWhenReleasedFlag = false;

    linkedLabel = NULL;
    linkedNumberBox = NULL;
}

//--------------------------------------------------------------

void hListItem::setLabel(string s)
{
	data->label = s;
}

void hListItem::displayIndex(bool dispFlag)
{
    data->indexDisplayFlag = dispFlag;
}

void hListItem::setIndexShift(int shift1, int shift10, int shift100)
{
    data->indexShift1   = shift1;
    data->indexShift10  = shift10;
    data->indexShift100 = shift100;
}

void hListItem::sendWhenReleased(bool flag)
{
    sendWhenReleasedFlag = flag;
}

//--------------------------------------------------------------

void hListItem::setLinkedLabel(hLabel * labelWidget)
{
    // cout << "hListItem::setLinkedLabel " << labelWidget->getData()->label << endl;
	linkedLabel  = labelWidget;
}

void hListItem::setLinkedNumberBox(hNumberBox * numberBoxWidget)
{
	linkedNumberBox = numberBoxWidget;
}

//--------------------------------------------------------------

void hListItem::setMessage(string s)
{
	data->message = s;
}

void hListItem::bang(void)
{
    if(data->message.size() > 0) {
        hEvents::getInstance()->sendEvent(data->message, data->label, data->index, data->selected);
    }
}

//--------------------------------------------------------------

void hListItem::draw(void)
{
    hGui * gui = hGui::getInstance();
	
    if(!data->selected) {
        hSetHexColor(gui->fillColor);
		hPaintRect(x, y, w, h);
		hSetHexColor(gui->textColor);
		
    }
	else {
        if(data->selectColor != -1)
			hSetHexColor(data->selectColor);
        else hSetHexColor(gui->itemSelColor);
		
		hPaintRect(x, y, w, h);
		hSetHexColor(gui->itemSelTextColor);
	}
	
    if(data->disabled == true)
		hSetHexColor(gui->disableColor);
	
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

void hListItem::mousePressed(int xx, int yy, int btn)
{
	// cout << "hListItem::mousePressed: " << getData()->name << endl;

    if(data->disabled == true) return;

    toggleSelection();

    // if(data->selected == true) {
        // cout << "selected!" << endl;
        if(linkedLabel != NULL) {
             //cout << "linkedLabel = " << linkedLabel->getData()->name << endl;
            if(data->label.size() > 0)
                linkedLabel->setLabel(data->label);
        }
        //else cout << "linkedLabel = NULL" << endl;

        if(linkedNumberBox != NULL) {
            // cout << "linkedNumberBox = " << linkedNumberBox->getData()->name << endl;
            if(parentPanel != NULL) {
                int value = data->index;
				// cout << "value = " << value << endl;
                linkedNumberBox->setValue(value, true, false); // <- false: we don't want to send to ourselves
            }
        }
        // else cout << "linkedNumberBox = NULL" << endl;

        if(sendWhenReleasedFlag == false)
            bang();
	// }
}

//--------------------------------------------------------------

void hListItem::mouseReleased(int xx, int yy, int btn)
{
    // cout << "hListItem::mouseReleased" << endl;
    if(sendWhenReleasedFlag == true)
        bang();
}

//--------------------------------------------------------------
