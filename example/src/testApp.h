#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "hEvents.h"
// The event system used by hGui
// Can also be used to create new events and listeners

#include "hObject.h"
// Base object that contain virtual functions
// Objects that inherit from hObject can use its event listeners for free

class testApp : public ofBaseApp, public hObject {
	public:
		void setup();
		void update();
		void exit();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

// Variables used by the widgets (linked to them) :
	bool drawFlag;

	int red, green, blue;

	float xPct, yPct;

	int curTime;

// Other objects:

	ofTrueTypeFont * font;
	std::string myString;

	// Methods called by the event listeners:
// (must have the same names, parameters and return value than the methods defined in "hObject.h")

	void start(void);
	void stop(void);
	void clear(void);

	void setValue(double val);
	void setValueToItem(double val, int index);
	void setXY(double x, double y);

	void selectItem(int item);
    void itemSetSelected(int item, bool flag);

	void setLabel(std::string label);

	void setText(std::string text);
	void addText(std::string text);
	void clearText(void);

	void openItem(int index);
	void answerDialog(int buttonID);

	// Custom listener:
    void setColors(hEventArgs& args);

	// GUI color customization example:
	void setDarkColors(void);
};

#endif
