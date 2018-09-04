#include "ofApp.h"
#include "Comparisons.h"

using namespace PixelComparisons;

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();

	ofFileDialogResult result = ofSystemLoadDialog("Select image/video", false, ofFilePath::getAbsolutePath(ofToDataPath("")));
	if (result.bSuccess) {
		string path = result.getPath();
		ofFile file(result.getPath());

		if (file.isFile()) {
			string ext = file.getExtension();

			if (ext == "jpg" || ext == "png") {
				useImage = true;
				img.load(path);
			}
			else if (ext == "mp4" || ext == "mv4") {
				useImage = false;

				vid.load(path);
				vid.setLoopState(ofLoopType::OF_LOOP_NORMAL);
				vid.play();

				img = ofImage(vid.getPixels());
			}
			else {
				ofLogError();
				exit();
			}
		}
	}
	else {
		ofLogError();
		exit();
	}

	pixelSorter.setup(img);

	gui.setup();
	gui.add(pixelSorter.params);

}

//--------------------------------------------------------------
void ofApp::update(){
	if (!useImage) {
		vid.update();
		if (vid.isFrameNew()) {
			img.setFromPixels(vid.getPixels());
			pixelSorter.setImage(img);
			pixelSorter.update();
		}
	}

	if (pixelSorter.isFrameNew()) {
		out = pixelSorter.getPixels();
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){

	float w = ofGetWidth() * 0.5;
	float h = w / img.getWidth() * img.getHeight();

	img.draw(0, 0, w, h);
	out.draw(w, 0, w, h);

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		pixelSorter.orientation = (int)ORIENTATION_TYPE::VERTICAL;
		pixelSorter.direction = (int)DIRECTION_TYPE::NEGATIVE;
		break;
	case OF_KEY_DOWN:
		pixelSorter.orientation = (int)ORIENTATION_TYPE::VERTICAL;
		pixelSorter.direction = (int)DIRECTION_TYPE::POSITIVE;
		break;
	case OF_KEY_LEFT:
		pixelSorter.orientation = (int)ORIENTATION_TYPE::HORIZONTAL;
		pixelSorter.direction = (int)DIRECTION_TYPE::NEGATIVE;
		break;
	case OF_KEY_RIGHT:
		pixelSorter.orientation = (int)ORIENTATION_TYPE::HORIZONTAL;
		pixelSorter.direction = (int)DIRECTION_TYPE::POSITIVE;
		break;
	case 'q':
		pixelSorter.sortDir = (int)SORT_DIR::POSITIVE;
		break;
	case 'w':
		pixelSorter.sortDir = (int)SORT_DIR::NEGATIVE;
		break;

		//-------------------------------------------------------------
	case '1':
		pixelSorter.sortMode = (int)COMPARITOR::BRIGHTNESS;
		break;
	case '2':
		pixelSorter.sortMode = (int)COMPARITOR::LIGHTNESS;
		break;
	case '3':
		pixelSorter.sortMode = (int)COMPARITOR::SATURATION;
		break;
	case '4':
		pixelSorter.sortMode = (int)COMPARITOR::HUE;
		break;
	case '5':
		pixelSorter.sortMode = (int)COMPARITOR::REDNESS;
		break;
	case '6':
		pixelSorter.sortMode = (int)COMPARITOR::BLUENESS;
		break;
	case '7':
		pixelSorter.sortMode = (int)COMPARITOR::GREENESS;
		break;

		//-------------------------------------------------------------
	case 'z':
		pixelSorter.startMode = (int)COMPARITOR::NONE;
		break;
	case 'x':
		pixelSorter.startMode = (int)COMPARITOR::BRIGHTNESS;
		break;
	case 'c':
		pixelSorter.startMode = (int)COMPARITOR::LIGHTNESS;
		break;
	case 'v':
		pixelSorter.startMode = (int)COMPARITOR::SATURATION;
		break;
	case 'b':
		pixelSorter.startMode = (int)COMPARITOR::HUE;
		break;
	case 'n':
		pixelSorter.startMode = (int)COMPARITOR::REDNESS;
		break;
	case 'm':
		pixelSorter.startMode = (int)COMPARITOR::BLUENESS;
		break;
	case ',':
		pixelSorter.startMode = (int)COMPARITOR::GREENESS;
		break;
	case '.':
		pixelSorter.startMode = (int)COMPARITOR::RANDOM;
		break;

	//-------------------------------------------------------------
	case 'Z':
		pixelSorter.stopMode = (int)COMPARITOR::NONE;
		break;
	case 'X':
		pixelSorter.stopMode = (int)COMPARITOR::BRIGHTNESS;
		break;
	case 'C':
		pixelSorter.stopMode = (int)COMPARITOR::LIGHTNESS;
		break;
	case 'V':
		pixelSorter.stopMode = (int)COMPARITOR::SATURATION;
		break;
	case 'B':
		pixelSorter.stopMode = (int)COMPARITOR::HUE;
		break;
	case 'N':
		pixelSorter.stopMode = (int)COMPARITOR::REDNESS;
		break;
	case 'M':
		pixelSorter.stopMode = (int)COMPARITOR::BLUENESS;
		break;
	case '<':
		pixelSorter.stopMode = (int)COMPARITOR::GREENESS;
		break;
	case '>':
		pixelSorter.stopMode = (int)COMPARITOR::RANDOM;
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
