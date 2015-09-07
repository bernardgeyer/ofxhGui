
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

#include "hWaveform.h"
#include "hGui.h"
#include "hEvents.h"

#include "ofGraphics.h"

//--------------------------------------------------------------

hWaveform::hWaveform(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hWidget(name, parent, dispMode, xx, yy, width, height)
// Actually : only with 16 bit samples
{
	data->type = "waveform";
	
	centerPosition = y + (h/2);
	ratio = 65536 / height;
	
	for(int i = 0; i < width; ++i)
		buffer.push_back(0);

	for(int i = 0; i < width; ++i)
		wavePoints.push_back(0);
}

//--------------------------------------------------------------

void hWaveform::fillBuffer(short * source, int size, int index, int step)
{
	for(int i = 0; i < w; ++i) {
		int ii = (i+index)*step;
		 if(ii < size)
			  buffer[i] = source[ii];
		 else buffer[i] = 0;
	}
}

void hWaveform::fillWavePoints(int * points, int size, int index)
{
	cout << "fillWavePoints" << endl;
	cout << "index = " << index << endl;

	int nextPointIndex = 0;
	int nextPoint = points[nextPointIndex];
	// cout << "nextPoint = " << nextPoint << endl;

	while(nextPoint < index) {
		++nextPointIndex;
		nextPoint = points[nextPointIndex];
	}
	
	for (int i = 0; i < w; ++i){
		int ii = i+index;
		if(ii == nextPoint) {
			wavePoints[i] = 1;
			++nextPointIndex;
			nextPoint = points[nextPointIndex];
			// cout << "nextPoint = " << nextPoint << endl;
		} else wavePoints[i] = 0;
	}
}

void hWaveform::clearWavePoints(void)
{
	for (int i = 0; i < w; ++i) wavePoints[i] = 0;
}

//--------------------------------------------------------------

void hWaveform::draw(void)
{
// hGui * gui = hGui::getInstance();

	hWidget::draw();

	// Draw center line
	ofLine(x, centerPosition, x+w, centerPosition);
	
	// Draw wave starting lines (only on step = 1 ?)
	for(int i = 0; i < wavePoints.size(); ++i) {
		if(wavePoints[i] == 1)
			ofLine(x+i, y, x+i+1, y+h);
	}
	
	// Draw waveform
    ofBeginShape();
	// int lastYCoord = centerPosition;
	for(int i = 0; i < buffer.size(); ++i) {
		int yCoord = centerPosition - (buffer[i]/ratio);
		
		ofVertex(x+i, yCoord);

		// ofLine(x+i, lastYCoord, x+i+1, yCoord);
		// lastYCoord = yCoord;
	}
    ofEndShape();
}

//--------------------------------------------------------------

void hWaveform::setIndex(int index)
{
    data->index = index;
}

//--------------------------------------------------------------

void hWaveform::setMessage(string s)
{
	data->message = s;
}

void hWaveform::bang(void)
{
	if(data->label.size() > 0)
		if(data->message.size() > 0) {
            hEvents::getInstance()->sendEvent(data->message, data->label, data->index);
		}
}

//--------------------------------------------------------------

void hWaveform::mousePressed(int xx, int yy, int btn)
{
	position = xx - x;
	
	if(position < 0) position = 0; else if(position > (w-2)) position = w-2;
	
	// cout << "position = " << position << endl;
	
	hEvents::getInstance()->sendEvent("wave_remember_start", data->index);
}

void hWaveform::mouseDragged(int xx, int yy, int btn)
{
	if(xx < x) xx = x; else if((xx-x) > (w-2)) xx = x + (w-2);

	int shift = 0 - ((xx - x) - position);
	
	// cout << "shift = " << shift << endl;
	
	hEvents::getInstance()->sendEvent("wave_shift", data->index, shift);
}

//--------------------------------------------------------------
