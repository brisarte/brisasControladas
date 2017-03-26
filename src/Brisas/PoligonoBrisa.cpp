#include "Brisa.h"

PoligonoBrisa::PoligonoBrisa() {
	iconPath = "../data/img/icon/poligon.png";
}

void PoligonoBrisa::draw() {

	ofSetColor(255,0,255);
	ofDrawRectangle(312,180,400,400);
}
