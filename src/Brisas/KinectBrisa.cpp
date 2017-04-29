#include "Brisa.h"

KinectBrisa::KinectBrisa() {
	setup();
	iconPath = "../data/img/icon/kinect.png";
}

void KinectBrisa::ligaKinect() {
	/*
	kinecto.setRegistration(true);
	kinecto.init();
	kinecto.open();
	kinecto.setCameraTiltAngle(0);
	*/
}

void KinectBrisa::draw() {

	ofSetColor(255,255,255);
	if (false) {
		kinecto.update();
		kinecto.draw(0,0);
	}

}

void KinectBrisa::drawControles() {
	ImGui::Text("kinect");
}
