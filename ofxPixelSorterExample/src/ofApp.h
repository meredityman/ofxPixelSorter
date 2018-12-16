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
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofImage img;
		ofImage out;
		bool imageLoaded = false;

		PixelSorter pixelSorter;
		ofxImGui::Gui gui;

		ofParameter<bool> autoUpdate = false;
};
