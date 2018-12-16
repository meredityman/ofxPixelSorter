#include "ofApp.h"
#include "Comparisons.h"

using namespace PixelComparisons;

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	ofSetLogLevel(OF_LOG_VERBOSE);
	pixelSorter.setup();
	setupGui();
}
//--------------------------------------------------------------
void ofApp::setupGui() {
	gui.setup();
	gui.setTheme(new ofxImGui::DefaultTheme());
	ImGui::GetIO().MouseDrawCursor = false;
}
//--------------------------------------------------------------
void ofApp::loadImage() {
	imageLoaded = false;
	ofFileDialogResult result = ofSystemLoadDialog("Load image", false, ofFilePath::getAbsolutePath(ofToDataPath("")));
	if (result.bSuccess) {
		string path = result.getPath();
		ofFile file(result.getPath());

		if (file.isFile()) {
			string ext = file.getExtension();

			if (ext == "jpg" || ext == "JPG" || ext == "png" || "PNG") {
				img.load(path);
				pixelSorter.setImage(img);
				out = ofImage(img);
				ofLogNotice() << "Loaded Image: " << result.fileName;
				imageLoaded = true;
			}
		}
	}
}
//--------------------------------------------------------------
void ofApp::saveImage() {
	ofFileDialogResult result = ofSystemSaveDialog("image.png", "Save Image" );

	if (result.bSuccess) {

		bool success = out.save(result.getPath());

		if (success) {
			ofLogNotice() << "Successfuly saved " << result.getName();
		}
	}
}
//--------------------------------------------------------------
void ofApp::update(){
	if (!imageLoaded) return;

	if (autoUpdate) {
		pixelSorter.update();
	}

	if (pixelSorter.isFrameNew()) {
		out = pixelSorter.getPixels();
	}

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (imageLoaded) {

		float w = ofGetWidth() * 0.5;
		float h = w / img.getWidth() * img.getHeight();

		img.draw(0, 0, w, h);
		out.draw(w, 0, w, h);
	}
	drawGUI();
	//ofDrawBitmapStringHighlight(pixelSorter.settings.toString(),
	//	ofVec2f(0, 0),
	//	ofColor::black,
	//	ofColor::white); 
}
//--------------------------------------------------------------
void ofApp::drawGUI() {
	auto mainSettings = ofxImGui::Settings();

	gui.begin();
	if (ofxImGui::BeginWindow("Settings", mainSettings, false)) {
		if (ImGui::Button("Load"))	 loadImage();
		if (ImGui::Button("Save"))	 saveImage();
		if (ImGui::Button("Update")) pixelSorter.update();

		ofxImGui::AddRadio(pixelSorter.settings.orientation, orientationNames, orientationNames.size());
		ofxImGui::AddRadio(pixelSorter.settings.direction  , directionNames  , directionNames.size());
		ofxImGui::AddRadio(pixelSorter.settings.sortDir    , sortDirNames    , sortDirNames.size());
		ofxImGui::AddRadio(pixelSorter.settings.sortMode   , comparitorNames , comparitorNames.size());
		ofxImGui::AddRadio(pixelSorter.settings.startMode  , comparitorNames , comparitorNames.size());
		ofxImGui::AddRadio(pixelSorter.settings.stopMode   , comparitorNames , comparitorNames.size());
	
		ofxImGui::AddParameter(pixelSorter.settings.upSwap);
		ofxImGui::AddParameter(pixelSorter.settings.downSwap);

		ofxImGui::AddParameter(pixelSorter.settings.upThresh);
		ofxImGui::AddParameter(pixelSorter.settings.downThresh);


		ofxImGui::AddParameter(pixelSorter.settings.maxSeq);
		ofxImGui::AddParameter(pixelSorter.settings.minSeq);
	
	}

	ofxImGui::EndWindow(mainSettings);



	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case OF_KEY_RETURN:
		if(!autoUpdate) pixelSorter.update();
		break;
	case OF_KEY_UP:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::VERTICAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_DOWN:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::VERTICAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::POSITIVE);
		break;
	case OF_KEY_LEFT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::HORIZONTAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_RIGHT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::HORIZONTAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::POSITIVE);
		break;
	case OF_KEY_RIGHT_ALT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::DIAGONAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_RIGHT_SHIFT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::DIAGONAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::POSITIVE);
		break;
	case OF_KEY_LEFT_ALT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::ANTIDIAGONAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::NEGATIVE);
		break;
	case OF_KEY_LEFT_SHIFT:
		pixelSorter.settings.setOrientation(ORIENTATION_TYPE::ANTIDIAGONAL);
		pixelSorter.settings.setDirection(DIRECTION_TYPE::POSITIVE);
		break;

	case 'q':
		pixelSorter.settings.setSortDir(SORT_DIR::POSITIVE);
		break;
	case 'w':
		pixelSorter.settings.setSortDir(SORT_DIR::NEGATIVE);
		break;

		//-------------------------------------------------------------
	case '1':
		pixelSorter.settings.setSortMode(COMPARATOR::BRIGHTNESS);
		break;
	case '2':
		pixelSorter.settings.setSortMode(COMPARATOR::LIGHTNESS);
		break;
	case '3':
		pixelSorter.settings.setSortMode(COMPARATOR::SATURATION);
		break;
	case '4':
		pixelSorter.settings.setSortMode(COMPARATOR::HUE);
		break;
	case '5':
		pixelSorter.settings.setSortMode(COMPARATOR::REDNESS);
		break;
	case '6':
		pixelSorter.settings.setSortMode(COMPARATOR::BLUENESS);
		break;
	case '7':
		pixelSorter.settings.setSortMode(COMPARATOR::GREENESS);
		break;

		//-------------------------------------------------------------
	case 'z':
		pixelSorter.settings.setStartMode(COMPARATOR::NONE);
		break;
	case 'x':
		pixelSorter.settings.setStartMode(COMPARATOR::BRIGHTNESS);
		break;
	case 'c':
		pixelSorter.settings.setStartMode(COMPARATOR::LIGHTNESS);
		break;
	case 'v':
		pixelSorter.settings.setStartMode(COMPARATOR::SATURATION);
		break;
	case 'b':
		pixelSorter.settings.setStartMode(COMPARATOR::HUE);
		break;
	case 'n':
		pixelSorter.settings.setStartMode(COMPARATOR::REDNESS);
		break;
	case 'm':
		pixelSorter.settings.setStartMode(COMPARATOR::BLUENESS);
		break;
	case ',':
		pixelSorter.settings.setStartMode(COMPARATOR::GREENESS);
		break;
	case '.':
		pixelSorter.settings.setStartMode(COMPARATOR::RANDOM);
		break;

	//-------------------------------------------------------------
	case 'Z':
		pixelSorter.settings.setStopMode(COMPARATOR::NONE);
		break;
	case 'X':
		pixelSorter.settings.setStopMode(COMPARATOR::BRIGHTNESS);
		break;
	case 'C':
		pixelSorter.settings.setStopMode(COMPARATOR::LIGHTNESS);
		break;
	case 'V':
		pixelSorter.settings.setStopMode(COMPARATOR::SATURATION);
		break;
	case 'B':
		pixelSorter.settings.setStopMode(COMPARATOR::HUE);
		break;
	case 'N':
		pixelSorter.settings.setStopMode(COMPARATOR::REDNESS);
		break;
	case 'M':
		pixelSorter.settings.setStopMode(COMPARATOR::BLUENESS);
		break;
	case '<':
		pixelSorter.settings.setStopMode(COMPARATOR::GREENESS);
		break;
	case '>':
		pixelSorter.settings.setStopMode(COMPARATOR::RANDOM);
		break;

	//-------------------------------------------------------------
	case '-':
		pixelSorter.settings.incUpThresh(-0.05);
		break;
	case '=':
		pixelSorter.settings.incUpThresh(0.05);
		break;
	case '_':
		pixelSorter.settings.incDownThresh(-0.05);
		break;
	case '+':
		pixelSorter.settings.incDownThresh(0.05);
		break;
	//-------------------------------------------------------------
	case 'a':
		pixelSorter.settings.setUpSwap(true);
		break;
	case 's':
		pixelSorter.settings.setUpSwap(false);
		break;
	case 'A':
		pixelSorter.settings.setDownSwap(true);
		break;
	case 'S':
		pixelSorter.settings.setDownSwap(false);
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
