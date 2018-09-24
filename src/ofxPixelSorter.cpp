#include "ofxPixelSorter.h"

//--------------------------------------------------------------
void PixelSorter::setup(const ofPixels & in)
{
	setImage(in);
	_isSetup = true;
}

//--------------------------------------------------------------
void PixelSorter::setImage(const ofPixels & in)
{
	this->in = in;
	out.allocate(in.getWidth(), in.getHeight(), in.getImageType());

	setupThreads();
	update();
}

//--------------------------------------------------------------
void PixelSorter::update()
{
	pixelSort();
	frameIsNew = true;
}
//--------------------------------------------------------------
void PixelSorter::setupThreads() {

	int nCores = std::thread::hardware_concurrency();

	int nLines = std::floor(in.getHeight() / nCores);
	int remLines = in.getHeight() % nCores;

	for (int i = 0; i < nCores; i++) {

		int srtLine = i * nLines;
		int endLine = srtLine + nLines;

		if (i == nCores - 1) {
			endLine += remLines;
		}

		unique_ptr<PixelSortingThread> newThread = make_unique<PixelSortingThread>();
		newThread->setLines(srtLine, endLine, in);

		threads.push_back(std::move(newThread));
		threads.back()->startThread();
	}
}

//--------------------------------------------------------------
void PixelSorter::pixelSort()
{
	uint64_t srtTime = ofGetSystemTimeMillis();

	for (auto &t : threads) {
		t->setParams(settings);
		t->startThread();		
	}

	uint64_t getLinesTime = ofGetSystemTimeMillis(); 

	// Wait for threads to finish

	for (auto &t : threads) {
		t->waitForThread(false, -1);

		//ofLogNotice() << "Exec time " << t->executionTime << " Time/line " << t->timePerLines();

		for (size_t y = t->srtLine; y < t->endLine; y++) {
			
			for (size_t x = 0; x < out.getWidth(); x++) {
				out.setColor(x, y, t->getColor(x, y));
			}
		}
	}

	uint64_t sortingTime = ofGetSystemTimeMillis();

	ofLogNotice() << "GetLines time: " << getLinesTime - srtTime << "ms";
	ofLogNotice() << "Sorting time: " << sortingTime - getLinesTime << "ms";
	ofLogNotice() << "Total Execution time: " << ofGetSystemTimeMillis() - srtTime << "ms";
}

ofPixels& PixelSorter::getPixels() { 
	frameIsNew = false;
	return out; 
}