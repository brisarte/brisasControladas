#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal) {
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/kinect.png";
	setup();
	kinecto = kinectGlobal;
	camera = 0; // 0 = camera RGB (default) | 1 = camera Depth
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
		if (camera == 0) {
			kinecto->draw(0,0,1024,768);
		} else {
			kinecto->drawDepth(0,0,1024,768);
		}
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsButtonSource);
}

void KinectBrisa::draw() {
	fboBrisa.draw(0,0);
}

void KinectBrisa::drawControles() {
	ImGui::Text("kinect");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);


	// Botões de liga e desliga do kinect
	if ( kinecto->isConnected() ) {
		if (ImGui::Button("Desliga Kinect")) { desligaKinect(); } 
	} else {
		if (ImGui::Button("Liga Kinect")) { ligaKinect(); } 
	}

	// Camêra fonte
	ImGui::Text("Camêra selecionada:");
	ImGui::RadioButton("RGB", &camera, 0); ImGui::SameLine();
	ImGui::RadioButton("Profundidade", &camera, 1);
}
