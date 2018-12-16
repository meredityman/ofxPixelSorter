#include "ofApp.h"
#include "Comparisons.h"

using namespace PixelComparisons;

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	ofSetLogLevel(OF_LOG_NOTICE);
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
		ofFile file(result.getPath());

		imageName = result.fileName;

		if (file.isFile()) {
			string ext = file.getExtension();

			if (ext == "jpg" || ext == "JPG" || ext == "png" || "PNG") {
				img.load(file.path());
				pixelSorter.setImage(img);
				out = ofImage(img);
				ofLogNotice() << "Loaded Image: " << imageName;
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

	if (autoUpdate && ofGetElapsedTimeMillis() % 1000 >= 1.0) {
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

}
//--------------------------------------------------------------
void ofApp::drawGUI() {
	auto mainSettings = ofxImGui::Settings();

	gui.begin();
	if (ofxImGui::BeginWindow("Settings", mainSettings, false)) {

		if (imageLoaded) {
			stringstream str;
			str << imageName << "\n";
			str << img.getWidth() << " x " << img.getHeight();
			ImGui::Text(str.str().c_str());
		}
		else {
			ImGui::Text("No Image Loaded...");
		}


		if (ImGui::Button("Load"))	 loadImage();
		ImGui::SameLine();
		if (ImGui::Button("Save"))	 saveImage();


		if (ImGui::Button("Update") && !autoUpdate) pixelSorter.update();
		ImGui::SameLine();
		ofxImGui::AddParameter(autoUpdate);

		ImGui::BeginGroup();
		ofxImGui::AddRadio(pixelSorter.settings.orientation, orientationNames, 2);
		ofxImGui::AddRadio(pixelSorter.settings.direction  , directionNames  , 2);
		ofxImGui::AddRadio(pixelSorter.settings.sortDir    , sortDirNames    , 2);
		ofxImGui::AddRadio(pixelSorter.settings.sortMode   , comparitorNames , 2);
		ofxImGui::AddRadio(pixelSorter.settings.startMode  , comparitorNames , 2);
		ofxImGui::AddRadio(pixelSorter.settings.stopMode   , comparitorNames , 2);
	
		ofxImGui::AddParameter(pixelSorter.settings.upSwap);
		ImGui::SameLine();
		ofxImGui::AddParameter(pixelSorter.settings.upThresh);


		ofxImGui::AddParameter(pixelSorter.settings.downSwap);
		ImGui::SameLine();
		ofxImGui::AddParameter(pixelSorter.settings.downThresh);


		ofxImGui::AddParameter(pixelSorter.settings.maxSeq);
		ofxImGui::AddParameter(pixelSorter.settings.minSeq);
		ImGui::EndGroup();
	}

	ofxImGui::EndWindow(mainSettings);

	gui.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch (key) {
	case OF_KEY_RETURN:
		if (!autoUpdate) pixelSorter.update();
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
