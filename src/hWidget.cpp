
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

#include "hWidget.h"
#include "hPanel.h"
#include "hGui.h"


hWidget::hWidget(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
{
	parentPanel = parent;
	data = new hGuiData; // data had to be created before addWidgetToPanel is used
	
	if(parentPanel != NULL) {
		displayMode = dispMode;
		
		calcWidgetPosition(); // Remember the position after the last widget of the parent panel
		
		// Add the widget (and its data) to the panel
		parentPanel->addWidgetToPanel(this); 
	} else displayMode = HGUI_ABSOLUTE_POSITION;
	
	w = width; h = height;

	// determine the position of the widget
	if(displayMode == HGUI_ABSOLUTE_POSITION) {
		x = xx;
		y = yy;
	}
	else if(displayMode == HGUI_TOP_LEFT) {
		x = parent->x + xx;
		y = parent->y + yy;
	}
	else {
		x = parentPanel->maxX + xx;
		y = parentPanel->maxY + yy;
	}
	
	addMaxXY(xx, yy);
	
	// Store the adress of the widget in the object map, for quickly search by hEvents
	if(name.size() > 0) {
		data->name = name;
		hEvents::getInstance()->addObject(name, this);
	}
	
	// Set default values
	visibleBorder = true;
	visibleBackground = false;
    backgroundColor = -1;
	
	data->type   = "widget";
    data->index  = 0;
    data->offset = 0;
	
    data->value  = 0.0;
    data->value2 = 0.0;

    data->selectable = false;
    data->selected = false;
    data->radioEnabled = false;
    data->disabled = false;

    data->selectColor = -1;
    data->indexDisplayFlag = false;
    data->indexShift1 = 0;
    data->indexShift10 = 0,
    data->indexShift100 = 0;

	editable = false;
    focusSendFlag = false; // focusSendFlag is actualy only used by number boxes
    x_extension = 0;       // x_extension is actualy only used by check boxes

	varType   = HGUI_NO_VAR;
	intVar    = NULL;
	floatVar  = NULL;
	doubleVar = NULL;
	boolVar   = NULL;

	/* now done in hGui.cpp
	// Store the adress of the widget in the main widget list
    hGui * gui = hGui::getInstance();
	gui->addWidget(this);
	 */
}

//--------------------------------------------------------------

void hWidget::move(int xShift, int yShift) { x += xShift; y += yShift; }
void hWidget::moveTo(int xx, int yy) { x = xx; y = yy; }

void hWidget::setWidth(int ww)  { w = ww;}
void hWidget::setHeight(int hh) { h = hh;}

void hWidget::incWidth(int ww)  { w += ww;}
void hWidget::incHeight(int hh) { h += hh;}

int hWidget::getX(void){return x;}
int hWidget::getY(void){return y;}
int hWidget::getWidth(void){return w;}
int hWidget::getHeight(void){return h;}

int hWidget::getRight(void){return x+w;}
int hWidget::getBottom(void){return y+h;}

//--------------------------------------------------------------

hPanel * hWidget::getParentPanel(void){return parentPanel;}

//--------------------------------------------------------------

void hWidget::setSelectable(bool selFlag)
{
	data->selectable = selFlag;
}

void hWidget::select(void)
{
	if(data->disabled   == true)  return;
	if(data->selectable == false) return;

	// cout << "select " << data->name << endl;
	// cout << "radioEnabled == " << data->radioEnabled << endl;

	if(parentPanel != NULL) {
		if(data->radioEnabled == true) {
			if(parentPanel->selectedRadio != NULL) {
				// cout << "selectedRadio == " << parentPanel->selectedRadio->name << endl;
				
				// cout << "unselect last radio " << parentPanel->selectedRadio->name << endl;
				parentPanel->selectedRadio->selected = false;
				parentPanel->selectedRadio = NULL;
			}
			// else cout << "selectedRadio == NULL" << endl;
		}
	}
	
	data->selected = true;
	
	if(parentPanel != NULL) {
		if(data->radioEnabled == true) {
			parentPanel->selectedRadio = data;
		}
	}
}

void hWidget::unselect(void)
{
	if(data->disabled   == true)  return;
	if(data->selectable == false) return;

	// cout << "unselect " << data->name << endl;
	data->selected = false;
	
	if(parentPanel != NULL) {
		if(data->radioEnabled == true) {
			if(data == parentPanel->selectedRadio) {
				// cout << "unselect last radio " << parentPanel->selectedRadio->name << endl;
				parentPanel->selectedRadio->selected = false;
				parentPanel->selectedRadio = NULL;
			}
		}
	}
}

void hWidget::setSelected(bool selFlag)
{
	if(selFlag == true)
		 select();
	else unselect();
}

bool hWidget::isSelected(void)
{
	if(data->disabled   == true)  return false;
	if(data->selectable == false) return false;
	else return data->selected;
}

void hWidget::toggleSelection(void)
{
    setSelected(! isSelected());
}

void hWidget::setRadioEnabled(bool radioFlag)
{
	data->radioEnabled = radioFlag;
}

//--------------------------------------------------------------

void hWidget::setVisibleBorder(bool visibleFlag)
{
	visibleBorder = visibleFlag;
}


void hWidget::setVisibleBackground(bool visibleFlag)
{
	visibleBackground = visibleFlag;
}


void hWidget::setBackgroundColor(int color)
{
	// cout << "hWidget::setBackgroundColor: " << color << endl;
	backgroundColor = color;
	setVisibleBackground(true);
}

void hWidget::setColor(int color)
// Actually the same variable than setSelectColor
{
	data->selectColor = color;
}

void hWidget::setSelectColor(int color)
{
	data->selectColor = color;
}

//--------------------------------------------------------------

bool hWidget::isEditable(void)
{
    return editable;
}

//--------------------------------------------------------------

void hWidget::setIntVar(int *var)
{
	intVar    = var;
	floatVar  = NULL;
	doubleVar = NULL;
	boolVar   = NULL;
	varType   = HGUI_INT_VAR;
}

void hWidget::setFloatVar(float *var)
{
	intVar    = NULL;
	floatVar  = var;
	doubleVar = NULL;
	boolVar   = NULL;
	varType   = HGUI_FLOAT_VAR;
}

void hWidget::setDoubleVar(double *var)
{
	intVar    = NULL;
	floatVar  = NULL;
	doubleVar = var;
	boolVar   = NULL;
	varType   = HGUI_DOUBLE_VAR;
}

void hWidget::setBoolVar(bool *var)
{
	intVar    = NULL;
	floatVar  = NULL;
	doubleVar = NULL;
	boolVar   = var;
	varType   = HGUI_BOOL_VAR;
}

void hWidget::unsetVar(void)
{
	intVar    = NULL;
	floatVar  = NULL;
	doubleVar = NULL;
	boolVar   = NULL;
	varType   = HGUI_NO_VAR;
}

//--------------------------------------------------------------

void hWidget::draw(void)
{ 
    hGui * gui = hGui::getInstance();
	
    if(visibleBackground){
        if(backgroundColor != -1)
			hSetHexColor(backgroundColor);
        else hSetHexColor(gui->backgroundColor);
        hPaintRect(x, y, w, h);
    }
	
    if(visibleBorder){
        hSetHexColor(gui->borderColor);
        hFrameRect(x, y, w, h);
    }
}

//--------------------------------------------------------
//						Helper methods:
//						Should not be called directly
// --------------------------------------------------------------

void hWidget::calcWidgetPosition(void)
{
	// Find the last object on the panel:
	hWidget * lastWidget = NULL;
	int numChildren = parentPanel->getNumWidgets();
	if(numChildren > 0) lastWidget = parentPanel->getWidgetAt(numChildren - 1);
	
	// Calculate the position of the widget depending on displayMode:
	if(lastWidget != NULL) {
		switch(displayMode) {
			case HGUI_RIGHT:
				parentPanel->maxX += lastWidget->w;
				break;
				
			case HGUI_BOTTOM:
				parentPanel->maxY += lastWidget->h;
				break;
				
			case HGUI_NEXT_ROW:
				parentPanel->maxX  = parentPanel->x;
				parentPanel->maxY += lastWidget->h;
				break;
				
			case HGUI_NEXT_COL:
				parentPanel->maxX += lastWidget->w;
				parentPanel->maxY  = parentPanel->y;
				break;
		}
	}
}

void hWidget::setMaxXY(int xx, int yy)
{
	if(parentPanel != NULL) {
		if(displayMode != HGUI_ABSOLUTE_POSITION) {
			parentPanel->maxX = xx;
			parentPanel->maxY = yy;
		}
	}
}

void hWidget::addMaxXY(int xx, int yy)
{
	if(parentPanel != NULL) {
		if(displayMode != HGUI_ABSOLUTE_POSITION) {
			parentPanel->maxX += xx;
			parentPanel->maxY += yy;
		}
	}
}

//--------------------------------------------------------------

void hWidget::syncVar(void)
{
	switch (varType) {
		case HGUI_INT_VAR:
			*intVar = data->value;
			break;
		case HGUI_FLOAT_VAR:
			*floatVar = data->value;
			break;
		case HGUI_DOUBLE_VAR:
			*doubleVar = data->value;
			break;
		case HGUI_BOOL_VAR:
			*boolVar = data->selected;
			break;
	}
}

void hWidget::syncWithVar(void)
{
	switch (varType) {
		case HGUI_INT_VAR:
			data->value = *intVar;
			break;
		case HGUI_FLOAT_VAR:
			data->value = *floatVar;
			break;
		case HGUI_DOUBLE_VAR:
			data->value = *doubleVar;
			break;
		case HGUI_BOOL_VAR:
			data->selected = *boolVar;
			break;
	}
}

//--------------------------------------------------------------

void hWidget::setData(hGuiData * dta)
{
    data = dta;
}


hGuiData * hWidget::getData(void)
{
    return data;
}

//--------------------------------------------------------------

