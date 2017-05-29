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
	string fragShaderPath;
	int iBrisaShader;
    bool ligaShader;
    bool clearFrames;

	virtual void setup();        	//Configura brisa
	virtual void update( float dt);   	//Recalcula brisa
	virtual void draw();

	virtual void drawControles(int iBrisa);
	void excluiBrisa(int iBrisa);
	void drawButton(bool desenhaMiniaturas, int i);

	void listaShaders();
	void loadShader(string shader);
	void listaBrisas();
	void desenharControlesShader();

	float brilhoBrisa, contrasteBrisa;
	bool rotacionaSozinho, torceSozinho;
	float proporcao, rotacao;
	int deslocX, deslocY;
	void desenharControlesDistorcao();
};

class MatrizBrisa : public Brisa {

	ofxKinect *kinecto;
	int camera;

public:
	MatrizBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent);
	void draw();
	void update(float dt);

	void ligaKinect();
	void desligaKinect();

	void drawControles(int iBrisa);
	bool blurKinect, desenhaBlur, mirrorHorizontal, mirrorVertical;
	float brightnessGray, contrastGray;
	ofPixels grayPixels;
	int intervaloX, intervaloY;

    ImVec4 coresBrisa[7];

	ofxCvGrayscaleImage grayImage, blurGray;
};

class VideoBrisa : public Brisa {
	float heightDraw, widthDraw, heightOrig, widthOrig;


public:
	VideoBrisa(vector<Brisa*> *brisasParent);
	void draw();
	void update(float dt);

	ofVideoPlayer video;
	string caminhoVideo;
	ofFbo fboKinect;

	void drawControles(int iBrisa);

	void listaVideos();
	void setupVideo(string videoPath);
};

class GifBrisa : public Brisa {
	float heightDraw, widthDraw, heightOrig, widthOrig;


public:
	GifBrisa(vector<Brisa*> *brisasParent);
	void draw();
	void update(float dt);

	ofVideoPlayer video;
	string caminhoVideo;
	float proporcao, rotacao;
	int deslocX, deslocY;

	void drawControles(int iBrisa);

	void listaVideos();
	void setupVideo(string videoPath);
};



class ImagemBrisa : public Brisa {


public:
	ImagemBrisa(vector<Brisa*> *brisasParent);
	void draw();
	void update(float dt);

	ofImage img;
	string caminhoImagem;

	void drawControles(int iBrisa);

	void listaImagens();
	void setupImagem(string imgPath);

	bool converterGray;
	ofxCvGrayscaleImage imagemGray;

};


class KinectBrisa : public Brisa {
	
	ofxKinect *kinecto;
	int camera;
	float angKinect;
public:
	KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent);
	void draw();
	void update( float dt );

	void ligaKinect();
	void desligaKinect();

	void drawControles(int iBrisa);

	bool mirrorHorizontal, mirrorVertical;
	bool ligaContornos;
	ofxCvContourFinder contourFinder;
	ofxCvGrayscaleImage grayImage;
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


	ImVec4 coresBrisa[7];
};

#endif