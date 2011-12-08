
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

#ifndef _HLABEL
#define _HLABEL

#include "hWidget.h"

//--------------------------------------------------------

class hLabel: public hWidget{
public:
    hLabel(std::string name, hPanel * parent, int dispMode, int xx, int yy, std::string s);

	void setLabel(std::string s);
	// Set the text to be displayed on the widget

	std::string getLabel(void);

	void setFixedMode(bool fixed);
	// If true, uses the fixed font instead of the default font

	void setIndex(int index);
	// The index of a label can be used as an additional  parameter
	// Usefull when we have a few selectable labels that do similar things

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change

	void bang(void);
	// Send the message

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    virtual void draw(void);

    void mousePressed(int xx, int yy, int btn);

protected:
    int textWidth;
    bool fixedMode;
};

//--------------------------------------------------------
#endif // _HLABEL
