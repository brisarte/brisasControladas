#ifndef BRISA_H__
#define BRISA_H__

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class Brisa {

public:
	bool ativa = false; // Controle de render

	virtual void setup();           	//Configura brisa
	virtual void update( float dt );   	//Recalcula brisa
	virtual void draw();

};


class VideoBrisa : public Brisa {
	
public:
	void draw();
};

class KinectBrisa : public Brisa {
	
public:
	ofxKinect kinecto;
	void setup();
	void draw();
};

class PoligonoBrisa : public Brisa {
	
public:
	void draw();
};

#endif