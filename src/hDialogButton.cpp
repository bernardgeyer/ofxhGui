
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

#include "hDialogButton.h"
#include "hDialog.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hDialogButton::hDialogButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int button_type, string s)
	: hButton(name, parent, dispMode, xx, yy, width, s)
{
	data->type = "dialog_button";
    buttonType = button_type;

    linkedDialog = NULL;
}

//--------------------------------------------------------------

void hDialogButton::setLinkedDialog(hDialog * dialog)
{
    linkedDialog = dialog;
}

//--------------------------------------------------------------

void hDialogButton::bang(void)
{
    // cout << "hDialogButton::sendMessage" << endl;

    if(linkedDialog == NULL) {
        // Send the message of the button
        if(data->message.size() > 0)
            hEvents::getInstance()->sendEvent(data->message);
    }
    else {
        hGuiData * dataPtr = linkedDialog->getData();
        linkedDialog->result = buttonType;

        switch(buttonType) {
            case hDialogCloseType:
                // Close the linked dialog widget
				// cout << "hDialogButton:close" << endl;
               linkedDialog->close();
            break;

            case hDialogConfirmType:
				// cout << "hDialogButton:confirm " << dataPtr->message << " " << hDialogConfirmType << endl;
                // Send the "confirm" message of the linked dialog widget
                if(dataPtr->message.size() > 0) {
					hEvents::getInstance()->sendEvent(dataPtr->message, hDialogConfirmType);
                }
                // Close the linked dialog widget
                linkedDialog->close();
           break;

            case hDialogCancelType:
				// cout << "hDialogButton:cancel " << dataPtr->message2 << " " << hDialogCancelType << endl;
                // Send the "close" message of the linked dialog widget
                // uses message2
                if(dataPtr->message2.size() > 0) {
                    hEvents::getInstance()->sendEvent(dataPtr->message2, hDialogCancelType);
                }

                // Close the linked dialog widget
                linkedDialog->close();
           break;
        }
    }

    // cout << "result = " << linkedDialog->result << endl;
}

//--------------------------------------------------------------
