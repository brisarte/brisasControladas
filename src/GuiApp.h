#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class GuiApp: public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	ofxKinect kinect;
	void startKinect();
	
    ofxImGui::Gui gui;

    GLuint kinectGLuintRGB;
    GLuint kinectGLuintDepth;

    bool kinectLigado;
    bool mirrorKinect;
    ofxCvColorImage kinectRGB;
    ofxCvGrayscaleImage kinectDepth;

    bool ativaBrisa1;

};