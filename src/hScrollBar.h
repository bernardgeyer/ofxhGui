
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

#ifndef _HSCROLLBAR
#define _HSCROLLBAR

#include "hWidget.h"

//------------------------------------------------------------------------------
// hScrollBar is not a widget to be used alone, it is merely created by hPanel
//------------------------------------------------------------------------------


class hListBox;

class hScrollBar: public hWidget{
public:
    hScrollBar(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);

    void setLinkedListBox(hListBox * listbox);
    void setPosition(int start_item);

    void draw(void);
    void mousePressed(int xx, int yy, int btn);
    void mouseDragged(int xx, int yy, int btn);

protected:
    int position;
    int startItem;

    hListBox * linkedListBox;
};

//--------------------------------------------------------
#endif // _HSCROLLBAR
