#include "GuiApp.h"
#include <vector>
using namespace std;
	

float t0, t1;

void GuiApp::setup(){
    gui.setup();
    
	btnCriaVideo = gui.loadTexture("../data/img/icon/video.png");
	btnCriaPoligono = gui.loadTexture("../data/img/icon/poligon.png");
	btnCriaKinect = gui.loadTexture("../data/img/icon/kinect.png");

    ImGui::GetIO().MouseDrawCursor = false;
}

void GuiApp::update(){
	
	// Quanto tempo passou desde o ultimo update?
	// Resp = t1 - t0
	t0 = t1;
	t1 = ofGetElapsedTimef();
	float dt = t1 - t0;

	// Atualiza as brisa tudo
	for( int i = 0; i < brisasAtivas.size(); i++ )
    {
        brisasAtivas[i]->update(dt);
    }
    
}

void GuiApp::draw(){
	ofBackground(0,0,0);

	gui.begin();
	
	ImGui::Text("Média de %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	bool criaVideo = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaVideo, ImVec2(200, 150));
	bool criaPoligono = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaPoligono, ImVec2(200, 150));
	bool criaKinect = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaKinect, ImVec2(200, 150));

	if(criaVideo) {
		cout << "btn pressionado: criaVideo";
		brisasAtivas.push_back( new VideoBrisa() );
	}
	if(criaPoligono) {
		cout << "btn pressionado: criaPoligono";
		brisasAtivas.push_back( new PoligonoBrisa() );
	}
	if(criaKinect) {
		cout << "btn pressionado: criaKinect";
		brisasAtivas.push_back( new KinectBrisa() );
	}


	ImGui::SetNextWindowSize(ofVec2f(20,10), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Brisas Ativas");

	// Me mostra essas brisa
	for( int i = 0; i < brisasAtivas.size(); i++ )
    {
        brisasAtivas[i]->drawButton(&gui, i);
    }

    ImGui::End();

	gui.end();

}