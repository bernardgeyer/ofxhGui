
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

#ifndef HBUTTONBOX
#define HBUTTONBOX

#include "hListBox.h"

//--------------------------------------------------------

class hButtonBox: public hListBox{
public:
    hButtonBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int item_width, int item_height);

	void addItems(int numXItems, int numYItems);
	// 'items' are the hListItem objects in the buttonbox
	// Adapt also the size of the panel to the size of all items inside

	int getXItems(void);
	// Return the number of colons

	int getYItems(void);
	// Return the number of lines

	void alternateLineColors(bool flag);
	// Alternate the colors of the lines if this flag is set
	// Warning : It is necessary to do this before adding items

	// LOOK IN "hListBox.h" FOR MORE METHODS TO USE
	
	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void saveSettings(ofxXmlSettings * xml);

	//--------------------------------------------------------

protected:
    int itemWidth, itemHeight;
    int xItems, yItems;

    bool altLineCols;
};

//--------------------------------------------------------
#endif // HBUTTONBOX
