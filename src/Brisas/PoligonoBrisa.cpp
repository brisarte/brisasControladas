#include "Brisa.h"

PoligonoBrisa::PoligonoBrisa() {
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/poligon.png";
	setup();
	
}

void PoligonoBrisa::update( float dt ) {
	fboBrisa.begin();
    
    ofClear(255,255,255, 0);
	ofSetColor(corBrisa);
	ofDrawRectangle(312,180,400,400);

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsButtonSource);
}

void PoligonoBrisa::draw() {
	fboBrisa.draw(0,0);
}

void PoligonoBrisa::drawControles() {
	ImGui::Text("poligon");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);
}
