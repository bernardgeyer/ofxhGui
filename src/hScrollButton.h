
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

#ifndef _HSCROLLBUTTON
#define _HSCROLLBUTTON

#include "hButton.h"

//----------------------------------------------------------------------------------------------------------------
//          hScrollButton is not a widget to be used alone, it is merely created by hListBox
//----------------------------------------------------------------------------------------------------------------

class hListBox;
class hTextArea;

class hScrollButton: public hButton{
public:
    hScrollButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);
    void draw(void);

    void setLinkedListBox(hListBox   * listBoxWidget);
    void setLinkedTextArea(hTextArea * textAreaWidget);

    void setEnabled(bool flag);
    void setDirection(bool dir);

    void mousePressed(int xx, int yy, int btn);

protected:
    bool enabled;
    bool direction;

    hListBox  * linkedListBox;
    hTextArea * linkedTextArea;
};

//--------------------------------------------------------
#endif // _HSCROLLBUTTON
