
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

#include "hTextArea.h"
#include "hTextAreaButton.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hTextAreaButton::hTextAreaButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int button_type, string s)
	: hButton(name, parent, dispMode, xx, yy, width, s)
{
	data->type = "text_area_button";
    buttonType = button_type;

    linkedTextArea = NULL;
}

//--------------------------------------------------------------

void hTextAreaButton::setLinkedTextArea(hTextArea * textarea)
{
    linkedTextArea = textarea;
}

//--------------------------------------------------------------

void hTextAreaButton::bang(void)
{
    // cout << "hTextAreaButton::sendMessage, ";

    if(linkedTextArea == NULL) {
        // Send the message of the button
        if(data->message.size() > 0)
            hEvents::getInstance()->sendEvent(data->message);
    }
    else {
        hGuiData * dataPtr = linkedTextArea->getData();
        switch(buttonType) {
            case hTextAreaSendButtonType:
                // Send the message of the linked text edit widget
                if(dataPtr->message.size() > 0) {
                    if(dataPtr->label.size() > 0) {
                        hEvents::getInstance()->sendEvent
                            (dataPtr->message, dataPtr->label);
                    }
                }
            break;

            case hTextAreaClearButtonType:
                // Send the "clear" message of the linked text edit widget
                // uses message2
                if(dataPtr->message2.size() > 0) {
                    hEvents::getInstance()->sendEvent
                        (dataPtr->message2);
                }

                // Clear the message of the linked text edit widget
                linkedTextArea->clearText(true);
           break;
        }
    }
}

//--------------------------------------------------------------
