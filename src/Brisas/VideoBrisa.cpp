#include "Brisa.h"

VideoBrisa::VideoBrisa() {
	iconPath = "../data/img/icon/video.png";
}

void VideoBrisa::draw() {

	ofSetColor(255,0,0);
	ofDrawCircle(200,200,200);
}