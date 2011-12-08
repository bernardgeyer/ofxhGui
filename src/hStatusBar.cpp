
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

#include "hStatusBar.h"
#include "hGui.h"
#include "hEvents.h"

int ofGetWidth(); int ofGetHeight();

//--------------------------------------------------------------

hStatusBar::hStatusBar(std::string name, hPanel * parent, int dispMode, int xx, int yy, string s)
	: hLabel(name, parent, dispMode, xx, yy, s)
{
	data->type = "status_bar";
    w = ofGetWidth(); h = ofGetHeight(); x = 0; y = h - 13;
}

void hStatusBar::setDisabled(bool disableFlag)
{
	data->disabled = disableFlag;
}

//--------------------------------------------------------------

void hStatusBar::draw(void)
{
	if(data->disabled == true) return;

	hGui * gui = hGui::getInstance();

    w = ofGetWidth(); h = ofGetHeight(); y = h - 13;

    if(visibleBackground){
        if(backgroundColor != -1)
			hSetHexColor(backgroundColor);
        else hSetHexColor(gui->backgroundColor);
        hPaintRect(x, y, w, h);
    }

    hSetHexColor(gui->borderColor);
    hLine(x, y, x+w, y);

	if(data->label.size() > 0) {
		hSetHexColor(gui->textColor);
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( __APPLE_CC__ )
		hDrawString(gui->ffont, data->label, x+2, y+gui->ftextHeight-1);
#else
		hDrawString(gui->ffont, data->label, x+2, y+gui->ftextHeight);
#endif
    }
}

//--------------------------------------------------------------
