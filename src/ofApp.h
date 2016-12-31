#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "GuiApp.h"

//classe da Brisa
class Brisa {

public:
	bool ativa = false;
	void setup();           	//Configura brisa
	void update( float dt );   	//Recalcula brisa
	void draw();

	ofShader shaderBrisaInteracao;
};

class BrisaGifFull : public Brisa {

public:
	void setup();           	//Configura brisa
	void update();   	//Recalcula brisa
	void draw();
	void loadImg(string gifPath);
	string urlpasta;
	vector<ofTexture> listaImg;
};

class BrisaVideo : public Brisa {
public:
	string urlpath;
	ofVideoPlayer video;
	float hOriginal, wOriginal; //tamanhos do arquivo
	float hVideo, wVideo; //tamanhos novos
	ofFbo fboKinect;
	int iShader;
	void setup();
	void update();
	void setShader(int i);
	void updateKinect(ofxCvGrayscaleImage depthCam);
	void draw();
};

class BrisaKinect : public Brisa {
public:
	ofFbo fboFiltro;
	ofxCvContourFinder contourFinder;
	bool mostraContorno;
	int iFiltro, iFonte, iShader;
	ofShader shaderKinectInteracao;
	void setContorno(bool kinectContorno);
	void setFiltro(int i);
	void setFonte(int i);
	void setShader(int i);
	void setup();
	void update();
	void updateFiltro(ofxCvGrayscaleImage depthCam);
	void draw();
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		void desenhaBrisa(int tipoBrisa);

		shared_ptr<GuiApp> gui;
		shared_ptr<ofAppBaseWindow> window;
		shared_ptr<ofBaseGLRenderer> gl;

		ofColor bgColor;

		string videoPath, pathGif;
		ofVideoPlayer video;
	
		ofFbo  fboLayer[4];	//buffer para telas
		int kinectAngle;

};

ofShader retornaShader(int iShader);