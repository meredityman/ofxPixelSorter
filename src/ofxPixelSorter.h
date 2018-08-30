#pragma once
#include "ofMain.h"
#include "Comparisons.h"
using namespace PixelComparisons;

class PixelSorter
{
public:

	const int maxLineLength = 5120;

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

	enum class  COMPARITOR {
		BRIGHTNESS,
		LIGHTNESS,
		SATURATION,
		HUE,
		REDNESS,
		BLUENESS,
		GREENESS,
		RANDOM,
		NONE
	};



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

	PixelSorter();
	~PixelSorter();
	void setup(const ofPixels in);
	void update();

	ofPixels& getPixels();

	void setImage(const ofPixels in);
	bool isFrameNew() { return frameIsNew; }


private:

	ofPixels out;
	ofPixels in;

	unique_ptr<Comparator> sortFunction;
	unique_ptr<Comparator> startCondition;
	unique_ptr<Comparator> stopCondition;

	bool frameIsNew = false;

	void pixelSort();
	void sortLine(vector<ofColor> & line);

	bool seqSmallerThanMax(const vector<ofColor> * subLine);
	bool seqLargerThanMin(const vector<ofColor> * subLine);

	unique_ptr<Comparator> GetTestCondition(bool start, bool swap);
	unique_ptr<Comparator> GetSortFunction();
	unique_ptr<Comparator> GetComparitor(COMPARITOR mode, bool swap);

	void parameterChanged(ofAbstractParameter & parameter){ 
		update();
		ofLogNotice() << params.toString(); 
	}
};

