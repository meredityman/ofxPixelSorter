#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	img.load("Vita_beatae_Hedwigis.jpg");

	pixelSorter.setup();
	pixelSorter.setImage(img);

	pixelSorter.settings.orientation = (int)ORIENTATION_TYPE::ANTIDIAGONAL; // Orientation of the sort
	pixelSorter.settings.direction   = (int)DIRECTION_TYPE::POSITIVE; // Direction from that the sorter travels
	pixelSorter.settings.sortDir     = (int)SORT_DIR::POSITIVE;   // Sort direction
	pixelSorter.settings.sortMode    = (int)COMPARATOR::REDNESS;  // Sort condition
	pixelSorter.settings.startMode   = (int)COMPARATOR::BLUENESS; // Start condition
	pixelSorter.settings.stopMode    = (int)COMPARATOR::REDNESS;  // Stop condition

	pixelSorter.settings.startSwap   = false; // Whether to swap the start condition
	pixelSorter.settings.stopSwap    = true;  // Whether to swap the stop condition

	pixelSorter.settings.startThresh = 0.537; // Threshold for the start condition;
	pixelSorter.settings.stopThresh  = 0.689; // Threshold for the stop condition;

	pixelSorter.settings.maxSeq      = 0.047; // Max length to sort
	pixelSorter.settings.minSeq      = 0.000; // Min length to sort
}

//--------------------------------------------------------------
void ofApp::update(){
	pixelSorter.update();
	out.setFromPixels(pixelSorter.getPixels());
}

//--------------------------------------------------------------
void ofApp::draw(){	
	out.draw(0,0);
}
