
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

#include "hGui_all.h"

#include "ofUtils.h"
#include "ofxXmlSettings.h"

hGui * hGui::_gui =  0;
// Singleton initialization

void hGui::setup(std::string fnt,  int size)
{
	rootWidget = NULL;

	setDefaultColors();

	// -------------------------------------

    tabHeight        = 21;
    buttonHeight     = 21;
    squareButtonSize = 26;
    checkBoxSize    = 15;
    sliderSize      = 15;
    sliderBoxStep   = 28;
    scrollBarSize   = 15;
    scrollHandleHeight = 7;
    scrollButtonHeight = 15;

	// -------------------------------------

    numberBoxWidth  = 30;
    numberBoxWidth2 = 23;
	fnumberBoxWidth = 48;

    margin1			= 10;
    margin2			= 7;
    margin3			= 4;

    defListBoxWidth = 130;
    defButtonWidth  = 130;

// -------------------------------------

	// Set default font everywhere
	// Fonts needed for special widgets have to be defined later
	setDefaultFont(fnt, size);
    setCounterFont(fnt, size);
    setAlertFont (fnt, size);
    setFixedFont (fnt, size, 0);

	// -------------------------------------

	// Create the xml object
	xml = new ofxXmlSettings();

	// -------------------------------------

	visible = true; // visible by default
}

// ---------------------------------------------------------------
//						LINK WIDGETS TO THE GUI ENGINE
// ---------------------------------------------------------------

void hGui::setRootWidget(hWidget * root)
// Actual way to link the interface to the GUI engine
{
	rootWidget = root;
}

hWidget * hGui::getRootWidget(void)
{
	return rootWidget;
}

// ---------------------------------------------------------------
//					ADD DIFFERENT KIND OF WIDGETS
// ---------------------------------------------------------------

h2DSlider * hGui::add2DSlider(std::string name, hPanel * parent, int dispMode, int x, int y, int size)
{ h2DSlider * wp =  new h2DSlider(name, parent, dispMode, x, y, size); addWidget(wp); return wp; }

hAlert *  hGui::addAlert(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height)
{ hAlert * wp =  new hAlert(name, parent, dispMode, x, y, width, height);  addWidget(wp); return wp; }

hButton *  hGui::addButton(std::string name, hPanel * parent, int dispMode, int x, int y, int width, std::string s)
{ hButton * wp =  new hButton(name, parent, dispMode, x, y, width, s);  addWidget(wp); return wp; }

hButtonBox *  hGui::addButtonBox(std::string name, hPanel * parent, int dispMode, int x, int y, int item_width, int item_height)
{ hButtonBox * wp =  new hButtonBox(name, parent, dispMode, x, y, item_width, item_height);  addWidget(wp); return wp; }

hCheckBox *  hGui::addCheckBox(std::string name, hPanel * parent, int dispMode, int x, int y)
{ hCheckBox * wp =  new hCheckBox(name, parent, dispMode, x, y);  addWidget(wp); return wp; }

hCounterLabel *  hGui::addCounterLabel(std::string name, hPanel * parent, int dispMode, int x, int y, std::string s)
{ hCounterLabel * wp =  new hCounterLabel(name, parent, dispMode, x, y, s);  addWidget(wp); return wp; }

hDialog *  hGui::addDialog(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height)
{ hDialog * wp =  new hDialog(name, parent, dispMode, x, y, width, height);  addWidget(wp); return wp; }

hLabel *  hGui::addLabel(std::string name, hPanel * parent, int dispMode, int x, int y, std::string s)
{ hLabel * wp =  new hLabel(name, parent, dispMode, x, y, s);  addWidget(wp); return wp; }

hListBox *  hGui::addListBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
{ hListBox * wp =  new hListBox(name, parent, dispMode, x, y, width);  addWidget(wp); return wp; }

hMessageBox *  hGui::addMessageBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height)
{ hMessageBox * wp =  new hMessageBox(name, parent, dispMode, x, y, width, height);  addWidget(wp); return wp; }

