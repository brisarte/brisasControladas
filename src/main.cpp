#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "ofAppGLFWWindow.h"


//========================================================================
int main(){
	int monitores = 2;
	
	ofGLFWWindowSettings settings;

	settings.width = WIDTH;
	settings.height = HEIGHT;
	// settings.setPosition(ofVec2f( (monitores-1)*WIDTH ,0));
	settings.setPosition(ofVec2f( 1366,0));
	settings.resizable = true;
	settings.decorated = false;
	settings.multiMonitorFullScreen = true;
	settings.numSamples = 8;
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 1363;
	settings.height = 750;
	settings.setPosition(ofVec2f( 0,0));
	settings.resizable = true;
	settings.decorated = true;
	settings.multiMonitorFullScreen = false;
	settings.numSamples = 8 ;
	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
	shared_ptr<GuiApp> guiApp(new GuiApp);

	mainApp->gui = guiApp;
	mainApp->window = mainWindow;
	mainApp->gl = dynamic_pointer_cast<ofBaseGLRenderer>(mainWindow->renderer());

	ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
