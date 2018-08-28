#include "ofxPixelSorter.h"
#include "Comparisons.h"
using namespace PixelComparisons;

//--------------------------------------------------------------
PixelSorter::PixelSorter()
{
}


//--------------------------------------------------------------
PixelSorter::~PixelSorter()
{
}

//--------------------------------------------------------------
void PixelSorter::setup(const ofPixels in)
{
	this->in = in;
	out.allocate(in.getWidth(), in.getHeight(), in.getImageType());
}

//--------------------------------------------------------------
void PixelSorter::update()
{
	pixelSort();
}

//--------------------------------------------------------------
void PixelSorter::pixelSort()
{
	vector<ofColor> line;

	sortFunction   = GetSortFunction();
	startCondition = GetTestCondition(true, upSwap);
	stopCondition  = GetTestCondition(false, downSwap);

	switch (orientation) {
		case ORIENTATION_TYPE::VERTICAL:
			for (int x = 0; x<in.getWidth(); x++) {

				for (int y = 0; y<in.getHeight(); y++) {
					line.push_back(in.getColor(x, y));
				}

				sortLine(line);

				for (int y = 0; y<in.getHeight(); y++) {
					out.setColor(x, y, line[y]);
				}
				line.clear();
			}
			break;
		case ORIENTATION_TYPE::HORIZONTAL:
			for (int y = 0; y<in.getHeight(); y++) {

				for (int x = 0; x < in.getWidth(); x++) {
					line.push_back(in.getColor(x, y));
				}

				sortLine(line);

				for (int x = 0; x < in.getWidth(); x++) {
					out.setColor(x, y, line[x]);
				}
				line.clear();
			}
			break;
	}
}
//--------------------------------------------------------------
void PixelSorter::sortLine(vector<ofColor> & line) {
	int srt, end, inc, stop;

	if (direction.get() == DIRECTION_TYPE::POSITIVE) {
		srt = 0;
		end = line.size();
		stop = line.size() - 1;
		inc = 1;
	}
	else {
		srt = line.size() -1;
		end = -1;
		stop = 0;
		inc = -1;
	}
	
	bool sorting = false;
	bool endOfLine = false;

	vector<ofColor> subLine;
	for (int i = srt; i != end; i += inc) {
		endOfLine |= (i == stop);

		if (!sorting) {
			sorting = testStartCondition(line[i], startCondition);
		}
		else {
			if (seqSmallerThanMax(&subLine) && seqLargerThanMin(&subLine) && !endOfLine) {
				sorting = testStopCondition(line[i], stopCondition);
			}
		}

		if (sorting) {
			subLine.push_back(line[i]);
		} else {
			ofSort(subLine, sortFunction);

			if ((DIRECTION_TYPE)direction.cast<DIRECTION_TYPE>() == DIRECTION_TYPE::POSITIVE) {
				std::copy(subLine.begin(), subLine.end(), line.begin() + i - subLine.size());
			}
			else {
				std::reverse(subLine.begin(), subLine.end());
				std::copy(subLine.begin(), subLine.end(), line.begin() + i);
			}

			subLine.clear();
		}
	}
};

//--------------------------------------------------------------
//
//--------------------------------------------------------------
void PixelSorter::setOrientation(ORIENTATION_TYPE _orientation) {
	ofLogNotice() << "Orientation: " + ofToString((int)_orientation);
	orientation = _orientation;
	update();
};

void PixelSorter::setDirection(DIRECTION_TYPE _direction) {
	ofLogNotice() << "Direction: " + ofToString((int)_direction);
	direction = _direction;
	update();
};


void PixelSorter::setSortDir(SORT_DIR _sortDir) {
	ofLogNotice() << "Sort Dir: " + ofToString((int)_sortDir);
	sortDir = _sortDir;
	update();
};

void PixelSorter::setSortMode(SORT_MODE _sortMode) {
	ofLogNotice() << "Sort Mode: " + ofToString((int)_sortMode);
	sortMode = _sortMode;
	update();
};

void PixelSorter::setStartMode(START_STOP_MODE  _startMode) {
	startMode = _startMode;
	ofLogNotice() << "Start Mode: " + ofToString(startMode);
	update();
};

void PixelSorter::setStopMode(START_STOP_MODE  _stopMode) {
	stopMode = _stopMode;
	ofLogNotice() << "Stop Mode: " + ofToString(startMode);
	update();
};

void PixelSorter::setUpThresh(float inc) {
	upThresh = ofClamp(upThresh + inc, 0.0, 1.0);
	ofLogNotice() << "Up Thresh: " + ofToString(upThresh);
	update();
};

void PixelSorter::setDownThresh(float inc) {
	downThresh = ofClamp(downThresh + inc, 0.0, 1.0);
	ofLogNotice() << "Down Thresh: " + ofToString(downThresh);
	update();
};

void PixelSorter::setUpSwap(bool swap) {
	ofLogNotice() << "Up Swap: " + ofToString(swap);
	upSwap = swap;
	update();
};

void PixelSorter::setDownSwap(bool swap) {
	ofLogNotice() << "Down Swap: " + ofToString(swap);
	downSwap = swap;
	update();
};

//--------------------------------------------------------------
//
//--------------------------------------------------------------
ofPixels& PixelSorter::getPixels() { 
	return out; 
}
//--------------------------------------------------------------


//--------------------------------------------------------------
// Comparision types
//--------------------------------------------------------------

