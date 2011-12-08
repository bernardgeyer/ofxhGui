
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

#ifndef _HINCBUTTON
#define _HINCBUTTON

#include "hButton.h"

//--------------------------------------------------------
class hNumberBox;

class hIncButton: public hButton{
public:
    hIncButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);

    void setAmount(double amount);
	// Set the amount to increment the value (can be negative)
	
    void setLinkedNumberBox(hNumberBox * numberBoxWidget);
	// Link this object to a number box object: when this button is pressed, the linked number box will incremented
	// by the amount defined with setAmount

    void mousePressed(int xx, int yy, int btn);
	// Important: when an incButton in connected to a number box,
	// the message of the numberbox will be sent too

protected:
    double incAmount;

    hNumberBox * linkedNumberBox;
};

//--------------------------------------------------------
#endif // _HINCBUTTON
