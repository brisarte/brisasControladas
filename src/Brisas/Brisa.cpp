#include "Brisa.h"

void Brisa::setup() {

	ativa = true;
}

void Brisa::update( float dt ) {
}

void Brisa::draw() {
}

void Brisa::drawButton(ofxImGui::Gui *gui) {

	btnConfigBrisa = gui->loadTexture(iconPath);
	bool configBrisa = ImGui::ImageButton((ImTextureID)(uintptr_t)btnConfigBrisa, ImVec2(200, 150));
/*
	if(criaVideo) {
		cout << "btn pressionado: criaVideo";
		brisasAtivas.push_back( new VideoBrisa() );
	}*/
}
