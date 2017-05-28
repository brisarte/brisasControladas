#include "Brisa.h"

ImagemBrisa::ImagemBrisa(vector<Brisa*> *brisasParent) {
	setup();
	brisasAtivas = brisasParent;
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/kinect.png";
	fboBrisa.allocate(1024, 768);
	fboBrisa.begin();
    ofClear(0,0,0, 0);
    fboBrisa.end();

	rotacao = 0;
	proporcao = 1;
	deslocX = deslocY = 0;
	rotacionaSozinho = true;
	torceSozinho = false;
}

void ImagemBrisa::update( float dt ) {
	
	fboBrisa.begin();
    ofClear(0,0,0, 0);
	ofSetColor(corBrisa);

	if (img.isAllocated()) {
		ofPushMatrix();
		ofTranslate(512 + deslocX, 384 + deslocY, 0);
		img.setAnchorPercent(0.5, 0.5);
		if (rotacionaSozinho) {
			rotacao += ofNoise(ofGetElapsedTimef());
			if (rotacao > 360) rotacao = 0;
		}
		ofRotate(rotacao);

		ofScale(proporcao, proporcao, 1);
		img.draw(0, 0);
		ofPopMatrix();
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void ImagemBrisa::draw() {
	if (ligaShader) {
		shaderBrisa.begin();
		if (iBrisaShader > -1 && brisasAtivas->at(iBrisaShader)->fboBrisa.isAllocated() ) {
			shaderBrisa.setUniformTexture("texture1", brisasAtivas->at(iBrisaShader)->fboBrisa.getTextureReference(), 1); //"1" means that it is texture 1
		}

		ofSetColor(255, 255, 255);
		fboBrisa.draw(0, 0);

		shaderBrisa.end();
	} else {
		fboBrisa.draw(0, 0);
	}

}

void ImagemBrisa::drawControles(int iBrisa) {
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);

	if (ImGui::Button("Carregar Imagem")) { 
		ImGui::OpenPopup("loadImagens");
	}
	if (ImGui::BeginPopup("loadImagens")) {
		listaImagens(); 
		ImGui::EndPopup();
	} 

	ImGui::SliderInt("desloca X", &deslocX, -600, 600);
	ImGui::SliderInt("desloca Y", &deslocY, -600, 600);
	ImGui::SliderFloat("Proporcao", &proporcao, 0.2, 10);
	ImGui::SliderFloat("Rotação", &rotacao, 0, 360);ImGui::SameLine();
	ImGui::Checkbox("Automático", &rotacionaSozinho); 
	ImGui::Checkbox("Torcer automático", &torceSozinho);

	desenharControlesShader();

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}



void ImagemBrisa::listaImagens() {

	ofDirectory dirImg;
	//2. Carrega numero de pastas de sequencias
	int nImgs = dirImg.listDir("../data/img/imagens");

	//4. Abre pastas
	for (int i=0; i<nImgs; i++) {
		string video = dirImg.getPath( i );
		if (ImGui::Selectable(video.c_str())) {
			setupImagem(video);
		}

	}
}

void ImagemBrisa::setupImagem(string imgPath) {
	caminhoImagem = imgPath;
	if(caminhoImagem != "") {
		img.load(imgPath);
		img.setAnchorPercent(0.5, 0.5);
	}
}