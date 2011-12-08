
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

#ifndef _HALERT
#define _HALERT

#include "hDialog.h"

// Create an alert box
// An alert box is a modal dialog used to make a choice (yes or no)
// It opens when the a display message is sent to it

// Alerts can be moved and closed by the user by clicking at a button
// They are visible in all tabs

class hPanel;

class hAlert: public hDialog{
public:
    hAlert(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);

    void clear(void);
	// Clear the label of the alert dialog
	
    void display(std::string str);
	// Display the alert dialog

	// void setMessage(std::string s);
	// Set the message that will be send when the user push the confirm button (sends also the value 1)
	
	// void setMessage2(std::string s);
	// Set the message that will be send when the user push the cancel button (sends also the value 2)
	
	//--------------------------------------------------------
	
// Deprecated! (use messages instead)
	
	int waitAnswer(void);
	// Wait the answer of the user (wait until the user has clicked on a button)
	// Works only when called from another thread
};

//--------------------------------------------------------
#endif // _HALERT
