
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

#include "hScrollButton.h"
#include "hScrollBar.h"
#include "hTScrollBar.h"
#include "hListBox.h"
#include "hTextArea.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hScrollButton::hScrollButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hButton(name, parent, dispMode, xx, yy, width, s)
// An scroll button is used to increment or decrement the start line
// of a hListBox or a hTextArea
// The parameters width and s are ignored
{
	data->type = "scroll_button";
    hGui * gui = hGui::getInstance();
    w = gui->checkBoxSize;
    h = gui->scrollButtonHeight;

/* NO MORE NECESSARY!
#if defined( __WIN32__ ) || defined( _WIN32 )
        h-=1;
#endif
*/
    enabled = false;
    direction = false;

    linkedListBox  = NULL;
    linkedTextArea = NULL;
}

void hScrollButton::draw(void)
{
    if(enabled) {
        hButton::draw();

        hGui * gui = hGui::getInstance();
        hSetHexColor(gui->scrollButtonColor);
        int x0, y0;

        if(direction == true) {
            // Draw lower triangle
            x0 = x + (gui->checkBoxSize/2);
            y0 = y + 10;

            if(pressed == true) { ++x0; ++y0; }
            for(int i = 0; i < 4; ++i) hLine(x0-i, y0-i, x0+i+1, y0-i);
        }
        else {
            // Draw uper triangle
            x0 = x + (gui->checkBoxSize/2);
            y0 = y+6;

            if(pressed == true) { ++x0; ++y0; }
            for(int i = 0; i < 4; ++i) hLine(x0-i, y0+i, x0+i+1, y0+i);
        }
    }
}

//--------------------------------------------------------------

void hScrollButton::setEnabled(bool flag)
// draw only if enabled
{
    enabled = flag;
}

void hScrollButton::setDirection(bool dir)
// false = up, true = down (used to draw the triangle)
{
    direction = dir;
}

//--------------------------------------------------------------

void hScrollButton::setLinkedListBox(hListBox * listBoxWidget)
// Link this object to a hListBox object
{
	linkedListBox = listBoxWidget;
}

void hScrollButton::setLinkedTextArea(hTextArea * textAreaWidget)
// Link this object to a hTextArea object
{
	linkedTextArea = textAreaWidget;
}

//--------------------------------------------------------------

void hScrollButton::mousePressed(int xx, int yy, int btn)
// Important: when an incButton in connected to a number box,
// the message of the numberbox will be sent too
{
    if(enabled == false) return;

    pressed = true;

	if(linkedListBox != NULL) {
        int numItems  = linkedListBox->getNumWidgets();
        int numData   = linkedListBox->getNumData();
        int startItem = linkedListBox->getScrollPosition();

	    if(direction == false ) {
	        if(startItem > 0) {
	            --startItem;
                linkedListBox->scrollItems(startItem);
                linkedListBox->scrollBar->setPosition(startItem);
	        }
	        // cout << "linkedListBox up" << endl;
	    }
	    else {
	        if(startItem < (numData - numItems)) {
	            ++startItem;
                linkedListBox->scrollItems(startItem);
                linkedListBox->scrollBar->setPosition(startItem);
	        }
	        // cout << "linkedListBox down" << endl;
	    }
	}

	if(linkedTextArea != NULL) {
        int numItems = linkedTextArea->maxLines;
        int numData  = linkedTextArea->lines.size();

	    if(direction == false ) {
	        if(linkedTextArea->startLine > 0) {
                --linkedTextArea->startLine;
                linkedTextArea->scrollBar->setPosition(linkedTextArea->startLine);
	        }
	        // cout << "linkedTextArea up: " << linkedTextArea->startLine << endl;
	    }
	    else {
	        if(linkedTextArea->startLine < (numData - numItems)) {
                ++linkedTextArea->startLine;
                linkedTextArea->scrollBar->setPosition(linkedTextArea->startLine);
	        }
	        // cout << "linkedTextArea down: " << linkedTextArea->startLine << endl;
	    }
	}
}

//--------------------------------------------------------------
