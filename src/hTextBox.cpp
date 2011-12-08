
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

#include "hTextBox.h"
#include "hLabel.h"
#include "hGui.h"
#include "hEvents.h"

using namespace std;

//--------------------------------------------------------------

hTextBox::hTextBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, string s)
	: hWidget(name, parent, dispMode, xx, yy, width, hGui::getInstance()->buttonHeight)
{
	data->type = "text_box";
    hGui * gui = hGui::getInstance();

	data->label = s;

	textWidth  = gui->font->stringWidth(s);
	h = gui->textHeight+5;

    clearFlag = false;
	data->selectable = true;
    editable = true;
    linkedLabel = NULL;
}

//--------------------------------------------------------------

void hTextBox::clearLabel()
{
    data->label.clear();
}

void hTextBox::setLabel(string s)
// lastChar needed for spacial processing
// f.e. OF bug by displaying spaces
{
    hGui * gui = hGui::getInstance();

    int width = gui->font->stringWidth(s);

    //OF bug hacking : (in case the last character is a space)
    if(s.size() > 0) {
        char lastChar = s[s.length()-1]; // get last char

        if(lastChar == 32) {
            string s2 = s.substr(0, s.length() - 1); // make copy of string without last char.
            s2 += '_'; // add underscore (seems to have the same size as space)
            width = gui->font->stringWidth(s2); // recalculates width of the copied string
        } // don't affect the real string
    }

//062 if(width < (w+1)) {
    if(width < (w-2)) {
        textWidth = width;
        data->label = s;
   }
}

string hTextBox::getLabel(void)
{
    return data->label;
}

void hTextBox::setLinkedLabel(hLabel * labelWidget)
{
	linkedLabel  = labelWidget;
}

void hTextBox::clearAfterReturn(bool flag)
{
    clearFlag = flag;
}

void hTextBox::sendOnLoosingFocus(bool flag)
{
    focusSendFlag = flag;
}

//--------------------------------------------------------------

void hTextBox::setMessage(string s)
{
	data->message = s;
}

void hTextBox::bang(void)
{
	if(data->message.size() > 0)
        hEvents::getInstance()->sendEvent(data->message, data->label);
}

//--------------------------------------------------------------

void hTextBox::draw()
{
    hGui * gui = hGui::getInstance();
	
    hSetHexColor(gui->editBackColor);
    hPaintRect(x, y, w, h);
	
    hWidget::draw();
	
    if(data->label.size() > 0) { // draw text
        hSetHexColor(gui->editTextColor);
        hDrawString(gui->font, data->label, x+3, y+gui->textHeight);
    }
	
    hSetHexColor(gui->caretColor);
	
    if(data->selected) { // draw caret
        if(data->label.size() > 0) {
#if OF_VERSION < 7
			hLine(x+textWidth+0, y+2, x+textWidth+0, y+gui->textHeight+2);
#else
			hLine(x+textWidth+5, y+2, x+textWidth+5, y+gui->textHeight+2);
#endif
        }
        else hLine(x+2,           y+2, x+2          , y+gui->textHeight+2);
    }
}

//--------------------------------------------------------------

void hTextBox::keyPressed(int key)
{
    string s = data->label;

    if((key == 10) ||  (key == 13)){ // RETURN
        if(linkedLabel != NULL)
            linkedLabel->setLabel(s);
        bang();
        if(clearFlag == true) clearLabel();
    }
    else if((key == 8) || (key == 127)) { // BACKSPACE
        if(s.size() > 0)
            setLabel(s.substr(0, s.length() - 1));
    }
    else if((key >= 32) && (key <= 255)) { // NORMAL KEY
        s += (char)key;
        setLabel(s);
    }
    // cout << key << endl;
}

//--------------------------------------------------------------

void hTextBox::mousePressed(int xx, int yy, int btn)
{
    setSelected(true);
}

//--------------------------------------------------------------
