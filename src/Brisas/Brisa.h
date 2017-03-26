#ifndef BRISA_H__
#define BRISA_H__

#include "ofxImGui.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class Brisa {

public:
	bool ativa = false; // Controle de render
	string iconPath;
	GLuint btnConfigBrisa; // Botão pra mostrar as configs

	virtual void setup();           	//Configura brisa
	virtual void update( float dt );   	//Recalcula brisa
	virtual void draw();
	void drawButton(ofxImGui::Gui *gui);
};


class VideoBrisa : public Brisa {
public:
	VideoBrisa();
	void draw();
};

class KinectBrisa : public Brisa {
	
public:
	KinectBrisa();
	ofxKinect kinecto;
	void setup();
	void draw();
};

class PoligonoBrisa : public Brisa {
	
public:
	PoligonoBrisa();
	void draw();
};

#endif