PixelSorter::SortFunction PixelSorter::GetSortFunction() {
	if (sortDir.get() == SORT_DIR::POSITIVE) {
		switch (sortMode) {
			case SORT_MODE::BRIGHTNESS:
				return [](ofColor a, ofColor b) {return CompareBrightness(a, b, true); };
			case SORT_MODE::LIGHTNESS:
				return [](ofColor a, ofColor b) {return CompareLightness(a, b, true); };
			case SORT_MODE::SATURATION:
				return [](ofColor a, ofColor b) {return CompareSaturation(a, b, true); };
			case SORT_MODE::HUE:
				return [](ofColor a, ofColor b) {return CompareHue(a, b, true); };
			case SORT_MODE::REDNESS:
				return [](ofColor a, ofColor b) {return CompareRedness(a, b, true); };
			case SORT_MODE::BLUENESS:
				return [](ofColor a, ofColor b) {return CompareBlueness(a, b, true); };
			case SORT_MODE::GREENESS:
				return [](ofColor a, ofColor b) {return CompareGreeness(a, b, true); };
			case SORT_MODE::RANDOM:
			default:
				return [](ofColor a, ofColor b) {return CompareRandom(a, b, true); };
		}
	}
	else {
		switch (sortMode) {
			case SORT_MODE::BRIGHTNESS:
				return [](ofColor a, ofColor b) {return CompareBrightness(a, b, false); };
			case SORT_MODE::LIGHTNESS:
				return [](ofColor a, ofColor b) {return CompareLightness(a, b, false); };
			case SORT_MODE::SATURATION:
				return [](ofColor a, ofColor b) {return CompareSaturation(a, b, false); };
			case SORT_MODE::HUE:
				return [](ofColor a, ofColor b) {return CompareHue(a, b, false); };
			case SORT_MODE::REDNESS:
				return [](ofColor a, ofColor b) {return CompareRedness(a, b, false); };
			case SORT_MODE::BLUENESS:
				return [](ofColor a, ofColor b) {return CompareBlueness(a, b, false); };
			case SORT_MODE::GREENESS:
				return [](ofColor a, ofColor b) {return CompareGreeness(a, b, false); };
			case SORT_MODE::RANDOM:
				return [](ofColor a, ofColor b) {return CompareRandom(a, b, false); };
			default:
				return [](ofColor a, ofColor b) {return CompareRandom(a, b, false); };
		}
	}
}


//--------------------------------------------------------------
// Start Stop Conditions types
//--------------------------------------------------------------

bool PixelSorter::testStartCondition(ofColor i, TestCondition testCondition) {
	return (testCondition)(i, upThresh);
}

bool PixelSorter::testStopCondition(ofColor i, TestCondition testCondition) {
	return (testCondition)(i, downThresh);
}

PixelSorter::TestCondition PixelSorter::GetTestCondition(bool start, bool swap) {

	START_STOP_MODE mode;
	if (start) {
		mode = startMode;
	}
	else {
		mode = stopMode;
	}

	if (swap) {
		switch (mode) {
			case START_STOP_MODE::BRIGHTNESS:
				return [](ofColor a, float b) {return CompareBrightness(a, b, true); };
			case START_STOP_MODE::LIGHTNESS:
				return [](ofColor a, float b) {return CompareLightness(a, b, true); };
			case START_STOP_MODE::SATURATION:
				return [](ofColor a, float b) {return CompareSaturation(a, b, true); };
			case START_STOP_MODE::HUE:
				return [](ofColor a, float b) {return CompareHue(a, b, true); };
			case START_STOP_MODE::REDNESS:
				return [](ofColor a, float b) {return CompareRedness(a, b, true); };
			case START_STOP_MODE::BLUENESS:
				return [](ofColor a, float b) {return CompareBlueness(a, b, true); };
			case START_STOP_MODE::GREENESS:
				return [](ofColor a, float b) {return CompareGreeness(a, b, true); };
			case START_STOP_MODE::RANDOM:
				return [](ofColor a, float b) {return CompareRandom(a, b, true); };
			case START_STOP_MODE::NONE:
				return [](ofColor a, float b) {return CompareNone(a, b, true); };
		}
	}
	else {
		switch (mode) {
			case START_STOP_MODE::BRIGHTNESS:
				return [](ofColor a, float b) {return CompareBrightness(a, b, false); };
			case START_STOP_MODE::LIGHTNESS:
				return [](ofColor a, float b) {return CompareLightness(a, b, false); };
			case START_STOP_MODE::SATURATION:
				return [](ofColor a, float b) {return CompareSaturation(a, b, false); };
			case START_STOP_MODE::HUE:
				return [](ofColor a, float b) {return CompareHue(a, b, false); };
			case START_STOP_MODE::REDNESS:
				return [](ofColor a, float b) {return CompareRedness(a, b, false); };
			case START_STOP_MODE::BLUENESS:
				return [](ofColor a, float b) {return CompareBlueness(a, b, false); };
			case START_STOP_MODE::GREENESS:
				return [](ofColor a, float b) {return CompareGreeness(a, b, false); };
			case START_STOP_MODE::RANDOM:
				return [](ofColor a, float b) {return CompareRandom(a, b, false); };
			case START_STOP_MODE::NONE:
				return [](ofColor a, float b) {return CompareNone(a, b, false); };
		}
	}
}

bool PixelSorter::seqSmallerThanMax(const vector<ofColor> * subLine) {
	if (maxSeq == 0) return true;
	else return subLine->size() < maxSeq;
}
bool PixelSorter::seqLargerThanMin(const vector<ofColor> * subLine) {
	if (minSeq == 0) return true;
	else return subLine->size() > minSeq;
}

