
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

#ifndef _HLIST_ITEM
#define _HLIST_ITEM

#include "hWidget.h"

//------------------------------------------------------------------------------
// hListItem is not a widget to be used alone, it is merely created by hListBox
//------------------------------------------------------------------------------

class hLabel;
class hNumberBox;

class hListItem: public hWidget{
public:
    hListItem(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);

	void setLabel(std::string s);

    void displayIndex(bool dispFlag);
	// display the index before the label if true

    void setIndexShift(int shift1, int shift10, int shift100);
	// set the x shift for the values 0..9, 10..99, >= 100

    void sendWhenReleased(bool flag);
	// Ask to send the message when the list box is realised instead of when it is pushed.
	// Do this when the message needs a lenghty processing

	void setLinkedLabel(hLabel * labelWidget);
	// Link this object to a label object: when this object is updated, the label will be too

    void setLinkedNumberBox(hNumberBox * numberBoxWidget);
	// Link this object to a numberBox object: when this object is updated, the numberBox will be too

	void setMessage(std::string s);
	void bang(void);

    virtual void draw(void);
    void mousePressed(int xx, int yy, int btn);
    void mouseReleased(int xx, int yy, int btn);

protected:
    bool sendWhenReleasedFlag;

    hLabel * linkedLabel;
    hNumberBox * linkedNumberBox;
};

//--------------------------------------------------------
#endif // _HLIST_ITEM
