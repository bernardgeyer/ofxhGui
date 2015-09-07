
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

#ifndef _HWAVEFORM
#define _HWAVEFORM

#include "hWidget.h"
#include <vector>
using namespace std;

//--------------------------------------------------------

class hWaveform: public hWidget{
public:
    hWaveform(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);

	void fillBuffer(short * source, int size, int index, int step);
	// Fill the buffer with values
	// source = wave buffer, size = it's size, index = where to start, step = how many samples by point
	
	void fillWavePoints(int * points, int size, int index);
	// Fill the wavePoints with values (0 = nothing, 1 = start of waveform of waveset)
	// source = array of point indexes, size = it's size, index = where to start in that array
	void clearWavePoints(void);

	void setIndex(int index);

	void setMessage(std::string s);
	// Set the message that will be send when the widget state change

	void bang(void);
	// Send the message

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    virtual void draw(void);

    void mousePressed(int xx, int yy, int btn);
	void mouseDragged(int xx, int yy, int btn);
	
	//--------------------------------------------------------
	vector<short int> buffer;
	vector<char> wavePoints;
	int centerPosition, ratio;
	
	int position;
};

//--------------------------------------------------------
#endif // _HWAVEFORM
