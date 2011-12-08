
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

#include "hTextArea.h"
#include "hPanel.h"
#include "hTScrollBar.h"
#include "hScrollButton.h"
#include "hTextAreaButton.h"

#include "hEvents.h"
#include "hGui.h"

using namespace std;

//--------------------------------------------------------------

hTextArea::hTextArea(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height)
	: hWidget(name, parent, dispMode, xx, yy, width, height)
{
	data->type = "text_area";
	w = width; h = height;

    hGui * gui = hGui::getInstance();

	data->label = "";

    charWidth = gui->fcharWidth;
    maxChars  = ((w-4) / charWidth);
    maxLines  = ((h-4) / gui->ftextHeight);

    // cout << "maxChars = " << maxChars << " ";
    // cout << "maxLines = " << maxLines << endl;

    startLine = 0;
    updateLines(); // important to do this already here !

    lineNum = 0;
    numChars = 0;
    lineSelection = 0;
    charSelection = 0;

	data->selectable = true;
    editable = true;

    incButton = NULL;
    decButton = NULL;
    scrollBar = NULL;

    addScrollBar();

	clearButton = NULL;
	sendButton = NULL;

	// Remove the last values of maxX and maxY
#if defined( __WIN32__ ) || defined( _WIN32 )
	addMaxXY(-(gui->scrollBarSize-1), - (gui->buttonHeight-8));
#else
	addMaxXY(-(gui->scrollBarSize-1), - (gui->buttonHeight-6));
#endif

	// Set the new values of maxX and maxY
	addMaxXY((w+gui->scrollBarSize), (h));
}

//--------------------------------------------------------------

void hTextArea::addTools(int width, int position, std::string sendStr, std::string clearStr)
{
	hGui * gui = hGui::getInstance();

    int centerX = x + (w/2);

    if(position < 0)
		sendButton = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, x, y+h-1, width+1, hTextAreaSendButtonType, sendStr);
    else if(position == 0)
		sendButton = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, centerX-width, y+h-1, width+1, hTextAreaSendButtonType, sendStr);
    else if(position > 0)
		sendButton = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, (x+w)-(width*2), y+h-1, width+1, hTextAreaSendButtonType, sendStr);

	sendButton->setLinkedTextArea(this);

    if(position < 0)
        clearButton  = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, x+width-1, y+h-1, width+1, hTextAreaClearButtonType, clearStr);
    else if(position == 0)
        clearButton  = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, centerX-1, y+h-1, width+1, hTextAreaClearButtonType, clearStr);
    else if(position > 0)
        clearButton  = new hTextAreaButton("", parentPanel, HGUI_ABSOLUTE_POSITION, (x+w)-width-1, y+h-1, width+1, hTextAreaClearButtonType, clearStr);

    clearButton->setLinkedTextArea(this);

/* NO MORE NECESSARY!
#if defined( __WIN32__ ) || defined( _WIN32 )
    sendButton->move(0, 1);  sendButton->incHeight(-1);
    clearButton->move(0, 1); clearButton->incHeight(-1);
#endif
*/
	hWidget * lastWidget = parentPanel->getLastWidget();
	if(lastWidget != NULL)
		addMaxXY(gui->scrollBarSize-lastWidget->getWidth(), gui->buttonHeight-7);
}

//--------------------------------------------------------------

void hTextArea::setText(string s)
{
	setText(s, false);
}

void hTextArea::setText(string s, bool endFlag)
{
    data->label = s;

    updateLines();

    if(endFlag == true)
		jumpToEnd();
}

//--------------------------------------------------------------

void hTextArea::addText(string s)
{
	addText(s, false);
}

void hTextArea::addText(std::string s, bool endFlag)
{
    data->label += s;

    updateLines();

    if(endFlag == true)
		jumpToEnd();
}

//--------------------------------------------------------------

void hTextArea::clearText(void)
{
	clearText(false);
}

