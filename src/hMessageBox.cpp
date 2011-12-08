
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

#include "hMessageBox.h"
#include "hTextArea.h"
#include "hGui.h"


//--------------------------------------------------------------

hMessageBox::hMessageBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hDialog(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "message_box";
    hGui * gui = hGui::getInstance();

	dialogColor = gui->messageBoxColor;

    msgTextXStart = x+1;
    msgTextYStart = (y + gui->checkBoxSize)-1;
    msgTextWidth  = (w - gui->checkBoxSize)-1;
    msgTextHeight = ((h - gui->checkBoxSize) - gui->buttonHeight) + 2;

    msgTextArea =
        new hTextArea("", this, HGUI_ABSOLUTE_POSITION, msgTextXStart, msgTextYStart, msgTextWidth, msgTextHeight);

    msgTextArea->setVisibleBackground(true);
    msgTextArea->setVisibleBorder(false);
    msgTextArea->setEditable(false);

    addCloseButton();
}

//--------------------------------------------------------------

void hMessageBox::clear(void)
{
    msgTextArea->clearText(true);
}

void hMessageBox::display(std::string str)
{
    if(! isOpen()) {
        clear(); open();
    }

    msgTextArea->addText(str, true);
    msgTextArea->addText("\n", true);
}

void hMessageBox::displayWOcr(std::string str)
{
    if(! isOpen()) {
        clear(); open();
    }

    msgTextArea->addText(str, true);
}

//--------------------------------------------------------------
