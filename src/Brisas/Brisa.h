#ifndef BRISA_H__
#define BRISA_H__

#include "ofxImGui.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"


class Brisa {

public:
	
    vector<Brisa*> *brisasAtivas;

	string iconPath;
	GLuint btnConfigBrisa; // Botão pra mostrar as configs
	bool configBrisa;
	ofFbo fboBrisa;
	GLuint textureSourceID;
	ofPixels pixelsBrisa;
	void mostraBrisas();
    ImVec4 corBrisa;

	ofShader shaderBrisa;
	int iBrisaShader;
    bool ligaShader;
    bool clearFrames;

	virtual void setup();        	//Configura brisa
	virtual void update( float dt);   	//Recalcula brisa
	virtual void draw();

	virtual void drawControles(int iBrisa);
	void excluiBrisa(int iBrisa);
	void drawButton(ofxImGui::Gui *gui, int i);
	void listaShaders();
	void loadShader(string shader);
	void listaBrisas();
};


class VideoBrisa : public Brisa {
	float heightDraw, widthDraw, heightOrig, widthOrig;


public:
	VideoBrisa(vector<Brisa*> *brisasParent);
	void draw();
	void update( float dt );

	ofVideoPlayer video;
	string caminhoVideo;
	ofFbo fboKinect;

	void drawControles(int iBrisa);

	void listaVideos();
	void setupVideo(string videoPath);
};


class KinectBrisa : public Brisa {
	
	ofxKinect *kinecto;
	int camera;
public:
	KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent);
	void draw();
	void update( float dt );

	void ligaKinect();
	void desligaKinect();

	void drawControles(int iBrisa);

	bool ligaContornos;
};


class PoligonoBrisa : public Brisa {
	
public:
	PoligonoBrisa(vector<Brisa*> *brisasParent);
	void draw();
	void update( float dt );

	void drawControles(int iBrisa);

	void desenhaPoligono(int radius);
	ImVec4 corComplementar;
	int vertices;
	int quantidade;
	int distancia;
	bool preencher;
	bool trocaVertices;
	bool rotacionar; 
};

#endif