#include "ofxPixelSorter.h"

//--------------------------------------------------------------
PixelSorter::PixelSorter()
{
}


//--------------------------------------------------------------
PixelSorter::~PixelSorter()
{
}

//--------------------------------------------------------------
void PixelSorter::setup(const ofImage in)
{
	this->in = ofImage(in);
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
	out.update();
}
//--------------------------------------------------------------
void PixelSorter::sortLine(vector<ofColor> & line) {
	int srt, end, inc, stop;

	if ((DIRECTION_TYPE)direction.cast<DIRECTION_TYPE>() == DIRECTION_TYPE::POSITIVE) {
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
	
	SortFunction sortFunction = GetSortFunction();
	TestCondition startCondition = GetTestCondition(true, upSwap);
	TestCondition stopCondition  = GetTestCondition(false, downSwap);

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
void PixelSorter::setOrientation(ORIENTATION_TYPE _orientation) {
	ofLogNotice() << "Orientation: " + ofToString((int)_orientation);
	orientation = _orientation;
};

void PixelSorter::setDirection(DIRECTION_TYPE _direction) {
	ofLogNotice() << "Direction: " + ofToString((int)_direction);
	direction = _direction;
};


void PixelSorter::setSortDir(SORT_DIR _sortDir) {
	ofLogNotice() << "Sort Dir: " + ofToString((int)_sortDir);
	sortDir = _sortDir;
};

void PixelSorter::setSortMode(SORT_MODE _sortMode) {
	ofLogNotice() << "Sort Mode: " + ofToString((int)_sortMode);
	sortMode = _sortMode;
};

void PixelSorter::setStartMode(START_STOP_MODE  _startMode) {
	startMode = _startMode;
	ofLogNotice() << "Start Mode: " + ofToString(startMode);
};

void PixelSorter::setStopMode(START_STOP_MODE  _stopMode) {
	stopMode = _stopMode;
	ofLogNotice() << "Stop Mode: " + ofToString(startMode);
};

void PixelSorter::setUpThresh(float inc) {
	upThresh = ofClamp(upThresh + inc, 0.0, 1.0);
	ofLogNotice() << "Up Thresh: " + ofToString(upThresh);
};

void PixelSorter::setDownThresh(float inc) {
	downThresh = ofClamp(downThresh + inc, 0.0, 1.0);
	ofLogNotice() << "Down Thresh: " + ofToString(downThresh);
};

void PixelSorter::setUpSwap(bool swap) {
	ofLogNotice() << "Up Swap: " + ofToString(swap);
	upSwap = swap;
};

void PixelSorter::setDownSwap(bool swap) {
	ofLogNotice() << "Down Swap: " + ofToString(swap);
	downSwap = swap;

};

//--------------------------------------------------------------
// Comparision types
//--------------------------------------------------------------

PixelSorter::SortFunction PixelSorter::GetSortFunction() {
	if ((SORT_DIR)sortDir.cast<SORT_DIR>() == SORT_DIR::POSITIVE) {
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

bool PixelSorter::CompareBrightness(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.getBrightness() > b.getBrightness();
	}
	else {
		return a.getBrightness() < b.getBrightness();
	}	
}
bool PixelSorter::CompareBrightness(ofColor a, float b, bool swap) {
	if (swap) {
		return a.getBrightness() >= b * 255;
	}
	else {
		return a.getBrightness() <= b * 255;
	}
}

//--------------------------------------------------------------

bool PixelSorter::CompareLightness(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.getLightness() > b.getLightness();
	}
	else {
		return a.getLightness() < b.getLightness();
	}
}

bool PixelSorter::CompareLightness(ofColor a, float b, bool swap) {
	if (swap) {
		return a.getLightness() >= b * 255;
	}
	else {
		return a.getLightness() <= b * 255;
	}
}

//--------------------------------------------------------------


bool PixelSorter::CompareSaturation(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.getSaturation() > b.getSaturation();
	}
	else {
		return a.getSaturation() < b.getSaturation();
	}
}

bool PixelSorter::CompareSaturation(ofColor a, float b, bool swap) {
	if (swap) {
		return a.getSaturation() >= b * 255;
	}
	else {
		return a.getSaturation() <= b * 255;
	}
}

//--------------------------------------------------------------


bool PixelSorter::CompareHue(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.getHue() > b.getHue();
	}
	else {
		return a.getHue() < b.getHue();
	}
}

bool PixelSorter::CompareHue(ofColor a, float b, bool swap) {
	if (swap) {
		return a.getHue() >= b * 255;
	}
	else {
		return a.getHue() <= b * 255;
	}
}

//--------------------------------------------------------------

bool PixelSorter::CompareRedness(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.r > b.r;
	}
	else {
		return a.r < b.r;
	}
}

bool PixelSorter::CompareRedness(ofColor a, float b, bool swap) {
	if (swap) {
		return a.r >= b;
	}
	else {
		return a.r <= b;
	}
}

//--------------------------------------------------------------

bool PixelSorter::CompareGreeness(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.g > b.g;
	}
	else {
		return a.g < b.g;
	}
}

bool PixelSorter::CompareGreeness(ofColor a, float b, bool swap) {
	if (swap) {
		return a.r >= b;
	}
	else {
		return a.r <= b;
	}
}
//--------------------------------------------------------------

bool PixelSorter::CompareBlueness(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.b > b.b;
	}
	else {
		return a.b < b.b;
	}
}

bool PixelSorter::CompareBlueness(ofColor a, float b, bool swap) {
	if (swap) {
		return a.b >= b;
	}
	else {
		return a.b <= b;
	}
}

//--------------------------------------------------------------

bool PixelSorter::CompareRandom(ofColor a, ofColor b, bool swap) {
	if (swap) {
		return a.b > b.b; // BROKEN!!!!
	}
	else {
		return a.b < b.b;
	}
}

bool PixelSorter::CompareRandom(ofColor a, float b, bool swap) {
	if (swap) {
		return ofRandomuf() > b;
	}
	else {
		return ofRandomuf() < b;
	}
	
}

//--------------------------------------------------------------
bool PixelSorter::CompareNone(ofColor a, float b, bool swap) {
	return swap;
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
	} else {
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
