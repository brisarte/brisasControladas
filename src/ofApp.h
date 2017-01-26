#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "GuiApp.h"


//classe da Brisa
class Brisa {

public:
	bool ativa = false; // Controle de render
	void setup();           	//Configura brisa
	void update( float dt );   	//Recalcula brisa
	void draw();

	int tipoBrisa;

	// Brisa Video
	void setupVideo(string videoPath);
	void updateKinect(ofxCvGrayscaleImage imgKinect);
	string urlpath;
	ofVideoPlayer video;
	float hOriginal, wOriginal; //tamanhos do arquivo
	float hVideo, wVideo; //tamanhos novos
	ofFbo fboKinect;

	// Brisa Contorno
	ofxCvContourFinder contourFinder;

	// Brisa Gif
	void loadGif(string gifPath);
	string urlpasta;
	vector<ofTexture> listaImg;

	// Brisa Poligono
	void desenhaPoligono(int vertices, int radius, bool rotate, bool fill);
	ofColor cor1,cor2;
	int vertices;

	// Brisa Illuminati e Girassol
	ofPoint lookAt;
	int whiteTotalSlow;
	ofPoint baricentro;
	ofPoint olhaPraMim();
	ofImage olho, orbita, girassol;
	ofxCvGrayscaleImage blurImage(ofxCvGrayscaleImage imgOriginal);

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
		
		
		shared_ptr<GuiApp> gui;
		shared_ptr<ofAppBaseWindow> window;
		shared_ptr<ofBaseGLRenderer> gl;

		Brisa brisa1,brisa2,brisa3,brisa4;
    	bool ativaBrisa1,ativaBrisa2,ativaBrisa3,ativaBrisa4;
    	ofFbo fboLayer;
};