void hTextArea::clearText(bool endFlag)
{
    data->label.clear();

    updateLines();
    updateSelection(false);
}

//--------------------------------------------------------------

string hTextArea::getText(void)
{
    return data->label;
}

void hTextArea::setEditable(bool flag)
{
    editable = flag;
}

//--------------------------------------------------------------

void hTextArea::setMessage(string s)
{
	data->message = s;
}

void hTextArea::setMessage2(std::string s)
{
    data->message2 = s;
}

void hTextArea::bang(void)
{
	if((data->message.size() > 0) && (data->label.size() > 0))
        hEvents::getInstance()->sendEvent(data->message, data->label);
        cout << "data->label: " << data->label << endl;
}

//--------------------------------------------------------------

void hTextArea::draw()
{
	hGui * gui = hGui::getInstance();

    if(editable){
        hSetHexColor(gui->editBackColor);
        hPaintRect(x, y, w, h);
    }

    hWidget::draw();

    int xPos, yPos; string s;
    int lineIndex, charIndex;
    int start_line;

	// if(data->label.size() > 0) { // draw text
	if(lines.size() > 0) { // draw text
		// when data->label.size() > 0, lines.size() is also > 0
		if(editable)
			hSetHexColor(gui->editTextColor2);
		else hSetHexColor(gui->textColor);

        start_line = startLine;
        if(start_line > (lines.size() - 1))
            start_line = lines.size() - 1;

        lineIndex = 0;
        int size = lines.size();
        for(int j = start_line; j < size; ++j) {
            charIndex = 0;
            if(lines[j].used == true) {
                int jEnd = lines[j].end;
                for(int i = lines[j].start; i <= jEnd; ++i) {
                    s = data->label[i];
                    yPos = y+(gui->ftextHeight * (lineIndex+1));
                    xPos = x+(charWidth*charIndex);
                    if((unsigned int)s[0] > 31) { // control characters (specially CR) are drawed as ||
                        hDrawString(gui->ffont, s, xPos+3, yPos);
                    }
                    /*  // we need no more to display the <return> character
					 // BUT KEEP IT SO (maybe it could be put in preferences later)
					 else {
					 hDrawString(gui->ffont, "|", xPos+3, yPos);
					 hDrawString(gui->ffont, "|", xPos+4, yPos);
					 }
					 */
                    ++charIndex;
                }
            }
            ++lineIndex;
            if(lineIndex >= maxLines) break;
		}
    }

    if(data->selected) { // draw caret
        if(lines.size() > 0) {
            hSetHexColor(gui->caretColor);
            yPos = y+(gui->ftextHeight * ((lineSelection-start_line) + 1));
            if(yPos < ((y+h)-2)) { // don't draw the caret outside
                xPos = x+(charWidth*charSelection);
                hLine(xPos+3,(yPos - gui->ftextHeight)+2, xPos+3, yPos+2);
            }
        }
		else hLine(x+0, y+2, x+0, y+gui->ftextHeight+2);
    }
}

//--------------------------------------------------------------

