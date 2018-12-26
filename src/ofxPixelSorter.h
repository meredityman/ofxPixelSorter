#pragma once
#include "ofMain.h"
#include "PixelSortingThread.h"
#include "PixelSorterSettings.h"

class PixelSorter : public ofThread
{
public:

	void setup();
	void setImage(const ofPixels & in);

	void update( bool threaded = false);

	ofPixels& getPixels();

	bool isFrameNew() const;
	bool isSetup() const;
	bool isUpdating() const;
	bool settingsHaveChanged() const;

	void updateRequired(bool & update);
	void threadSetupRequired(bool & thread);

	PixelSorterSettings settings;

private:
	bool preUpdateChecks();
	void threadedFunction();
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

