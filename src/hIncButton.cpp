
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

#include "hIncButton.h"
#include "hNumberBox.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hIncButton::hIncButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hButton(name, parent, dispMode, xx, yy, width, s)
// An inc button is used to increment a number box by a certain amount
// a negative amount means to decrement
{
	data->type = "inc_button";
    linkedNumberBox = NULL;
}

//--------------------------------------------------------------

void hIncButton::setAmount(double amount)
{
    incAmount = amount;
}

void hIncButton::setLinkedNumberBox(hNumberBox * numberBoxWidget)
{
	linkedNumberBox = numberBoxWidget;
}

//--------------------------------------------------------------

void hIncButton::mousePressed(int xx, int yy, int btn)
{
    if(data->disabled == true) return;

    pressed = true;

    // cout << "incAmount = " << incAmount << endl;
    // cout << "linkedNumberBox = " << linkedNumberBox << endl;

	if(linkedNumberBox != NULL) {
        linkedNumberBox->addValue(incAmount, true, true);
        linkedNumberBox->bang();
	}

	bang();
}

//--------------------------------------------------------------
