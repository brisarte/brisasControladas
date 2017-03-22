#include "ofApp.h"

bool kinectLigado;
ofxCvColorImage kinectRGB;
ofxCvGrayscaleImage kinectDepth, kinectDepthBlur;


float prevTime, actualTime;

ofImage logoBrisa;
ofShader shaders[6];

int vw = 1024;
int vh = 768;

VideoBrisa video1;
PoligonoBrisa poligono1;
KinectBrisa kinect1;

//--------------------------------------------------------------
void ofApp::setup(){

	kinectRGB.allocate(640,480);
	kinectDepth.allocate(640,480);
	fboLayer.allocate(1024,768);

	timeUltimaBrisa = 0;
	tempoFade = 2; 


	logoBrisa.load("../data/img/logobrisarte.png");

	




	shaders[0].load( "shaders/vertexdummy.c", "shaders/fragdummy.c" ); // dummyShader
	shaders[1].load( "shaders/vertexdummy.c", "shaders/blackAsAlpha.c" ); // blackAsAlpha
	shaders[2].load( "shaders/vertexdummy.c", "shaders/whiteAsAlpha.c" ); // whiteAsAlpha
	shaders[3].load( "shaders/vertexdummy.c", "shaders/invertColor.c" ); // invertColor
	shaders[4].load( "shaders/vertexdummy.c", "shaders/frenteNegativo.c" ); // frenteNegativo
	shaders[5].load( "shaders/vertexdummy.c", "shaders/fundoNegativo.c" ); // fundoNegativo
}

//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(0,0,0);

	prevTime = actualTime;
	actualTime = ofGetElapsedTimef();

	// Pega configurações do kinect da Janela de GUI
	kinectLigado = gui->kinectLigado;

	kinectRGB = gui->kinectRGB;
	kinectDepth = gui->kinectDepth;

	tempoBrisa = gui->tempoBrisa;

	ativaBrisa1 = gui->ativaBrisa1;
	ativaBrisa2 = gui->ativaBrisa2;
	ativaBrisa3 = gui->ativaBrisa3;
	ativaBrisa4 = gui->ativaBrisa4;

/*
	if(ativaBrisa1 && !brisa1.ativa) {
		brisa1.tipoBrisa = 3; //video
		brisa1.setup();
		brisa1.ativa = true;
	}
	if(ativaBrisa2 && !brisa2.ativa) {
		brisa2.tipoBrisa = 4; //gifFull
		brisa2.setup();
		brisa2.ativa = true;
	}
	if(ativaBrisa3 && !brisa3.ativa) {
		brisa3.tipoBrisa = 5; //contorno
		brisa3.setup();
		brisa3.ativa = true;
	}
	if(ativaBrisa4 && !brisa4.ativa) {
		brisa4.tipoBrisa = 1; //contorno
		brisa4.setup();
		brisa4.ativa = true;
	}

	if(brisa1.ativa) {
		brisa1.update(actualTime - prevTime);
	}
	if(brisa2.ativa) {
		brisa2.update(actualTime - prevTime);
	}
	if(brisa3.ativa) {
		brisa3.update(actualTime - prevTime);
	}
	if(brisa4.ativa) {
		brisa4.update(actualTime - prevTime);
	}


	fboLayer.begin();
	if(brisa1.ativa) {
		brisa1.draw();
	}
	if(brisa2.ativa) {
		brisa2.draw();
	}
	if(brisa3.ativa) {
		brisa3.draw();
	}
	if(brisa4.ativa) {
		brisa4.draw();
	}
	fboLayer.end();
	*/

}

//--------------------------------------------------------------
void ofApp::draw(){


	fboLayer.draw(0,0,vw,vh);
	video1.draw();
	kinect1.draw();
	poligono1.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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