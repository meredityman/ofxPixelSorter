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

	gui.setup();
	gui.add(pixelSorter.params);

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
	//pixelSorter.update();
	if (pixelSorter.isFrameNew()) {
		out = pixelSorter.getPixels();
	}

	
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

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		pixelSorter.orientation = (int)PixelSorter::ORIENTATION_TYPE::VERTICAL;
		pixelSorter.direction = (int)PixelSorter::DIRECTION_TYPE::NEGATIVE;
		break;
	case OF_KEY_DOWN:
		pixelSorter.orientation = (int)PixelSorter::ORIENTATION_TYPE::VERTICAL;
		pixelSorter.direction = (int)PixelSorter::DIRECTION_TYPE::POSITIVE;
		break;
	case OF_KEY_LEFT:
		pixelSorter.orientation = (int)PixelSorter::ORIENTATION_TYPE::HORIZONTAL;
		pixelSorter.direction = (int)PixelSorter::DIRECTION_TYPE::NEGATIVE;
		break;
	case OF_KEY_RIGHT:
		pixelSorter.orientation = (int)PixelSorter::ORIENTATION_TYPE::HORIZONTAL;
		pixelSorter.direction = (int)PixelSorter::DIRECTION_TYPE::POSITIVE;
		break;
	case 'q':
		pixelSorter.sortDir = (int)PixelSorter::SORT_DIR::POSITIVE;
		break;
	case 'w':
		pixelSorter.sortDir = (int)PixelSorter::SORT_DIR::NEGATIVE;
		break;

		//-------------------------------------------------------------
	case '1':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::BRIGHTNESS;
		break;
	case '2':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::LIGHTNESS;
		break;
	case '3':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::SATURATION;
		break;
	case '4':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::HUE;
		break;
	case '5':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::REDNESS;
		break;
	case '6':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::BLUENESS;
		break;
	case '7':
		pixelSorter.sortMode = (int)PixelSorter::COMPARITOR::GREENESS;
		break;

		//-------------------------------------------------------------
	case 'z':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::NONE;
		break;
	case 'x':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::BRIGHTNESS;
		break;
	case 'c':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::LIGHTNESS;
		break;
	case 'v':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::SATURATION;
		break;
	case 'b':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::HUE;
		break;
	case 'n':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::REDNESS;
		break;
	case 'm':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::BLUENESS;
		break;
	case ',':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::GREENESS;
		break;
	case '.':
		pixelSorter.startMode = (int)PixelSorter::COMPARITOR::RANDOM;
		break;

	//-------------------------------------------------------------
	case 'Z':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::NONE;
		break;
	case 'X':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::BRIGHTNESS;
		break;
	case 'C':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::LIGHTNESS;
		break;
	case 'V':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::SATURATION;
		break;
	case 'B':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::HUE;
		break;
	case 'N':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::REDNESS;
		break;
	case 'M':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::BLUENESS;
		break;
	case '<':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::GREENESS;
		break;
	case '>':
		pixelSorter.stopMode = (int)PixelSorter::COMPARITOR::RANDOM;
		break;

	//-------------------------------------------------------------
	case '-':
		pixelSorter.upThresh -= 0.05;
		break;
	case '=':
		pixelSorter.upThresh += 0.05;
		break;
	case '_':
		pixelSorter.downThresh -= 0.05;
		break;
	case '+':
		pixelSorter.downThresh += 0.05;
		break;
	//-------------------------------------------------------------
	case 'a':
		pixelSorter.upSwap = true;
		break;
	case 's':
		pixelSorter.upSwap = false;
		break;
	case 'A':
		pixelSorter.downSwap = true;
		break;
	case 'S':
		pixelSorter.downSwap = false;
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
