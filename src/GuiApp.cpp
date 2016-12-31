/*
 * GuiApp.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: arturo
 */

#include "GuiApp.h"

void GuiApp::setup(){
	ofBackground(0);
	ofSetVerticalSync(false);
	
	bgColor.set(0,0,0);


	//1. Pasta de gifs
	ofDirectory dirGifsFull;
	//2. Carrega numero de pastas de sequencias
	int nGifsFull = dirGifsFull.listDir("gifs/fullscreen");
	//3. Set array size 
	listaGifFull.resize( nGifsFull );

	//4. Abre pastas
	for (int i=0; i<nGifsFull; i++) {	
		//Pega caminho da pasta
		string folderName = dirGifsFull.getPath( i );	
		listaGifFull[i] = folderName;

	}

	tiposBrisa = {"SEM BRISA", "VIDEO", "KINECT", "GIF", "POLIGONOS"};
	tipoBrisaFbo = { 0, 1, 0, 0};


	/*:::::::::::::::::::::::: 
	:: :: CONTROLES GERAIS  ::
	::::::::::::::::::::::::*/  	

	ofxDatGui* guiGeral = new ofxDatGui( 210, 0 );
	guiGeral->addHeader(":: CONTROLES GERAIS::");
	guiGeral->addFRM(1.0f);
	colorPicker = guiGeral->addColorPicker("BG");

	colorPicker->onColorPickerEvent(this, &GuiApp::onBGColorPickerEvent);

	// Botão kinect
	ofxDatGuiButton* btnKinect = guiGeral->addButton("LIGAR Kinect");
	btnKinect->onButtonEvent(this, &GuiApp::startKinect);
	ofxDatGuiButton* btnCKinect = guiGeral->addButton("DESLIGAR Kinect");
	btnCKinect->onButtonEvent(this, &GuiApp::closeKinect);
	guiGeral->addFooter();
	guiGeral->getFooter()->setLabelWhenCollapsed(":: CONTROLES GERAIS ::");
	


	int ybrisa = 170;
	int hbrisa = 56;

	/*:::::::::::: 
	:: Brisa 1  ::
	::::::::::::*/

	ofxDatGui* gui = new ofxDatGui( 210, ybrisa );
	gui->addHeader(":: BRISA 1 ::");

	ofxDatGuiDropdown* tipoBrisa1 = gui->addDropdown("TIPO BRISA", tiposBrisa);
	tipoBrisa1->onDropdownEvent(this, &GuiApp::onChangeTipoBrisa1);
	//gui->addFooter();
	//gui->getFooter()->setLabelWhenCollapsed(":: BRISA 1 ::");


	/*:::::::::::: 
	:: Brisa 2  ::
	::::::::::::*/   

	ofxDatGui* guiB2 = new ofxDatGui( 210, ybrisa+hbrisa);
	guiB2->addHeader(":: BRISA 2 ::");

	ofxDatGuiDropdown* tipoBrisa2 = guiB2->addDropdown("TIPO BRISA", tiposBrisa);
	tipoBrisa2->onDropdownEvent(this, &GuiApp::onChangeTipoBrisa2);
	//guiB2->addFooter();
	//guiB2->getFooter()->setLabelWhenCollapsed(":: BRISA 2 ::");


	/*:::::::::::: 
	:: Brisa 3  ::
	::::::::::::*/    

	ofxDatGui* guiB3 = new ofxDatGui( 210,  ybrisa+hbrisa*2 );
	guiB3->addHeader(":: BRISA 3 ::");

	ofxDatGuiDropdown* tipoBrisa3 = guiB3->addDropdown("TIPO BRISA", tiposBrisa);
	tipoBrisa3->onDropdownEvent(this, &GuiApp::onChangeTipoBrisa3);
	//guiB3->addFooter();
	//guiB3->getFooter()->setLabelWhenCollapsed(":: BRISA 3 ::");

	
	/*:::::::::::: 
	:: Brisa 4  ::
	::::::::::::*/

	ofxDatGui* guiB4 = new ofxDatGui( 210,  ybrisa+hbrisa*3 );
	guiB4->addHeader(":: BRISA 4 ::");

	ofxDatGuiDropdown* tipoBrisa4 = guiB4->addDropdown("TIPO BRISA", tiposBrisa);
	tipoBrisa4->onDropdownEvent(this, &GuiApp::onChangeTipoBrisa4);
	//guiB4->addFooter();
	//guiB4->getFooter()->setLabelWhenCollapsed(":: BRISA 4 ::");

	/*:::::::::::::: 
	::~ Gif Full  ::
	::::::::::::::*/  


	ofxDatGui* guiGifFull = new ofxDatGui( 500, 0 );
	guiGifFull->addHeader(":: Gif full ::");

	addControles(guiGifFull, 3);

	guiGifFull->addFooter();
	guiGifFull->getFooter()->setLabelWhenCollapsed(":: Gif full ::");


	/*:::::::::: 
	::~ Video ::
	::::::::::*/    

	ofxDatGui* guiVideo = new ofxDatGui( 500, 100 );
	guiVideo->addHeader(":: Vídeo ::");

	addControles(guiVideo, 1);

	guiVideo->addFooter();
	guiVideo->getFooter()->setLabelWhenCollapsed(":: VIDEO ::");


	/*:::::::::::: 
	::~ Kinect  ::
	::::::::::::*/    

	ofxDatGui* guiKinect = new ofxDatGui( 500, 230 );
	guiKinect->addHeader(":: Kinect ::");

	addControles(guiKinect, 2);

	guiKinect->addFooter();
	guiKinect->getFooter()->setLabelWhenCollapsed(":: Kinect ::");

}

