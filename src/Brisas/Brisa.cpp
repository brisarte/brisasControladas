#include "Brisa.h"

void Brisa::setup() {
    configBrisa = true;
    //btnConfigBrisa = gui->loadTexture(iconPath);fboBrisa.clear();
    pixelsBrisa.allocate(WIDTH,HEIGHT, OF_IMAGE_COLOR);
    fboBrisa.allocate(WIDTH, HEIGHT);
    fboBrisa.begin();
    ofClear(255,255,255, 0);
    fboBrisa.end();

    corBrisa = ofColor(255, 255, 255);

    ligaShader = false;
    clearFrames = true;

    iBrisaShader = 0;

    // Inicializa variaveis de distorções
    brilhoBrisa = contrasteBrisa = 0.5;
    deslocX = deslocY = 0;
}

void Brisa::update(float dt) {
}

void Brisa::mostraBrisas() {

}

void Brisa::draw() {
}

void Brisa::drawControles(int iBrisa) {
}

void Brisa::desenhaMiniatura(int i) {
    imgBtn.setFromPixels(pixelsBrisa);
    imgBtn.draw(0,i*150,200,150);
}

void Brisa::desenhaJanela(int i) {

    std::ostringstream oss;
    std::string text = "Brisa ";
    text += std::to_string(i);

    if (ImGui::Button( text.c_str() )) { 
        configBrisa ^= 1;
        cout << "\nBrisa " << i << ": configBrisa=" << configBrisa;
    }

    if(configBrisa) {
        ImGui::SetNextWindowSize(ofVec2f(300,200), ImGuiSetCond_FirstUseEver);
        string titulo = "Configurações Brisa #" + to_string(i+1);
        ImGui::Begin(titulo.c_str(), &configBrisa);

        drawControles(i);

        ImGui::End();
    }
}

void Brisa::excluiBrisa(int iBrisa) {
    brisasAtivas->erase(brisasAtivas->begin()+iBrisa);
}

void Brisa::loadShader(string shader) {
    fragShaderPath = shader;
    shaderBrisa.load("../data/shaders/vertexdummy.c", fragShaderPath);
}

void Brisa::listaBrisas() {

    int nBrisas = brisasAtivas->size();
    if (ImGui::Selectable("Nenhuma")) {
        iBrisaShader = -1;
    }
    for (int i=0; i<nBrisas; i++) {	
        string numBrisa = "Brisa #" + to_string(i+1);
        if (ImGui::Selectable(numBrisa.c_str())) {
            iBrisaShader = i;
        }

    }
}

void Brisa::desenharControlesShader() {
    if (ImGui::CollapsingHeader("Shader")) {
        if (shaderBrisa.isLoaded()) {
            ImGui::Text(fragShaderPath.substr(25).c_str());
            ImGui::Checkbox("Ligar Shader", &ligaShader);
        }
        if (ImGui::Button("Carregar Shader")) {
            ImGui::OpenPopup("loadShader");
        }
        if (ImGui::BeginPopup("loadShader")) {
            listaShaders();
            ImGui::EndPopup();
        }
        string numBrisa = "Brisa Shader: #" + to_string(iBrisaShader + 1);
        if (ImGui::Button(numBrisa.c_str())) {
            ImGui::OpenPopup("selectBrisa");
        }
        if (ImGui::BeginPopup("selectBrisa")) {
            listaBrisas();
            ImGui::EndPopup();
        }
    }
}

void Brisa::listaShaders() {
    if (ImGui::CollapsingHeader("Alpha"))
    {
        ofDirectory dirShaders;
        //2. Carrega numero de pastas de sequencias
        int nShaders = dirShaders.listDir("../data/shaders/alpha");

        //4. Abre pastas
        for (int i = 0; i < nShaders; i++) {
            string shader = dirShaders.getPath(i);
            if (ImGui::Selectable(shader.substr(21).c_str())) {
                loadShader(shader);
            }
        }
    }
    if (ImGui::CollapsingHeader("Mix Brisa"))
    {
        ofDirectory dirShaders;
        //2. Carrega numero de pastas de sequencias
        int nShaders = dirShaders.listDir("../data/shaders/mixbrisa");

        //4. Abre pastas
        for (int i = 0; i < nShaders; i++) {
            string shader = dirShaders.getPath(i);
            if (ImGui::Selectable(shader.substr(25).c_str())) {
                loadShader(shader);
            }
        }
    }
    if (ImGui::CollapsingHeader("Outros"))
    {
        ofDirectory dirShaders;
        //2. Carrega numero de pastas de sequencias
        int nShaders = dirShaders.listDir("../data/shaders/outros");

        //4. Abre pastas
        for (int i = 0; i < nShaders; i++) {
            string shader = dirShaders.getPath(i);
            if (ImGui::Selectable(shader.substr(21).c_str())) {
                loadShader(shader);
            }
        }
    }
}

void Brisa::aplicarShader() {
    if (ligaShader) {
        shaderBrisa.begin();
        if (iBrisaShader > -1 && brisasAtivas->at(iBrisaShader)->fboBrisa.isAllocated()) {
            shaderBrisa.setUniformTexture("texture1", brisasAtivas->at(iBrisaShader)->fboBrisa.getTextureReference(), 1); //"1" means that it is texture 1
        }

        ofSetColor(255, 255, 255);
        fboBrisa.draw(0, 0);

        shaderBrisa.end();
    }
    else {
        fboBrisa.draw(0, 0);
    }
}

void Brisa::desenharControlesDistorcao() {
    if (ImGui::CollapsingHeader("Distorções")) {
        ImGui::SliderFloat("brilho", &brilhoBrisa, 0, 1); ImGui::SameLine(); ImGui::Text("n funciona");
        ImGui::SliderFloat("contraste", &contrasteBrisa, 0, 1);ImGui::SameLine(); ImGui::Text("n funciona");
        ImGui::SliderInt("desloca X", &deslocX, -200, 200);
        ImGui::SliderInt("desloca Y", &deslocY, -200, 200);
        ImGui::SliderFloat("Proporcao", &proporcao, 0.2, 2);
        ImGui::SliderFloat("Rotação", &rotacao, -180, 180); ImGui::SameLine();
        ImGui::Checkbox("Automático", &rotacionaSozinho);
        ImGui::Checkbox("Torcer automático", &torceSozinho);
    }
}
