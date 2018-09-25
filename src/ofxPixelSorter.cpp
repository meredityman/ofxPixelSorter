#include "ofxPixelSorter.h"

//--------------------------------------------------------------
void PixelSorter::setup(const ofPixels & in)
{
	setImage(in);
	bIsSetup = true;
	bUpdateRequired = true;
}

//--------------------------------------------------------------
void PixelSorter::setImage(const ofPixels & in)
{
	this->in = in;
	out = ofPixels(in);
	bUpdateRequired = true;
}

//--------------------------------------------------------------
void PixelSorter::update()
{
	if (!bIsSetup) { 
		ofLogError() << "Pixel sorter not initialised"; 
		return;
	}
	else if (!bUpdateRequired) {
		return;
	}

	if (!bThreadsSetup) { setupThreads(); }


	pixelSort();
	bUpdateRequired = false;
	bFrameIsNew = true;
}

//--------------------------------------------------------------
ofPixels& PixelSorter::getPixels() {
	if (!bIsSetup) {
		ofLogError() << "Pixel sorter not initialised";
	}

	bFrameIsNew = false;
	return out;
}
//--------------------------------------------------------------
void PixelSorter::setupThreads() {

	threads.clear();

	int nCores = std::thread::hardware_concurrency();

	for (int i = 0; i < nCores; i++) {

		unique_ptr<PixelSortingThread> newThread = make_unique<PixelSortingThread>();
		newThread->setLines(in, i);
		threads.push_back(std::move(newThread));
	}
	bThreadsSetup = true;
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