void hTextArea::keyPressed(int key)
{
    string s = data->label;
    int strOffset = (lines[lineSelection].start + charSelection);

    if((key == 10) ||  (key == 13)){ // RETURN
        // OLD: s += '\n';
        s.insert(strOffset,1,'\n');
		data->label = s;
        updateLines();
        updateSelection(true);
    }
    else if((key == 8) || (key == 127)) { // BACKSPACE
        if(s.size() > 0) {
            if(strOffset > 0) {

            if(charSelection == 0) {
                // correct the selection when removing <return> on the start of a line
                // -------------------------------------------------------------------
                // cout << "lineSelection = " << lineSelection << " ";
                // cout << "lineNum = " << lineNum << endl;
                if(lineSelection < lineNum) { // not needed on last line
                    // int numChars = lines[lineSelection].end - lines[lineSelection].start;
                    // cout << "numChars = " << numChars << endl;

                    // correction is only necessary if last character of previous line is <return>
                    int lastCharOffset = lines[lineSelection-1].end;
                    int lastCharOfPrevLine = data->label[lastCharOffset];
                    // cout << "last character of previous line = " << lastCharOfPrevLine << endl;

                    // Here is the correction :
                    if((lastCharOfPrevLine == 10) || (lastCharOfPrevLine == 13)) { // RETURN/ENTER
                        int numCharsInPrevLine = lines[lineSelection-1].end - lines[lineSelection-1].start;

                         --lineSelection;
                         charSelection = numCharsInPrevLine + 1;
                    }
               } // <- if(lineSelection < lineNum)
            } // <- if(charSelection == 0)

                // cout << "strOffset: " << strOffset << endl;
                // OLD: setText(s.substr(0, s.length() - 1));
                s.erase(strOffset-1, 1);
				data->label = s;
                updateLines();
                updateSelection(false);
            } // <- if(strOffset > 0)
        } // <- if(s.size() > 0)
    } // <- if((key == 8) || (key == 127))

    else if( (key >= 32) && (key <= 255) ) { // NORMAL KEY
        // OLD: s += (char)key;
        s.insert(strOffset,1,key);
		data->label = s;
        updateLines();
        updateSelection(true);
    }
}

//--------------------------------------------------------------

void hTextArea::mousePressed(int xx, int yy, int btn)
{
    // cout << "hTextArea::mousePressed" << endl;
    if(editable == false) return;

    hGui * gui = hGui::getInstance();

    setSelected(true);

    int strOffset = 0;
    int charNum   = 0;

#if OF_VERSION < 7
	int lineShift = 5;
#else
	int lineShift = 2;
#endif

#if defined( __WIN32__ ) || defined( _WIN32 )
    lineShift-=1;
#endif

    lineSelection = (((yy - y) - lineShift) / gui->ftextHeight) + startLine;

    if(lineSelection <= lineNum) {
        if(lines[lineSelection].used == true) {
            int startIndex = lines[lineSelection].start;
            int endIndex   = lines[lineSelection].end;
            // unsigned int startChar = data->label[startIndex];
            // cout << startChar << endl;
            charNum = (endIndex + 1) - startIndex;
        }

        charSelection = (xx - x) / charWidth;
        if(charSelection > charNum) charSelection = charNum;

        strOffset = lines[lineSelection].start + charSelection;
    }
    else { // we are out of the existing text
        lineSelection = lineNum;
        charSelection = numChars; // is this necessary ?

        if(data->label.size() > 0)
            strOffset = data->label.size(); // (data->label.size()-1) + 1
   }

    // cout << "charNum = " << charNum << " ";
    // cout << "charSelection = " << charSelection << " ";
    // cout << "lineSelection = " << lineSelection << " ";
    // cout << "strOffset[" << strOffset << "] = " << (unsigned int)data->label[strOffset] << endl;

    if(strOffset > 0) {
        if(charSelection > 0) {
            // skip (back) the <return> character
            unsigned int prevChar = (unsigned int)data->label[strOffset-1];
            // cout << "previous character on this line was " << prevChar << endl;

            if((prevChar == 10) || (prevChar == 13)) { // RETURN/ENTER
                --charSelection;
                // cout << "previous character on this line was <return>";
                // cout << "=> --charSelection" << endl;
           }
        }
    }
}

//--------------------------------------------------------
//					Helper methods:
//					Should not be called directly
//--------------------------------------------------------


