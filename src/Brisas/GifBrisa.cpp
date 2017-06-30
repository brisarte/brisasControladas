#include "Brisa.h"

GifBrisa::GifBrisa(vector<Brisa*> *brisasParent) {
	setup();
	brisasAtivas = brisasParent;
	cout << brisasAtivas->size();
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/gif.png";
	fboBrisa.allocate(1024, 768);
	fboBrisa.begin();
    ofClear(0,0,0, 0);
    fboBrisa.end();

	rotacao = 0;
	proporcao = 1;
	deslocX = deslocY = 0;
}

void GifBrisa::update( float dt ) {
	if( video.isLoaded() )  {
		video.update();
	}

	fboBrisa.begin();
    ofClear(0,0,0, 0);
	ofSetColor(corBrisa);


	if( video.isLoaded() ) {
		ofPushMatrix();
		ofTranslate(512 + deslocX, 384 + deslocY, 0);
		video.setAnchorPercent(0.5, 0.5);
		ofRotate(rotacao);

		ofScale(proporcao, proporcao, 1);
		video.draw(-(widthDraw - 1024) / 2, -(heightDraw - 768) / 2, widthDraw, heightDraw);
		ofPopMatrix();
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void GifBrisa::draw() {
	aplicarShader();
}

void GifBrisa::drawControles(int iBrisa) {
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);

	if (ImGui::Button("Carregar Gif")) { 
		ImGui::OpenPopup("loadVideo");
	}
	if (ImGui::BeginPopup("loadVideo")) {
		listaVideos(); 
		ImGui::EndPopup();
	} 

	ImGui::SliderInt("desloca X", &deslocX, -600, 600);
	ImGui::SliderInt("desloca Y", &deslocY, -600, 600);
	ImGui::SliderFloat("Proporcao", &proporcao, 0.2, 10);
	ImGui::SliderFloat("Rotação", &rotacao, 0, 360);

	desenharControlesShader();

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}



void GifBrisa::listaVideos() {

	ofDirectory dirVideos;
	//2. Carrega numero de pastas de sequencias
	int nVideos = dirVideos.listDir("../data/gifs/mp4/");

	//4. Abre pastas
	for (int i=0; i<nVideos; i++) {	
		string video = dirVideos.getPath( i );
		if (ImGui::Selectable(video.substr(16).c_str())) {
			setupVideo(video);
		}

	}
}

void GifBrisa::setupVideo(string videoPath) {
	caminhoVideo = videoPath;
	if(caminhoVideo != "") {
		video.load(caminhoVideo);
		cout << "\nVideo loaded: " << caminhoVideo;
		video.play();
		cout << "\nVideo played: " << caminhoVideo;
		video.setVolume(0);

		heightOrig = video.getHeight();
		widthOrig = video.getWidth();

		// Caso tenha dado algo errado no codec/video/etc
		if(heightOrig == 0 || widthOrig == 0) {
			video.close();
			return;
		}
		
		// background-size: cover;
		float videoProp = (float)widthOrig/heightOrig;
		cout << "\nProporções calculadas: " << caminhoVideo;
		if( videoProp > 4./3. ) {
			heightDraw = 768;
			widthDraw = widthOrig * (heightDraw/heightOrig);
		} else {
			widthDraw = 1024;
			heightDraw = heightOrig * (widthDraw/widthOrig);
		}
		cout << "\nredimensionado: " << widthOrig << "x" << heightOrig << " => " 
			<< widthDraw << "x" << heightDraw;
	}
}