
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

#ifndef _HDRAWING_PRIMITIVES
#define _HDRAWING_PRIMITIVES

#include <string>

//--------------------------------------------------------------
//		All drawings are done here
//		This permits to change later how to draw (f.e with pango)
//		without touching the code of the widgets
//--------------------------------------------------------------


void hFrameRect(int x, int y, int w, int h);
void hPaintRect(int x, int y, int w, int h);
// Necessary to draw correct rectangles on all platforms:

//--------------------------------------------------------

void hLine(float x1, float y1, float x2, float y2);
// Actually identical to 'ofLine', but we let us the possibility the change
// it in the future

void hSetHexColor(int hexColor);
// Necessary to use ofSetHexColor on OF 6

class ofTrueTypeFont;
void hDrawString(ofTrueTypeFont *fnt, std::string s, float x, float y);
// Necessary to draw correctly the strings on OF 6 AND OF 7

//--------------------------------------------------------
#endif // _HDRAWING_PRIMITIVES
