
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

#include "hPanel.h"
#include "hGui.h"
#include "hNumberBox.h"

#include <typeinfo>
#include <iostream>
using namespace std;

//--------------------------------------------------------------

hWidget * hPanel::selectedTextObj = NULL; // static members have to be initialized on global level

hPanel::hPanel(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height, bool hasBorder)
	: hWidget(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "panel";
    visibleBorder = hasBorder;

	clickedWidget = NULL;
	selectedRadio = NULL;
//	selectedTextObj = NULL; // statically initialized

	maxX = x; 
	maxY = y;
}

//--------------------------------------------------------------

void hPanel::clearWidgets(void)
{
    widgets.clear();
}

int hPanel::getNumWidgets(void)
{
    return widgets.size();
}

int hPanel::getNumData(void)
{
    return data_buffer.size();
}

hWidget * hPanel::getLastWidget(void)
{
	int size = widgets.size();
	
	if(size > 0)
		 return widgets[size-1];
	else return NULL;
}

hWidget * hPanel::getSelectedTextObj(void)
{
    return selectedTextObj;
}

//--------------------------------------------------------------

void hPanel::addWidgetToPanel(hWidget *widget)
{
	widgets.push_back(widget);
	data_buffer.push_back(widget->getData()); // Each widget has its default data block, so remember its adress
}

//--------------------------------------------------------------

void hPanel::adaptPanelSize(int xx, int yy)
{
	int panelRight  = x + w;
	int panelBottom = y + h;
	
	int widgetRight, widgetBottom;
	
	int size = widgets.size();
	for(int i = 0; i < size; ++i) {
		hWidget *widget = widgets[i];
		widgetRight  = widget->x + widget->w;
		widgetBottom = widget->y + widget->h;
		
		if(panelRight  < widgetRight)  w = (widgetRight  - x) + xx;
		if(panelBottom < widgetBottom) h = (widgetBottom - y) + yy;
	}
}

//--------------------------------------------------------------

void hPanel::draw(void)
{
	if(visibleBorder || visibleBackground) hWidget::draw();
	
    int size = widgets.size();
    for(int i = 0; i < size; ++i)
        widgets[i]->draw();
}

//--------------------------------------------------------------

void hPanel::mousePressed(int xx, int yy, int btn)
{
    // cout << "hPanel::mousePressed" << endl;
    switch(btn) {
        case 0: {
        hWidget *widget = findWidget(xx, yy);

        if(widget != NULL) {
            // cout << "hPanel::mousePressed " << widget->getData()->index << " " << widget->getData()->ID << endl;

            // First remove last radio selection and set the new one:
            hGuiData * dataPtr = widget->getData();
            if(dataPtr->disabled == false) {
                if(dataPtr->radioEnabled) {
                    if(selectedRadio != NULL) {
                        selectedRadio->selected = false;
                    } // <- if(selectedRadio != NULL)
                    selectedRadio = dataPtr;
                } // <- radioEnabled
            } // <- widget->disabled == false

           // Remove last editing selection:
           if(selectedTextObj != NULL) {
                // cout << "selectedTextObj: " << selectedTextObj << endl;
                if(selectedTextObj->focusSendFlag == true) {
                    hNumberBox * numberBox = dynamic_cast<hNumberBox *>(selectedTextObj);
                    if(numberBox != NULL) { // numberBox ?
						double value;
						// value = ofToFloat(numberBox->data->label); // round the numerical value too
						value = atof(numberBox->data->label.c_str()); // kind of ofToDouble

                        numberBox->setValue(value, true, true);
                        numberBox->bang();
                    }
                    else { // textBox ?
                        hTextBox * textBox = dynamic_cast<hTextBox *>(selectedTextObj);
                        if(textBox != NULL) textBox->bang();
                    }
				}

                selectedTextObj->setSelected(false);
                selectedTextObj = NULL;
            }

			// Set a new editing selection if needed:
			if(widget->isEditable()) {
                selectedTextObj = widget;
            }

             // Process actual selection:
            // cout << "widget: " << widget->getData()->name << " mousePressed" << endl;
            widget->mousePressed(xx, yy, btn);
            /*
            // debug: see wich widget is pressed
            cout << widget << endl;
            */
        } // <- if(widget != NULL)

        clickedWidget = widget; // will be null if no widget found (necessary for drag)
        }
        break;
    }
}

//--------------------------------------------------------------

void hPanel::mouseReleased(int xx, int yy, int btn)
{
    // cout << "hPanel::mouseReleased" << endl;
    switch(btn) {
        case 0: {
        hWidget *widget = clickedWidget;
        if(widget != NULL) widget->mouseReleased(xx, yy, btn);
        clickedWidget = NULL; // necessary ?
        }
        break;
   }
}

//--------------------------------------------------------------

void hPanel::mouseDragged(int xx, int yy, int btn)
{
    switch(btn) {
        case 0:
        if(clickedWidget != NULL) {
            clickedWidget->mouseDragged(xx, yy, btn);
        }
        break;
   }
}

//--------------------------------------------------------
//						Helper methods:
//						Should not be called directly
//--------------------------------------------------------

void hPanel::addWidgetPtr(hWidget *widget)
{
	widgets.push_back(widget);
}

//--------------------------------------------------------------

hWidget * hPanel::findWidget(int xx, int yy)
{
	hWidget *foundWidget = NULL;
	
    int size = widgets.size();
    for(int i = size - 1; i >= 0; i--) {
        hWidget *widget = widgets[i];
		
        if(xx >= widget->x)
            if(yy >= widget->y)
                if(xx <= (widget->x + widget->w + widget->x_extension))
                    if(yy <= widget->y + widget->h) {
                        foundWidget = widget;
                        break;
                    }
	}
	
	return foundWidget;
}

int hPanel::findWidgetIndex(hWidget * widget)
{
    unsigned int  result = -1;
    int size = widgets.size();
	
    for(int i = size - 1; i >= 0; i--) {
        if(widget == widgets[i]) {
            result = i;
            break;
        }
    }
	
    return result;
}

//--------------------------------------------------------------

hWidget * hPanel::getWidgetAt(int index)
{
    return widgets[index];
}

hGuiData * hPanel::getDataAt(int index)
{
    return data_buffer[index];
}

//--------------------------------------------------------------

void hPanel::removeWidgetPtrAt(int index)
{
    widgets.erase(widgets.begin()+index);
}

void hPanel::removeDataPtrAt(int index)
{
    data_buffer.erase(data_buffer.begin()+index);
}

//--------------------------------------------------------------
