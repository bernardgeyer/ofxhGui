
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

#include "hTScrollBar.h"
#include "hScrollButton.h"
#include "hTextArea.h"
#include "hGui.h"
#include "hEvents.h"

hTScrollBar::hTScrollBar(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hWidget(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "text_scroll_bar";
    hGui * gui = hGui::getInstance();
    position = (gui->scrollHandleHeight/2) + 2;
	startItem = 0;

    linkedTextArea = NULL;
}

//--------------------------------------------------------------

void hTScrollBar::setLinkedTextArea(hTextArea * textarea)
{
    linkedTextArea = textarea;
}

//--------------------------------------------------------------

void hTScrollBar::setPosition(int start_item)
{
    if(linkedTextArea == NULL) return;

    hGui * gui = hGui::getInstance();
    startItem = start_item;

    int hh  = gui->scrollHandleHeight;
    int hh2 = (hh/2) + 2;

    if(startItem < 1) {
        position = hh2;
    }
    else {
        int numItems = linkedTextArea->maxLines;
        int numData  = linkedTextArea->lines.size();

        int maxWidth = (h+1) - hh;

        position = (startItem * maxWidth) / (numData - numItems);
    }
    // cout << "position  = " << position << endl;
}

// --------------------------------------------------------------

void hTScrollBar::draw(void)
// WARNING: draw it only if usable
{
    if(linkedTextArea == NULL) return;

    int numItems = linkedTextArea->maxLines;
    int numData  = linkedTextArea->lines.size();

    if((numData - numItems) > 0) {
        hGui * gui = hGui::getInstance();

        int hh  = gui->scrollHandleHeight;
        int yy  = (y + position) - (hh/2);
/*
#if defined( __WIN32__ ) || defined( _WIN32 )
        hh-=1;
#endif
*/
        hSetHexColor(gui->fillColor);
        hPaintRect(x+1, y, w-2, h);

        hSetHexColor(gui->scrollHandleColor);
        hPaintRect(x+1, yy, w-2, hh);

        hSetHexColor(gui->borderColor);
        hFrameRect(x, y, w, h);
        hFrameRect(x+2, yy, w-4, hh);

        // Enable the drawing of the other small widgets
        linkedTextArea->incButton->setEnabled(true);
        linkedTextArea->decButton->setEnabled(true);
    }// (numData - numItems) > 0)
    else {
        // Disable the drawing of the other small widgets
        linkedTextArea->incButton->setEnabled(false);
        linkedTextArea->decButton->setEnabled(false);
    }
}

//--------------------------------------------------------------

void hTScrollBar::mousePressed(int xx, int yy, int btn)
{
	mouseDragged(xx, yy, btn); // same routine...
}

void hTScrollBar::mouseDragged(int xx, int yy, int btn)
{
    hGui * gui = hGui::getInstance();

    if(linkedTextArea != NULL) {
        // Calculate sizes:
        int numItems = linkedTextArea->maxLines;
        int numData  = linkedTextArea->lines.size();

        // cout << "numItems = " << numItems << " ";
        // cout << "numData = " << numData << endl;

        if(numData > numItems) {
            // Calculate position:
            int hh  = gui->scrollHandleHeight;
            int hh2 = (hh/2) + 2;
            int maxWidth = (h+1) - hh;

            position = yy - y;
            if(position < hh2) position = hh2;
            else if(position > maxWidth) position = maxWidth;

            // Calculate selection:
            if(position > hh2) // new (necessary when many lines)
                 startItem = (position * (numData - numItems)) / maxWidth;
            else startItem = 0; // new
            // cout << "startItem = " << startItem << endl;
            linkedTextArea->startLine = startItem;
       }
   }
}

//--------------------------------------------------------------
