#include "GuiApp.h"
#include <vector>
using namespace std;

float t0, t1;

void GuiApp::setup(){
    gui.setup();

    btnCriaVideo = gui.loadTexture("../data/img/icon/video.png");
    btnCriaPoligono = gui.loadTexture("../data/img/icon/poligon.png");
    btnCriaKinect = gui.loadTexture("../data/img/icon/kinect.png");
    btnCriaImg = gui.loadTexture("../data/img/icon/img.png");
    btnCriaGif = gui.loadTexture("../data/img/icon/gif.png");
    btnCriaMatriz = gui.loadTexture("../data/img/icon/matriz.png");
    btnCriaSombras = gui.loadTexture("../data/img/icon/sombras.png");
    btnCriaMandala = gui.loadTexture("../data/img/icon/mandala.png");
    btnCriaBorda = gui.loadTexture("../data/img/icon/borda.png");

    ImGui::GetIO().MouseDrawCursor = false;
    desenhaMiniaturas = true;

    coresPaleta.push_back(ofColor::fromHex(0x00126D));
    coresPaleta.push_back(ofColor::fromHex(0xC0126D));

    iBlend = 2;
    anguloKinect = 0;
}

void GuiApp::update(){
    // Quanto tempo passou desde o ultimo update?
    // Resp = t1 - t0
    t0 = t1;
    t1 = ofGetElapsedTimef();
    float dt = t1 - t0;

    // Atualiza as brisa tudo
    for( int i = 0; i < brisasAtivas.size(); i++ )
    {
        brisasAtivas[i]->update(dt);
    }
}

void GuiApp::draw() {
    ofBackground(0, 0, 0);

    gui.begin();


    ImGui::Text("Adicione uma camada de brisa:");
    bool criaKinect = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaKinect, ImVec2(120, 90)); ImGui::SameLine();
    bool criaMatriz = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaMatriz, ImVec2(120, 90)); ImGui::SameLine();
    bool criaSombras = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaSombras, ImVec2(120, 90));
    bool criaVideo = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaVideo, ImVec2(120, 90)); ImGui::SameLine();
    bool criaGif = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaGif, ImVec2(120, 90)); ImGui::SameLine();
    bool criaImg = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaImg, ImVec2(120, 90));
    bool criaPoligono = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaPoligono, ImVec2(120, 90)); ImGui::SameLine();
    bool criaMandala = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaMandala, ImVec2(120, 90)); ImGui::SameLine();
    bool criaBorda = ImGui::ImageButton((ImTextureID)(uintptr_t)btnCriaBorda, ImVec2(120, 90));

    if (criaVideo) {
        cout << "btn pressionado: criaVideo";
        brisasAtivas.push_back(new VideoBrisa(&brisasAtivas));
    }
    if (criaPoligono) {
        cout << "btn pressionado: criaPoligono";
        brisasAtivas.push_back(new PoligonoBrisa(&brisasAtivas, &coresPaleta));
    }
    if (criaKinect) {
        cout << "btn pressionado: criaKinect";
        brisasAtivas.push_back(new KinectBrisa(&kinectGlobal, &brisasAtivas));
    }
    if (criaImg) {
        cout << "btn pressionado: criaImg";
        brisasAtivas.push_back(new ImagemBrisa(&brisasAtivas));
    }
    if (criaGif) {
        cout << "btn pressionado: criaGif";
        brisasAtivas.push_back(new GifBrisa(&brisasAtivas));
    }
    if (criaMatriz) {
        cout << "btn pressionado: criaMatriz";
        brisasAtivas.push_back(new MatrizBrisa(&kinectGlobal, &brisasAtivas, &coresPaleta));
    }
    if (criaSombras) {
        cout << "btn pressionado: criaSombras";
        brisasAtivas.push_back(new SombraBrisa(&kinectGlobal, &brisasAtivas, &coresPaleta));
    }



    ImGui::SetNextWindowSize(ofVec2f(20, 10), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Controles Gerais");

    ImGui::Text("%.1f FPS (%.3f ms/frame) ", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Checkbox("Desenha miniaturas", &desenhaMiniaturas);

    // Botões de liga e desliga do kinect
    if ( kinectGlobal.isConnected() ) {
        kinectGlobal.setCameraTiltAngle(anguloKinect);
        ImGui::SliderInt("angulo", &anguloKinect, -30, 30);
        if (ImGui::Button("Desliga Kinect")) { desligaKinect(); } 
    } else {
        if (ImGui::Button("Liga Kinect")) { ligaKinect(); } 
    }
    
    if (ImGui::CollapsingHeader("Paleta de cores")) {
        for (int i = 0; i < coresPaleta.size(); i++) {
            string nomeCor = "Cor " + to_string(i + 1);
            ImGui::ColorEdit4(nomeCor.c_str(), (float*)&coresPaleta[i]);
            ImGui::SameLine();
            nomeCor = "[X] Excluir " + to_string(i + 1);
            if (ImGui::Button(nomeCor.c_str())) { coresPaleta.erase(coresPaleta.begin() + i); }
        }

        if (ImGui::Button(" + ")) {
            coresPaleta.push_back(ofColor::fromHex(0xC0126D));
        }
    }


    ImGui::Text("Blend Mode");
    ImGui::RadioButton("alpha", &iBlend, 1); ImGui::SameLine();
    ImGui::RadioButton("add", &iBlend, 2); ImGui::SameLine();
    ImGui::RadioButton("screen", &iBlend, 3); //ImGui::SameLine();

    // Me mostra essas brisa
    for (int i = 0; i < brisasAtivas.size(); i++)
    {
        if( desenhaMiniaturas ) {
            brisasAtivas[i]->desenhaMiniatura(i);
        }
        brisasAtivas[i]->desenhaJanela(i);
    }

    ImGui::End();

    gui.end();

}

void GuiApp::ligaKinect() {
    if( !kinectGlobal.isConnected() ) {
        kinectGlobal.setRegistration(true);
        kinectGlobal.init();
        kinectGlobal.open();
        kinectGlobal.setCameraTiltAngle(0);
    }
}

void GuiApp::desligaKinect() {
    kinectGlobal.close();
}

