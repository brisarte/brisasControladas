#ifndef BRISA_H__
#define BRISA_H__

const float WIDTH = 1024;
const float HEIGHT = 768;

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
        GLuint pixelsBtn;
        ofPixels pixelsBrisa;
        void mostraBrisas();
        ImVec4 corBrisa;
        ofImage imgBtn;

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
        virtual void desenhaMiniatura(int i);
        void desenhaJanela(int i);

        void listaShaders();
        void loadShader(string shader);
        void listaBrisas();
        void aplicarShader();
        void desenharControlesShader();

        float brilhoBrisa, contrasteBrisa;
        bool rotacionaSozinho, torceSozinho;
        float proporcao, rotacao;
        int deslocX, deslocY;
        void desenharControlesDistorcao();
};

class SombraBrisa : public Brisa {

    ofxKinect *kinecto;
    int camera;

    public:
    SombraBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent, vector<ImVec4> *coresPaleta);
    void draw();
    void update(float dt);

    void ligaKinect();
    void desligaKinect();

    void drawControles(int iBrisa);
    bool blurKinect, desenhaBlur, mirrorHorizontal, mirrorVertical;
    float brightnessGray, contrastGray;
    int iBlur;
    bool sombraHoriz, sombraVert;
    ImVec4 corComplementar;
    ofPixels grayPixels;

    ofxCvGrayscaleImage grayImage, blurGray;
};

class MatrizBrisa : public Brisa {

    ofxKinect *kinecto;
    int camera;

    public:
    MatrizBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent, vector<ImVec4> *coresPaleta);
    void draw();
    void update(float dt);

    void drawControles(int iBrisa);
    void desenhaPixels(int brilho, int width, int height, int x, int y, int gapX, int gapY);
    void desenhaColunas(int brilho, int width, int height, int x, int y, int gapX, int gapY);
    bool blurKinect, desenhaBlur, mirrorHorizontal, mirrorVertical;
    float brightnessGray, contrastGray;
    ofPixels grayPixels;
    int intervaloX, intervaloY;

    vector<ImVec4> *coresPaleta;

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

    float posVideo;

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

    void listaGifs();
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


class FonteKinect : public Brisa {

    ofxKinect *kinect;
    int camera;
    float angKinect;
    float nivelFade;
    public:
    FonteKinect(ofxKinect *kinectGlobal, int cameraSelecionada);
    void draw();
    void update( float dt );

    void ligaKinect();
    void desligaKinect();
    int iBlur;

    void drawControles();

    bool mirrorHorizontal, mirrorVertical;
    ofxCvGrayscaleImage grayImage;
    ofImage exemploGray, exemploCor;
    ofxCvColorImage colorImage;
};

class KinectBrisa : public Brisa {

    ofxKinect *kinecto;
    int camera;
    float angKinect;
    float nivelFade;
    public:
    KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent);
    void draw();
    void update( float dt );

    void desenhaMiniatura(int i);

    void drawControles(int iBrisa);

    bool mirrorHorizontal, mirrorVertical;
    bool ligaContornos;
    ofxCvContourFinder contourFinder;
    ofxCvGrayscaleImage grayImage;
    FonteKinect* fonteKinect;
};
class PoligonoBrisa : public Brisa {

    public:
        PoligonoBrisa(vector<Brisa*> *brisasParent, vector<ImVec4> *coresPaleta);
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
