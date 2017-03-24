#include "Brisa.h"


void KinectBrisa::setup() {
	kinecto.setRegistration(true);
	kinecto.init();
	kinecto.open();
	kinecto.setCameraTiltAngle(0);

	ativa = true;
}
void KinectBrisa::draw() {

	ofSetColor(255,255,255);
	if (ativa) {
		kinecto.update();
		kinecto.draw(0,0);
	}

}