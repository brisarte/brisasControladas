#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Brisas/Brisa.h"

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void startKinect();
    
    ofxImGui::Gui gui;

    vector<Brisa*> brisas;

    GLuint btnCriaVideo,btnCriaPoligono,btnCriaKinect;
};