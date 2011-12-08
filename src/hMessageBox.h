
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

#ifndef _HMESSAGE_BOX
#define _HMESSAGE_BOX

#include "hDialog.h"

class hPanel;

// A message box is a dialog used to display info for the user
// It opens when the first display message is sent to it

// Message boxes can be moved and closed by the user
// They are visible in all tabs

class hMessageBox: public hDialog{
public:
    hMessageBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);

    void clear(void);
	// Clear the text of the message box
	
    void display(std::string str);
	// Display a line in the message box
	// Open it if before if needed
	
    void displayWOcr(std::string str);
	// Display a line without a '\n' on the end of the line
	// Used for string that have already an endline
};

//--------------------------------------------------------
#endif // _HMESSAGE_BOX
