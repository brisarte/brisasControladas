#include "GuiApp.h"

void GuiApp::setup(){

    gui.setup();
    
    ImGui::GetIO().MouseDrawCursor = false;

    kinectLigado = false;
	mirrorKinect = false;

	kinectRGB.allocate(640,480);
	kinectDepth.allocate(640,480);

	ativaBrisa1 = false;

	tempoBrisa = 115;

	//1. Pasta de gifs
	ofDirectory dirGifsFull;
	//2. Carrega numero de pastas de sequencias
	nGifsFull = dirGifsFull.listDir("gifs/fullscreen");
	//3. Set array size 
	listaGifFull.resize( nGifsFull );

	//4. Abre pastas
	for (int i=0; i<nGifsFull; i++) {	
		//Pega caminho da pasta
		string folderName = dirGifsFull.getPath( i );	
		listaGifFull[i] = folderName;

	}

	//1. Pasta de videos
	ofDirectory dirVideo;
	//2. Carrega numero de pastas de sequencias
	nVideos = dirVideo.listDir("videos");
	//3. Set array size 
	listaVideos.resize( nVideos );

	//4. Abre pastas
	for (int i=0; i<nVideos; i++) {	
		//Pega caminho da pasta
		string folderName = dirVideo.getPath( i );	
		listaVideos[i] = folderName;
		cout << "listaVideos[" << i << "] : " << listaVideos[i];
	}


}

void GuiApp::update(){

	if(kinectLigado) {
		kinect.update();

		kinectRGB = kinect.getPixels();
		kinectDepth = kinect.getDepthPixels();

		// Testa se deve espelhar a fonte do Kinect
		if(mirrorKinect) {
			kinectDepth.mirror(false,true);
			kinectRGB.mirror(false,true);

        	kinectRGB.flagImageChanged();
        	kinectDepth.flagImageChanged();
		}

    	kinectGLuintRGB = gui.loadPixels(kinectRGB.getPixels());
    	kinectGLuintDepth = gui.loadPixels(kinectDepth.getPixels());

	}

}

void GuiApp::draw(){

	ofBackground(0,0,0);

	gui.begin();

    // Kinect cams
    {   
    	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  
  
        if(ImGui::Button("Brisa 1"))
        {
        	ativaBrisa1 = !ativaBrisa1;
        }
        if(ImGui::Button("Brisa 2"))
        {
        	ativaBrisa2 = !ativaBrisa2;
        }
        if(ImGui::Button("Brisa 3"))
        {
        	ativaBrisa3 = !ativaBrisa3;
        }
        if(ImGui::Button("Brisa 4"))
        {
        	ativaBrisa4 = !ativaBrisa4;
        }

        if(ImGui::Button("Configura Proxima"))
        {
        	
			configsBrisa1.tipoBrisa = 1; //Video
			configsBrisa1.iShader = 4;
			int randomVideo = ofRandom(0,nVideos-1);
			configsBrisa1.urlpath = listaVideos[randomVideo]; 
			cout << "\nlistaVideos[" << randomVideo << "] = " << listaVideos[randomVideo];

			configsBrisa2.tipoBrisa = 1;

			configsBrisa3.tipoBrisa = 2; //giffull
			int randomGif = ofRandom(0,nGifsFull-1);
			configsBrisa3.gifPath = listaGifFull[randomGif]; 
			cout << "\nlistaGifFull[" << randomGif << "] = " << listaGifFull[randomGif];

			configsBrisa4.tipoBrisa = 4;
        }

        if(ImGui::Button("Câmeras Kinect"))
        {
            startKinect();
        }
        if(ImGui::Button("Espelhar Kinect"))
        {
        	mirrorKinect = !mirrorKinect;
        }
    	
    	bool btnPressedKinRGB = ImGui::ImageButton((ImTextureID)(uintptr_t)kinectGLuintRGB, ImVec2(200, 150));
    	bool btnPressedKinDepth = ImGui::ImageButton((ImTextureID)(uintptr_t)kinectGLuintDepth, ImVec2(200, 150));
    }

	gui.end();
}

void GuiApp::startKinect() {
	if(!kinectLigado) {
		kinect.setRegistration(true);
		kinect.init();
		kinect.open();
		kinect.setCameraTiltAngle(0);

		/*
		depthCam.allocate(kinect.width, kinect.height);
		sombra.allocate(kinect.width, kinect.height);
		sombraMirror.allocate(kinect.width, kinect.height);
		*/

		kinectLigado = true;
	}
}