hNumberBox *  hGui::addNumberBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width, std::string s)
{ hNumberBox * wp =  new hNumberBox(name, parent, dispMode, x, y, width, s);  addWidget(wp); return wp; }

hPanel *  hGui::addPanel(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height, bool hasBorder)
{ hPanel * wp =  new hPanel(name, parent, dispMode, x, y, width, height, hasBorder);  addWidget(wp); return wp; }

hSlider *  hGui::addSlider(std::string name, hPanel * parent, int dispMode, int x, int y, int size)
{ hSlider * wp =  new hSlider(name, parent, dispMode, x, y, size);  addWidget(wp); return wp; }

hSliderBox *  hGui::addSliderBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
{ hSliderBox * wp =  new hSliderBox(name, parent, dispMode, x, y, width);  addWidget(wp); return wp; }

hStatusBar *  hGui::addStatusBar(std::string name, hPanel * parent, std::string s)
{ hStatusBar * wp =  new hStatusBar(name, parent, 0, 0, 0, s);  addWidget(wp); return wp; }

hTabBox *  hGui::addTabBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width)
{ hTabBox * wp =  new hTabBox(name, parent, dispMode, x, y, width);  addWidget(wp); return wp; }

hTextArea *  hGui::addTextArea(std::string name, hPanel * parent, int dispMode, int x, int y, int width, int height)
{ hTextArea * wp =  new hTextArea(name, parent, dispMode, x, y, width, height);  addWidget(wp); return wp; }

hTextBox * hGui::addTextBox(std::string name, hPanel * parent, int dispMode, int x, int y, int width, std::string s)
{ hTextBox * wp =  new hTextBox(name, parent, dispMode, x, y, width, s);  addWidget(wp); return wp; }

// ---------------------------------------------------------------
//							ADD/REMOVE LISTENERS
// ---------------------------------------------------------------

void hGui::addListeners(void)
{
	ofAddListener(ofEvents.draw, this, &hGui::draw);
	ofAddListener(ofEvents.keyPressed, this, &hGui::keyPressed);

	ofAddListener(ofEvents.mousePressed, this, &hGui::mousePressed);
	ofAddListener(ofEvents.mouseDragged, this, &hGui::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &hGui::mouseReleased);
}

void hGui::removeListeners(void)
{
	ofRemoveListener(ofEvents.draw, this, &hGui::draw);
	ofRemoveListener(ofEvents.keyPressed, this, &hGui::keyPressed);

	ofRemoveListener(ofEvents.mousePressed, this, &hGui::mousePressed);
	ofRemoveListener(ofEvents.mouseDragged, this, &hGui::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &hGui::mouseReleased);
}

// ---------------------------------------------------------------
//                          LOAD FROM XML/SAVE TO XML
// ---------------------------------------------------------------

