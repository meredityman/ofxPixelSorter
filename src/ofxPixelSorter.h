#pragma once
#include "ofMain.h"
#include "PixelSortingThread.h"

class PixelSorter
{
public:

	const int maxLineLength = 5120;

	// Parameters
	ofParameterGroup params;

	ofParameter<int> orientation;
	ofParameter<int> direction;
	ofParameter<int> sortDir;
	ofParameter<int> sortMode;
	ofParameter<int> startMode;
	ofParameter<int> stopMode;

	ofParameter<bool> upSwap;
	ofParameter<bool> downSwap;

	ofParameter<float> upThresh;
	ofParameter<float> downThresh;

	ofParameter<unsigned int> maxSeq;
	ofParameter<unsigned int> minSeq;

	void setup(const ofPixels & in);
	void update();

	ofPixels& getPixels();

	void setImage(const ofPixels & in);
	bool isFrameNew() { return frameIsNew; }


private:
	ofPixels in;
	ofPixels out;

	vector<unique_ptr<PixelSortingThread>> threads;

	bool frameIsNew = false;

	void setupParams();
	void setupThreads();
	void pixelSort();


	void parameterChanged(ofAbstractParameter & parameter){ 
		ofLogNotice() << params.toString();
		update();
	}
};

