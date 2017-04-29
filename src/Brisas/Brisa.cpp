#include "Brisa.h"

void Brisa::setup() {
	configBrisa = true;
}

void Brisa::update( float dt ) {
}

void Brisa::draw() {
}

void Brisa::drawControles() {
}

void Brisa::drawButton(ofxImGui::Gui *gui, int i) {

	btnConfigBrisa = gui->loadTexture(iconPath);

	if(ImGui::ImageButton((ImTextureID)(uintptr_t)btnConfigBrisa, ImVec2(100, 75))) {
		configBrisa != configBrisa;
		cout << "clicou nas config: " << configBrisa;
	}
	if(configBrisa) {
		ImGui::SetNextWindowSize(ofVec2f(200,200), ImGuiSetCond_FirstUseEver);
		string titulo = "Configurações Brisa[" + to_string(i) + "]";
		ImGui::Begin(titulo.c_str(), &configBrisa);

		drawControles();

		ImGui::End();
	}
}