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

	PixelSorterSettings settings;

private:

	void setupThreads();
	void pixelSort();

	void updateRequired() {
		ofLogNotice() << "Update Required";
		bUpdateRequired = true;
	}
	void threadSetupRequired() {
		bThreadsSetup = false;
	}
	ofEventListeners onUpdateRequired;
	ofEventListener onThreadSetupRequired;

	ofPixels in;
	ofPixels out;

	bool bIsSetup = false;
	bool bFrameIsNew = false;
	bool bThreadsSetup = false;
	bool bUpdateRequired = false;

	vector<unique_ptr<PixelSortingThread>> threads;	
};

