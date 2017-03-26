#include "ofApp.h"

float t0, t1;

vector<Brisa*> brisasAtivas;

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

	// Atualiza as brisas configuradas
	brisasAtivas = gui->brisasAtivas;

	// Quanto tempo passou desde o ultimo update?
	// Resp = t1 - t0
	t0 = t1;
	t1 = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Me mostra essas brisa
	for( int i = 0; i < brisasAtivas.size(); i++ )
    {
        brisasAtivas[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

	// Libera a memória das brisas
	// Brisa vivida é brisa passada
	/*
    for( vector<Brisa*>::iterator i = brisas.begin(); i != brisas.end(); ++i )
    {
        
        brisas.erase(i);
    }*/
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