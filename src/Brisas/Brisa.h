#ifndef BRISA_H__
#define BRISA_H__

#include "ofxImGui.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"


class Brisa {

public:

	string iconPath;
	GLuint btnConfigBrisa; // Botão pra mostrar as configs
	bool configBrisa;
	ofFbo fboBrisa;
	GLuint textureSourceID;
	ofPixels pixelsButtonSource;

    ImVec4 corBrisa;

	virtual void setup();        	//Configura brisa
	virtual void update( float dt );   	//Recalcula brisa
	virtual void draw();

	virtual void drawControles();
	void drawButton(ofxImGui::Gui *gui, int i);
};


class VideoBrisa : public Brisa {
public:
	VideoBrisa();
	void draw();
	void update( float dt );
	ofFbo fboVideo;

	void drawControles();
};


class KinectBrisa : public Brisa {
	
	ofxKinect *kinecto;
	int camera;
public:
	KinectBrisa(ofxKinect *kinectGlobal);
	void draw();
	void update( float dt );

	void ligaKinect();
	void desligaKinect();

	void drawControles();
};


class PoligonoBrisa : public Brisa {
	
public:
	PoligonoBrisa();
	void draw();
	void update( float dt );

	void drawControles();
};

#endif