void hGui::loadSettings(std::string path)
{
	hEvents * events = hEvents::getInstance();

	bool loaded = xml->loadFile(path);
	// cout << "xml loaded = " << loaded << endl;
	if(loaded == false) return;

	int numTags;
	string widgetName, boolSymbol, message;
	double widgetValue, widgetValue2;

	numTags = xml->getNumTags("gui_settings");
	// cout << "gui_settings tags: " << numTags << endl;

	if(numTags > 0) {
		xml->pushTag("gui_settings", numTags-1);

		numTags = xml->getNumTags("check_box");
		// cout << "check_box tags: " << numTags << endl;
		if(numTags > 0) {
			for(int i = 0; i < numTags; i++){
				widgetName = xml->getValue("check_box:name", "", i);
				boolSymbol = xml->getValue("check_box:selected", "", i);

				if(boolSymbol == "true") {
					message = widgetName + "." + "select";
					events->sendEvent(message);
				}
				else if(boolSymbol == "false") {
					message = widgetName + "." + "unselect";
					events->sendEvent(message);
				}
			}
		}

		numTags = xml->getNumTags("number_box");
			// cout << "number_box tags: " << numTags << endl;
			if(numTags > 0) {
				for(int i = 0; i < numTags; i++){
					widgetName = xml->getValue("number_box:name",  "", i);
					widgetValue = xml->getValue("number_box:value", 0.0, i);

					message = widgetName + "." + "setValue";
					events->sendEvent(message, widgetValue);
				}
			}

			numTags = xml->getNumTags("slider");
			// cout << "slider tags: " << numTags << endl;
			if(numTags > 0) {
				for(int i = 0; i < numTags; i++){
					widgetName = xml->getValue("slider:name",  "", i);
					widgetValue = xml->getValue("slider:value", 0.0, i);

					message = widgetName + "." + "setValue";
					events->sendEvent(message, widgetValue);
				}
			}

			numTags = xml->getNumTags("slider2D");
			// cout << "slider2D tags: " << numTags << endl;
			if(numTags > 0) {
				for(int i = 0; i < numTags; i++){
					widgetName = xml->getValue("slider2D:name", "", i);
					widgetValue  = xml->getValue("slider2D:x", 0.0, i);
					widgetValue2 = xml->getValue("slider2D:y", 0.0, i);

					message = widgetName + "." + "setXY";
					events->sendEvent(message, widgetValue, widgetValue2);
				}
			}

			numTags = xml->getNumTags("list_box");
			// cout << "list_box tags: " << numTags << endl;
			if(numTags > 0) {
				for(int i = 0; i < numTags; i++){
					widgetName = xml->getValue("list_box:name",  "", i);
					widgetValue = xml->getValue("list_box:selection", 0, i);

					message = widgetName + "." + "selectElement";
					events->sendEvent(message, widgetValue);
					// cout << message << " " << widgetValue  << endl;
				}
			}

			numTags = xml->getNumTags("button_box");
			// cout << "button_box tags: " << numTags << endl;
			if(numTags > 0) {
				for(int i = 0; i < numTags; i++){
					widgetName = xml->getValue("button_box:name",  "", i);
					widgetValue = xml->getValue("button_box:selection", 0, i);

					message = widgetName + "." + "selectItem";
					events->sendEvent(message, widgetValue);
				}
			}

		xml->popTag();
	}
}

void hGui::saveSettings(std::string path)
{
	int size = widgets.size();
	if(size > 0) {
		xml->clear();

		int tag = xml->addTag("gui_settings");
		xml->pushTag("gui_settings", tag);

		for(int i = 0; i < size; ++i)
			widgets[i]->saveSettings(xml);

		xml->popTag();

		xml->saveFile(path);
	}
}

// ---------------------------------------------------------------
//							SHOW/HIDE THE GUI
// ---------------------------------------------------------------

void hGui::show(void)
{
	visible = true;
}

void hGui::hide(void)
{
	visible = false;
}

// ---------------------------------------------------------------
//                          SET/MODIFY A FONT
//                          Warning: font must be a valid font
//                             else the system can crash!!!!!
// ---------------------------------------------------------------

// no prefix  means default font (used for the most widgets)
// prefix 'c' means counter font (used for displaying counters)
// prefix 'a' means alert font (used for displaying alerts / generally big fonts)
// prefix 'f' means fixed font (used for text editing)
// fshrink factor: text editing looks better with smaller space between characters


void hGui::setDefaultFont(std::string fnt, int size)
{
    if(fnt.size() > 0) {
        font = new ofTrueTypeFont;
        font->loadFont(fnt, size, true, true);
        textHeight = font->getLineHeight();
    }
}

void hGui::setCounterFont(std::string cfnt, int csize)
{
    if(cfnt.size() > 0) {
        cfont = new ofTrueTypeFont;
        cfont->loadFont(cfnt, csize, true, true);
        ctextHeight = cfont->getLineHeight();
    }
}

void hGui::setAlertFont(std::string afnt, int asize)
{
    if(afnt.size() > 0) {
        afont = new ofTrueTypeFont;
        afont->loadFont(afnt, asize, true, true);
        atextHeight = afont->getLineHeight();
    }
}

