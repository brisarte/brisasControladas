#include "Brisa.h"


void KinectBrisa::setup() {
	kinecto.setRegistration(true);
	kinecto.init();
	kinecto.open();
	kinecto.setCameraTiltAngle(0);

	ativa = true;
}
void KinectBrisa::draw() {

	if (ativa) {
		kinecto.update();
		kinecto.draw(0,0);
	}

	ofSetColor(255,255,0);
	ofDrawTriangle(700,100,500,300,900,300);
}