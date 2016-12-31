#include "ofApp.h"

int vw, vh;
ofxKinect kinect;


BrisaVideo bVideo;
BrisaKinect bKinect;
BrisaGifFull bGifFull;

// Variáveis globais pro kinect
ofxCvGrayscaleImage depthCam;
bool kinectLigado = false;

ofShader blackAsAlpha, whiteAsAlpha, invertColor, fundoNegativo, frenteNegativo, dummyShader;

ofShader shaderInteracao;

//--------------------------------------------------------------
void ofApp::setup(){
	// Aloca memoria com tamanho da viewport
	vh = 768;
	vw = 1024;
	gl->background(bgColor);
	videoPath = "";
	pathGif = "";

	//alloc de fbo
	for(int i = 0; i < 4; i++) {
		fboLayer[i].allocate(vw,vh);
	}

	dummyShader.load( "shaders/vertexdummy.c", "shaders/fragdummy.c" );
	blackAsAlpha.load( "shaders/vertexdummy.c", "shaders/blackAsAlpha.c" );
	whiteAsAlpha.load( "shaders/vertexdummy.c", "shaders/whiteAsAlpha.c" );
	invertColor.load( "shaders/vertexdummy.c", "shaders/invertColor.c" );
	frenteNegativo.load( "shaders/vertexdummy.c", "shaders/frenteNegativo.c" );
	fundoNegativo.load( "shaders/vertexdummy.c", "shaders/fundoNegativo.c" );

	// kinect
	kinectAngle = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
	bgColor = gui->bgColor;

	if(videoPath != gui->videoPath) {
		videoPath = gui->videoPath;
		bVideo.urlpath = videoPath;
		bVideo.setup();
	}
	bVideo.update();
	bVideo.setShader(gui->shaderVideoSelected);

	if(pathGif != gui->pastaGif) {
		pathGif = gui->pastaGif;
		bGifFull.loadImg(pathGif);
	}

	if(kinectLigado) {
		kinect.update();
		if(depthCam.bAllocated) {
			depthCam.setFromPixels(kinect.getDepthPixels());
		}
	}


	
	if(bKinect.ativa) {
		bKinect.update();
		bKinect.setFiltro(gui->filtroKinectSelected);
		bKinect.setContorno(gui->kinectContorno);
		bKinect.setShader(gui->shaderKinectSelected);
		bKinect.setFonte(gui->fonteKinectSelected);
	}

	gl->background(bgColor);

	fboLayer[0].begin();
		ofBackground(0, 0, 0, 0);	
		desenhaBrisa(gui->tipoBrisaFbo[0]);

	fboLayer[0].end();

	fboLayer[1].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(gui->tipoBrisaFbo[1]);
	fboLayer[1].end();

	fboLayer[2].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(gui->tipoBrisaFbo[2]);

	fboLayer[2].end();

	fboLayer[3].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(gui->tipoBrisaFbo[3]);
	fboLayer[3].end();

}

