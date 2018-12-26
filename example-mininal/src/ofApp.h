#pragma once

#include "ofMain.h"
#include "ofxPixelSorter.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		PixelSorter pixelSorter;
		ofImage img, out;
};
