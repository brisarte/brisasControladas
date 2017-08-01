#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent) {
	// Configura a brisa e defini o ícone
	brisasAtivas = brisasParent;
	iconPath = "../data/img/icon/kinect.png";
	kinecto = kinectGlobal;
	camera = 0; // 0 = camera RGB (default) | 1 = camera Depth
	mirrorHorizontal = mirrorVertical = false;
        clearFrames = true;
        nivelFade = 20;
	setup();
        ofSetBackgroundAuto(false);
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
	kinecto->setCameraTiltAngle(angKinect);
        
	fboBrisa.begin();
    
	if (clearFrames) {
            // Defini um alpha de acordo com o nivel Fade
            ofSetColor( ofFloatColor(1.0, 1.0, 1.0, 0.05*(nivelFade/100) ) );
	} else {
            ofSetColor(255,255,255,255);
        }

	if ( kinecto->isConnected() ) {
		kinecto->update();
		grayImage.setFromPixels(kinecto->getDepthPixels());
		grayImage.mirror(mirrorVertical, mirrorHorizontal);
		grayImage.brightnessContrast(brilhoBrisa, contrasteBrisa);
		if (camera == 1) {
			kinecto->draw(0,0,WIDTH,HEIGHT);
		} else if (camera == 2) {
			grayImage.draw(0,0,WIDTH,HEIGHT);
		}
		if (ligaContornos) {
			contourFinder.findContours(grayImage, 10, (kinecto->width*kinecto->height)/2, 20, false);
			contourFinder.draw(0,0,WIDTH,HEIGHT);
		}
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void KinectBrisa::draw() {
	aplicarShader();
}

void KinectBrisa::drawControles(int iBrisa) {
	ImGui::Text("kinect");
	ImGui::Checkbox("Liga Fade", &clearFrames);
        if(clearFrames){
	    ImGui::SliderFloat("Fade", &nivelFade, 0, 100);
        }

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

	ImGui::Checkbox("mirror <->", &mirrorHorizontal);
	ImGui::Checkbox("mirror V", &mirrorVertical);

	ImGui::Checkbox("Contornos", &ligaContornos);


	ImGui::SliderFloat("Posição kinect", &angKinect, -30, 30);

	desenharControlesDistorcao();

	desenharControlesShader();
		
	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
