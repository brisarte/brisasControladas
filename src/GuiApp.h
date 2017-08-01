#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Brisas/Brisa.h"


//classe da Brisa
class configsBrisa {

public: 
    int tipoBrisa;

    int iShader;
    string urlpath;
    ofVideoPlayer video;
    float hOriginal, wOriginal; //tamanhos do arquivo
    float hVideo, wVideo; //tamanhos novos
    ofFbo fboKinect;

    // Brisa Contorno

    // Brisa Gif
    string gifPath;
    string urlpasta;
    vector<ofTexture> listaImg;

    // Brisa Poligono
    ofColor cor1,cor2;
    int vertices;

};

class GuiApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    
    ofxImGui::Gui gui;

    vector<Brisa*> brisas;
    vector<Brisa*> brisasAtivas;
    ofxKinect kinectGlobal;

    GLuint btnCriaVideo,btnCriaPoligono, btnCriaKinect, btnCriaImg, 
		btnCriaGif, btnCriaMatriz, btnCriaSombras, btnCriaMandala, btnCriaBorda;

	vector<ImVec4> coresPaleta;
	ofBlendMode blendMode;
	int iBlend;
    bool desenhaMiniaturas;

};