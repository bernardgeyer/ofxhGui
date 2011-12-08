
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

#include "hDialog.h"

#include "hLabel.h"
#include "hTextArea.h"
#include "hDialogButton.h"
#include "hGui.h"

#include <typeinfo>

int ofGetWidth(); int ofGetHeight();

//--------------------------------------------------------------

hDialog::hDialog(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hPanel(name, parent, dispMode, xx, yy, width, height, true)
{
	data->type = "dialog";
    hGui * gui = hGui::getInstance();

	dialogColor = gui->dialogColor;
    setVisibleBackground(true);

    openFlag = false;
	inTopBar = false;

	clickedX    = 0;
	clickedY    = 0;
	clickedXpos = 0;
	clickedYpos = 0;
	xShift      = 0;
	yShift      = 0;

    result = 0; // result 1 = confirm, 2 = cancel (or close)

	closeButton   = NULL;
	confirmButton = NULL;
	cancelButton  = NULL;

	msgTextArea   = NULL; // Used by message boxes
	alertLabel    = NULL; // Used by alerts
}

//--------------------------------------------------------------

void hDialog::setTitle(string s)
{
	data->label = s;
}


void hDialog::addCloseButton(void)
{
	if(closeButton == NULL) {
        hGui * gui = hGui::getInstance();

        closeButton =
            new hDialogButton("", this, HGUI_ABSOLUTE_POSITION,
				(x+w)-gui->checkBoxSize, y, gui->checkBoxSize, hDialogCloseType, "x");

        closeButton->setHeight(gui->checkBoxSize);
        closeButton->setLabelOffset(2, -3);
        closeButton->setBackgroundColor(backgroundColor);
	    closeButton->setLinkedDialog(this);
	}
}

void hDialog::addTools(int width, int position, std::string confirmStr, std::string cancelStr)
{
    hGui * gui = hGui::getInstance();

    int centerX = x + (w/2);
    int yy = (y+h) - gui->buttonHeight;

#if defined( __WIN32__ ) || defined( _WIN32 )
    yy += 1;
#endif

    if(position < 0)
         confirmButton = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, x, yy, width, hDialogConfirmType, confirmStr);
    else if(position == 0)
         confirmButton = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, centerX-width, yy, width, hDialogConfirmType, confirmStr);
    else if(position > 0)
         confirmButton = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, (x+w)-(width*2), yy, width, hDialogConfirmType, confirmStr);

	confirmButton->setLinkedDialog(this);

    if(position < 0)
        cancelButton  = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, x+width, yy, width, hDialogCancelType, cancelStr);
    else if(position == 0)
        cancelButton  = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, centerX, yy, width, hDialogCancelType, cancelStr);
    else if(position > 0)
        cancelButton  = new hDialogButton("", this, HGUI_ABSOLUTE_POSITION, (x+w)-width, yy, width, hDialogCancelType, cancelStr);

    cancelButton->setLinkedDialog(this);
}

void hDialog::changeToolNames(std::string confirmStr, std::string cancelStr)
{
	if(confirmButton != NULL) confirmButton->setLabel(confirmStr);
	if(cancelButton  != NULL) cancelButton->setLabel(cancelStr);
}

//--------------------------------------------------------------

void hDialog::setMessage(string s)
{
	data->message = s;
}

void hDialog::setMessage2(std::string s)
{
    data->message2 = s;
}

//--------------------------------------------------------------

void hDialog::open(void)
{
    if(openFlag == false) {
		hPanel * rootWidget = dynamic_cast<hPanel *>(hGui::getInstance()->getRootWidget());

		if(rootWidget != NULL) {
			rootWidget->addWidgetPtr(this);

			openFlag = true;
			result = 0;
		}
    }
}

void hDialog::close(void)
{
    if(openFlag == true) {
		hPanel * rootWidget = dynamic_cast<hPanel *>(hGui::getInstance()->getRootWidget());
		if(rootWidget != NULL) {
			int index = rootWidget->findWidgetIndex(this);
			if(index > -1) rootWidget->removeWidgetPtrAt(index);
			openFlag = false;
		}
    }
}

bool hDialog::isOpen(void)
{
    return openFlag;
}


//--------------------------------------------------------------

void hDialog::moveToFront(void)
{
    if(openFlag == true) {
		hPanel * rootWidget = dynamic_cast<hPanel *>(hGui::getInstance()->getRootWidget());
		if(rootWidget != NULL) {
			int index = rootWidget->findWidgetIndex(this);
			if(index > -1) {
				rootWidget->removeWidgetPtrAt(index);
				rootWidget->addWidgetPtr(this);
			}
		}
    }
}

