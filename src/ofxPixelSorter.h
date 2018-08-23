#pragma once
#include "ofMain.h"

class PixelSorter
{
public:
	enum class ORIENTATION_TYPE {
		HORIZONTAL,
		VERTICAL
	};

	enum class DIRECTION_TYPE {
		POSITIVE,
		NEGATIVE
	};

	enum class SORT_DIR {
		POSITIVE,
		NEGATIVE
	};

	enum class  SORT_MODE {
		BRIGHTNESS,
		LIGHTNESS,
		SATURATION,
		HUE,
		REDNESS,
		BLUENESS,
		GREENESS,
		RANDOM
	};

	enum class  START_STOP_MODE {
		NONE,
		BRIGHTNESS,
		LIGHTNESS,
		SATURATION,
		HUE,
		REDNESS,
		BLUENESS,
		GREENESS,
		RANDOM
	};

	typedef bool (*SortFunction)(ofColor a, ofColor b);
	typedef bool(*TestCondition)(ofColor a, float thresh);

	PixelSorter();
	~PixelSorter();
	void setup(const ofImage in);
	void update();
	ofImage out;
	ofImage in;

	SortFunction GetSortFunction();

	void setOrientation(ORIENTATION_TYPE _orientation);
	void setDirection(DIRECTION_TYPE _direction);
	void setSortDir(SORT_DIR _sortDir);
	void setSortMode(SORT_MODE _sortMode);
	void setStartMode(START_STOP_MODE  _startMode);
	void setStopMode(START_STOP_MODE  _stopMode);
	void setUpThresh(float inc);
	void setDownThresh(float inc);
	void setUpSwap(bool swap);
	void setDownSwap(bool swap);

private:

	ofParameter<ORIENTATION_TYPE> orientation = ORIENTATION_TYPE::HORIZONTAL;
	ofParameter<DIRECTION_TYPE>   direction = DIRECTION_TYPE::POSITIVE;
	ofParameter<SORT_DIR>         sortDir = SORT_DIR::POSITIVE;
	ofParameter<SORT_MODE>        sortMode = SORT_MODE::BRIGHTNESS;
	ofParameter<START_STOP_MODE>  startMode = START_STOP_MODE::BRIGHTNESS;
	ofParameter<START_STOP_MODE>  stopMode = START_STOP_MODE::BRIGHTNESS;

	ofParameter<bool> upSwap = true;
	ofParameter<bool> downSwap = true;

	ofParameter<float> upThresh = 0.5;
	ofParameter<float> downThresh = 0.5;
	
	ofParameter<unsigned int> maxSeq = 200;
	ofParameter<unsigned int> minSeq = 20;

	ofEventListener updateOnChanged() {
		update();
	}

	void pixelSort(ofImage image);
	void pixelSort();
	void sortLine(vector<ofColor> & line);

	bool seqSmallerThanMax (const vector<ofColor> * subLine){ 
		if (maxSeq == 0) return true;
		else return subLine->size() < maxSeq;
	}
	bool seqLargerThanMin  (const vector<ofColor> * subLine) {
		if (minSeq == 0) return true;
		else return subLine->size() > minSeq;
	}



	bool testStartCondition(ofColor i, TestCondition testCondition);
	bool testStopCondition(ofColor i,  TestCondition testCondition);

	TestCondition GetTestCondition(bool start, bool swap);
};

