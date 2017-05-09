#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal) {
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/kinect.png";
	setup();
	kinecto = kinectGlobal;
}

void KinectBrisa::ligaKinect() {
	if( !kinecto->isConnected() ) {
		kinecto->setRegistration(true);
		kinecto->init();
		kinecto->open();
		kinecto->setCameraTiltAngle(0);
	}
}

void KinectBrisa::desligaKinect() {
	kinecto->close();
	
}

void KinectBrisa::update( float dt ) {
	fboBrisa.begin();
    
    ofClear(255,255,255, 0);
	ofSetColor(corBrisa);

	if ( kinecto->isConnected() ) {
		kinecto->update();
		kinecto->draw(0,0);
	}

    fboBrisa.end();
}

void KinectBrisa::draw() {
	fboBrisa.draw(0,0);
}

void KinectBrisa::drawControles() {
	ImGui::Text("kinect");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);


	if (ImGui::Button("Liga Kinect")) { ligaKinect(); } 
	if (ImGui::Button("Desliga Kinect")) { desligaKinect(); } 
}
