#include "ofApp.h"

int vw, vh;
ofxKinect kinect;


BrisaVideo bVideo;
BrisaKinect bKinect;
BrisaGifFull bGifFull;
BrisaPoligonos bPoligonos;
BrisaIllu bIllu;
BrisaGira bGira;

// Variáveis globais pro kinect
ofxCvGrayscaleImage depthCam;
ofxCvGrayscaleImage depthBlur, sombra, sombraMirror;
bool kinectLigado = false;

ofShader blackAsAlpha, whiteAsAlpha, invertColor, fundoNegativo, frenteNegativo, dummyShader;

ofShader shaderInteracao;
ofColor coresRole[4];
ofColor verdeCor(0,231,109), cianoCor(0,255,255), laranjaCor(254,165,1), rosaCor(255,82,110);

ofImage olho, orbita, girassol, logoBrisa, msg;
float time0, timeUltimaBrisa = 0;

float tempoBrisa = 10;
float tempoFade = 3;

int whiteTotalSlow = 0;
ofPoint baricentro(0,0);

int experiencia = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	// Aloca memoria com tamanho da viewport
	vh = 768;
	vw = 1024;
	gl->background(bgColor);
	videoPath = "";
	pathGif = "";

	//alloc de fbo
	for(int i = 0; i < 4; i++) {
		fboLayer[i].allocate(vw,vh);
	}

	dummyShader.load( "shaders/vertexdummy.c", "shaders/fragdummy.c" );
	blackAsAlpha.load( "shaders/vertexdummy.c", "shaders/blackAsAlpha.c" );
	whiteAsAlpha.load( "shaders/vertexdummy.c", "shaders/whiteAsAlpha.c" );
	invertColor.load( "shaders/vertexdummy.c", "shaders/invertColor.c" );
	frenteNegativo.load( "shaders/vertexdummy.c", "shaders/frenteNegativo.c" );
	fundoNegativo.load( "shaders/vertexdummy.c", "shaders/fundoNegativo.c" );

	// kinect
	kinectAngle = 0;

	coresRole[0] = verdeCor;
	coresRole[1] = cianoCor;
	coresRole[2] = laranjaCor;
	coresRole[3] = rosaCor;

	bPoligonos.setup();

	girassol.load("../data/img/girassol.png");
	olho.load("../data/img/olhoillu.png");
	logoBrisa.load("../data/img/logobrisarte.png");
	orbita.load("../data/img/orbitaillu.png");

	tipoBrisaFbo = { 0, 0, 0, 0};

}

