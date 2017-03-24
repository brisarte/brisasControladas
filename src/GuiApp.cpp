#include "GuiApp.h"

void GuiApp::setup(){

    gui.setup();
    
    ImGui::GetIO().MouseDrawCursor = false;

    kinectLigado = false;
	mirrorKinect = false;

	kinectRGB.allocate(640,480);
	kinectDepth.allocate(640,480);

	ativaBrisa1 = false;
}

void GuiApp::update(){

/*
	if(kinectLigado) {
		kinect.update();

		kinectRGB = kinect.getPixels();
		kinectDepth = kinect.getDepthPixels();

		// Testa se deve espelhar a fonte do Kinect
		if(mirrorKinect) {
			kinectDepth.mirror(false,true);
			kinectRGB.mirror(false,true);

        	kinectRGB.flagImageChanged();
        	kinectDepth.flagImageChanged();
		}

    	kinectGLuintRGB = gui.loadPixels(kinectRGB.getPixels());
    	kinectGLuintDepth = gui.loadPixels(kinectDepth.getPixels());

	}*/
}

void GuiApp::draw(){

	ofBackground(0,0,0);

	gui.begin();

    // Kinect cams
    {   
    	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  
  
        if(ImGui::Button("Câmeras Kinect"))
        {
            startKinect();
        }
        if(ImGui::Button("Espelhar Kinect"))
        {
        	mirrorKinect = !mirrorKinect;
        }
    	
    	bool btnPressedKinRGB = ImGui::ImageButton((ImTextureID)(uintptr_t)kinectGLuintRGB, ImVec2(200, 150));
    	bool btnPressedKinDepth = ImGui::ImageButton((ImTextureID)(uintptr_t)kinectGLuintDepth, ImVec2(200, 150));
    }

	gui.end();
}

void GuiApp::startKinect() {
	
}