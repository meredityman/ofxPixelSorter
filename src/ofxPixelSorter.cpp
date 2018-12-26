#include "ofxPixelSorter.h"

//--------------------------------------------------------------
void PixelSorter::setup()
{
	ofLogVerbose() << "Setting up Pixel Sorter...";
	ofAddListener(settings.onUpdateRequired, this, &PixelSorter::updateRequired);
	ofAddListener(settings.onThreadSetupRequired, this, &PixelSorter::threadSetupRequired);
}
//--------------------------------------------------------------
bool PixelSorter::isFrameNew() const { 
	return bFrameIsNew; 
}
//--------------------------------------------------------------
bool PixelSorter::isSetup() const { 
	return bImageSet;
};
//--------------------------------------------------------------
bool PixelSorter::isUpdating() const { 
	return isThreadRunning();
};
//--------------------------------------------------------------
bool PixelSorter::settingsHaveChanged() const {
	return bUpdateRequired;
};
//--------------------------------------------------------------
void PixelSorter::updateRequired(bool & update) {
	PixelSorter::bUpdateRequired = update;
}
//--------------------------------------------------------------
void PixelSorter::threadSetupRequired(bool & thread) {
	bSetupRequired = thread;
}
//--------------------------------------------------------------
void PixelSorter::setImage(const ofPixels & in)
{
	ofLogVerbose() << "Setting Image...";
	this->in = in;
	out = ofPixels(in);
	bImageSet = true;
	bUpdateRequired = true;
	bSetupRequired = true;
}
//--------------------------------------------------------------
bool PixelSorter::preUpdateChecks() {
	if (!bImageSet) { 
		ofLogWarning() << "Pixel sorter not initialised"; 
		return false;
	}
	else if (isUpdating()) {
		//ofLogVerbose() << "Already updating";
		return false;
	}
	else if (!bUpdateRequired) {
		//ofLogVerbose() << "No update required";
		return false;
	}

	ofLogVerbose() << settings.toString();

	if (bSetupRequired) {
		setupThreads(); 
	}
}
//--------------------------------------------------------------
void PixelSorter::update(bool threaded) {
	if (preUpdateChecks()) {
		if (threaded) {
			startThread();
		}
		else {
			threadedFunction();
		}
		
	}	
}
//--------------------------------------------------------------
void PixelSorter::threadedFunction() {	
	pixelSort();
	bUpdateRequired = settings.isRandom();	
	bFrameIsNew = true;
}

//--------------------------------------------------------------
ofPixels& PixelSorter::getPixels() {
	if (!bImageSet) {
		ofLogError() << "Pixel sorter not initialised";
	}

	bFrameIsNew = false;
	return out;
}
//--------------------------------------------------------------
void PixelSorter::setupThreads() {
	ofLogVerbose() << "Setting up threads";
	threads.clear();

	int nCores = std::thread::hardware_concurrency();

	for (int i = 0; i < nCores; i++) {

		unique_ptr<PixelSortingThread> newThread = make_unique<PixelSortingThread>();
			
		newThread->setSettings(settings);
		newThread->setLines(in, i);
		threads.push_back(std::move(newThread));
	}
	bSetupRequired = false;
}

//--------------------------------------------------------------
void PixelSorter::pixelSort()
{
	uint64_t srtTime = ofGetSystemTimeMillis();

	for (auto &t : threads) {

		t->setSettings(settings);
		t->startThread();		
	}

	uint64_t getLinesTime = ofGetSystemTimeMillis(); 

	// Wait for threads to finish
	for (auto &t : threads) {
		t->waitForThread(false, -1);

		ofLogVerbose() << "Exec time " << t->executionTime << " Time/line " << t->timePerLines();
		t->readOutPixels(out);
	}

	uint64_t sortingTime = ofGetSystemTimeMillis();

	ofLogVerbose() << "GetLines time: " << getLinesTime - srtTime << "ms";
	ofLogVerbose() << "Sorting time: " << sortingTime - getLinesTime << "ms";
	ofLogVerbose() << "Total Execution time: " << ofGetSystemTimeMillis() - srtTime << "ms";
}
