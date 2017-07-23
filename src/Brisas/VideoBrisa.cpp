#include "Brisa.h"

VideoBrisa::VideoBrisa(vector<Brisa*> *brisasParent) {
	setup();
	brisasAtivas = brisasParent;
	cout << brisasAtivas->size();
	// Configura a brisa e defini o ícone
	iconPath = "../data/img/icon/video.png";
	fboBrisa.allocate(1024, 768);
	fboBrisa.begin();
    ofClear(0,0,0, 0);
    fboBrisa.end();
	posVideo = 0;
}

void VideoBrisa::update( float dt ) {
    if( video.isLoaded() )  {
        posVideo = video.getPosition();
        video.update();
    }

    fboBrisa.begin();
    ofClear(0,0,0, 0);

    if( video.isLoaded() ) {
        video.draw(-(widthDraw-1024)/2, -(heightDraw-768)/2, widthDraw, heightDraw);
    }

    fboBrisa.end();
    fboBrisa.readToPixels(pixelsBrisa);
}

void VideoBrisa::draw() {
	aplicarShader();
}

void VideoBrisa::drawControles(int iBrisa) {
	if (video.isLoaded()) {
		// play e pause
		if (video.isPaused()) {
			if (ImGui::Button("Play")) {
				video.setPaused(false);
			}
		}
		else {
			if (ImGui::Button("Pause")) {
				video.setPaused(true);
			}
		}
		// Timeline
		//ImGui::SliderFloat("Tempo", &posVideo, 0, 1);
	}

	if (ImGui::Button("Carregar Vídeo")) { 
		ImGui::OpenPopup("loadVideo");
	}
	if (ImGui::BeginPopup("loadVideo")) {
		listaVideos(); 
		ImGui::EndPopup();
	}

	desenharControlesShader();

	if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}



void VideoBrisa::listaVideos() {

	ofDirectory dirVideos;

	if (ImGui::CollapsingHeader("Videos Old")) {

		//2. Carrega numero de pastas de sequencias
		int nVideos = dirVideos.listDir("../data/videos/naovaiusar/");

		//4. Abre pastas
		for (int i = 0; i < nVideos; i++) {
			string video = dirVideos.getPath(i);
			if (ImGui::Selectable(video.c_str())) {
				setupVideo(video);
			}

		}
	}
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
		cout << "\nVideo carregado: " << caminhoVideo;
		video.play();
		cout << "\nVideo played: " << caminhoVideo;
		video.setVolume(0);

		heightOrig = video.getHeight();
		widthOrig = video.getWidth();

		// Caso tenha dado algo errado no codec/video/etc
		if(heightOrig == 0 || widthOrig == 0) {
                    cout << "\nVideo deu ruim:" << caminhoVideo;
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
