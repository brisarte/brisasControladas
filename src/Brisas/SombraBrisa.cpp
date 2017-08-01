#include "Brisa.h"

SombraBrisa::SombraBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent, vector<ImVec4> *coresPaleta) {
	// Configura a brisa e defini o ícone
	brisasAtivas = brisasParent;
	kinecto = kinectGlobal;
	camera = 1; // 0 = camera RGB (default) | 1 = camera Depth
	setup();

	mirrorHorizontal = mirrorVertical = false;
	desenhaBlur = true;
	blurKinect = false;
	brightnessGray = 0.5;
	contrastGray = 0.95;
	iBlur = 2;
	sombraHoriz = true;
	sombraVert = false;

	int sizePaleta = coresPaleta->size();
	int iCor1 = ofRandom(0, sizePaleta-1);
	int iCor2 = ofRandom(0, sizePaleta-1);
	// Caso as cores sejam iguais troca a segunda	
	if (iCor1 == iCor2) {
		iCor2 = iCor2 + 1 > sizePaleta ? iCor2 - 1 : iCor2 + 1;
	}
	corBrisa = coresPaleta->at(iCor1);
	corComplementar = coresPaleta->at(iCor2);
}

void SombraBrisa::ligaKinect() {
	if( !kinecto->isConnected() ) {
		kinecto->setRegistration(true);
		kinecto->init();
		kinecto->open();
		kinecto->setCameraTiltAngle(0);
	}
}

void SombraBrisa::desligaKinect() {
	kinecto->close();
}

void SombraBrisa::update( float dt ) {
	fboBrisa.begin();
    
	if (clearFrames) {
		ofClear(255,255,255, 0);
	}

	if ( kinecto->isConnected() ) {
		
		kinecto->update();
		grayImage.setFromPixels(kinecto->getDepthPixels());
		grayImage.mirror(mirrorVertical, mirrorHorizontal);
		grayImage.brightnessContrast(brightnessGray, contrastGray);

		blurGray = grayImage;
		for (int i = 0; i < iBlur; i++) {
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.blurHeavily();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.blur(3);
		}
		ofSetColor(corBrisa);
			blurGray.draw(0, 0, WIDTH, HEIGHT);
		if (sombraHoriz || sombraVert) {
			ofEnableBlendMode(OF_BLENDMODE_ADD);
			if (sombraVert) {
				ofSetColor(corComplementar);
				blurGray.mirror(true, false);
				blurGray.draw(0, 0, WIDTH, HEIGHT);
			}
			if (sombraHoriz) {
				ofSetColor(corComplementar);
				blurGray.mirror(false, true);
				blurGray.draw(0, 0, WIDTH, HEIGHT);
			}
			if (sombraVert && sombraHoriz) {
				ofSetColor(corBrisa);
				blurGray.mirror(true, false);
				blurGray.draw(0, 0, WIDTH, HEIGHT);
			}
		}

		grayPixels = grayImage.getPixels();
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void SombraBrisa::draw() {
	aplicarShader();
}

void SombraBrisa::drawControles(int iBrisa) {
	// Botões de liga e desliga do kinect
	if ( kinecto->isConnected() ) {
		if (ImGui::Button("Desliga Kinect")) { desligaKinect(); } 
	} else {
		if (ImGui::Button("Liga Kinect")) { ligaKinect(); } 
	}

	ImGui::ColorEdit4("Base", (float*)&corBrisa);
	ImGui::ColorEdit4("Complementar", (float*)&corComplementar);

	// Camêra fonte
	ImGui::Text("Sombras");
	ImGui::Checkbox("--", &sombraHoriz);
	ImGui::Checkbox("|", &sombraVert);

	ImGui::Checkbox("mirror <->", &mirrorHorizontal);
	ImGui::Checkbox("mirror V", &mirrorVertical);

	ImGui::SliderInt("blur", &iBlur, 0, 20);

	ImGui::SliderFloat("brilho", &brightnessGray, 0, 1);
	ImGui::SliderFloat("contraste", &contrastGray, 0, 1);

	ImGui::Checkbox("Limpa Frames", &clearFrames);

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
