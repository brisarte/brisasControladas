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

};

class BrisaVideo : public Brisa {
public:
	string urlpath;
	ofVideoPlayer video;
	float hVideo, wVideo; //tamanhos novos
	ofxCvGrayscaleImage depthCam;
	void setup();
	void update();
	void draw();
};

class BrisaKinect : public Brisa {
public:
	void setup();
	void update();
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
		

		void startShader(int numShader);
		void endShader(int numShader);

		shared_ptr<GuiApp> gui;
		shared_ptr<ofAppBaseWindow> window;
		shared_ptr<ofBaseGLRenderer> gl;

		ofColor bgColor;

		string videoPath;
		ofVideoPlayer video;
	
		ofFbo  fboLayer[4];	//buffer para telas
		int vw,vh, kinectAngle;

};
