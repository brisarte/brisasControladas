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
	
	ofxDatGui* gui = new ofxDatGui( 0,0 );
	gui->addHeader(":: BRISA 1 ::");
	gui->addFRM(1.0f);
	colorPicker = gui->addColorPicker("BG");

	colorPicker->onColorPickerEvent(this, &GuiApp::onBGColorPickerEvent);


	gui->addFooter();
	gui->getFooter()->setLabelWhenCollapsed(":: BRISA 1 ::");

	ofxDatGui* guiB2 = new ofxDatGui( 300,0);
	guiB2->addHeader(":: BRISA 2 ::");

	ofxDatGuiTextInput* inputVideo = guiB2->addTextInput("URL VIDEO","videos/taspb.mp4");
	inputVideo->onTextInputEvent(this, &GuiApp::onVideoChange);

	guiB2->addFooter();
	guiB2->getFooter()->setLabelWhenCollapsed(":: BRISA 2 ::");


	
	ofxDatGui* guiB3 = new ofxDatGui( 0, 300 );
	guiB3->addHeader(":: BRISA 3 ::");

	// Botão kinect
	ofxDatGuiButton* btnKinect = guiB3->addButton("LIGAR Kinect");
	btnKinect->onButtonEvent(this, &GuiApp::startKinect);
	ofxDatGuiButton* btnCKinect = guiB3->addButton("DESLIGAR Kinect");
	btnCKinect->onButtonEvent(this, &GuiApp::closeKinect);
	// Botão brisa kinect
	ofxDatGuiButton* btnBKinect = guiB3->addButton("BRISAR Kinect");
	btnBKinect->onButtonEvent(this, &GuiApp::startBrisaKinect);


	vector<string> options = {"SEM SHADER", "PRETO->TRANSPARENTE", "BRANCO->TRANSPARENTE", "INVERTE COR", "INVERTE FUNDO DEPTH", "INVERTE FRENTE DEPTH"};
	ofxDatGuiDropdown* ddShader = guiB3->addDropdown("SHADER", options);
	ddShader->onDropdownEvent(this, &GuiApp::onDropdownShaderEvent);


	guiB3->addFooter();
	guiB3->getFooter()->setLabelWhenCollapsed(":: BRISA 3 ::");

	
	ofxDatGui* guiB4 = new ofxDatGui( 300, 300 );
	guiB4->addHeader(":: BRISA 4 ::");


	guiB4->addFooter();
	guiB4->getFooter()->setLabelWhenCollapsed(":: BRISA 4 ::");

}

void GuiApp::onDropdownShaderEvent(ofxDatGuiDropdownEvent e)
{
	shaderSelected = e.child;

    cout << "the option at index # " << e.child << " was selected " << endl;

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
}