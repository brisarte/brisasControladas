#include "Brisa.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

void Brisa::setup() {

	ativa = true;
}

void Brisa::update( float dt ) {
}

void Brisa::draw() {
}

void VideoBrisa::draw() {

	ofSetColor(255,0,0);
	ofDrawCircle(200,200,200);
}

void KinectBrisa::draw() {

	ofSetColor(255,255,0);
	ofDrawTriangle(700,100,500,300,900,300);
}

void PoligonoBrisa::draw() {

	ofSetColor(255,0,255);
	ofDrawRectangle(312,180,400,400);
}
