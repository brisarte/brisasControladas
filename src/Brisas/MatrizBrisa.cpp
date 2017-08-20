#include "Brisa.h"

MatrizBrisa::MatrizBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent, vector<ImVec4> *paletaGeral) {
    // Configura a brisa e defini o ícone
    brisasAtivas = brisasParent;
    kinecto = kinectGlobal;
    camera = 1; // 0 = camera RGB (default) | 1 = camera Depth
    setup();

    desenhaBlur = true;
    blurKinect = false;
    brightnessGray = 0.5;
    contrastGray = 0.95;
    intervaloX = 50;
    intervaloY = 46;

    coresPaleta = paletaGeral;
}

void MatrizBrisa::update( float dt ) {
    fboBrisa.begin();

    if (clearFrames) {
        ofClear(255,255,255, 0);
    }

    ofSetColor(corBrisa);

    if ( kinecto->isConnected() ) {
        kinecto->update();
        grayImage.setFromPixels(kinecto->getDepthPixels());
        grayImage.mirror(mirrorVertical, mirrorHorizontal);
        grayImage.brightnessContrast(brightnessGray, contrastGray);
        grayImage.blurHeavily();
        grayImage.dilate_3x3();
        grayImage.erode_3x3();
        grayImage.blurHeavily();

        grayPixels = grayImage.getPixels();

        int grayWidth = grayImage.getWidth();
        int grayHeight = grayImage.getHeight();
        for (int x = 0; x < grayWidth; x += intervaloX) {
            for (int y = 0; y < grayHeight; y += intervaloY) {
                int index = y*grayWidth + x; // Pega brilho do pixel[x,y]
                int brilho = grayPixels[index];
                desenhaPixels(brilho, grayWidth, grayHeight, x, y, intervaloX, intervaloY);
            }
        }
    }

    fboBrisa.end();
    fboBrisa.readToPixels(pixelsBrisa);
}

void MatrizBrisa::draw() {
    aplicarShader();
}


void MatrizBrisa::desenhaColunas(int brilho, int width, int height, int x, int y, int gapX, int gapY) {
    int altura = brilho;
    ofColor corPilar = coresPaleta->at(0);
    ofColor corQuadrado = coresPaleta->at(1);
    ofColor corBorda = coresPaleta->at(2);

    ofColor corPilarEscuro = corPilar;
    corPilarEscuro.setBrightness(100); // Escurece o lado do pilar

    int tamanhoCol = gapX*0.72;

    glPushMatrix();

    glTranslatef(x*gapX, y*gapX * 0.81 - altura, 0);
    ofSetColor(corPilar);

    ofFill();
    ofDrawRectangle(-tamanhoCol*0.7, tamanhoCol*0.57, tamanhoCol*0.7, tamanhoCol * 5);
    ofSetColor(corBorda);
    ofNoFill();
    ofDrawRectangle(-tamanhoCol*0.7, tamanhoCol*0.57, tamanhoCol*0.7, tamanhoCol * 5);

    ofSetColor(corPilarEscuro);
    ofFill();
    ofDrawRectangle(0, tamanhoCol*0.57, tamanhoCol*0.7, tamanhoCol * 5);
    ofSetColor(corBorda);
    ofNoFill();
    ofDrawRectangle(0, tamanhoCol*0.57, tamanhoCol*0.7, tamanhoCol * 5);

    glScalef(1, 0.8, 1);
    glRotatef(45, 0, 0, 1);
    ofSetColor(corQuadrado);
    ofFill();
    ofDrawRectangle(0, 0, tamanhoCol, tamanhoCol);
    ofSetColor(corBorda);
    ofNoFill();
    ofDrawRectangle(0, 0, tamanhoCol, tamanhoCol);


    glPopMatrix();
}

void MatrizBrisa::desenhaPixels(int brilho, int width, int height, int x,int y, int gapX, int gapY) {
    if (brilho > 10) {
        // sorteia cor desse quadrado
        ofColor corQuad = coresPaleta->at((int)ofRandom(0, coresPaleta->size() - 1));
        corQuad.setBrightness(brilho);
        ofSetColor(corQuad);
    }
    else {
        ofSetColor(0, 0, 0, 0);
    }
    ofDrawRectangle(x * (WIDTH / (float)width), y * (HEIGHT / (float)height), gapX* (WIDTH / (float)width), gapY*(HEIGHT / (float)height));
}

void MatrizBrisa::drawControles(int iBrisa) {

    ImGui::Checkbox("blur Kinect", &blurKinect);

    ImGui::SliderInt("intervalo X", &intervaloX, 2, 100);
    ImGui::SliderInt("intervalo Y", &intervaloY, 2, 100);

    ImGui::Checkbox("Limpa Frames", &clearFrames);

    if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
