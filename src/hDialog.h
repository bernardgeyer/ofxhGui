
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

#ifndef _HDIALOG
#define _HDIALOG

#include "hPanel.h"

class hLabel;
class hTextArea;
class hDialogButton;

class hDialog: public hPanel{
public:
    hDialog(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);

	void setTitle(std::string s);
	// Set the text to be displayed on the top of the dialog
	
    void addCloseButton(void);
	// Add a 'close' button on the top right of the dialog
	
    void addTools(int width, int position, std::string confirmStr, std::string cancelStr);
	// Add a 'confirm' and a 'cancel' button to a dialog object
	// "width" is the width of each button
	// position: 0 = center, -1 = left, 1 = right
	
	void changeToolNames(std::string confirmStr, std::string cancelStr);
	// Modify the name of the strings used in the buttons
	// Permits for example to use alerts in different languages
	
	void setMessage(std::string s);
	// Set the message that will be send when the user push the confirm button
	
	void setMessage2(std::string s);
	// Set the message that will be send when the user push the cancel button

    void open(void);
    void close(void);
	
    bool isOpen(void);
    void moveToFront(void);

	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    void draw(void);
	
    void mousePressed(int xx, int yy, int btn);
    void mouseDragged(int xx, int yy, int btn);
	
	//--------------------------------------------------------
	
	// Helper methods:
	// Should not be called directly
	
    void checkMouseInTopBar(void);
    bool isInWindow(int xx, int yy);
	
	//--------------------------------------------------------

    int result;

protected:
    bool openFlag;

	hDialogButton * closeButton;
	hDialogButton * confirmButton;
	hDialogButton * cancelButton;

    int dialogColor;

    hTextArea * msgTextArea;
    int msgTextXStart, msgTextYStart;
    int msgTextWidth, msgTextHeight;

    hLabel * alertLabel;

    int clickedX, clickedY;       // clicked coordinates
    int clickedXpos, clickedYpos; // clicked pixel in the dialog
    int xShift, yShift;           // amount to shift the dialog
    bool inTopBar;
};

//--------------------------------------------------------
#endif // _HDIALOG