void hGui::setFixedFont(std::string ffnt, int fsize, int fshrk)
{
    if(ffnt.size() > 0) {
        fshrink = fshrk;
        ffont = new ofTrueTypeFont;
        ffont->loadFont(ffnt, fsize, true, true);
        ftextHeight = ffont->getLineHeight();
        fcharWidth  = ffont->stringWidth("0") - fshrink;
    }
}

// ---------------------------------------------------------------
//                          SET/MODIFY A COLOR
// ---------------------------------------------------------------

void hGui::setBackgroundColor	(int backgroundColor)	{this->backgroundColor = backgroundColor;}
void hGui::setBorderColor		(int borderColor)		{this->borderColor		= borderColor;}
void hGui::setFillColor			(int fillColor)			{this->fillColor		= fillColor;}
void hGui::setAltFillColor		(int altFillColor)		{this->altFillColor		= altFillColor;}
void hGui::setButtonShadowColor	(int buttonShadowColor)	{this->buttonShadowColor= buttonShadowColor;}

void hGui::setScrollHandleColor	(int scrollHandleColor)	{this->scrollHandleColor= scrollHandleColor;}
void hGui::setScrollButtonColor	(int scrollButtonColor)	{this->scrollButtonColor= scrollButtonColor;}
void hGui::setTextColor			(int textColor)			{this->textColor		= textColor;}
void hGui::setTextColor2		(int textColor2)		{this->textColor2		= textColor2;}
void hGui::setAlertTextColor	(int alertTextColor)	{this->alertTextColor	= alertTextColor;}

void hGui::setDisableColor		(int disableColor)		{this->disableColor		= disableColor;}
void hGui::setEditTextColor		(int editTextColor)		{this->editTextColor	= editTextColor;}
void hGui::setEditTextColor2	(int editTextColor2)	{this->editTextColor2	= editTextColor2;}
void hGui::setEditBackColor		(int editBackColor)		{this->editBackColor	= editBackColor;}
void hGui::setCaretColor		(int caretColor)		{this->caretColor		= caretColor;}

void hGui::setLabelSelColor		(int labelSelColor)		{this->labelSelColor	= labelSelColor;}
void hGui::setItemSelColor		(int itemSelColor)		{this->itemSelColor		= itemSelColor;}
void hGui::setItemSelTextColor	(int itemSelTextColor)	{this->itemSelTextColor	= itemSelTextColor;}
void hGui::setTabBoxSelColor	(int tabBoxSelColor)	{this->tabBoxSelColor	= tabBoxSelColor;}
void hGui::setButtonBoxSelColor	(int buttonBoxSelColor)	{this->buttonBoxSelColor= buttonBoxSelColor;}

void hGui::setCheckBoxColor		(int checkBoxColor)		{this->checkBoxColor	= checkBoxColor;}
void hGui::setSliderColor		(int sliderColor)		{this->sliderColor		= sliderColor;}
void hGui::setTwoDSliderColor	(int twoDSliderColor)	{this->twoDSliderColor	= twoDSliderColor;}
void hGui::setCounterColor		(int counterColor)		{this->counterColor		= counterColor;}

void hGui::setDialogColor		(int dialogColor)		{this->dialogColor		= dialogColor;}
void hGui::setMessageBoxColor	(int messageBoxColor)	{this->messageBoxColor	= messageBoxColor;}
void hGui::setAlertColor		(int alertColor)		{this->alertColor		= alertColor;}

