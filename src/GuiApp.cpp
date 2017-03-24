#include "GuiApp.h"
#include <vector>
using namespace std;
	

void GuiApp::setup(){

	brisas.push_back( new VideoBrisa() );
	brisas.push_back( new PoligonoBrisa() );
	brisas.push_back( new KinectBrisa() );

    gui.setup();
    
	btnCriaVideo = gui.loadImage("../data/img/girassol.png");
	btnCriaPoligono = gui.loadImage("../data/img/girassol.png");
	btnCriaKinect = gui.loadImage("../data/img/girassol.png");

    ImGui::GetIO().MouseDrawCursor = false;
}

void GuiApp::update(){

}

void GuiApp::draw(){

	ofBackground(0,0,0);

	gui.begin();
	
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	bool criaVideo = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaVideo, ImVec2(200, 150));
	bool criaPoligono = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaPoligono, ImVec2(200, 150));
	bool criaKinect = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaKinect, ImVec2(200, 150));

	if(criaVideo) {
		cout << "btn pressionado: criaVideo";
		brisas.push_back( new VideoBrisa() );
	}

	gui.end();
}