#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"

class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void onDropdownVideoEvent(ofxDatGuiDropdownEvent e);
	void onDropdownShaderVideoEvent(ofxDatGuiDropdownEvent e);
	void onDropdownFonteKinectEvent(ofxDatGuiDropdownEvent e);
	void onDropdownShaderKinectEvent(ofxDatGuiDropdownEvent e);
	void onDropdownFiltroKinectEvent(ofxDatGuiDropdownEvent e);

	void onBGColorPickerEvent(ofxDatGuiColorPickerEvent e);
	void onVideoChange(ofxDatGuiTextInputEvent e);
	
	void startKinect(ofxDatGuiButtonEvent e);
	void closeKinect(ofxDatGuiButtonEvent e);
	void startBrisaKinect(ofxDatGuiButtonEvent e);
	void drawKinect();

	void addControles(ofxDatGui* g, int iBrisa);

	// Controles
	ofxDatGuiColorPicker* colorPicker;

	// variáveis lidas pelo App
	ofColor bgColor;

	string videoPath;
	vector<string> videosDisponiveis;

	int shaderVideoSelected, shaderKinectSelected, fonteKinectSelected, filtroKinectSelected;
};