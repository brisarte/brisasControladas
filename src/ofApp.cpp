#include "ofApp.h"

float t0, t1;

vector<Brisa*> brisas;

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

	// Atualiza as brisas configuradas
	brisas = gui->brisas;

	// Quanto tempo passou desde o ultimo update?
	// Resp = t1 - t0
	t0 = t1;
	t1 = ofGetElapsedTimef();


	if (!brisas[2]->ativa) {
		brisas[2]->setup();
		cout << "kinect ligou";
	}


}

//--------------------------------------------------------------
void ofApp::draw(){

	// Me mostra essas brisa
	for( int i = 0; i < brisas.size(); i++ )
    {
        brisas[i]->draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

	// Libera a memória das brisas
	// Brisa vivida é brisa passada
	/*
    for( vector<Brisa*>::iterator i = brisas.begin(); i != brisas.end(); ++i )
    {
        delete *i;
    }
    // empty the container
    brisas.clear();
    */
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