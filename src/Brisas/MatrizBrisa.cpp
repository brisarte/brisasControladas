#include "Brisa.h"

MatrizBrisa::MatrizBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent) {
	// Configura a brisa e defini o ícone
	brisasAtivas = brisasParent;
	iconPath = "../data/img/icon/matriz.png";
	kinecto = kinectGlobal;
	camera = 1; // 0 = camera RGB (default) | 1 = camera Depth
	setup();

	mirrorHorizontal = mirrorVertical = false;
	desenhaBlur = true;
	blurKinect = false;
	brightnessGray = 0.5;
	contrastGray = 0.95;
	intervaloX = 50;
	intervaloY = 46;

	coresBrisa[0] = ofColor::fromHex(0x00126D);
	coresBrisa[1] = ofColor::fromHex(0xF8D03F);
	coresBrisa[2] = ofColor::fromHex(0xF8A63C);
	coresBrisa[3] = ofColor::fromHex(0xE82130);
	coresBrisa[4] = ofColor::fromHex(0xED6134);
	coresBrisa[5] = ofColor::fromHex(0xD12585);
	coresBrisa[6] = ofColor::fromHex(0x531577);
}

void MatrizBrisa::ligaKinect() {
	if( !kinecto->isConnected() ) {
		kinecto->setRegistration(true);
		kinecto->init();
		kinecto->open();
		kinecto->setCameraTiltAngle(0);
	}
}

void MatrizBrisa::desligaKinect() {
	kinecto->close();
}

void MatrizBrisa::update( float dt ) {
	fboBrisa.begin();
    
	if (clearFrames) {
		ofClear(255,255,255, 0);
	}

	ofSetColor(corBrisa);

	if ( kinecto->isConnected() ) {
		kinecto->update();
		grayImage.setFromPixels(kinecto->getDepthPixels());
		grayImage.mirror(mirrorVertical, mirrorHorizontal);
		grayImage.brightnessContrast(brightnessGray, contrastGray);
		grayImage.blurHeavily();
		grayImage.dilate_3x3();
		grayImage.erode_3x3();
		grayImage.blurHeavily();

		if (blurKinect) {
			blurGray = grayImage;
			blurGray.erode_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.dilate_3x3();
			blurGray.dilate_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.blurHeavily();
			blurGray.blurHeavily();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.dilate_3x3();
			blurGray.erode_3x3();
			blurGray.blurHeavily();
			blurGray.blurHeavily();
			blurGray.blurHeavily();
			blurGray.blurHeavily();
			if (desenhaBlur) {
				blurGray.draw(0, 0, 1024, 768);
			}
		}
		grayPixels = grayImage.getPixels();

		int grayWidth = grayImage.getWidth();
		int grayHeight = grayImage.getHeight();
		for (int x = 0; x < grayWidth; x += intervaloX) {
			for (int y = 0; y < grayHeight; y += intervaloY) {
				int index = y*grayWidth + x; // Pega brilho do pixel[x,y]
				int brilho = grayPixels[index];
				if (brilho > 10) {
					// sorteia cor desse quadrado
					ofColor corQuad = coresBrisa[(int)ofRandom(0, 6)];
					corQuad.setBrightness(brilho);
					ofSetColor(corQuad);
				}
				else {
					ofSetColor(0, 0, 0, 0);
				}
				ofDrawRectangle(x * (1024 / (float)grayWidth), y * (768 / (float)grayHeight), intervaloX* (1024 / (float)grayWidth), intervaloY*(768 / (float)grayHeight));
			}
		}
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void MatrizBrisa::draw() {
	aplicarShader();
}

void MatrizBrisa::drawControles(int iBrisa) {
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

	ImGui::Checkbox("mirror <->", &mirrorHorizontal);
	ImGui::Checkbox("mirror V", &mirrorVertical);

	ImGui::Checkbox("blur Kinect", &blurKinect);

	ImGui::SliderInt("intervalo X", &intervaloX, 2, 100);
	ImGui::SliderInt("intervalo Y", &intervaloY, 2, 100);

	ImGui::SliderFloat("brilho", &brightnessGray, 0, 1);
	ImGui::SliderFloat("contraste", &contrastGray, 0, 1);

	ImGui::Checkbox("Limpa Frames", &clearFrames);

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
