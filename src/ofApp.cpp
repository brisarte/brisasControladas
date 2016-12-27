#include "ofApp.h"

ofxKinect kinect;


BrisaVideo bVideo;
BrisaKinect bKinect;

// Variáveis globais pro kinect
ofxCvGrayscaleImage depthCam;
bool kinectLigado = false;

ofShader blackAsAlpha, whiteAsAlpha, invertColor, fundoNegativo, frenteNegativo, dummyShader;
ofFbo	fboDepthKinect, fboRGBKinect;


ofShader shaderInteracao;
ofFbo fboInteracao;

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
	fboDepthKinect.allocate(vw,vh);
	fboInteracao.allocate(vw,vh);

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

	if(kinectLigado) {
		fboDepthKinect.begin();
			ofSetColor( 255, 255, 255 );
			depthCam.draw(0,0);
		fboDepthKinect.end();	

		if(depthCam.bAllocated) {
			depthCam.setFromPixels(kinect.getDepthPixels());
		}
	}

	kinect.update();

	// useless
	if(bKinect.ativa) {
		bKinect.update();
	}

	gl->background(bgColor);

	fboLayer[0].begin();
		ofBackground(0, 0, 0, 0);	

		bVideo.draw();

	fboLayer[0].end();

	fboLayer[1].begin();
		ofBackground(0, 0, 0, 0);

		startShader(gui->shaderSelected);

		bVideo.draw();

		endShader(gui->shaderSelected);

	fboLayer[1].end();

	fboLayer[2].begin();
		ofBackground(0, 0, 0, 0);

		startShader(gui->shaderSelected);
		
		bKinect.draw();

		endShader(gui->shaderSelected);

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
void ofApp::startShader(int numShader){
	if(numShader > 0) {		
			
		fboInteracao = fboDepthKinect;
		switch(numShader) {
			case 1:
				shaderInteracao = blackAsAlpha;
				break;
			case 2:
				shaderInteracao = whiteAsAlpha;
				break;
			case 3:
				shaderInteracao = invertColor;
				break;
			case 4:
				shaderInteracao = fundoNegativo;
				break;
			case 5:
				shaderInteracao = frenteNegativo;
				break;
		}
		shaderInteracao.begin();

		shaderInteracao.setUniformTexture( "texture1", fboInteracao.getTextureReference(), 1 );
	}
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
void BrisaVideo::setup() {
	if(urlpath != "") {
		video.load(urlpath);
		video.play();
		video.setVolume(0);

		float videoH = video.getHeight();
		float videoW = video.getWidth();
		float videoProp = (float)videoW/videoH;
		if( videoProp > 4./3. ) {
			hVideo = 768;
			wVideo = videoW * (hVideo/videoH);
		} else {
			wVideo = 1024;
			hVideo = videoH * (wVideo/videoW);
		}
	}
}
void BrisaVideo::update() {
	if( video.isLoaded() )  {
		video.update();
	}
}
void BrisaVideo::draw() {
	if( video.isLoaded() ) {
		
		video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);
	}
}

void BrisaKinect::setup() {
	ativa = true;
}
void BrisaKinect::update() {
}
void BrisaKinect::draw() {
	if(depthCam.bAllocated && ativa) {

		kinect.draw(600,450,400,300);
	}
}