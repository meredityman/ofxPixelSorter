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
	ofPixels& getPixels();

	bool isFrameNew() const { 
		return bFrameIsNew; 
	}
	bool isSetup() const { 
		return bIsSetup;
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

	bool bIsSetup = false;
	bool bFrameIsNew = false;
	bool bSetupRequired = true;
	bool bUpdateRequired = false;

	vector<unique_ptr<PixelSortingThread>> threads;	
};

