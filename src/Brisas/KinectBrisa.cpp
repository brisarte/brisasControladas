#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent) {
    // Configura a brisa e defini o ícone
    brisasAtivas = brisasParent;
    kinecto = kinectGlobal;
    camera = 0; // 0 = camera RGB (default) | 1 = camera Depth
    mirrorHorizontal = mirrorVertical = false;
    clearFrames = true;
    nivelFade = 20;
    setup();
    ofSetBackgroundAuto(false);
    ligaContornos = true;
    fonteKinect = new FonteKinect(kinectGlobal, 2);
}


void KinectBrisa::update( float dt ) {
    fonteKinect->update(dt);
    fboBrisa.begin();

    if (clearFrames) {
        // Define um alpha de acordo com o nivel Fade
        ofSetColor( ofFloatColor(1.0, 1.0, 1.0, 0.05*(nivelFade/100) ) );
    } else {
        ofSetColor(255,255,255,255);
    }

    grayImage = fonteKinect->grayImage;
    grayImage.draw(0,0,WIDTH,HEIGHT);

    if (ligaContornos) {
        contourFinder.findContours(grayImage, 10, (kinecto->width*kinecto->height)/2, 20, false);
        contourFinder.draw(0,0,WIDTH,HEIGHT);
    }

    fboBrisa.end();
    fboBrisa.readToPixels(pixelsBrisa);
}

void KinectBrisa::draw() {
    aplicarShader();
}

void KinectBrisa::desenhaMiniatura(int i) {
    imgBtn.setFromPixels(pixelsBrisa);
    imgBtn.draw(0,i*150,200,150);
    fonteKinect->fboBrisa.draw(200,i*150,200,150);
}

void KinectBrisa::drawControles(int iBrisa) {
    ImGui::Checkbox("Liga Fade", &clearFrames);
    if(clearFrames){
        ImGui::SliderFloat("Fade", &nivelFade, 0, 100);
    }


    ImGui::Checkbox("Contornos", &ligaContornos);

    fonteKinect->drawControles();
    desenharControlesShader();

    if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
