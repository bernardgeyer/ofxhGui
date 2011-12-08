
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

#ifndef _HPANEL
#define _HPANEL

#include "hWidget.h"
#include <vector>

//--------------------------------------------------------

class hScrollBar;

// A panel is a widgets that hold other widgets
// if radioFlag is set, the widgets inside the panel that are radioEnabled behave like radio buttons

class hPanel: public hWidget{
public:
    hPanel(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height, bool hasBorder);

    void clearWidgets(void);
	// Remove all widgets from the panel

    int getNumWidgets(void);
	// Return the number of widgets in the panel

    int getNumData(void);
	// Return the number of data records in the panel

    hWidget * getLastWidget(void);
	// Return the last widget in the panel
	
    static hWidget * getSelectedTextObj(void);
	// Return the actually used text object (return NULL if none)

	void addWidgetToPanel(hWidget *widget);
	// Add a widget * and its data record * to a panel
	// Usefull when we want the same widget displayed on different tabs
	
	void adaptPanelSize(int xx, int yy);
	// Grow the size of the panel to fit the widgets inside of it
	// x,y is the amount for right and bottom margins
	
	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    void draw(void);

	virtual void mousePressed(int xx, int yy, int btn);
    virtual void mouseReleased(int xx, int yy, int btn);
    virtual void mouseDragged(int xx, int yy, int btn);
		
	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
    void addWidgetPtr(hWidget *widget);
	// Similar to addWidgetToPanel : add ONLY a widget to a panel
	// Used to add scrollbars.
	// !!! Only for internal use of the gui library
		
    hWidget * findWidget(int xx, int yy);
	// Find the widget under the mouse
	// Find in reverse order
	// in case some widgets cover others, the top (visible) widget will be found

    int findWidgetIndex(hWidget * widget);
	// Search if a widget is in the panel
	// return the index or -1 if not found

    hWidget * getWidgetAt(int index);
	// Return the pointer of a widget at a certain index in the widget vector
	// Warning 1 : index starts with #0
	// Warning 2 : no bound checking here !!! has to be done in the calling function !

    hGuiData * getDataAt(int index);
	// Return a data pointer at a certain index in the data buffer
	// Warning 1 : index starts with #0
	// Warning 2 : no bound checking here !!! has to be done in the calling function !
	
    void removeWidgetPtrAt(int index);
	// Remove the pointer of a widget at a certain index in the widget vector
	// Warning 1 : index starts with #0
	// Warning 2 : no bound checking here !!! has to be done in the calling function !

    void removeDataPtrAt(int index);
	// Remove the data pointer at a certain index in the data buffer
	// Warning 1 : index starts with #0
	// Warning 2 : no bound checking here !!! has to be done in the calling function !
	// Warning  3 : This does not delete the data itself !
	
	//--------------------------------------------------------
	
	int maxX, maxY;

protected:
friend class hWidget;
	std::vector<hWidget*> widgets;
	hWidget *clickedWidget;

	std::vector<hGuiData*> data_buffer;

	hGuiData *selectedRadio;
	static hWidget *selectedTextObj; // same value shared for all panels
};

//--------------------------------------------------------
#endif // _HPANEL
