#pragma once
#include "ofMain.h"
#include "PixelSortingThread.h"
#include "PixelSorterSettings.h"

class PixelSorter
{
public:

	void setup(const ofPixels & in);
	void setImage(const ofPixels & in);

	void update();

	bool isFrameNew() { return frameIsNew; }
	ofPixels& getPixels();


	bool isSetup() const {
		return _isSetup;
	};

private:

	void setupParams();
	void setupThreads();
	void pixelSort();

	PixelSorterSettings settings;
	ofPixels in;
	ofPixels out;

	bool _isSetup = false;
	bool frameIsNew = false;

	vector<unique_ptr<PixelSortingThread>> threads;	
	
};

