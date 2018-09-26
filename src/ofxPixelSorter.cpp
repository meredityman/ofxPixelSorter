#include "ofxPixelSorter.h"

//--------------------------------------------------------------
void PixelSorter::setup(const ofPixels & in)
{
	setImage(in);
	bIsSetup = true;
	bUpdateRequired = true;

	onUpdateRequired.push(settings.orientation.newListener([&](int&) {this->updateRequired(); }));
	onThreadSetupRequired = settings.orientation.newListener([&](int&) {this->threadSetupRequired(); });

	onUpdateRequired.push(settings.direction.newListener([&](int&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.sortDir.newListener([&](int&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.sortMode.newListener([&](int&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.startMode.newListener([&](int&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.stopMode.newListener([&](int&) {this->updateRequired(); }));

	onUpdateRequired.push(settings.upSwap.newListener([&](bool&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.downSwap.newListener([&](bool&) {this->updateRequired(); }));

	onUpdateRequired.push(settings.upThresh.newListener([&](float&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.downThresh.newListener([&](float&) {this->updateRequired(); }));

	onUpdateRequired.push(settings.maxSeq.newListener([&](unsigned int&) {this->updateRequired(); }));
	onUpdateRequired.push(settings.minSeq.newListener([&](unsigned int&) {this->updateRequired(); }));
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
		newThread->setSettings(settings);
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