#include "ofApp.h"


vector<Brisa*> brisasAtivas;

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

	// Atualiza as brisas configuradas
	brisasAtivas = gui->brisasAtivas;

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
	for( vector<Brisa*>::iterator i = brisasAtivas.begin(); i != brisasAtivas.end(); ++i )
    {
        
        brisasAtivas.erase(i);
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