void hTextArea::addScrollBar(void)
{
    if(parentPanel == NULL) return;

	if(scrollBar == NULL) {
        hGui * gui = hGui::getInstance();

        // Add the scrollBar widget:
	    scrollBar = new hTScrollBar("", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, (y+gui->scrollButtonHeight)-1,
									gui->scrollBarSize, (h - (gui->scrollButtonHeight*2)+1+1) );
	    scrollBar->setLinkedTextArea(this);

        // Add the dec button widget (up):
        decButton = new hScrollButton("", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, y, 0, "");
        decButton->setDirection(false);
	    decButton->setLinkedTextArea(this);

        // Add the inc button widget (down):
        incButton = new hScrollButton(
									  "", parentPanel, HGUI_ABSOLUTE_POSITION, x+w-1, ((y + h+1) - gui->scrollButtonHeight)-1, 0, "");
        incButton->setDirection(true);
	    incButton->setLinkedTextArea(this);

/* NO MORE NECESSARY!
#if defined( __WIN32__ ) || defined( _WIN32 )
        incButton->move(0, 1);
#endif
*/
    }
}

//--------------------------------------------------------------

void hTextArea::updateLines(void)
{
    lines.clear();
    lineNum = 0; numChars = 0;
    bool newLineFlag = false;

    hLineInfo lineInfo = {0, 0,0}; // dummy info on start (used=not empty, start offset, end offset)
    lines.push_back(lineInfo);

    int size = data->label.size();
    startLine = 0;
    for(int i = 0; i < size; ++i) {
        newLineFlag = false; // init

        if(numChars >= maxChars ) { // new line necessary ?
            lines.push_back(lineInfo);
            ++lineNum; numChars = 0;

            lines[lineNum].used = true;
            lines[lineNum].start = i;
            lines[lineNum].end = i;
            newLineFlag = true;
            ++numChars;
        }

        if(data->label[i] == '\n') { // CR -> new line
            lines[lineNum].used = true;
            lines[lineNum].end = i;

            lines.push_back(lineInfo);
            ++lineNum; numChars = 0;
            lines[lineNum].start = i+1; // will hold next char
            newLineFlag = true;
        }

        if(newLineFlag == false) {  // normal character
            lines[lineNum].used = true;
            lines[lineNum].end = i;
            ++numChars;
        }
    }
}

//--------------------------------------------------------------

void hTextArea::updateSelection(bool insertFlag)
{
    int strOffset = (lines[lineSelection].start + charSelection);
    if(insertFlag == true) ++strOffset; else --strOffset;

    int numlines  = lines.size();

	//    cout << "strOffset: " << strOffset << " ";
	//    cout << "numlines: " << numlines << endl;

    int line_selection = -1; // -1 means nothing (0 is already used)
    int char_selection = -1;

    for(int i = 0; i < numlines; ++i) {
        if(lines[i].used)
			//             cout << "line (used)   " << i << ": " << lines[i].start << " " << lines[i].end << endl;
			//        else cout << "line (unused) " << i << ": " << lines[i].start << " " << lines[i].end << endl;

			if(strOffset >= lines[i].start)
				if(strOffset <= lines[i].end) {
					line_selection = i;
				}
    }

    if(line_selection > -1) {
        int startOffset = lines[line_selection].start;
        char_selection =  strOffset - startOffset;
    }

    if((line_selection > -1) && (char_selection > -1)) {
        lineSelection = line_selection;
		//        cout << "line_selection is " << line_selection << endl;
        charSelection = char_selection;
		//        cout << "char_selection is " << char_selection << endl;
    }
    else { // not found means : we are at the end of the text
        lineSelection = lineNum;
        charSelection = numChars;
		//        cout << " selection = end of text" << endl;
    }

    if(lineSelection >= maxLines) // maximum line reached ->scroll
		startLine = (lineSelection + 1) - maxLines;
    else startLine = 0;

    // cout << "startLine: " << startLine << " ";
    // cout << endl;

    if(scrollBar != NULL)
        scrollBar->setPosition(startLine);
}

void hTextArea::jumpToEnd()
{
    startLine = (lineNum + 1) - maxLines;
    if(startLine < 0 )startLine = 0; // not 'very' correct, but works

    if(scrollBar != NULL)
        scrollBar->setPosition(startLine);
}

//--------------------------------------------------------------
