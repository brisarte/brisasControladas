#include "Brisa.h"

VideoBrisa::VideoBrisa() {
	setup();
	iconPath = "../data/img/icon/video.png";
}

void VideoBrisa::draw() {

	ofSetColor(255,0,0);
	ofDrawCircle(200,200,200);
}


void VideoBrisa::drawControles() {
	ImGui::Text("video");
}