void GuiApp::addControles(ofxDatGui* g, int iBrisa)
{

	switch(iBrisa) {
		// No Breeza
		case 0: {
		}break;

		// Controles de video
		case 1: {
			videosDisponiveis = {"verduras.mp4", "vegetais.mp4", "preda.mp4", "conchas.mp4"};
			ofxDatGuiDropdown* ddVideos = g->addDropdown("SELECIONAR VIDEO", videosDisponiveis);
			ddVideos->onDropdownEvent(this, &GuiApp::onDropdownVideoEvent);

			ofxDatGuiTextInput* inputVideo = g->addTextInput("INSERIR VIDEO","videos/taspb.mp4");
			inputVideo->onTextInputEvent(this, &GuiApp::onVideoChange);

			vector<string> optionsShaderVideo = {"SEM SHADER", "PRETO->TRANSPARENTE", "BRANCO->TRANSPARENTE", "INVERTE COR", "INVERTE FUNDO DEPTH", "INVERTE FRENTE DEPTH"};
			ofxDatGuiDropdown* ddShaderVideo = g->addDropdown("SHADER V", optionsShaderVideo);
			ddShaderVideo->onDropdownEvent(this, &GuiApp::onDropdownShaderVideoEvent);

		}break;

		// Controles de kinect
		case 2: {
			// Botão brisa kinect
			ofxDatGuiButton* btnBKinect = g->addButton("BRISAR Kinect");
			btnBKinect->onButtonEvent(this, &GuiApp::startBrisaKinect);

			ofxDatGuiToggle* contornoKinectToggle = g->addToggle("CONTORNO");
			contornoKinectToggle->onToggleEvent(this, &GuiApp::onContornoKinectToggle);

			vector<string> optionsFonte = {"RGB", "PROFUNDIDADE"};
			ofxDatGuiDropdown* ddFonteKinect = g->addDropdown("FONTE", optionsFonte);
			ddFonteKinect->onDropdownEvent(this, &GuiApp::onDropdownFonteKinectEvent);

			vector<string> options = {"SEM SHADER", "PRETO->TRANSPARENTE", "BRANCO->TRANSPARENTE", "INVERTE COR", "INVERTE FUNDO DEPTH", "INVERTE FRENTE DEPTH"};
			ofxDatGuiDropdown* ddShaderKinect = g->addDropdown("SHADER", options);
			ddShaderKinect->onDropdownEvent(this, &GuiApp::onDropdownShaderKinectEvent);

			
			vector<string> optionsFiltro = {"RGB", "PROFUNDIDADE"};
			ofxDatGuiDropdown* ddFiltroKinect = g->addDropdown("FILTRO", optionsFiltro);
			ddFiltroKinect->onDropdownEvent(this, &GuiApp::onDropdownFiltroKinectEvent);
		}break;

		// Gif fullscreen
		case 3: {
			
			ofxDatGuiDropdown* ddGifFull = g->addDropdown("GIF", listaGifFull);
			ddGifFull->onDropdownEvent(this, &GuiApp::onDropdownGifFullEvent);

		}break;
	}
}

