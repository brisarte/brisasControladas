#include "Brisa.h"

VideoBrisa::VideoBrisa(vector<Brisa*> *brisasParent) {
	brisasAtivas = brisasParent;
	cout << brisasAtivas->size();
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/video.png";
	setup();
	fboBrisa.allocate(1024, 768);
	fboBrisa.begin();
    ofClear(255,255,255, 0);
    fboBrisa.end();

    setupVideo("../data/videos/claricefalcao.mp4");
	shaderKinect.load("../data/shaders/vertexdummy.c", "../data/shaders/whiteAsAlpha.c");
}

void VideoBrisa::update( float dt ) {
	if( video.isLoaded() )  {
		video.update();
	}

	fboBrisa.begin();
    ofClear(255,255,255, 0);
	ofSetColor(corBrisa);

	if( video.isLoaded() ) {
		video.draw(-(widthDraw-1024)/2, -(heightDraw-768)/2, widthDraw, heightDraw);
	}

    fboBrisa.end();
	fboBrisa.readToPixels(pixelsBrisa);
}

void VideoBrisa::draw() {
	shaderKinect.begin();

	if (fboKinect.isAllocated()) {
		shaderKinect.setUniformTexture("texture1", brisasAtivas->at(0)->fboBrisa.getTextureReference(), 1); //"1" means that it is texture 1
	}

	ofSetColor(255, 255, 255);
	fboBrisa.draw(0, 0);

	shaderKinect.end();

}

void VideoBrisa::drawControles(int iBrisa) {
	ImGui::Text("video");
	ImGui::ColorEdit3("Cor da Brisa ", (float*)&corBrisa);

	if (ImGui::Button("Carregar Vídeo")) { 
		ImGui::OpenPopup("loadVideo");
	}
	if (ImGui::BeginPopup("loadVideo")) {
		listaVideos(); 
		ImGui::EndPopup();
	} 

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}

void VideoBrisa::listaVideos() {

	ofDirectory dirVideos;
	//2. Carrega numero de pastas de sequencias
	int nVideos = dirVideos.listDir("../data/videos/");

	//4. Abre pastas
	for (int i=0; i<nVideos; i++) {	
		string video = dirVideos.getPath( i );
		if (ImGui::Selectable(video.c_str())) {
			setupVideo(video);
		}

	}
}

void VideoBrisa::setupVideo(string videoPath) {
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