#pragma once

#include "ofxDatGui.h"
#include "ofMain.h"

class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void updateControles();

	void onContornoKinectToggle(ofxDatGuiToggleEvent e);

	void onChangeTipoBrisa1(ofxDatGuiDropdownEvent e);
	void onChangeTipoBrisa2(ofxDatGuiDropdownEvent e);
	void onChangeTipoBrisa3(ofxDatGuiDropdownEvent e);
	void onChangeTipoBrisa4(ofxDatGuiDropdownEvent e);
	void onDropdownVideoEvent(ofxDatGuiDropdownEvent e);
	void onDropdownGifFullEvent(ofxDatGuiDropdownEvent e);
	void onDropdownShaderVideoEvent(ofxDatGuiDropdownEvent e);
	void onDropdownFonteKinectEvent(ofxDatGuiDropdownEvent e);
	void onDropdownShaderKinectEvent(ofxDatGuiDropdownEvent e);
	void onDropdownFiltroKinectEvent(ofxDatGuiDropdownEvent e);

	void onCoresColorPickerEvent(ofxDatGuiColorPickerEvent e);
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
	ofColor bgColor, corPrimaria, corSecundaria;

	string videoPath, pastaGif;
	vector<string> videosDisponiveis, tiposBrisa;

	vector<int> tipoBrisaFbo;

	int shaderVideoSelected, shaderKinectSelected, fonteKinectSelected, filtroKinectSelected;
	bool kinectContorno;

	vector<string> listaGifFull;
};