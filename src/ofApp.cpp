#include "ofApp.h"

ofxKinect kinect;


BrisaVideo bVideo;
BrisaKinect bKinect;

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

	if(kinectLigado) {
		kinect.update();
		if(depthCam.bAllocated) {
			depthCam.setFromPixels(kinect.getDepthPixels());
		}

	}


	
	if(bKinect.ativa) {
		bKinect.update();
		bKinect.setFiltro(gui->filtroKinectSelected);
		bKinect.setShader(gui->shaderKinectSelected);
		bKinect.setFonte(gui->fonteKinectSelected);
	}

	gl->background(bgColor);

	fboLayer[0].begin();
		ofBackground(0, 0, 0, 0);	


	fboLayer[0].end();

	fboLayer[1].begin();
		ofBackground(0, 0, 0, 0);

		bVideo.draw();

	fboLayer[1].end();

	fboLayer[2].begin();
		ofBackground(0, 0, 0, 0);

		bKinect.draw();

	fboLayer[2].end();

	fboLayer[3].begin();
		ofBackground(0, 0, 0, 0);
	fboLayer[3].end();

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

//--------------------------------------------------------------
void ofApp::endShader(int numShader){
	if(numShader > 0) {		
		shaderInteracao.end();	
	}
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