//--------------------------------------------------------------
void ofApp::update(){
	time0 = ofGetElapsedTimef();
	if(time0 - timeUltimaBrisa > tempoBrisa) {
		timeUltimaBrisa = time0;
		experiencia = (int)ofRandom(0,4);
		switch(experiencia) {
			case 0: {
				//video random
				bVideo.setup(gui->videosDisponiveis[(int)ofRandom(0,gui->videosDisponiveis.size())]);

				float probShader = ofRandom(0,1);
				if(probShader > 0.95) {
					gui->shaderVideoSelected = 4;
				} else if(probShader > 0.9) {
					gui->shaderVideoSelected = 1;
				} else if(probShader > 0.85) {
					gui->shaderVideoSelected = 2;
				} else if(probShader > 0.75) {
					gui->shaderVideoSelected = 3;
				} else if(probShader > 0.55) {
					gui->shaderVideoSelected = 0;
				} else {
					gui->shaderVideoSelected = 5;
				}

				int brisaKinect = 2;
				float probKinect = ofRandom(0,1);
				if (probKinect > 0.5) { // n mostra kinect
					brisaKinect = 0;
				}

				float probFonteKinect = ofRandom(0,1);
				gui->fonteKinectSelected = 0;
				if (probFonteKinect > 0.5) { // n mostra kinect
					gui->fonteKinectSelected = 1;
				}

				float probShaderKinect = (int)ofRandom(0,6);
				gui->shaderKinectSelected = probShaderKinect;

				float probFiltroKinect = ofRandom(0,1);
				gui->filtroKinectSelected = 0;
				if (probFiltroKinect > 0.5) { // n mostra kinect
					gui->filtroKinectSelected = 1;
				}

				gui->tipoBrisaFbo = { 1, brisaKinect, 0, 0 };
				}break;

			case 1: {//random gif full
				bGifFull.loadImg(gui->listaGifFull[(int)ofRandom(0,gui->listaGifFull.size())]);

				int brisaKinect = 2;
				float probKinect = ofRandom(0,1);
				if (probKinect > 0.5) { // n mostra kinect
					brisaKinect = 0;
				}

				float probFonteKinect = ofRandom(0,1);
				gui->fonteKinectSelected = 0;
				if (probFonteKinect > 0.5) { // n mostra kinect
					gui->fonteKinectSelected = 1;
				}

				float probShaderKinect = (int)ofRandom(0,6);
				gui->shaderKinectSelected = probShaderKinect;

				float probFiltroKinect = ofRandom(0,1);
				gui->filtroKinectSelected = 0;
				if (probFiltroKinect > 0.5) { // n mostra kinect
					gui->filtroKinectSelected = 1;
				}

				gui->tipoBrisaFbo = { 3, brisaKinect, 0, 0 };
				}break;
			case 2: { //poligonos

				float probIlluGira = ofRandom(0,1);
				int brisaLook = 5; //olho illu
				if (probIlluGira > 0.5) { // girassol
					brisaLook = 6;
				}

				gui->tipoBrisaFbo = { 0, 4, brisaLook, 0 };
				}break;
			case 3: { //sombras

				gui->tipoBrisaFbo = { 0, 0, 0, 8};
				}break;
		}
		float probContorno = ofRandom(0,1);
		if (probContorno > 0.8) { // mostra contorno
			gui->tipoBrisaFbo[3] = 7;
		}
	}

	bgColor = gui->bgColor;

	if(videoPath != gui->videoPath) {
		videoPath = gui->videoPath;
		bVideo.setup(videoPath);
	}
	bVideo.update();
	bVideo.setShader(gui->shaderVideoSelected);

	if(pathGif != gui->pastaGif) {
		pathGif = gui->pastaGif;
		bGifFull.loadImg(pathGif);
	}

	if(kinectLigado) {
		kinect.update();
		if(depthCam.bAllocated) {
			depthCam.setFromPixels(kinect.getDepthPixels());
			depthBlur = depthCam;
			getBlurImage(depthBlur, 111);
			setSombraMirror(depthCam, 0.95 );
		}

		bKinect.update();

	}

	bIllu.update();
	bGira.update();

	
	if(bKinect.ativa) {
		bKinect.setFiltro(gui->filtroKinectSelected);
		bKinect.setContorno(gui->kinectContorno);
		bKinect.setShader(gui->shaderKinectSelected);
		bKinect.setFonte(gui->fonteKinectSelected);
	}


	//se trocou a brisa manualmente atualiza
	for(int i = 0; i < 4; i++) {
		if(gui->tipoBrisaFbo[i] != tipoBrisaFbo[i]) {
			tipoBrisaFbo[i] = gui->tipoBrisaFbo[i];
		}
	}

	bPoligonos.update();

	gl->background(bgColor);

	fboLayer[0].begin();
		ofBackground(0, 0, 0, 0);	
		desenhaBrisa(tipoBrisaFbo[0]);

	fboLayer[0].end();

	fboLayer[1].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(tipoBrisaFbo[1]);
	fboLayer[1].end();

	fboLayer[2].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(tipoBrisaFbo[2]);

	fboLayer[2].end();

	fboLayer[3].begin();
		ofBackground(0, 0, 0, 0);
		desenhaBrisa(tipoBrisaFbo[3]);

	fboLayer[3].end();

}

//--------------------------------------------------------------
void ofApp::desenhaBrisa(int tipoBrisa){
	switch(tipoBrisa){
		//No Breeza
		case 0:
			break;
		//Video
		case 1:
			bVideo.draw();
			break;
		//Video
		case 2:
			bKinect.draw();
			break;
		//GifFull
		case 3:
			bGifFull.draw();
			break;
		//Poligonos
		case 4:
			bPoligonos.draw();
			break;
		//Olho illu
		case 5:
			bIllu.draw();
			break;
		//Gira
		case 6:
			bGira.draw();
			break;
			
		//Contorno
		case 7:
			bKinect.desenhaContorno();
			break;

		//Contorno
		case 8:
			desenhaSombraMirror();
			break;
			
		default:
			break;
	}
}


