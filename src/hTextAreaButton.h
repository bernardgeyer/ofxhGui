
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

#ifndef _HTEXTAREA_BUTTON
#define _HTEXTAREA_BUTTON

#include "hButton.h"

//----------------------------------------------------------------------------------------------------------------
//          hTextAreaButton is not a widget to be used alone, it is merely created by hTextArea
//----------------------------------------------------------------------------------------------------------------

enum hTextAreaButtonTypes {
    hTextAreaClearButtonType,
    hTextAreaSendButtonType
};

// A text area button is used to control a text area
// There are actually 2 types : hTextAreaSendButtonType and hTextAreaClearButtonTypeS

class hTextAreaButton: public hButton{
public:
    hTextAreaButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int button_type, std::string s);

    void setLinkedTextArea(hTextArea * textarea);

    void bang(void);

protected:
    bool buttonType;
    hTextArea * linkedTextArea;
};

//--------------------------------------------------------
#endif // _HTEXTAREA_BUTTON
