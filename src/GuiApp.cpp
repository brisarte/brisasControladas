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
	
	ofxDatGui* guiGeral = new ofxDatGui( 10,420 );
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
	
	ofxDatGui* gui = new ofxDatGui( 310,0 );
	gui->addHeader(":: BRISA 1 ::");
	

	gui->addFooter();
	gui->getFooter()->setLabelWhenCollapsed(":: BRISA 1 ::");



	ofxDatGui* guiB2 = new ofxDatGui( 310,300);
	guiB2->addHeader(":: BRISA 2 ::");

	addControles(guiB2, 0);

	guiB2->addFooter();
	guiB2->getFooter()->setLabelWhenCollapsed(":: BRISA 2 ::");


	
	ofxDatGui* guiB3 = new ofxDatGui( 600, 0 );
	guiB3->addHeader(":: BRISA 3 ::");

	
	addControles(guiB3, 1);


	guiB3->addFooter();
	guiB3->getFooter()->setLabelWhenCollapsed(":: BRISA 3 ::");

	
	ofxDatGui* guiB4 = new ofxDatGui( 600, 300 );
	guiB4->addHeader(":: BRISA 4 ::");

	guiB4->addFooter();
	guiB4->getFooter()->setLabelWhenCollapsed(":: BRISA 4 ::");

}

void GuiApp::addControles(ofxDatGui* g, int iBrisa)
{
	switch(iBrisa) {
		// Controles de video
		case 0: {
			videosDisponiveis = {"cg.mp4", "tas.mp4", "testerau.mp4", "claricefalcao.mp4"};
			ofxDatGuiDropdown* ddVideos = g->addDropdown("SELECIONAR VIDEO", videosDisponiveis);
			ddVideos->onDropdownEvent(this, &GuiApp::onDropdownVideoEvent);

			ofxDatGuiTextInput* inputVideo = g->addTextInput("INSERIR VIDEO","videos/taspb.mp4");
			inputVideo->onTextInputEvent(this, &GuiApp::onVideoChange);

			vector<string> optionsShaderVideo = {"SEM SHADER", "PRETO->TRANSPARENTE", "BRANCO->TRANSPARENTE", "INVERTE COR", "INVERTE FUNDO DEPTH", "INVERTE FRENTE DEPTH"};
			ofxDatGuiDropdown* ddShaderVideo = g->addDropdown("SHADER V", optionsShaderVideo);
			ddShaderVideo->onDropdownEvent(this, &GuiApp::onDropdownShaderVideoEvent);

		}break;

		// Controles de kinect
		case 1: {
			// Botão brisa kinect
			ofxDatGuiButton* btnBKinect = g->addButton("BRISAR Kinect");
			btnBKinect->onButtonEvent(this, &GuiApp::startBrisaKinect);

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