#include "ofApp.h"

bool kinectLigado;
ofxCvColorImage kinectRGB;
ofxCvGrayscaleImage kinectDepth;

float prevTime, actualTime;
//--------------------------------------------------------------
void ofApp::setup(){

	kinectRGB.allocate(640,480);
	kinectDepth.allocate(640,480);

}

//--------------------------------------------------------------
void ofApp::update(){
	prevTime = actualTime;
	actualTime = ofGetElapsedTimef();

	// Pega configurações do kinect da Janela de GUI
	kinectLigado = gui->kinectLigado;

	kinectRGB = gui->kinectRGB;
	kinectDepth = gui->kinectDepth;


	ativaBrisa1 = gui->ativaBrisa1;

	if(ativaBrisa1 && !brisa1.ativa) {
		brisa1.setup();
		brisa1.ativa = true;
	}

	if(brisa1.ativa) {
		brisa1.update(actualTime - prevTime);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	kinectDepth.draw(0,0,1024,768);


	if(brisa1.ativa) {
		brisa1.draw();
	}
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



void Brisa::setup() {
	setupVideo("claricefalcao.mp4");
	ativa = true;
}

void Brisa::update(float dt) {
	if( video.isLoaded() )  {
		video.update();

		if(kinectLigado) {
		// alloca um fbo com o tamanho original do video
		// pra poder mesclar no shader
			if( !fboKinect.isAllocated() || fboKinect.getWidth() != wOriginal ) {
				fboKinect.clear();
				fboKinect.allocate(wOriginal,hOriginal);
			}
			updateKinect(kinectDepth);
		}
	}
}

void Brisa::draw() {
	if( video.isLoaded() ) {

		/*shaderBrisaInteracao = retornaShader(iShader);

		shaderBrisaInteracao.begin();

		if(fboKinect.isAllocated()) {
			shaderBrisaInteracao.setUniformTexture( "texture1", fboKinect.getTextureReference(), 1 );
		}
*/
		video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);


//		shaderBrisaInteracao.end();	
	}
}
void Brisa::setupVideo(string videoPath) {
	urlpath = "videos/" + videoPath;
	cout << "Video load: " << urlpath;
	if(urlpath != "") {
		video.load(urlpath);
		video.play();
		video.setPosition(prevTime-(long)prevTime);
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
		cout << "\nredimensionado: " << wOriginal << "x" << hOriginal << " => " << wVideo << "x" << hVideo;
	}
}
void Brisa::updateKinect(ofxCvGrayscaleImage imgKinect) {
		fboKinect.begin();
			ofSetColor( 255, 255, 255 );

			// acertar a proporção (cover do kinect com o tam do video argh)
			imgKinect.draw(-wOriginal/10,-hOriginal/10,wOriginal*1.1,hOriginal*1.1);
		fboKinect.end();	
}