void GuiApp::onChangeTipoBrisa1(ofxDatGuiDropdownEvent e)
{
	tipoBrisaFbo[0] = e.child;
    cout << "tipo  #" << e.child << " selecionado para a brisa 1";
}
void GuiApp::onChangeTipoBrisa2(ofxDatGuiDropdownEvent e)
{
	tipoBrisaFbo[1] = e.child;
    cout << "tipo  #" << e.child << " selecionado para a brisa 2";
}
void GuiApp::onChangeTipoBrisa3(ofxDatGuiDropdownEvent e)
{
	tipoBrisaFbo[2] = e.child;
    cout << "tipo  #" << e.child << " selecionado para a brisa 3";
}
void GuiApp::onChangeTipoBrisa4(ofxDatGuiDropdownEvent e)
{
	tipoBrisaFbo[3] = e.child;
    cout << "tipo  #" << e.child << " selecionado para a brisa 4";
}

void GuiApp::onContornoKinectToggle(ofxDatGuiToggleEvent e)
{
    cout << e.target->getLabel() << " checked = " << e.checked << endl;
    kinectContorno = e.checked;
}


void GuiApp::onDropdownGifFullEvent(ofxDatGuiDropdownEvent e)
{	
	if( listaGifFull.size() > e.child ) {
		pastaGif = listaGifFull[e.child];
	    cout << "gif #" << pastaGif << " selecionado " << endl;
	}
}
void GuiApp::onDropdownFonteKinectEvent(ofxDatGuiDropdownEvent e)
{	
	fonteKinectSelected = e.child;
    cout << "fonte nº #" << e.child << " selecionado " << endl;
    cout << "fontekinect #" << e.parent<< endl;
}

void GuiApp::onDropdownShaderKinectEvent(ofxDatGuiDropdownEvent e)
{
	shaderKinectSelected = e.child;
    cout << "Shader kinect nº #" << e.child << " selecionado " << endl;
    cout << "shaderKinect #" << e.parent<< endl;
}

void GuiApp::onDropdownFiltroKinectEvent(ofxDatGuiDropdownEvent e)
{
	filtroKinectSelected = e.child;
    cout << "filtro nº #" << e.child << " selecionado " << endl;
    cout << "filtrokinect #" << e.parent<< endl;
}


void GuiApp::onDropdownShaderVideoEvent(ofxDatGuiDropdownEvent e)
{
	shaderVideoSelected = e.child;
    cout << "Shader video nº #" << e.child << " selecionado " << endl;
    
}

void GuiApp::onDropdownVideoEvent(ofxDatGuiDropdownEvent e)
{
	if( videosDisponiveis.size() > e.child ) {
		videoPath = "videos/" + videosDisponiveis[e.child];
	    cout << "video (" << videoPath << ") selecionado " << endl;
	}
	
    
}

void GuiApp::onVideoChange(ofxDatGuiTextInputEvent e)
{
    videoPath = e.text;
    cout << videoPath << " é o novo video"  << endl;
}

void GuiApp::onBGColorPickerEvent(ofxDatGuiColorPickerEvent e)
{
	bgColor.set(e.color);
    cout << "bg was set to: " << e.color << endl;
}

void GuiApp::update(){

}

void GuiApp::draw(){
	drawKinect();
}