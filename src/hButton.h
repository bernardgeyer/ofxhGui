
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

#ifndef _HBUTTON
#define _HBUTTON

#include "hWidget.h"

//--------------------------------------------------------

class hButton: public hWidget{
public:
    hButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);

    void setDisabled(bool disableFlag);
	// If 'disableFlag' is true, the button will be disabled

	void setLabel(std::string s);
	// Set the text to be displayed on the widget
	
	void setLabelOffset(int xOffset, int yOffset);
	// The text will be shift to the right and to the bottom of the box

	void setIndex(int index);
	// The index of a button can be used as an additional  parameter
	// Usefull when we have a few buttons that do similar things

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change

    void sendWhenReleased(bool flag);
	// Ask to send the message when the button is realised instead of when it is pushed.
	// Do this when the message needs a lenghty processing
	
	virtual void bang(void);
	// Send the message

	//--------------------------------------------------------
	
	// Methods called by event listeners:

    virtual void draw(void);
	
    virtual void mousePressed(int xx, int yy, int btn);
    void mouseReleased(int xx, int yy, int btn);
	
	//--------------------------------------------------------

protected:
    bool pressed;
    bool sendWhenReleasedFlag;
    int labelXoffset, labelYoffset;
};

//--------------------------------------------------------
#endif // _HBUTTON