void hGui::setDefaultColors(void)
{
	setBackgroundColor	(0xFFFFFF);
	setBorderColor		(0x000000);
	setFillColor		(0xE5E5E5);
	setAltFillColor		(0xDDFFEE);
	setButtonShadowColor(0xAAAAAA);

	setScrollHandleColor(0xAAAAAA);
	setScrollButtonColor(0x333333);
	setTextColor		(0x000000);
	setTextColor2		(0xFFFFFF);
	setAlertTextColor	(0x111111);

	setDisableColor		(0x999999);
	setEditTextColor	(0x113388);
	setEditTextColor2	(0x113388);
	setEditBackColor	(0xDDEEFF);
	setCaretColor		(0x000000);

	setLabelSelColor	(0x0077FF);
	setItemSelColor		(0xAAAAAA);
	setItemSelTextColor	(0x000000);
	setTabBoxSelColor	(0x77AAFF);
	setButtonBoxSelColor(0x77FFAA);

	setCheckBoxColor	(0x77FFAA);
	setSliderColor		(0xAAAAAA);
	setTwoDSliderColor	(0x33BB66);
	setCounterColor		(0x33BB66);

	setDialogColor		(0xE5E5E5);
	setMessageBoxColor	(0x77FFAA);
	setAlertColor		(0xFF7777);
}

// ---------------------------------------------------------------
//							ANSWER TO LISTENERS
// ---------------------------------------------------------------

void hGui::draw(void)
{
	if(visible == false) return;

    if(rootWidget != NULL) {
		ofPushStyle();
			rootWidget->draw();
		ofPopStyle();
	}
}

void hGui::draw(ofEventArgs & args)
{
	draw();
}

// ---------------------------------------------------------------

void hGui::keyPressed(int key)
{
	if(visible == false) return;

    hWidget * textObj = hPanel::getSelectedTextObj();

    if(textObj != NULL) {
        hTextArea * textArea = dynamic_cast<hTextArea *>(textObj);
        if(textArea != NULL) {
            // cout << "textArea" << endl;
            textArea->keyPressed(key);
        }
        else {
            hTextBox * textBox = dynamic_cast<hTextBox *>(textObj);
            if(textBox != NULL) {
                // cout << "textBox" << endl;
                textBox->keyPressed(key);
            }
        }
    }
}

void hGui::keyPressed(ofKeyEventArgs & args){
	keyPressed(args.key);
}

// ---------------------------------------------------------------

void hGui::mousePressed(int xx, int yy, int btn)
{
	if(visible == false) return;

    // cout << "hGui::mousePressed" << endl;

    if(rootWidget != NULL)
        rootWidget->mousePressed(xx, yy, btn);
}

void hGui::mousePressed(ofMouseEventArgs & args){
	mousePressed(args.x, args.y, args.button);
}

// ---------------------------------------------------------------

void hGui::mouseReleased(int xx, int yy, int btn)
{
	if(visible == false) return;

    if(rootWidget != NULL)
        rootWidget->mouseReleased(xx, yy, btn);
}

void hGui::mouseReleased(ofMouseEventArgs & args){
	mouseReleased(args.x, args.y, args.button);
}

// ---------------------------------------------------------------

void hGui::mouseDragged(int xx, int yy, int btn)
{
	if(visible == false) return;

    if(rootWidget != NULL)
        rootWidget->mouseDragged(xx, yy, btn);
}

void hGui::mouseDragged(ofMouseEventArgs & args){
	mouseDragged(args.x, args.y, args.button);
}


// ---------------------------------------------------------------
//									HELPER FUNCTIONS
// ---------------------------------------------------------------

void hGui::addWidget(hWidget * widget)
// add a widget to the list of all widgets
// called when a new widget is created
{
	// cout << "add widget " << widget->getData()->name << " at position #" << widgets.size() << endl;
	widgets.push_back(widget);
}

void hGui::removeWidget(hWidget * widget)
// remove a widget from the list of all widgets
// called before a widget is deleted
{
	int size = widgets.size();
	for(int i=0; i < size; ++i) {
		if(widgets[i] == widget) {
			// cout << "removing widget at position #" << i << endl;
			widgets.erase (widgets.begin()+i);
			return;
		}
	}
}

// ---------------------------------------------------------------
//									TESTS
// ---------------------------------------------------------------

void hGui::listWidgets(void)
// display all widgets
{
	int size = widgets.size();
	for(int i=0; i < size; ++i) {
		hGuiData *data = widgets[i]->getData();
		cout << data->type << " " <<  data->name << endl;
	}
}

// ---------------------------------------------------------------

