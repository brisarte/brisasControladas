#include "ofApp.h"

bool kinectLigado;
ofxCvColorImage kinectRGB;
ofxCvGrayscaleImage kinectDepth, kinectDepthBlur;


float prevTime, actualTime;

ofImage logoBrisa;
ofShader shaders[6];

int vw = 1024;
int vh = 768;
//--------------------------------------------------------------
void ofApp::setup(){

	kinectRGB.allocate(640,480);
	kinectDepth.allocate(640,480);
	fboLayer.allocate(1024,768);

	timeUltimaBrisa = 0;
	tempoFade = 2; 


	logoBrisa.load("../data/img/logobrisarte.png");

	




	shaders[0].load( "shaders/vertexdummy.c", "shaders/fragdummy.c" ); // dummyShader
	shaders[1].load( "shaders/vertexdummy.c", "shaders/blackAsAlpha.c" ); // blackAsAlpha
	shaders[2].load( "shaders/vertexdummy.c", "shaders/whiteAsAlpha.c" ); // whiteAsAlpha
	shaders[3].load( "shaders/vertexdummy.c", "shaders/invertColor.c" ); // invertColor
	shaders[4].load( "shaders/vertexdummy.c", "shaders/frenteNegativo.c" ); // frenteNegativo
	shaders[5].load( "shaders/vertexdummy.c", "shaders/fundoNegativo.c" ); // fundoNegativo
}

