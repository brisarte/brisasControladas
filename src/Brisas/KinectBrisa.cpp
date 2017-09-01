#include "Brisa.h"

KinectBrisa::KinectBrisa(ofxKinect *kinectGlobal, vector<Brisa*> *brisasParent) {
    // Configura a brisa e defini o ícone
    brisasAtivas = brisasParent;
    kinecto = kinectGlobal;
    mirrorHorizontal = mirrorVertical = false;
    clearFrames = true;
    nivelFade = 20;
    setup();
    ofSetBackgroundAuto(false);
    ligaContornos = true;
    fonteKinect = new FonteKinect(kinectGlobal, 2);
    minArea = 10;
    maxArea = (640*480)/2; // (kinect_width*kinect_height)/2
    blobsConsiderados = 10;
    bFindHoles = false;
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
    fonteKinect->pixelsBrisa.setImageType(OF_IMAGE_GRAYSCALE);
    grayImage.setFromPixels(fonteKinect->pixelsBrisa);
    grayImage.draw(0,0,WIDTH,HEIGHT);

    if (ligaContornos) {
        contourFinder.findContours(grayImage, minArea, maxArea, blobsConsiderados, bFindHoles);
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
    ImGui::Checkbox("Contorno: buracos", &bFindHoles);
    ImGui::SliderInt("min Area", &minArea, 0, 100);
    ImGui::SliderInt("max Area", &maxArea, 100, (640*480) );
    ImGui::SliderInt("blobs", &blobsConsiderados, 0, 20 );

    fonteKinect->drawControles();
    desenharControlesShader();

    if (ImGui::Button("Excluir Brisa")) { excluiBrisa(iBrisa); } 
}
