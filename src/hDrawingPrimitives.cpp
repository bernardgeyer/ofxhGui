
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

#include "ofConstants.h"
#include "ofGraphics.h"
#include "ofTrueTypeFont.h"

//--------------------------------------------------------------

void hFrameRect(int x, int y, int w, int h)
{
    ofNoFill();
    ofRect(x + .5, y + .5, w - 1, h - 1); // Thanks to kylemcdonald for his clever solution
										  // https://github.com/openframeworks/openFrameworks/issues/798
}

void hPaintRect(int x, int y, int w, int h)
{
    ofFill();
    ofRect(x, y, w, h);
    hFrameRect(x, y, w, h);
}

//--------------------------------------------------------------

void hLine(float x1, float y1, float x2, float y2)
{
	ofLine(x1, y1, x2, y2);
}

//--------------------------------------------------------------

void hSetHexColor(int hexColor)
{
#if OF_VERSION < 7
	// cout << "using OF version 6" << endl;
	ofSetColor(hexColor);
#else
	// cout << "using OF version 7" << endl;
	ofSetHexColor(hexColor);
#endif
}

//--------------------------------------------------------------

#if OF_VERSION < 7 // we need the getSize() method that exists only in OF 7
	class extendedOfTrueTypeFont : public ofTrueTypeFont { public: int getSize(void){return fontSize;} };
#endif

void hDrawString(ofTrueTypeFont *fnt, std::string s, float x, float y)
{
	int yShift;

#if OF_VERSION < 7
	int size = ((extendedOfTrueTypeFont *)fnt)->getSize();
#else
	int size = fnt->getSize();
#endif
	switch(size) {
		case 7: yShift = -1; break;
		case 8: yShift = -1; break;
		case 9: yShift =  0; break;
		default: yShift = size - 8;
	}

#if OF_VERSION < 7
	fnt->drawString(s, x-2, (y-2) - yShift);
#else
	fnt->drawString(s, x, y - yShift);
#endif
}

//--------------------------------------------------------------
