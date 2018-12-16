#include "ofxPixelSorter.h"

//--------------------------------------------------------------
void PixelSorter::setup()
{
	ofLogVerbose() << "Setting up...";
	ofAddListener(settings.onUpdateRequired, this, &PixelSorter::updateRequired);
	ofAddListener(settings.onThreadSetupRequired, this, &PixelSorter::threadSetupRequired);
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
void PixelSorter::update()
{
	if (!bImageSet) { 
		ofLogError() << "Pixel sorter not initialised"; 
		return;
	}
	else if (!bUpdateRequired) {
		ofLogNotice() << "No update required";
		return;
	}

	ofLogVerbose() << settings.toString();

	if (bSetupRequired) {
		setupThreads(); 
	}


	pixelSort();
	bUpdateRequired = false;
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

		//ofLogVerbose() << "Exec time " << t->executionTime << " Time/line " << t->timePerLines();
		t->readOutPixels(out);
	}

	uint64_t sortingTime = ofGetSystemTimeMillis();

	ofLogVerbose() << "GetLines time: " << getLinesTime - srtTime << "ms";
	ofLogVerbose() << "Sorting time: " << sortingTime - getLinesTime << "ms";
	ofLogVerbose() << "Total Execution time: " << ofGetSystemTimeMillis() - srtTime << "ms";
}