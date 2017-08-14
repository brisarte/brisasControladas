#include "Brisa.h"

FonteKinect::FonteKinect(ofxKinect *kinectGlobal, int cameraSelecionada = 0) {
    // Configura a brisa e defini o ícone
    kinect = kinectGlobal;
    camera = cameraSelecionada; // 0 = camera RGB (default) | 1 = camera Depth
    mirrorHorizontal = mirrorVertical = false;
    setup();
    ofSetBackgroundAuto(false);
}

void FonteKinect::ligaKinect() {
    if( !kinect->isConnected() ) {
        kinect->setRegistration(true);
        kinect->init();
        kinect->open();
        kinect->setCameraTiltAngle(0);
    }
}

void FonteKinect::desligaKinect() {
    kinect->close();
}

void FonteKinect::update( float dt ) {
    fboBrisa.begin();

    ofSetColor(255,255,255,255);

    if ( kinect->isConnected() ) {
        kinect->update();
        grayImage.setFromPixels(kinect->getDepthPixels());
        grayImage.brightnessContrast(brilhoBrisa, contrasteBrisa);
        if (camera == 1) {
            kinect->draw(0,0,1024,768);
        } else {
            grayImage.draw(0,0,1024,768);
        }
    }

    fboBrisa.end();
    fboBrisa.readToPixels(pixelsBrisa);
}

void FonteKinect::draw() {
    aplicarShader();
}

void FonteKinect::drawControles(int iBrisa) {
	// Camêra fonte
	ImGui::Text("Camêra selecionada:");
	ImGui::RadioButton("Nenhuma", &camera, 0); ImGui::SameLine();
	ImGui::RadioButton("RGB", &camera, 1); ImGui::SameLine();
	ImGui::RadioButton("Profundidade", &camera, 2);

	ImGui::Checkbox("Espelho Horizontal", &mirrorHorizontal);
	ImGui::Checkbox("Espelho Vertical", &mirrorVertical);
}
