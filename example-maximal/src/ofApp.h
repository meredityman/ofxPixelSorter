#pragma once
#include "ofMain.h"
#include "ofxPixelSorter.h"
#include "ofxImGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void setupGui();

		void update();

		void draw();
		void drawGUI();

		void loadImage();
		void saveImage();


		void keyPressed(int key);


		ofImage img;
		string imageName;
		ofImage out;
		bool imageLoaded = false;

		PixelSorter pixelSorter;
		ofxImGui::Gui gui;

		ofParameter<bool> autoUpdate = true;
};