//--------------------------------------------------------------
void ofApp::draw(){
	gl->setColor(0);

	// Desenha Brisas
	for(int i = 0; i < 4; i++) {

		//fade
		if(time0 > timeUltimaBrisa) {
			// Testa se ja passou tempo pra começar o fade && ainda nao acabou a brisa
			if(time0 - timeUltimaBrisa > (tempoBrisa - tempoFade) && time0 - timeUltimaBrisa < tempoBrisa) {
				ofSetColor(255, 255, 255, ofMap(time0,timeUltimaBrisa + tempoBrisa - tempoFade,timeUltimaBrisa + tempoBrisa,255,0));
			}
			//Testa se ta no comecinho da brisa
			else if(time0 - timeUltimaBrisa < tempoFade) {
				ofSetColor(255, 255, 255, ofMap(time0,timeUltimaBrisa,timeUltimaBrisa+tempoFade,0,255));
			} else {
				ofSetColor(255, 255, 255);
			}
		}

		fboLayer[i].draw(0,0,vw,vh);
	}

	// Testa se ja passou tempo pra começar o fade && ainda nao acabou a brisa
	if(time0 - timeUltimaBrisa > (tempoBrisa - tempoFade) && time0 - timeUltimaBrisa < tempoBrisa) {
		ofSetColor(255, 255, 255, ofMap(time0,timeUltimaBrisa + tempoBrisa - tempoFade,timeUltimaBrisa + tempoBrisa,0,255));
	}
	//Testa se ta no comecinho da brisa
	else if(time0 - timeUltimaBrisa < tempoFade) {
		ofSetColor(255, 255, 255, ofMap(time0,timeUltimaBrisa,timeUltimaBrisa+tempoFade,255,0));
	} else {
		ofSetColor(255, 255, 255, 0);
	}
	logoBrisa.setAnchorPercent(0.5,0.5);
	logoBrisa.draw(vw/2,vh/2);
	ofSetColor(255, 255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {

		case OF_KEY_UP:
			kinectAngle++;
			if(kinectAngle>30) kinectAngle=30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;
			
		case OF_KEY_DOWN:
			kinectAngle--;
			if(kinectAngle<-30) kinectAngle=-30;
			kinect.setCameraTiltAngle(kinectAngle);
			break;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
}

void GuiApp::startBrisaKinect(ofxDatGuiButtonEvent e)
{
	bKinect.setup();
}

void GuiApp::closeKinect(ofxDatGuiButtonEvent e)
{
	kinect.setCameraTiltAngle(0); // zero the tilt
	kinect.close();

	kinectLigado = false;

}
void GuiApp::startKinect(ofxDatGuiButtonEvent e)
{
	kinect.setRegistration(true);
	kinect.init();
	kinect.open();
	kinect.setCameraTiltAngle(0);

	depthCam.allocate(kinect.width, kinect.height);
	sombra.allocate(kinect.width, kinect.height);
	sombraMirror.allocate(kinect.width, kinect.height);

	kinectLigado = true;
}

void GuiApp::drawKinect()
{
	if(kinectLigado) {
		kinect.draw(0,0,200,150);
		depthCam.draw(0,150,200,150);
		depthBlur.draw(0,300,200,150);
		sombra.draw(0,450,200,150);
		sombraMirror.draw(0,600,200,150);
	}
}

void BrisaVideo::setup(string videoPath) {
	urlpath = "videos/" + videoPath;
	cout << "Video load: " << urlpath;
	if(urlpath != "") {
		video.load(urlpath);
		video.play();
		video.setPosition(time0-(long)time0);
		video.setVolume(0);

		hOriginal = video.getHeight();
		wOriginal = video.getWidth();

		// background-size: cover;
		float videoProp = (float)wOriginal/hOriginal;
		if( videoProp > 4./3. ) {
			hVideo = 768;
			wVideo = wOriginal * (hVideo/hOriginal);
		} else {
			wVideo = 1024;
			hVideo = hOriginal * (wVideo/wOriginal);
		}
	}
}

void BrisaVideo::update() {
	if( video.isLoaded() )  {
		video.update();

		if(kinectLigado) {
		// alloca um fbo com o tamanho original do video
		// pra poder mesclar no shader
			if( !fboKinect.isAllocated() || fboKinect.getWidth() != wOriginal ) {
				fboKinect.clear();
				fboKinect.allocate(wOriginal,hOriginal);
			}
			updateKinect(depthCam);
		}
	}
}

void BrisaVideo::updateKinect(ofxCvGrayscaleImage imgKinect) {
		fboKinect.begin();
			ofSetColor( 255, 255, 255 );

			// acertar a proporção (cover do kinect com o tam do video argh)
			imgKinect.draw(-wOriginal/10,-hOriginal/10,wOriginal*1.1,hOriginal*1.1);
		fboKinect.end();	
}

void BrisaVideo::setShader(int shader) {
	iShader = shader;
}

void BrisaVideo::draw() {
	if( video.isLoaded() ) {

		shaderBrisaInteracao = retornaShader(iShader);

		shaderBrisaInteracao.begin();

		if(fboKinect.isAllocated()) {
			shaderBrisaInteracao.setUniformTexture( "texture1", fboKinect.getTextureReference(), 1 );
		}

		video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);


		shaderBrisaInteracao.end();	
	}
}





void BrisaKinect::setup() {
	ativa = true;
}

void BrisaKinect::update() {

	if( !fboFiltro.isAllocated() ) {
		fboFiltro.allocate(1024, 768);
	}
	updateFiltro(depthCam);

	// Encontra contornos
	contourFinder.findContours(depthCam, 10, (kinect.width*kinect.height)/2, 20, false);

}

void BrisaKinect::updateFiltro(ofxCvGrayscaleImage imgKinect) {
		fboFiltro.begin();
			ofSetColor( 255, 255, 255 );
			switch(iFiltro) {
				case 0: //RGB
					kinect.draw(0,0);
					break;

				default: //profundidade
					depthCam.draw(0,0);
			}
		fboFiltro.end();	
}
void BrisaKinect::setFiltro(int filtro) {
	iFiltro = filtro;
}
void BrisaKinect::setContorno(bool kinectContorno) {
	mostraContorno = kinectContorno;
}
void BrisaKinect::setFonte(int fonte) {
	iFonte = fonte;
}
void BrisaKinect::setShader(int shader) {
	iShader = shader;
}
void BrisaKinect::draw() {
	if(depthCam.bAllocated && ativa) {

		shaderKinectInteracao = retornaShader(iShader);
	
		shaderKinectInteracao.begin();

		if(fboFiltro.isAllocated()) {
			shaderKinectInteracao.setUniformTexture( "texture1", fboFiltro.getTextureReference(), 1 );
		}

		switch(iFonte) {
			case 0: //RGB
				kinect.draw(0,0,1024,768);
				break;

			default: //profundidade
				depthCam.draw(0,0,1024,768);
		}

		shaderKinectInteracao.end();	


		if(mostraContorno) {
			contourFinder.draw(0,0, 1024,768);
		}
	}
}

void BrisaKinect::desenhaContorno() {
	if(depthCam.bAllocated) {
		contourFinder.draw(0,0, 1024,768);
	}
}



void BrisaGifFull::setup() {
	
}

void BrisaGifFull::update() {

}

void BrisaGifFull::loadImg(string gifPath) {
	//5. Carrega numero de img da sequencia
	ofDirectory dirgif;
	urlpasta = gifPath;
	int nimg = dirgif.listDir(urlpasta);

	cout << urlpasta << ": ";
	//6. Set array img size 
	listaImg.resize( nimg );
	//7. Load images
	for (int j=0; j<nimg; j++) {
		//Getting i-th file name
		string fileName = dirgif.getPath( j );
		//Load i-th image
		ofLoadImage( listaImg[j], fileName );
		cout << "|";
	}
	cout << nimg <<" imgs loaded"<< endl;
}

void BrisaGifFull::draw() {
	if(urlpasta !="" && listaImg.size() > 0) {

		float i = fmodf( time0/10, listaImg.size() ); // [0..duration]

		int ngif = listaImg.size();
		float duration = ngif / 12.0; //25fps		
		float pos = fmodf( time0, duration ); // [0..duration]
		//5. Convert pos in the frame number
		int j = int( pos / duration * ngif );

		listaImg[j].setAnchorPercent( 0.5, 0.5 );

		 // Encontra proporção para redimensionar p fullscreen
		int imgOldH = listaImg[j].getHeight();
		int imgOldW = listaImg[j].getWidth();
		float imgProp = imgOldW/imgOldH;
		int imgNewWidth = vw;
		int imgNewHeight = vh;
		if( imgProp < (4.0/3.0) ) {
			imgNewHeight = (vw*imgOldH)/imgOldW;
		} else {
			imgNewWidth = (vh*imgOldW)/imgOldH;
		}
		listaImg[j].draw( vw/2 , vh/2, imgNewWidth, imgNewHeight); 

	}
}



void BrisaPoligonos::setup() {
	ativa = true;
	int indCor = fmodf( time0/8, 4); // [0..4]
	cor1 = coresRole[indCor];
	cor1.set(0,255,0);

	cor2.set(cor1);
	cor2.setHue( (int(time0*5)+200) %360);
}

void BrisaPoligonos::update() {
	if(ativa) {

		float time0 = ofGetElapsedTimef();
		int indCor = fmodf( time0/8, 4); // [0..4]
		cor1 = coresRole[indCor];

		cor2.set(cor1);
		cor2.setHue( (int(time0*5)+200) %360);
	}
}

void BrisaPoligonos::draw() {

	// Desenha poligono
	ofSetColor(cor1);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7-.3))*100 + 800 ,true,true);

	// Desenha poligono
	ofSetColor(cor2);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7-.2))*100 + 700 ,true,true);

	// Desenha poligono
	ofSetColor(cor1);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7-.1))*100 + 600 ,true,true);

	// Desenha poligono
	ofSetColor(cor2);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7))*100 + 500 ,true,true);

	// Desenha poligono
	ofSetColor(cor1);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7+.1))*100 + 400 ,true,true);

	// Desenha poligono
	ofSetColor(cor2);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7+.2))*100 + 300 ,true,true);

	// Desenha poligono
	ofSetColor(cor1);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7+.3))*100 + 200 ,true,true);

	// Desenha poligono
	ofSetColor(cor2);
	desenhaPoligono( int(abs(sin(time0*0.1)*4)) + 4, abs(sin(time0*0.7)+.4)*100 + 100 ,true,true);
}