//--------------------------------------------------------------
void ofApp::update(){

	ofBackground(0,0,0);

	prevTime = actualTime;
	actualTime = ofGetElapsedTimef();

	// Pega configurações do kinect da Janela de GUI
	kinectLigado = gui->kinectLigado;

	kinectRGB = gui->kinectRGB;
	kinectDepth = gui->kinectDepth;

	tempoBrisa = gui->tempoBrisa;

	ativaBrisa1 = gui->ativaBrisa1;
	ativaBrisa2 = gui->ativaBrisa2;
	ativaBrisa3 = gui->ativaBrisa3;
	ativaBrisa4 = gui->ativaBrisa4;

	configsBrisa1 = gui->configsBrisa1;
	configsBrisa2 = gui->configsBrisa2;
	configsBrisa3 = gui->configsBrisa3;
	configsBrisa4 = gui->configsBrisa4;

	// Troca Brisa
	if(actualTime - timeUltimaBrisa > tempoBrisa) {
		timeUltimaBrisa = actualTime;

		brisa1.setConfig(configsBrisa1);
		brisa1.setup();
		brisa2.setConfig(configsBrisa2);
		brisa2.setup();
		brisa3.setConfig(configsBrisa3);
		brisa3.setup();
		brisa4.setConfig(configsBrisa4);
		brisa4.setup();
	}

	if(ativaBrisa1 && !brisa1.ativa) {
		brisa1.tipoBrisa = 3; //video
		brisa1.setup();
		brisa1.ativa = true;
	}
	if(ativaBrisa2 && !brisa2.ativa) {
		brisa2.tipoBrisa = 4; //gifFull
		brisa2.setup();
		brisa2.ativa = true;
	}
	if(ativaBrisa3 && !brisa3.ativa) {
		brisa3.tipoBrisa = 5; //contorno
		brisa3.setup();
		brisa3.ativa = true;
	}
	if(ativaBrisa4 && !brisa4.ativa) {
		brisa4.tipoBrisa = 1; //contorno
		brisa4.setup();
		brisa4.ativa = true;
	}

	if(brisa1.ativa) {
		brisa1.update(actualTime - prevTime);
	}
	if(brisa2.ativa) {
		brisa2.update(actualTime - prevTime);
	}
	if(brisa3.ativa) {
		brisa3.update(actualTime - prevTime);
	}
	if(brisa4.ativa) {
		brisa4.update(actualTime - prevTime);
	}


	fboLayer.begin();
	if(brisa1.ativa) {
		brisa1.draw();
	}
	if(brisa2.ativa) {
		brisa2.draw();
	}
	if(brisa3.ativa) {
		brisa3.draw();
	}
	if(brisa4.ativa) {
		brisa4.draw();
	}
	fboLayer.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	//fade
	if(actualTime >= timeUltimaBrisa) {
		// Testa se ja passou tempo pra começar o fade && ainda nao acabou a brisa
		if(actualTime - timeUltimaBrisa >= (tempoBrisa - tempoFade) && actualTime - timeUltimaBrisa < tempoBrisa) {
			ofSetColor(255, 255, 255, ofMap(actualTime,timeUltimaBrisa + tempoBrisa - tempoFade,timeUltimaBrisa + tempoBrisa,255,0));
		}
		//Testa se ta no comecinho da brisa
		else if(actualTime - timeUltimaBrisa <= tempoFade) {
			ofSetColor(255, 255, 255, ofMap(actualTime,timeUltimaBrisa,timeUltimaBrisa+tempoFade,0,255));
		} else {
			ofSetColor(255, 255, 255);
		}
	}

	fboLayer.draw(0,0,vw,vh);
	
	ofPushMatrix();
	ofTranslate(1024,0);

	fboLayer.draw(0,0,vw,vh);

	ofPopMatrix();

	// Testa se ja passou tempo pra começar o fade && ainda nao acabou a brisa
	if(actualTime - timeUltimaBrisa > (tempoBrisa - tempoFade) && actualTime - timeUltimaBrisa < tempoBrisa) {
		ofSetColor(255, 255, 255, ofMap(actualTime,timeUltimaBrisa + tempoBrisa - tempoFade,timeUltimaBrisa + tempoBrisa,0,255));
	}
	//Testa se ta no comecinho da brisa
	else if(actualTime - timeUltimaBrisa < tempoFade) {
		ofSetColor(255, 255, 255, ofMap(actualTime,timeUltimaBrisa,timeUltimaBrisa+tempoFade,255,0));
	} else {
		ofSetColor(255, 255, 255, 0);
	}

	logoBrisa.setAnchorPercent(0.5,0.5);
	logoBrisa.draw(vw/2,vh/2);
	ofSetColor(255, 255, 255, 255);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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



void Brisa::setup() {

	switch (tipoBrisa) {
		case 0 : // video
			if(iShader < 0 || iShader > 5) iShader = 0;
			if(urlpath == "") {
				urlpath = "claricefalcao.mp4";
			}
			setupVideo(urlpath);
			break;

		case 1 : // contorno
			
			break;

		case 2 : // gifFull
			if(gifPath == "") {
				gifPath = "fullscreen/blackboca";
			}
			loadGif(gifPath);
			break;

		case 3 : // poligonos
		{
			int indCor = fmodf( prevTime/8, 4); // [0..4]
			//cor1 = coresRole[indCor];
			cor1.set(0,255,0);

			cor2.set(cor1);
			cor2.setHue( (int(prevTime*5)+200) %360);
		}
		break;
		case 4 : // illu

		case 5 : // girassol
			whiteTotalSlow = 0;
			baricentro.set(0,0);
			girassol.load("../data/img/girassol.png");
			olho.load("../data/img/olhoillu.png");
			orbita.load("../data/img/orbitaillu.png");
			break;
	}
	ativa = true;
}

void Brisa::update(float dt) {
	switch (tipoBrisa) {
		case 0 : // video
			if( video.isLoaded() )  {
				video.update();

				if(kinectLigado) {
				// alloca um fbo com o tamanho original do video
				// pra poder mesclar no shader
					if( !fboKinect.isAllocated() || fboKinect.getWidth() != wOriginal ) {
						fboKinect.clear();
						fboKinect.allocate(wOriginal,hOriginal);
					}
					updateKinect(kinectDepth);
				}
				// shaderBrisaInteracao = shaders[iShader];
			}
			break;
		
		case 1 : // contorno
			// Encontra contornos
			contourFinder.findContours(kinectDepth, 10, (kinectDepth.width*kinectDepth.height)/2, 20, false);
			break;

		case 2 : // gifFull
			break;

		case 3 : // poligonos
		{
			int indCor = fmodf( prevTime/8, 4); // [0..4]
			//cor1 = coresRole[indCor];
			cor1.set(0,255,0);

			cor2.set(cor1);
			cor2.setHue( (int(prevTime*5)+200) %360);
		}
		break;

		case 4 : // illu
		case 5 : // girassol
			if(kinectLigado) {
				if(kinectDepth.bAllocated) {
					kinectDepthBlur = blurImage(kinectDepth);
				}
			}
			lookAt = olhaPraMim();
			break;
	}
	
}

void Brisa::draw() {

	switch (tipoBrisa) {
		case 0 : // video
			if( video.isLoaded() ) {

/*
				shaderBrisaInteracao.begin();

				if(kinectLigado && fboKinect.isAllocated()) {
					shaderBrisaInteracao.setUniformTexture( "texture1", fboKinect.getTextureReference(), 1 );
				}
				*/
				video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);
/*
				shaderBrisaInteracao.end();	*/
			}
			break;

		case 1 : // contorno
			contourFinder.draw(0,0, 1024,768);
			break;

		case 2 : // gifFull
			if(urlpasta !="" && listaImg.size() > 0) {

				float i = fmodf( actualTime/10, listaImg.size() ); // [0..duration]

				int ngif = listaImg.size();
				float duration = ngif / 12.0; //25fps		
				float pos = fmodf( actualTime, duration ); // [0..duration]
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
			break;
		case 3: // poligonos
			// Desenha poligono
		ofSetColor(0,0,0);
			// ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.3))*100 + 800 ,true,true);
			// ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.2))*100 + 700 ,true,true);
			// ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.1))*100 + 600 ,true,true);
			// ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7))*100 + 500 ,true,true);
			// ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.1))*100 + 400 ,true,true);
			// ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.2))*100 + 300 ,true,true);
			// ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.3))*100 + 200 ,true,true);
			// ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7)+.4)*100 + 100 ,true,true);
			break;

		case 4: // illu
		{
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
		break;

		case 5: // gira
		{
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
		break;

	}
}

void Brisa::setupVideo(string videoPath) {
	urlpath =  videoPath;
	cout << "Video load: " << urlpath;
	if(urlpath != "") {
		video.load(urlpath);
		video.play();
		video.setPosition(prevTime-(long)prevTime);
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
		cout << "\nredimensionado: " << wOriginal << "x" << hOriginal << " => " << wVideo << "x" << hVideo;
	}
	shaderBrisaInteracao = shaders[3];
}
void Brisa::updateKinect(ofxCvGrayscaleImage imgKinect) {
		fboKinect.begin();
			ofSetColor( 255, 255, 255 );

			// acertar a proporção (cover do kinect com o tam do video argh)
			imgKinect.draw(-wOriginal/10,-hOriginal/10,wOriginal*1.1,hOriginal*1.1);
		fboKinect.end();	
}

void Brisa::loadGif(string gPath) {
	// Carrega numero de img da sequencia
	ofDirectory dirgif;
	urlpasta = gPath;
	int nimg = dirgif.listDir(urlpasta);

	cout << urlpasta << ": ";
	// Set array img size 
	listaImg.resize( nimg );
	// Load images
	for (int j=0; j<nimg; j++) {
		//Getting i-th file name
		string fileName = dirgif.getPath( j );
		//Load i-th image
		ofLoadImage( listaImg[j], fileName );
		cout << "|";
	}
	cout << nimg <<" imgs loaded"<< endl;
}


// Desenha poligono
void Brisa::desenhaPoligono(int vertices, int radius, bool rotate, bool fill) {
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
		glRotatef( sin(prevTime*0.5)*50 + 	(360/vertices-1)-(360/vertices) + 100, 0, 0, 1); 
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

// Nova config
void Brisa::setConfig(configsBrisa c) {
	tipoBrisa = c.tipoBrisa;
	switch (tipoBrisa) {
		case 0 : // video
			urlpath = c.urlpath;
			iShader = c.iShader;
			break;
		
		case 1 : // contorno
			break;

		case 2 : // gifFull

			gifPath = c.gifPath;
			break;

		case 3 : 
		break;

		case 4 : // illu
		case 5 : // girassol
			break;
	}
}

ofxCvGrayscaleImage Brisa::blurImage(ofxCvGrayscaleImage imgOriginal) {
	imgOriginal.blur(11);
	imgOriginal.erode();
	imgOriginal.dilate();
	imgOriginal.blur(101);
	imgOriginal.erode();
	imgOriginal.dilate();
	imgOriginal.blur(101);

	imgOriginal.flagImageChanged();

	return imgOriginal;
}	


ofPoint Brisa::olhaPraMim() {
	ofPoint lookAt;
	if(kinectLigado) {
		ofPixels & pix = kinectDepthBlur.getPixels();
		int blurWidth = kinectDepthBlur.width;
		int whiteTotal = 0; // quantidade de coisa na frente da tela
		ofPoint centro( blurWidth/2, kinectDepthBlur.height/2 );

		ofPoint baricentro0 = baricentro;

		baricentro.set(0, 0);
		for(int j = 0; j < 10; j++) {
			ofVec2f vecDirecao(15 + j*30,0);
			for(int i = 0; i < 8; i++) {
				ofPoint pontoRef = centro+vecDirecao;
				// Caso o ponto esteja dentro da imagem
				if (pontoRef.x >= 0 && pontoRef.y >= 0 && 
					pontoRef.x < blurWidth && pontoRef.y < kinectDepthBlur.height) 
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
			baricentro.set( kinectDepthBlur.width/2, kinectDepthBlur.height/2 );
		}

		baricentro = baricentro*0.04 + baricentro0*0.96;

		lookAt.x = ofMap(baricentro.x, 0, kinectDepthBlur.width, 0, vw);
		lookAt.y = ofMap(baricentro.y, 0, kinectDepthBlur.height, 0, vh);

		whiteTotalSlow = whiteTotalSlow*0.9 + whiteTotal*0.1;
	}

	ofPoint perlinPoint;
	perlinPoint.x = vw * ofNoise( prevTime * 0.15 );
	perlinPoint.y = vh * ofNoise( prevTime * 0.2 );	

	if( whiteTotalSlow < 1000 || whiteTotalSlow > 7000) {
		lookAt = perlinPoint;
	}
	return lookAt;
}