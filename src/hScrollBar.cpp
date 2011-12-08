
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

#include "hScrollBar.h"
#include "hScrollButton.h"
#include "hListBox.h"
#include "hGui.h"
#include "hEvents.h"

//------------------------------------------------------------------------------
// hScrollBar is not a widget to be used alone, it is merely created by hListBox
//------------------------------------------------------------------------------


hScrollBar::hScrollBar(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hWidget(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "scroll_bar";
    hGui * gui = hGui::getInstance();
    position = (gui->scrollHandleHeight/2) + 2;
	startItem = 0;

    linkedListBox = NULL;
}

// --------------------------------------------------------------

void hScrollBar::setLinkedListBox(hListBox * listbox)
{
    linkedListBox = listbox;
}

// --------------------------------------------------------------

void hScrollBar::setPosition(int start_item)
{
    if(linkedListBox == NULL) return;

    hGui * gui = hGui::getInstance();
    startItem = start_item;

    int hh  = gui->scrollHandleHeight;
    int hh2 = (hh/2) + 2;

    if(startItem < 1) {
        position = hh2;
    }
    else {
        int numItems  = linkedListBox->getNumWidgets();
        int numData   = linkedListBox->getNumData();

        int maxWidth = (h+1) - hh;

        position = (startItem * maxWidth) / (numData - numItems);
    }
    // cout << "position  = " << position << endl;
}

//--------------------------------------------------------------

void hScrollBar::draw(void)
{
    if(linkedListBox == NULL) return;

    int numItems  = linkedListBox->getNumWidgets();
    int numData   = linkedListBox->getNumData();

    if((numData - numItems) > 0)
    {
        hGui * gui = hGui::getInstance();

        int hh  = gui->scrollHandleHeight;
        int yy  = (y + position) - (hh/2);

/* NO MORE NECESSARY!
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
        linkedListBox->incButton->setEnabled(true);
        linkedListBox->decButton->setEnabled(true);
	} // (numData - numItems) > 0)
    else {
        // Disable the drawing of the other small widgets
        linkedListBox->incButton->setEnabled(false);
        linkedListBox->decButton->setEnabled(false);
    }
}

// --------------------------------------------------------------

void hScrollBar::mousePressed(int xx, int yy, int btn)
{
	mouseDragged(xx, yy, btn); // same routine...
}

void hScrollBar::mouseDragged(int xx, int yy, int btn)
{
    hGui * gui = hGui::getInstance();

    if(linkedListBox != NULL) {
        // Calculate sizes:
        int numItems = linkedListBox->getNumWidgets();
        int numData  = linkedListBox->getNumData();

        if(numData > numItems) {
            // Calculate position:
            int hh  = gui->scrollHandleHeight;
            int hh2 = (hh/2) + 2;
            int maxWidth = (h+1) - hh;

            position = (yy - y);
            if(position < hh2) position = hh2;
            else if(position > maxWidth) position = maxWidth;

            // Calculate selection:
            if(position > hh2) // new (necessary when many lines)
                 startItem = (position * (numData - numItems)) / maxWidth;
            else startItem = 0; // new
            // cout << startItem << endl;

            // Move the data pointers to show the new data to the widgets:
            hListBox * listBox = dynamic_cast<hListBox *>(linkedListBox);
            if(listBox != NULL) listBox->scrollItems(startItem);
        }
    }
}

//--------------------------------------------------------------
