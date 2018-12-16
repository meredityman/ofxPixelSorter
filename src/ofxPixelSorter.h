#pragma once
#include "ofMain.h"
#include "PixelSortingThread.h"
#include "PixelSorterSettings.h"

class PixelSorter
{
public:

	void setup();
	void setImage(const ofPixels & in);

	void update();
	ofPixels& getPixels();

	bool isFrameNew() const { 
		return bFrameIsNew; 
	}
	bool isSetup() const { 
		return bImageSet;
	};
	bool settingsHaveChanged() const {
		return bUpdateRequired;
	};

	void updateRequired(bool & update) {
		bUpdateRequired = update;
	}
	void threadSetupRequired(bool & thread) {
		bSetupRequired = thread;
	}

	PixelSorterSettings settings;


private:

	void setupThreads();
	void pixelSort();

	ofPixels in;
	ofPixels out;

	bool bImageSet = false;
	bool bFrameIsNew = false;
	bool bSetupRequired = true;
	bool bUpdateRequired = false;

	vector<unique_ptr<PixelSortingThread>> threads;	
};