//--------------------------------------------------------------
void ofApp::desenhaBrisa(int tipoBrisa){
	switch(tipoBrisa){
		//No Breeza
		case 0:
			break;
		//Video
		case 1:
			bVideo.draw();
			break;
		//Video
		case 2:
			bKinect.draw();
			break;
		//GifFull
		case 3:
			bGifFull.draw();
			break;
			
		default:
			break;
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	gl->setColor(0);

	gl->setColor(255);

	// Desenha Brisas
	for(int i = 0; i < 4; i++) {
		fboLayer[i].draw(0,0,vw,vh);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {

		case OF_KEY_UP:
			kinectAngle++;
			if(kinectAngle>30) kinectAngle=30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
			
		case OF_KEY_DOWN:
			kinectAngle--;
			if(kinectAngle<-30) kinectAngle=-30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}

void GuiApp::startBrisaKinect(ofxDatGuiButtonEvent e)
{
	bKinect.setup();
}

void GuiApp::closeKinect(ofxDatGuiButtonEvent e)
{
	kinect.setCameraTiltAngle(0); // zero the tilt
	kinect.close();

	kinectLigado = false;

}
void GuiApp::startKinect(ofxDatGuiButtonEvent e)
{
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	kinect.setCameraTiltAngle(0);

	depthCam.allocate(kinect.width, kinect.height);

	kinectLigado = true;
}

void GuiApp::drawKinect()
{
	if(kinectLigado) {
		kinect.draw(0,0,200,150);
		depthCam.draw(0,150,200,150);
	}
}

void BrisaVideo::setup() {
	if(urlpath != "") {
		video.load(urlpath);
		video.play();
		video.setVolume(0);

		hOriginal = video.getHeight();
		wOriginal = video.getWidth();

		// background-size: cover;
		float videoProp = (float)wOriginal/hOriginal;
		if( videoProp > 4./3. ) {
			hVideo = 768;
			wVideo = wOriginal * (hVideo/hOriginal);
		} else {
			wVideo = 1024;
			hVideo = hOriginal * (wVideo/wOriginal);
		}
	}
}

void BrisaVideo::update() {
	if( video.isLoaded() )  {
		video.update();

		if(kinectLigado) {
		// alloca um fbo com o tamanho original do video
		// pra poder mesclar no shader
			if( !fboKinect.isAllocated() ) {
				fboKinect.allocate(wOriginal,hOriginal);
			}
			updateKinect(depthCam);
		}
	}
}

void BrisaVideo::updateKinect(ofxCvGrayscaleImage imgKinect) {
		fboKinect.begin();
			ofSetColor( 255, 255, 255 );

			// acertar a proporção (cover do kinect com o tam do video argh)
			imgKinect.draw(-wOriginal/10,-hOriginal/10,wOriginal*1.1,hOriginal*1.1);
		fboKinect.end();	
}

void BrisaVideo::setShader(int shader) {
	iShader = shader;
}

void BrisaVideo::draw() {
	if( video.isLoaded() ) {

		shaderBrisaInteracao = retornaShader(iShader);

		shaderBrisaInteracao.begin();

		if(fboKinect.isAllocated()) {
			shaderBrisaInteracao.setUniformTexture( "texture1", fboKinect.getTextureReference(), 1 );
		}

		video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);


		shaderBrisaInteracao.end();	
	}
}





void BrisaKinect::setup() {
	ativa = true;
}

void BrisaKinect::update() {

	if( !fboFiltro.isAllocated() ) {
		fboFiltro.allocate(1024, 768);
	}
	updateFiltro(depthCam);

	// Encontra contornos
	contourFinder.findContours(depthCam, 10, (kinect.width*kinect.height)/2, 20, false);

}

void BrisaKinect::updateFiltro(ofxCvGrayscaleImage imgKinect) {
		fboFiltro.begin();
			ofSetColor( 255, 255, 255 );
			switch(iFiltro) {
				case 0: //RGB
					kinect.draw(0,0);
					break;

				default: //profundidade
					depthCam.draw(0,0);
			}
		fboFiltro.end();	
}
void BrisaKinect::setFiltro(int filtro) {
	iFiltro = filtro;
}
void BrisaKinect::setContorno(bool kinectContorno) {
	mostraContorno = kinectContorno;
}
void BrisaKinect::setFonte(int fonte) {
	iFonte = fonte;
}
void BrisaKinect::setShader(int shader) {
	iShader = shader;
}
void BrisaKinect::draw() {
	if(depthCam.bAllocated && ativa) {

		shaderKinectInteracao = retornaShader(iShader);
	
		shaderKinectInteracao.begin();

		if(fboFiltro.isAllocated()) {
			shaderKinectInteracao.setUniformTexture( "texture1", fboFiltro.getTextureReference(), 1 );
		}

		switch(iFonte) {
			case 0: //RGB
				kinect.draw(0,0,1024,768);
				break;

			default: //profundidade
				depthCam.draw(0,0,1024,768);
		}

		shaderKinectInteracao.end();	


		if(mostraContorno) {
			contourFinder.draw(0,0, 1024,768);
		}
	}
}



void BrisaGifFull::setup() {
	
}

void BrisaGifFull::update() {

}

void BrisaGifFull::loadImg(string gifPath) {
	//5. Carrega numero de img da sequencia
	ofDirectory dirgif;
	urlpasta = gifPath;
	int nimg = dirgif.listDir(urlpasta);

	cout << urlpasta << ": ";
	//6. Set array img size 
	listaImg.resize( nimg );
	//7. Load images
	for (int j=0; j<nimg; j++) {
		//Getting i-th file name
		string fileName = dirgif.getPath( j );
		//Load i-th image
		ofLoadImage( listaImg[j], fileName );
		cout << "|";
	}
	cout << nimg <<" imgs loaded"<< endl;
}

void BrisaGifFull::draw() {
	if(urlpasta !="" && listaImg.size() > 0) {

		float time0 = ofGetElapsedTimef();

		float i = fmodf( time0/10, listaImg.size() ); // [0..duration]

		int ngif = listaImg.size();
		float duration = ngif / 12.0; //25fps		
		float pos = fmodf( time0, duration ); // [0..duration]
		//5. Convert pos in the frame number
		int j = int( pos / duration * ngif );

		listaImg[j].setAnchorPercent( 0.5, 0.5 );

		 // Encontra proporção para redimensionar p fullscreen
		int imgOldH = listaImg[j].getHeight();
		int imgOldW = listaImg[j].getWidth();
		float imgProp = imgOldW/imgOldH;
		int imgNewWidth = vw;
		int imgNewHeight = vh;
		if( imgProp < (4.0/3.0) ) {
			imgNewHeight = (vw*imgOldH)/imgOldW;
		} else {
			imgNewWidth = (vh*imgOldW)/imgOldH;
		}
		listaImg[j].draw( vw/2 , vh/2, imgNewWidth, imgNewHeight); 

	}

}






ofShader retornaShader(int iShader) {
	switch(iShader) {
		
			case 1:
				return blackAsAlpha;
				break;
			case 2:
				return whiteAsAlpha;
				break;
			case 3:
				return invertColor;
				break;
			case 4:
				return fundoNegativo;
				break;
			case 5:
				return frenteNegativo;
				break;

			default:
				return dummyShader;
		}
}