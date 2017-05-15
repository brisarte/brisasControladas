#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent) {
	// Configura a brisa e defini o ícone
	brisasAtivas = brisasParent;
	iconPath = "../data/img/icon/kinect.png";
	kinecto = kinectGlobal;
	camera = 0; // 0 = camera RGB (default) | 1 = camera Depth
	setup();
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
    
	if (clearFrames) {
		ofClear(255,255,255, 0);
	}

	ofSetColor(corBrisa);

	if ( kinecto->isConnected() ) {
		kinecto->update();
		if (camera == 1) {
			kinecto->draw(0,0,1024,768);
		} else if (camera == 2) {
			kinecto->drawDepth(0,0,1024,768);
		}

		if (ligaContornos) {
		}
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void KinectBrisa::draw() {
	fboBrisa.draw(0,0);
}

void KinectBrisa::drawControles(int iBrisa) {
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
	ImGui::RadioButton("Nenhuma", &camera, 0); ImGui::SameLine();
	ImGui::RadioButton("RGB", &camera, 1); ImGui::SameLine();
	ImGui::RadioButton("Profundidade", &camera, 2);

	ImGui::Checkbox("Contornos", &ligaContornos);
	ImGui::Checkbox("Limpa Frames", &clearFrames);

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
