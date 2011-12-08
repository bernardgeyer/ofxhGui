
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

#ifndef _HWIDGET
#define _HWIDGET

#include "hDrawingPrimitives.h"
#include "hObject.h"

#include <string>

//--------------------------------------------------------

struct hGuiData {
// This is the data used by the widgets, but not always totaly displayed
// When a scrollbar is available, it selects which data is effectively displayed
// else the defaut data is displayed
	std::string type;
	std::string name;
    int index;	// index as needed for display or sending parameter
	int offset; // offset in the parent panel
	
	std::string label;
	double value, value2;
	bool selectable;
	bool selected;
    bool radioEnabled;
    bool disabled;
	
    int selectColor;
	
    int indexDisplayFlag;
    int indexShift1, indexShift10, indexShift100;
    std::string message, message2;
};

//--------------------------------------------------------

// Display modes (where to place the widgets)

const int HGUI_ABSOLUTE_POSITION = 0; // position from the top/left border of the window
const int HGUI_TOP_LEFT = 1; // on the top/left position in the parent panel
const int HGUI_RIGHT    = 2; // on the right of the last widget in the parent panel
const int HGUI_BOTTOM   = 3; // on the bottom of the last widget in the parent panel
const int HGUI_NEXT_ROW = 4; // to next row
const int HGUI_NEXT_COL = 5; // to next colomn

// WARNING:
// After a composite object (hListBox, hButtonBox ...) 
// the dispModes HGUI_RIGHT and HGUI_BOTTOM cannot be used.
// Use HGUI_NEXT_ROW or HGUI_NEXT_COL instead

//--------------------------------------------------------

// Parameters for variables synchronized with hGui

const int HGUI_NO_VAR     = 0;
const int HGUI_INT_VAR    = 1;
const int HGUI_FLOAT_VAR  = 2;
const int HGUI_DOUBLE_VAR = 3;
const int HGUI_BOOL_VAR   = 4;

//--------------------------------------------------------

class hPanel;
class ofxXmlSettings;

class hWidget : public hObject {
public:
	
    hWidget(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
	// Constructor: called when a special kind of widget is created
	// Should not be called directly.

	//--------------------------------------------------------

	// Methods used to modify the settings of a widget:

    void move(int xShift, int yShift);
	// Move the widget a certain amount of pixels

    void moveTo(int x, int y);
	// Move the widget to a specified position

	// Change the size of the widget:
    void setWidth(int ww);
    void setHeight(int hh);
    void incWidth(int ww);
    void incHeight(int hh);

	// Get the coordinates of the widget:
    int getX(void); int getY(void);
    int getWidth(void); int getHeight(void);

	int getRight(void); int getBottom(void);
	// Return the right coordinate / the bottom coordinate of the widget

	hPanel * getParentPanel(void);
	// Return the parent panel of the widget
	// Return NULL if the widget has no parent panel
	
	void setSelectable(bool selFlag);
	// Allow the widget to be selected or not
	
	void select(void);
	void unselect(void);
	void setSelected(bool selFlag);
	// Select/unselect the widget
	
	bool isSelected(void);
	// Check if the widget is selected
	
    void toggleSelection(void);
	// Select if not selected, unselect if selected
	
	virtual void setRadioEnabled(bool radioFlag);
	// Transform the widget into a radio button
	
    void setVisibleBorder(bool visibleFlag);
	// Make the background visible (on by default)

    void setVisibleBackground(bool visibleFlag);
	// Make the background visible (off by default)
	
	virtual void setBackgroundColor(int color);
	// If color != -1, overwite the default background color
	// Warning : for listBox objects it is necessary to do this before adding items and data

	virtual void setColor(int color);
	// If color != -1, overwite the default foreground color

	virtual void setSelectColor(int color);
	// If color != -1, overwite the default selection color
	// Warning : for listBox objects it is necessary to do this before adding items and data

    bool isEditable(void);
	// Check if the widget is editable
	
	//--------------------------------------------------------

	// Methods used to synchronize the widget with a variable:

	void setIntVar(int *var);
	// Ask the widget to synchronize with an int variable

	void setFloatVar(float *var);
	// Ask the widget to synchronize with a float variable

	void setDoubleVar(double *var);
	// Ask the widget to synchronize with a double variable

	void setBoolVar(bool *var);
	// Ask the widget to synchronize with a bool variable
	// Used by checkBoxes
	
	void unsetVar(void);
	// Remove the synchronization between widget and variable

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    virtual void draw(void);
	
    virtual void mousePressed(int xx, int yy, int btn){}
    virtual void mouseReleased(int xx, int yy, int btn){}
    virtual void mouseDragged(int xx, int yy, int btn){}

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void calcWidgetPosition(void);
	// Remember the position after the last widget of the parent panel
	// note: this cannot be done in addWidgetToPanel, because the size of a widget
	// can be changed after that
	// For composite objects: must be done each time new itms are add
	
	void setMaxXY(int xx, int yy);
	// Set the new values of maxX and maxY

	void addMaxXY(int xx, int yy);
	// Increments maxX and maxY by a value
	
	void syncVar(void);
	// Synchronize the used variable with the state of the widget

	void syncWithVar(void);
	// Synchronize the widget with the used variable

    void setData(hGuiData * dta);
	// Let the widget point to another data record (used by scrollbars)

    hGuiData * getData(void);
	// Return a pointer to the data of the widget

	virtual void saveSettings(ofxXmlSettings * xml){}
	// Save the state of the widgets that implement this method to the open xml file
	
	//--------------------------------------------------------

protected:
friend class hPanel;

	int displayMode;
    int x, y, w, h;
    bool visibleBorder;
    bool visibleBackground;
    int backgroundColor;

    bool editable;
    bool focusSendFlag;
    int x_extension;
	
	int		varType;
	int    *intVar;
	float  *floatVar;
	double *doubleVar;
	bool   *boolVar;

	hPanel * parentPanel; // panel in which the pointer of the widget can be located
    hGuiData * data;	  // data used by the widget
};

//--------------------------------------------------------
#endif // _HWIDGET
