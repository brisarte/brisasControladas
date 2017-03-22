#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"


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

    ofxKinect kinect;
    void startKinect();
    
    ofxImGui::Gui gui;

    GLuint kinectGLuintRGB;
    GLuint kinectGLuintDepth;

    bool kinectLigado;
    bool mirrorKinect;
    ofxCvColorImage kinectRGB;
    ofxCvGrayscaleImage kinectDepth;

    configsBrisa configsBrisa1,configsBrisa2,configsBrisa3,configsBrisa4;
    bool ativaBrisa1,ativaBrisa2,ativaBrisa3,ativaBrisa4;

    float tempoBrisa;


    vector<string> listaGifFull, listaVideos;
    int nVideos, nGifsFull;
};