// Desenha poligono
void BrisaPoligonos::desenhaPoligono(int vertices, int radius, bool rotate, bool fill) {
	if(vertices < 3)
		vertices = 3;
	//corrigindo tamanho aparente
	radius = radius - vertices*8;
	if(fill) {
		ofFill();
	}else {
		ofNoFill();
	}
	glPushMatrix();

	//Gambizinha pra caso seja o triangulo com beat
	if(vertices == 3 && !rotate){
		glTranslatef(vw/2,vh/2+70, 0);
	} else {
		// o que aocntecia normalmente antes da gambi
		glTranslatef(vw/2,vh/2, 0);
	}

	if (rotate) {
		glRotatef( sin(time0*0.5)*50 + 	(360/vertices-1)-(360/vertices) + 100, 0, 0, 1); 
	} else {
		glRotatef( 180, 0, 0, 1); 
	}

	ofBeginShape();
	for(int i = 0; i < vertices+1; i++) {
		float theta = (TWO_PI/vertices) * i;
		ofVertex( sin(theta)*radius , cos(theta)*radius ,0);
	}
	ofEndShape();

	glPopMatrix();
}




void BrisaIllu::setup() {
}

void BrisaIllu::update() {
	lookAt = olhaPraMim();
}

void BrisaIllu::draw() {
	glPushMatrix();

	glTranslatef(vw/2,vh/2, 0);

	ofPoint moveOlho;
	moveOlho.x = ofMap(lookAt.x,0,vw,-25,25);
	moveOlho.y = ofMap(lookAt.y,0,vh,-15,15);

	olho.setAnchorPercent(0.5, 0.5);
	orbita.setAnchorPercent(0.5, 0.5);

	olho.draw(moveOlho);
	orbita.draw(0,0);

	glPopMatrix();
}



