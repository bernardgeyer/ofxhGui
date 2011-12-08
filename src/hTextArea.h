
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

#ifndef _HTEXTAREA
#define _HTEXTAREA

#include "hWidget.h"
#include <vector>

//--------------------------------------------------------

struct hLineInfo {
    bool used;
    int start;
    int end;
};

class hPanel;
class hTScrollBar;
class hScrollButton;
class hTextAreaButton;

//--------------------------------------------------------

class hTextArea: public hWidget{
public:
    hTextArea(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
// Unlike hTextBox, hTextArea widgets cannot use default text in the constructor
	
    void addTools(int width, int position, std::string sendStr, std::string clearStr);
	// void addTools(int width, int position, std::string sendStr, std::string clearStr);
	// Add a 'send' and a 'clear' button to a textedit object
	// "width" is the width of each button
	// position: 0 = center, -1 = left, 1 = right
	
	// When the send button is pushed, the message is sent (with the text as parameter)
	// When the clear button is pushed, the text is cleared
	// An additional message2 can be set to perform another action when the text is cleared
	
	void setText(std::string s);
	// Store the text of the string s  and adapt the selections and scrollbars
	
	void setText(std::string s, bool endFlag);
	// Store the text of the string s  and adapt the selections and scrollbars
	// if endFlag == true, jump to then end of the text

    void addText(std::string s);
	// Add a string to the text and adapt the selections and scrollbars

    void addText(std::string s, bool endFlag);
	// Add a string to the text and adapt the selections and scrollbars
	// if endFlag == true, jump to then end of the text

	void clearText(void);
	// Clear the text and adapt the selections and scrollbars

	void clearText(bool endFlag = true);
	// Clear the text and adapt the selections and scrollbars
	// parameter ignored here
	
	std::string getText(void);
	// enable/disable the editability of the widget
	// A text area is editable by default

    void setEditable(bool flag);
	// The textbox is editable if the flag is true (true by default)
	
	void setMessage(std::string s);
	// Set the message that will be send when the widget state change

	void setMessage2(std::string s);
	// A text area can have a second message that is sent when it is cleared

	// Send the message
	void bang(void);

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    void draw();
    void keyPressed(int key);
    void mousePressed(int xx, int yy, int btn);

	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
	void addScrollBar(void);
	// Add a scrollbar to a textedit object (automatically done)

    void updateLines(void);
	// Store the line numbers for the actual string

    void updateSelection(bool insertFlag);
	// Update the selection cursor after character insert or erase
	// insertFlag: true after insert, false after erase
	// Could eventually be used just to move the cursor <- or ->
	// but there are some bugs when used by scrolling.
	
    void jumpToEnd();
	// Jump to the end of the text
	// Usefull when data is automatically add to the textArea
	
	//--------------------------------------------------------

protected:
friend class hTScrollBar;
friend class hScrollButton;
    int charWidth, maxLines, maxChars;
    int lineNum;  // lineNum starts with 0
    int numChars; // numChars = number of chars in last line
    int startLine; // First line to display
    int lineSelection, charSelection;
    std::vector<hLineInfo> lines;

	hTScrollBar * scrollBar;
    hScrollButton * incButton, * decButton;

	hTextAreaButton * clearButton;
	hTextAreaButton * sendButton;
};

//--------------------------------------------------------
#endif // _HTEXTAREA
