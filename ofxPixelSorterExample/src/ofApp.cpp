#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();

	if (useImage) {
		img.load("ExampleImage.jpg");
	}
	else {
		vid.load("vid-facade.m4v");
		vid.setLoopState(ofLoopType::OF_LOOP_NORMAL);
		vid.play();

		img = ofImage(vid.getPixels());
	}

	pixelSorter.setup(img);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (useImage) {

	}
	else {
		vid.update();
		if (vid.isFrameNew()) {
			img.setFromPixels(vid.getPixels());
			pixelSorter.update();
		}
	}
	pixelSorter.update();
	out = pixelSorter.out;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (useImage) {
		img.draw(0, 0);
		out.draw(img.getWidth(), 0);
	}
	else {
		img.draw(0, 0);
		out.draw(vid.getWidth(), 0);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		pixelSorter.setOrientation( PixelSorter::ORIENTATION_TYPE::VERTICAL);
		pixelSorter.setDirection( PixelSorter::DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_DOWN:
		pixelSorter.setOrientation(PixelSorter::ORIENTATION_TYPE::VERTICAL);
		pixelSorter.setDirection(PixelSorter::DIRECTION_TYPE::POSITIVE);
		break;
	case OF_KEY_LEFT:
		pixelSorter.setOrientation(PixelSorter::ORIENTATION_TYPE::HORIZONTAL);
		pixelSorter.setDirection(PixelSorter::DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_RIGHT:
		pixelSorter.setOrientation(PixelSorter::ORIENTATION_TYPE::HORIZONTAL);
		pixelSorter.setDirection(PixelSorter::DIRECTION_TYPE::POSITIVE);
		break;
	case 'q':
		pixelSorter.setSortDir( PixelSorter::SORT_DIR::POSITIVE);
		break;
	case 'w':
		pixelSorter.setSortDir(PixelSorter::SORT_DIR::NEGATIVE);
		break;

		//-------------------------------------------------------------
	case '1':
		pixelSorter.setSortMode( PixelSorter::SORT_MODE::BRIGHTNESS);
		break;
	case '2':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::LIGHTNESS);
		break;
	case '3':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::SATURATION);
		break;
	case '4':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::HUE);
		break;
	case '5':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::REDNESS);
		break;
	case '6':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::BLUENESS);
		break;
	case '7':
		pixelSorter.setSortMode(PixelSorter::SORT_MODE::GREENESS);
		break;

		//-------------------------------------------------------------
	case 'z':
		pixelSorter.setStartMode( PixelSorter::START_STOP_MODE::NONE);
		break;
	case 'x':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::BRIGHTNESS);
		break;
	case 'c':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::LIGHTNESS);
		break;
	case 'v':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::SATURATION);
		break;
	case 'b':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::HUE);
		break;
	case 'n':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::REDNESS);
		break;
	case 'm':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::BLUENESS);
		break;
	case ',':
		pixelSorter.setStartMode(PixelSorter::START_STOP_MODE::GREENESS);
		break;
	case '.':
		pixelSorter.setStartMode( PixelSorter::START_STOP_MODE::RANDOM);
		break;

	//-------------------------------------------------------------
	case 'Z':
		pixelSorter.setStopMode( PixelSorter::START_STOP_MODE::NONE);
		break;
	case 'X':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::BRIGHTNESS);
		break;
	case 'C':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::LIGHTNESS);
		break;
	case 'V':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::SATURATION);
		break;
	case 'B':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::HUE);
		break;
	case 'N':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::REDNESS);
		break;
	case 'M':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::BLUENESS);
		break;
	case '<':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::GREENESS);
		break;
	case '>':
		pixelSorter.setStopMode(PixelSorter::START_STOP_MODE::RANDOM);
		break;

	//-------------------------------------------------------------
	case '-':
		pixelSorter.setUpThresh(-0.05);
		break;
	case '=':
		pixelSorter.setUpThresh(0.05);
		break;
	case '_':
		pixelSorter.setDownThresh(-0.05);
		break;
	case '+':
		pixelSorter.setDownThresh(0.05);
		break;
	//-------------------------------------------------------------
	case 'a':
		pixelSorter.setUpSwap(true);
		break;
	case 's':
		pixelSorter.setUpSwap(false);
		break;
	case 'A':
		pixelSorter.setDownSwap(true);
		break;
	case 'S':
		pixelSorter.setDownSwap(false);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
