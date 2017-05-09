#include "Brisa.h"

KinectBrisa::KinectBrisa() {
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/kinect.png";
	setup();
}

void KinectBrisa::ligaKinect() {
	/*
	kinecto.setRegistration(true);
	kinecto.init();
	kinecto.open();
	kinecto.setCameraTiltAngle(0);
	*/
}

void KinectBrisa::update( float dt ) {
	fboBrisa.begin();
    ofClear(255,255,255, 0);

	ofSetColor(corBrisa);
	if (false) {
		kinecto.update();
		kinecto.draw(0,0);
	}

    fboBrisa.end();
}

void KinectBrisa::draw() {
	fboBrisa.draw(0,0);
}

void KinectBrisa::drawControles() {
	ImGui::Text("kinect");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);
}
