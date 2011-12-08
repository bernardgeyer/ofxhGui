
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

#ifndef _HGUI
#define _HGUI

#include "ofTrueTypeFont.h"
#include "hEvents.h"
#include <map>

class hWidget;
class h2DSlider;
class hAlert;
class hButton;
class hButtonBox;
class hCheckBox;
class hCounterLabel;
class hDialog;
class hLabel;
class hListBox;
class hMessageBox;
class hNumberBox;
class hPanel;
class hSlider;
class hSliderBox;
class hStatusBar;
class hTabBox;
class hTextArea;
class hTextBox;

class ofxXmlSettings;

// ---------------------------------------------------------------

class hGui : public hObject
// singleton class hGui
{
 private:
	static hGui * _gui;

	// Private constructor / destructor :

    hGui()  {}
	~hGui() {}

public :
	// Public constructor :
	static hGui * getInstance() {
        if(_gui == 0) {
			_gui = new hGui;
        }
        return _gui;
    }

    void setup(std::string fnt, int size);

	void setRootWidget(hWidget * root); 
	// The root widget is the first widget to be processed by the gui engine
	// It holds pointers to all other widgets 
	// It can be a hPanel or a hTabBox

	hWidget *  getRootWidget(void); 

	// ---------------------------------------------------------------

	// Add different kind of widgets to the gui
	// Uses the same parameters than the direct creation of the widgets with the 'new' operator
	// excepted for addStatusBar
	
	// Permits also to save the state of certain widgets by storing them in a table available by the xml file i/o routines
	
	h2DSlider *  add2DSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size);
	hAlert *  addAlert(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
	hButton *  addButton(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);
	hButtonBox *  addButtonBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int item_width, int item_height);
	hCheckBox *  addCheckBox(std::string name, hPanel * parent, int dispMode, int xx, int yy);
	hCounterLabel *  addCounterLabel(std::string name, hPanel * parent, int dispMode, int xx, int yy, std::string s);
	hDialog *  addDialog(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
	hLabel *  addLabel(std::string name, hPanel * parent, int dispMode, int xx, int yy, std::string s);
	hListBox *  addListBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	hMessageBox *  addMessageBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
	hNumberBox *  addNumberBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);
	hPanel *  addPanel(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height, bool hasBorder);
	hSlider *  addSlider(std::string name, hPanel * parent, int dispMode, int xx, int yy, int size);
	hSliderBox *  addSliderBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	hStatusBar *  addStatusBar(std::string name, hPanel * parent, std::string s);
	hTabBox *  addTabBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width);
	hTextArea *  addTextArea(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, int height);
	hTextBox *  addTextBox(std::string name, hPanel * parent, int dispMode, int xx, int yy, int width, std::string s);
	
	// ---------------------------------------------------------------

	// Let our gui engine respond to draw, keyPressed, mousePressed, mouseDragged and mouseReleased events
	// Alternative: instead of using gui->addListeners() one can also call gui->draw(), gui->keyPressed() (etc...)
	// in the draw(), keyPressed() (etc...) methods

	void addListeners(void);
	void removeListeners(void);
	
	// ---------------------------------------------------------------

	// Load/Save state from/to xml file
	
	void loadSettings(std::string path);
	void saveSettings(std::string path);
	
	// The following widgets can actually be saved:
	// hCheckBox hNumberBox hSlider h2DSlider hListBox hButton_box
	// and the individual sliders of a sliderBox

	// ---------------------------------------------------------------

	// Show/Hide the GUI (can f.e. be implemented with a key shortcut)
	
	void show(void);
	void hide(void);
	
	// ---------------------------------------------------------------
	
    void setDefaultFont(std::string fnt, int size);
	// Set default font. Called when the GUI engine is created
	
    void setCounterFont(std::string cfnt, int csize);
	// hCounterLabel widgets use a special font called counter font
	// if a counter font is set, the counter uses it instead of the default font

	void setAlertFont(std::string afnt, int asize);
	// Alerts use a special font called counter font
	// if a counter font is set, the counter uses it instead of the default font

    void setFixedFont(std::string ffnt, int fsize, int fshrk);
	// hTextArea need a fixed size font to work correctly (to be set before any text area creation) :
	// fshrk = shrink factor: text editing looks better with smaller space between characters
	
	// ---------------------------------------------------------------
	
	// Color customization of the GUI
	
	void setBackgroundColor		(int backgroundColor);
	void setBorderColor			(int borderColor);
	void setFillColor			(int fillColor);
	void setAltFillColor		(int altFillColor);
	void setButtonShadowColor	(int buttonShadowColor);
	
	void setScrollHandleColor	(int scrollHandleColor);
	void setScrollButtonColor	(int scrollButtonColor);
	void setTextColor			(int textColor);
	void setTextColor2			(int textColor2);
	void setAlertTextColor		(int alertTextColor);
	
	void setDisableColor		(int disableColor);
	void setEditTextColor		(int editTextColor);
	void setEditTextColor2		(int editTextColor2);
	void setEditBackColor		(int editBackColor);
	void setCaretColor			(int caretColor);
	
	void setLabelSelColor		(int labelSelColor);
	void setItemSelColor		(int itemSelColor);
	void setItemSelTextColor	(int itemSelTextColor);
	void setTabBoxSelColor		(int tabBoxSelColor);
	void setButtonBoxSelColor	(int buttonBoxSelColor);
	
	void setCheckBoxColor		(int checkBoxColor);
	void setSliderColor			(int sliderColor);
	void setTwoDSliderColor		(int twoDSliderColor);
	void setCounterColor		(int counterColor);
	
	void setDialogColor			(int dialogColor);
	void setMessageBoxColor		(int messageBoxColor);
	void setAlertColor			(int alertColor);
	
	void setDefaultColors(void);
	// Reset the GUI to the default colors
	
	//--------------------------------------------------------
	
	// Methods called by event listeners:
	
    void draw(void);
	void draw(ofEventArgs & args);
	
    void keyPressed(int key);
	void keyPressed(ofKeyEventArgs & args);
	
    void mousePressed(int xx, int yy, int btn);
	void mousePressed(ofMouseEventArgs & args);
	
    void mouseReleased(int xx, int yy, int btn);
	void mouseReleased(ofMouseEventArgs & args);
	
    void mouseDragged(int xx, int yy, int btn);
	void mouseDragged(ofMouseEventArgs & args);
	
	//--------------------------------------------------------
	
	// Helper methods and tests:
	//  (Helper methods should not be called directly)
	
	void addWidget(hWidget * widget); 
	void removeWidget(hWidget * widget); 
	void listWidgets(void); 
	
	// -----------------------------------------------
	
	std::vector<hWidget*> widgets; // <- the pointers of all existing widgets are stored here
	hWidget * rootWidget;
	bool visible;
    
	int backgroundColor;
    int borderColor;
    int fillColor;
    int altFillColor;
    int buttonShadowColor;
    int scrollHandleColor;
    int scrollButtonColor;
    int textColor;
    int textColor2;
    int disableColor;
    int editTextColor;
    int editTextColor2;
    int alertTextColor;
    int editBackColor;
    int caretColor;

    int labelSelColor;
    int itemSelColor;
    int itemSelTextColor;
    int tabBoxSelColor;
    int buttonBoxSelColor;

    int checkBoxColor;
    int sliderColor;
    int twoDSliderColor;
    int counterColor;

    int dialogColor;
    int messageBoxColor;
    int alertColor;

    int tabHeight;
    int buttonHeight;
    int squareButtonSize;

    int checkBoxSize;
    int sliderSize;
    int sliderBoxStep;

    int scrollBarSize;
    int scrollHandleHeight;
    int scrollButtonHeight;

    int numberBoxWidth;
    int numberBoxWidth2;
	int fnumberBoxWidth;

    int margin1;
    int margin2;
    int margin3;
	
    int defListBoxWidth;
    int defButtonWidth;

    ofTrueTypeFont *font, *cfont, *afont, *ffont;
    int textHeight, ctextHeight, atextHeight, ftextHeight, fcharWidth, fshrink;

	ofxXmlSettings * xml;

    bool verbose;
};

#endif // HGUI
