#ifndef BRISA_H__
#define BRISA_H__

class Brisa {

public:
	bool ativa = false; // Controle de render

	void setup();           	//Configura brisa
	void update( float dt );   	//Recalcula brisa
	void draw();

};


class VideoBrisa : public Brisa {
	
public:
	void draw();
};

class KinectBrisa : public Brisa {
	
public:
	void draw();
};

class PoligonoBrisa : public Brisa {
	
public:
	void draw();
};

#endif