//--------------------------------------------------------

void hDialog::draw(void)
{
    hGui * gui = hGui::getInstance();

    int hh;

    if((confirmButton != NULL) || (msgTextArea != NULL))
		hh = (h - gui->buttonHeight) + 1;
    else hh = h;

    // Draw the dialog background
    if(visibleBackground){
        if(backgroundColor != -1)
			hSetHexColor(backgroundColor);
        else hSetHexColor(gui->backgroundColor);
        hPaintRect(x, y, w, hh);
    }

    // Draw top bar content
    hSetHexColor(dialogColor);
    hPaintRect(x, y, w, gui->checkBoxSize);

// NEW
    hSetHexColor(gui->textColor);
	hDrawString(gui->font,  data->label, x+2, y+gui->textHeight);
// END NEW
	
    // Draw all widgets inside the dialog
    int size = widgets.size();
    for(int i = 0; i < size; ++i)
        widgets[i]->draw();

	//  Frames have to be done last, in case they are recovered by something else
    // Draw the dialog frame
    if(visibleBorder){
        hSetHexColor(gui->borderColor);
        hFrameRect(x, y, w, hh);
    }

    // Draw top bar frame
    hSetHexColor(gui->borderColor);
    hFrameRect(x, y, w, gui->checkBoxSize);

#if defined( __WIN32__ ) || defined( _WIN32 )
    hSetHexColor(dialogColor);
    hLine(x, y+gui->checkBoxSize-1, x+w-gui->checkBoxSize-1, y+gui->checkBoxSize-1);
#endif
}

//--------------------------------------------------------

void hDialog::mousePressed(int xx, int yy, int btn)
{
    hPanel::mousePressed(xx, yy, btn);

    clickedX    = xx;
    clickedY    = yy;
    clickedXpos = xx-x;
    clickedYpos = yy-y;
    xShift      = 0;
    yShift      = 0;

    moveToFront();
    checkMouseInTopBar();

    // cout << "clickedXpos " << clickedXpos << endl;
    // cout << "clickedYpos " << clickedYpos << endl;
}

//--------------------------------------------------------

void hDialog::mouseDragged(int xx, int yy, int btn)
// Used to move the dialog box
{
    if(inTopBar == true) {
        xShift = xx-clickedX;
        yShift = yy-clickedY;

        if(isInWindow(xx, yy)) {
            // cout << "hDialog::mouseDragged " << xShift << " " << yShift << endl;

            // Move the panel
            this->move(xShift, yShift);

            // Move the widgets inside
            int size = widgets.size();
            for(int i = 0; i < size; ++i)
                widgets[i]->move(xShift, yShift);

            clickedX += xShift;
            clickedY += yShift;
        }
    }
    else hPanel::mouseDragged(xx, yy, btn);
}

//--------------------------------------------------------------
//							Helper methods:
//							Should not be called directly
//--------------------------------------------------------------

void hDialog::checkMouseInTopBar(void)
// Check if the user has clicked in the "top" bar of the dialog box
// Used to move the dialog box
{
    hGui * gui = hGui::getInstance();

    bool flag = false;

    int xx = clickedX; int yy = clickedY;
    int ww; int hh = gui->checkBoxSize;

    if(closeButton != NULL)
		ww = (w - gui->checkBoxSize);
    else ww = w;

    if(xx >= x)
        if(yy >= y)
            if(xx <= (x + ww))
                if(yy <= (y + hh))
                    flag = true;

    inTopBar =  flag;
}

bool hDialog::isInWindow(int xx, int yy)
// Check if the area where the user wants to move the dialog box is in the window
// Used to move the dialog box
{
    hGui * gui = hGui::getInstance();

    bool flag = false;

    int minX;
    if(closeButton == NULL)
		minX = -(w - gui->checkBoxSize);
    else minX = -(w - (gui->checkBoxSize * 2));

    int minY = 1;
    int maxX = (ofGetWidth()  - gui->checkBoxSize) - 1;
    int maxY = (ofGetHeight() - gui->checkBoxSize) - 1;

    if((xx - clickedXpos) >= minX)
        if((yy - clickedYpos) >= minY)
            if((xx - clickedXpos) <= maxX)
                if((yy - clickedYpos) <= maxY)
                    flag = true;

    return flag;
}


//--------------------------------------------------------------
