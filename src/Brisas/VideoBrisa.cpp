#include "Brisa.h"

VideoBrisa::VideoBrisa() {
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/video.png";
	setup();
	fboVideo.allocate(1024, 768);
	fboVideo.begin();
    ofClear(255,255,255, 0);
    fboVideo.end();
}

void VideoBrisa::update( float dt ) {
	fboVideo.begin();
    ofClear(255,255,255, 0);
	ofSetColor(corBrisa);

	ofDrawCircle(200,200,200);
	
    fboVideo.end();
	fboVideo.readToPixels(pixelsButtonSource);
}

void VideoBrisa::draw() {

	fboVideo.draw(0,0);
}

void VideoBrisa::drawControles() {
	ImGui::Text("video");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);
}
