#include "Brisa.h"

FonteKinect::FonteKinect(ofxKinect *kinectGlobal, int cameraSelecionada = 0) {
    // Configura a brisa e defini o ícone
    kinect = kinectGlobal;
    camera = cameraSelecionada; // 0 = camera RGB (default) | 1 = camera Depth

    mirrorHorizontal = mirrorVertical = false;
    setup();
    ofSetBackgroundAuto(false);
    iRastro = 0;
    iBlur = 4;
    iErode = 10;
    iDilate = 10;
    colorImage.allocate(640,480);
    floatImage.allocate(640,480);
    grayImage.allocate(640,480);
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

    // Camera RGB
    if (camera == 1) {
        // Kinect ta funcionando
        if ( kinect->isConnected() ) {
            kinect->update();
            colorImage.setFromPixels(kinect->getPixels());
        } else {
            // Kinect desligado, carrega video Demo
            if( danceRGB.isLoaded() )  {
                danceRGB.update();
            } else {
                danceRGB.load("../data/kinectdemo/rgbdance.mp4");
                danceRGB.play();
            }
            colorImage.setFromPixels(danceRGB.getPixels());
        }
    } else {
    // Camera Depth
        // Kinect ta funcionando
        if ( kinect->isConnected() ) {
            kinect->update();
            colorImage.setFromPixels(kinect->getDepthPixels());
        } else {
            // Kinect desligado, carrega video Demo
            if( danceDepth.isLoaded() )  {
                danceDepth.update();
            } else {
                danceDepth.load("../data/kinectdemo/depthdance.mp4");
                danceDepth.play();
            }
            colorImage.setFromPixels(danceDepth.getPixels());
        }
    }
    
    int maxI = 0;
    maxI = iBlur > maxI ? iBlur : maxI;
    maxI = iErode > maxI ? iErode : maxI;
    maxI = iDilate > maxI ? iDilate : maxI;

    // Aplica blur, erode e dilate
    for (int i = 0; i < maxI; i++) {
        if (iErode >= i )
            colorImage.erode();
        if (iDilate >= i )
            colorImage.dilate();
        if (iBlur >= i )
            colorImage.blurGaussian(5);
    }

    //Aplica o Rastro
    ofFloatPixels & pixF = floatImage.getFloatPixelsRef();
    floatColor = colorImage;
    ofFloatPixels & pixA = floatColor.getFloatPixelsRef();
    int numPixels = pixF.size();
    for (int i = 0; i < numPixels; i++) {
        pixF[i] = pixF[i] * ((float)iRastro/100) + pixA[i] * (1 - (float)iRastro/100);// Aumenta contraste de distancia
    }
    floatImage.flagImageChanged();
    colorImage = floatImage;

    colorImage.mirror(mirrorVertical, mirrorHorizontal);
    if (camera == 1) {
        colorImage.draw(0,0,WIDTH,HEIGHT);
    } else {
        grayImage = colorImage;
        grayImage.brightnessContrast(brilhoBrisa, contrasteBrisa);
        grayImage.draw(0,0,WIDTH,HEIGHT);
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

        ImGui::SliderInt("blur", &iBlur, 0, 10);
        ImGui::SliderInt("erode", &iErode, 0, 10);
        ImGui::SliderInt("dilate", &iDilate, 0, 10);
        ImGui::SliderInt("Rastro", &iRastro, 0, 99);
        if (camera == 2) {
            ImGui::SliderFloat("brilho", &brilhoBrisa, 0, 1);
            ImGui::SliderFloat("contraste", &contrasteBrisa, 0, 1);
        }

    }
}
