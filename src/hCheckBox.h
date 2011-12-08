
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

#ifndef _HCHECKBOX
#define _HCHECKBOX

#include "hWidget.h"

//--------------------------------------------------------

class hCheckBox: public hWidget{
public:
    hCheckBox(std::string name, hPanel * parent, int dispMode, int xx, int yy);

    void setLabelExtension(std::string s);
	// Extends the clicking size of the check box by the length of a label located on its right
	// (the label object has to be defined elsewhere)

	void setIndex(int index);
	// The index of a checkBox can be used as an additional  parameter
	// Usefull when we have a few checkBoxes that do similar things

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change

	void setMessage2(std::string s);
	// A checkbox can have a second message that is used when it is deselected
	// When it is not empty, it is used instead of the normal message

	void bang(void);
	// Send the message

	//--------------------------------------------------------
	
	// Methods called by event listeners:

    void draw(void);

    void mousePressed(int xx, int yy, int btn);

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void saveSettings(ofxXmlSettings * xml);
	// Save the state of the widget to the open xml file
};

//--------------------------------------------------------
#endif // _HCHECKBOX
