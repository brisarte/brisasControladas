#include "Brisa.h"

FonteKinect::FonteKinect(ofxKinect *kinectGlobal, int cameraSelecionada = 0) {
    // Configura a brisa e defini o ícone
    kinect = kinectGlobal;
    camera = cameraSelecionada; // 0 = camera RGB (default) | 1 = camera Depth
    exemploGray.load("../data/img/exemplogray.png");
    exemploGray.setImageType(OF_IMAGE_GRAYSCALE); 
    exemploCor.load("../data/img/exemplogray.png");
    mirrorHorizontal = mirrorVertical = false;
    setup();
    ofSetBackgroundAuto(false);
    iBlur = 0;
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

    // TODO atribuir videos "exemplo"
    if ( kinect->isConnected() ) {
        kinect->update();
        grayImage.setFromPixels(kinect->getDepthPixels());
        colorImage.setFromPixels(kinect->getPixels());
    } else {
        colorImage.setFromPixels(exemploCor.getPixels());
        grayImage.setFromPixels(exemploGray.getPixels());
    }

    for (int i = 0; i < iBlur; i++) {
        grayImage.erode_3x3();
        grayImage.dilate_3x3();
        grayImage.blurHeavily();
        grayImage.erode_3x3();
        grayImage.dilate_3x3();
        grayImage.blur(3);
    }

    colorImage.mirror(mirrorVertical, mirrorHorizontal);
    grayImage.mirror(mirrorVertical, mirrorHorizontal);

    grayImage.brightnessContrast(brilhoBrisa, contrasteBrisa);
    if (camera == 1) {
        colorImage.draw(0,0,1024,768);
    } else {
        grayImage.draw(0,0,1024,768);
    }

    fboBrisa.end();
    fboBrisa.readToPixels(pixelsBrisa);
}

void FonteKinect::draw() {
    aplicarShader();
}

void FonteKinect::drawControles() {
    if (ImGui::CollapsingHeader("Kinect")) {
	// Camêra fonte
	ImGui::Text("Camêra selecionada:");
	ImGui::RadioButton("RGB", &camera, 1); ImGui::SameLine();
	ImGui::RadioButton("Profundidade", &camera, 2);

	ImGui::Checkbox("Espelho Horizontal", &mirrorHorizontal);
	ImGui::Checkbox("Espelho Vertical", &mirrorVertical);

        ImGui::SliderFloat("brilho", &brilhoBrisa, 0, 1);
        ImGui::SliderFloat("contraste", &contrasteBrisa, 0, 1);
        ImGui::SliderInt("blur", &iBlur, 0, 10);

    }
}