void BrisaGira::setup() {
}

void BrisaGira::update() {
	lookAt = olhaPraMim();
	
}

void BrisaGira::draw() {
	glPushMatrix();

	glTranslatef(vw/2,vh/2 + 10, 0);

	float anguloX = ofMap(lookAt.x,0,vw,-50,50);
	glRotatef(anguloX, 0, 1, 0); 

	float anguloY = ofMap(lookAt.y,0,vh,-50,50);
	glRotatef(anguloY, -1, 0, 0); 
	glRotatef(anguloY+anguloX, 0, 0, 0.2); 

	ofSetColor(255, 255, 255);
	girassol.setAnchorPercent(0.5, 0.5);
	girassol.draw(0,0);

	glPopMatrix();
}


void ofApp::getBlurImage(ofxCvGrayscaleImage &imgBlur, int indiceBlur) {
	imgBlur.blur(11);
	imgBlur.erode();
	imgBlur.dilate();
	imgBlur.blur(101);
	imgBlur.erode();
	imgBlur.dilate();
	imgBlur.blur(101);

	imgBlur.flagImageChanged();
}	


void ofApp::setSombraMirror(ofxCvGrayscaleImage imgAtual, float iRastro) {
	
	sombra.blur(11);
	sombra.blur(11);
	sombra.erode();
	sombra.dilate();
	sombra.erode();
	ofPixels & pixF = sombra.getPixels();
	ofPixels & pixA = imgAtual.getPixels();
	int numPixels = pixF.size();
	for (int i = 0; i < numPixels; i++) {
		pixF[i] =ofClamp(pixF[i] * iRastro + pixA[i] * (1.2 - iRastro),0,255); // Aumenta contraste de distancia
	}
	sombra.flagImageChanged();
	sombra.blur(11);

	sombraMirror = sombra;
	sombraMirror.mirror(false, true);
}


