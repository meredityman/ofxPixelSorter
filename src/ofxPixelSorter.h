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

	void setOrientation(const PixelSorterSettings::ORIENTATION_TYPE orientation) { 
		settings.orientation = orientation; 
		bThreadsSetup = false;
		bUpdateRequired = true;
	};
	void setDirection(const PixelSorterSettings::DIRECTION_TYPE direction) {
		settings.direction = direction;
		bUpdateRequired = true;
	};
	void setSortDir(const PixelSorterSettings::SORT_DIR sortDir) {
		settings.sortDir = sortDir;
		bUpdateRequired = true;
	};
	void setSortMode(const PixelSorterSettings::COMPARATOR sortMode) {
		settings.sortMode = sortMode;
		bUpdateRequired = true;
	};
	void setStartMode(const PixelSorterSettings::COMPARATOR startMode) {
		settings.startMode = startMode;
		bUpdateRequired = true;
	};
	void setStopMode(const PixelSorterSettings::COMPARATOR stopMode) {
		settings.stopMode = stopMode;
		bUpdateRequired = true;
	};
	void setUpSwap(const bool upSwap) {
		settings.upSwap = upSwap;
		bUpdateRequired = true;
	};
	void setDownSwap(const bool downSwap) {
		settings.downSwap = downSwap;
		bUpdateRequired = true;
	};
	void setUpThresh(const float upThresh) {
		settings.upThresh = upThresh;
		bUpdateRequired = true;
	};
	void setDownThresh(const float downThresh) {
		settings.downThresh = downThresh;
		bUpdateRequired = true;
	};
	void setMaxSeq(const unsigned int maxSeq) {
		settings.maxSeq = maxSeq;
		bUpdateRequired = true;
	};
	void setMinSeq(const unsigned int minSeq) {
		settings.minSeq = minSeq;
		bUpdateRequired = true;
	};

private:

	void setupThreads();
	void pixelSort();

	PixelSorterSettings settings;

	ofPixels in;
	ofPixels out;

	bool bIsSetup = false;
	bool bFrameIsNew = false;
	bool bThreadsSetup = false;
	bool bUpdateRequired = false;

	vector<unique_ptr<PixelSortingThread>> threads;	
};

