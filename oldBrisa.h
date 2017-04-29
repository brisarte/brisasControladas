
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
