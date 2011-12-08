
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

#ifndef _HTABBOX
#define _HTABBOX

#include "hListBox.h"

//--------------------------------------------------------

// hTabBox is a horizontal listbox used to control tabs.
// A hTabBox is used to display widgets, where each tab is linked to specific panel to display
// mainTabSelectionPanel is the panel where the choice is displayed (for the main tab)
// It is the first on the list (widgets[0]) before the tabs.

class hTabBox: public hListBox{
public:
    hTabBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);

	void addItems(int numItems);
	// Add the needed number of items to the tabBox
	
	void setItemLabel(int item, std::string s);
	// Set a label to an item 
	// 'item' is the item number to modify (starting with 1)

	void setItemPanel(int item, hPanel * panel);
	// Set a panel to an item 
	// 'item' is the item number to modify (starting with 1)

	void selectItem(int item);
	// Select a tabBox item.
	// first element = #1
	// Note: there is no unselectItem method for tab boxes


	//--------------------------------------------------------
	
	// Methods called by event listeners:

    void mousePressed(int xx, int yy, int btn);

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void storeItemPanel(hPanel * linkedPanel);
	// Helper function used by selectItemPanel and mousePressed
	// If it is the root panel: store the ptr of the item panel in the mainTabSelectionPanel
	// else store the ptr of the item panel in the parent panel after removing the last item panel Ptr

	//--------------------------------------------------------
	
	void saveSettings(ofxXmlSettings * xml){}
	// Does nothing for the moment
	// (must be different than for hListBox)
	
	//--------------------------------------------------------

protected:
    hPanel * mainTabSelectionPanel;
    hPanel * curTabSelectionPanel;
};

//--------------------------------------------------------
#endif // _HTABBOX
