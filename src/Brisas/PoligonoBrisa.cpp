#include "Brisa.h"

PoligonoBrisa::PoligonoBrisa() {
	setup();
	iconPath = "../data/img/icon/poligon.png";
}

void PoligonoBrisa::draw() {

	ofSetColor(255,0,255);
	ofDrawRectangle(312,180,400,400);
}


void PoligonoBrisa::drawControles() {
	ImGui::Text("poligon");
}
