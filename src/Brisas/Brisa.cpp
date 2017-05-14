#include "Brisa.h"

void Brisa::setup() {
	configBrisa = true;
	//btnConfigBrisa = gui->loadTexture(iconPath);fboBrisa.clear();
	pixelsBrisa.allocate(1024,768, OF_IMAGE_COLOR);
	fboBrisa.allocate(1024, 768);
	fboBrisa.begin();
    ofClear(255,255,255, 0);
    fboBrisa.end();

    corBrisa = ofColor(255, 255, 255);
}

void Brisa::update(float dt) {
}

void Brisa::mostraBrisas() {

}

void Brisa::draw() {
}

void Brisa::drawControles(int iBrisa) {
}

void Brisa::drawButton(ofxImGui::Gui *gui, int i) {

	ofImage imgBtn;
	imgBtn.setFromPixels(pixelsBrisa);
	imgBtn.draw(0,i*150,200,150);

	std::ostringstream oss;
	std::string text = "Brisa ";
	text += std::to_string(i);

	if (ImGui::Button( text.c_str() )) { 
		configBrisa ^= 1;
		cout << "\nBrisa " << i << ": configBrisa=" << configBrisa;
	}
	
	if(configBrisa) {
		ImGui::SetNextWindowSize(ofVec2f(300,200), ImGuiSetCond_FirstUseEver);
		string titulo = "Configurações Brisa[" + to_string(i) + "]";
		ImGui::Begin(titulo.c_str(), &configBrisa);

		drawControles(i);

		ImGui::End();
	}
}

void Brisa::excluiBrisa(int iBrisa) {
	brisasAtivas->erase(brisasAtivas->begin()+iBrisa);
}