#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"

class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void onDropdownShaderEvent(ofxDatGuiDropdownEvent e);
	void onBGColorPickerEvent(ofxDatGuiColorPickerEvent e);
	void onVideoChange(ofxDatGuiTextInputEvent e);
	
	void startKinect(ofxDatGuiButtonEvent e);
	void closeKinect(ofxDatGuiButtonEvent e);
	void startBrisaKinect(ofxDatGuiButtonEvent e);

	ofxDatGuiColorPicker* colorPicker;
	ofColor bgColor;

	string videoPath;

	int shaderSelected;
};