ofShader retornaShader(int iShader) {
	switch(iShader) {
		
		case 1:
			return blackAsAlpha;
			break;
		case 2:
			return whiteAsAlpha;
			break;
		case 3:
			return invertColor;
			break;
		case 4:
			return fundoNegativo;
			break;
		case 5:
			return frenteNegativo;
			break;

		default:
			return dummyShader;
	}
}

ofPoint olhaPraMim() {
	ofPoint lookAt;
	if(kinectLigado) {
		unsigned char * pix = depthBlur.getPixels();
		int blurWidth = depthBlur.width;
		int whiteTotal = 0; // quantidade de coisa na frente da tela
		ofPoint centro( blurWidth/2, depthBlur.height/2 );

		ofPoint baricentro0 = baricentro;

		baricentro.set(0, 0);
		for(int j = 0; j < 10; j++) {
			ofVec2f vecDirecao(15 + j*30,0);
			for(int i = 0; i < 8; i++) {
				ofPoint pontoRef = centro+vecDirecao;
				// Caso o ponto esteja dentro da imagem
				if (pontoRef.x >= 0 && pontoRef.y >= 0 && 
					pontoRef.x < blurWidth && pontoRef.y < depthBlur.height) 
				{

					int white = pix[int(pontoRef.y)*blurWidth + int(pontoRef.x)];
					
					whiteTotal += white;
					baricentro += pontoRef*white;
				}

				vecDirecao.rotate(45);
			}
		}

		if(whiteTotal>0) {
			baricentro /= whiteTotal;
		} else {
			baricentro.set( depthBlur.width/2, depthBlur.height/2 );
		}

		baricentro = baricentro*0.04 + baricentro0*0.96;

		lookAt.x = ofMap(baricentro.x, 0, depthBlur.width, 0, vw);
		lookAt.y = ofMap(baricentro.y, 0, depthBlur.height, 0, vh);

		whiteTotalSlow = whiteTotalSlow*0.9 + whiteTotal*0.1;
	}

	ofPoint perlinPoint;
	perlinPoint.x = vw * ofNoise( time0 * 0.15 );
	perlinPoint.y = vh * ofNoise( time0 * 0.2 );	

	if( whiteTotalSlow < 1000 || whiteTotalSlow > 7000) {
		lookAt = perlinPoint;
	}
	return lookAt;
}


void ofApp::desenhaSombraMirror() {


	int c1 = fmodf( time0/7, 4); // [0..duration]
	int c2 = fmodf( time0/8, 4); // [0..duration]
	if(c1==c2) {
		c1++;
		c1 %= 4;
	}

	ofEnableBlendMode(OF_BLENDMODE_ADD);

	ofSetColor(coresRole[c1]);
	sombra.draw(-10,-10,vw+20,vh+20);
	ofSetColor(coresRole[c2]);
	sombraMirror.draw(-10,-10,vw+20,vh+20);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}
