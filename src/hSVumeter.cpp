
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

#include "hSVumeter.h"
#include "hGui.h"
#include "hEvents.h"

//--------------------------------------------------------------

hSVumeter::hSVumeter(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hLabel(name, parent, dispMode, xx, yy, "")
{
	data->type = "vumeter";
    setWidth(width);
    setHeight(height);
	data->value = 0.0;
}

void hSVumeter::setValue(double val)
{
		 if(val < 0) val = 0;
	else if(val > 1) val = 1;
	
	data->value = val;
}

void hSVumeter::draw(void)
{
    hGui * gui = hGui::getInstance();

	if(data->value > 0) {
		hSetHexColor(gui->vumeterColor);
		int position = (h-2) * (1.0 - data->value);
		hPaintRect(x, (y+1) + position, w, (h-2) - position);
	}

	if(data->selected) {
        hSetHexColor(gui->vumeterBorderColor);
        hFrameRect(x, y, w, h);
	}
    else if(visibleBorder){
        hSetHexColor(gui->borderColor);
        hFrameRect(x, y, w, h);
    }
	
}

//--------------------------------------------------------------
