
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

#ifndef _HTEXTBOX
#define _HTEXTBOX

#include "hWidget.h"

//--------------------------------------------------------

class hLabel;

class hTextBox: public hWidget{
public:
    hTextBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);

	void clearLabel(void);
	// Clear the text displayed on the widget

	void setLabel(std::string s);
	// Set the text to be displayed on the widget

	std::string getLabel(void);
	
    void setLinkedLabel(hLabel * label);
	// Link this object to a label (or a numberbox) object: when this object is updated, the label will be too

    void clearAfterReturn(bool flag);
	// Clear the text box after the user has typed return
	// Usefull for execution of commands

    void sendOnLoosingFocus(bool flag);
	// Send the message of the text box when it looses focus
	// Note: this is default for number boxes

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change
	
	virtual void bang(void);
	// Send the message
	// Warning: empty strings can also be sent

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    void draw();
	
    virtual void keyPressed(int key);
    void mousePressed(int xx, int yy, int btn);

	//--------------------------------------------------------

protected:
    int textWidth;
    bool clearFlag;

    hLabel * linkedLabel;
};

//--------------------------------------------------------
#endif // _HTEXTBOX
