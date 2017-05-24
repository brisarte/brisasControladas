#include "GuiApp.h"
#include <vector>
using namespace std;
	

float t0, t1;

void GuiApp::setup(){
    gui.setup();
    
	btnCriaVideo = gui.loadTexture("../data/img/icon/video.png");
	btnCriaPoligono = gui.loadTexture("../data/img/icon/poligon.png");
	btnCriaKinect = gui.loadTexture("../data/img/icon/kinect.png");
	btnCriaImg = gui.loadTexture("../data/img/icon/img.png");
	btnCriaGif = gui.loadTexture("../data/img/icon/gif.png");

    ImGui::GetIO().MouseDrawCursor = false;
    desenhaMiniaturas = true;
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
	

	if (ImGui::CollapsingHeader("Controles Gerais")) {
		ImGui::Text("Média :%.1f FPS (%.3f ms/frame) ",  ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
		ImGui::Checkbox("Desenha miniaturas", &desenhaMiniaturas);
	}

	ImGui::Text("Adicione uma Brisa Nova:");
	bool criaVideo = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaVideo, ImVec2(120, 90)); ImGui::SameLine();
	bool criaPoligono = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaPoligono, ImVec2(120, 90));
	bool criaKinect = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaKinect, ImVec2(120, 90)); ImGui::SameLine();
	bool criaImg = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaImg, ImVec2(120, 90));
	bool criaGif = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaGif, ImVec2(120, 90));

	if(criaVideo) {
		cout << "btn pressionado: criaVideo";
		brisasAtivas.push_back( new VideoBrisa( &brisasAtivas ) );
	}
	if(criaPoligono) {
		cout << "btn pressionado: criaPoligono";
		brisasAtivas.push_back( new PoligonoBrisa(&brisasAtivas) );
	}
	if (criaKinect) {
		cout << "btn pressionado: criaKinect";
		brisasAtivas.push_back(new KinectBrisa(&kinectGlobal, &brisasAtivas));
	}
	if (criaImg) {
		cout << "btn pressionado: criaImg";
		brisasAtivas.push_back(new ImagemBrisa(&brisasAtivas));
	}
	if (criaGif) {
		cout << "btn pressionado: criaGif";
		brisasAtivas.push_back(new GifBrisa(&brisasAtivas));
	}



	ImGui::SetNextWindowSize(ofVec2f(20,10), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Brisas Ativas");

	// Me mostra essas brisa
	for( int i = 0; i < brisasAtivas.size(); i++ )
    {
        brisasAtivas[i]->drawButton(desenhaMiniaturas, i);
    }

    ImGui::End();

	gui.end();

}