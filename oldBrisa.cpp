
void Brisa::setup() {

	switch (tipoBrisa) {
		case 0 : // video
			setupVideo("claricefalcao.mp4");
			break;

		case 1 : // contorno
			
			break;

		case 2 : // gifFull
			loadGif("fullscreen/blackboca");
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

				/*shaderBrisaInteracao = retornaShader(iShader);

				shaderBrisaInteracao.begin();

				if(fboKinect.isAllocated()) {
					shaderBrisaInteracao.setUniformTexture( "texture1", fboKinect.getTextureReference(), 1 );
				}
				*/
				video.draw(-(wVideo-1024)/2, -(hVideo-768)/2, wVideo, hVideo);

				// shaderBrisaInteracao.end();	
			}
			break;

		case 1 : // contorno
			contourFinder.draw(0,0, 1024,768);
			break;

		case 2 : // gifFull
			if(urlpasta !="" && listaImg.size() > 0) {

				float i = fmodf( prevTime/10, listaImg.size() ); // [0..duration]

				int ngif = listaImg.size();
				float duration = ngif / 12.0; //25fps		
				float pos = fmodf( prevTime, duration ); // [0..duration]
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
			ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.3))*100 + 800 ,true,true);
			ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.2))*100 + 700 ,true,true);
			ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7-.1))*100 + 600 ,true,true);
			ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7))*100 + 500 ,true,true);
			ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.1))*100 + 400 ,true,true);
			ofSetColor(cor2);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.2))*100 + 300 ,true,true);
			ofSetColor(cor1);
			desenhaPoligono( int(abs(sin(prevTime*0.1)*4)) + 4, abs(sin(prevTime*0.7+.3))*100 + 200 ,true,true);
			ofSetColor(cor2);
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
	urlpath = "videos/" + videoPath;
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
}
void Brisa::updateKinect(ofxCvGrayscaleImage imgKinect) {
		fboKinect.begin();
			ofSetColor( 255, 255, 255 );

			// acertar a proporção (cover do kinect com o tam do video argh)
			imgKinect.draw(-wOriginal/10,-hOriginal/10,wOriginal*1.1,hOriginal*1.1);
		fboKinect.end();	
}

void Brisa::loadGif(string gifPath) {
	// Carrega numero de img da sequencia
	ofDirectory dirgif;
	urlpasta = "gifs/"+gifPath;
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