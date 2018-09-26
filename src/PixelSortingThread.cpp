#include "PixelSortingThread.h"


//--------------------------------------------------------------
void PixelSortingThread::setSettings(PixelSorterSettings settings) {
	this->settings = settings;

	sortFunctions.sortFunction   = GetSortFunction();
	sortFunctions.startCondition = GetTestCondition(true, settings.upSwap);
	sortFunctions.stopCondition  = GetTestCondition(false, settings.downSwap);
	lineFinder = GetLineFinder(settings.getOrientation());

}
//--------------------------------------------------------------
void PixelSortingThread::setLines(const ofPixels & in, int threadNum) {
	lineFinder = GetLineFinder(settings.getOrientation());
	lineFinder->findLines(in, threadNum);
}
//--------------------------------------------------------------
void PixelSortingThread::readOutPixels(ofPixels & out) {

	for (int i = 0; i < orig_coords.size(); i++) {
		for (int j = 0; j < orig_coords[i].size(); j++) {

			out.setColor(	std::get<0>(orig_coords[i][j]),
							std::get<1>(orig_coords[i][j]), 
							out_lines[i][j]);
		}
	}
}
//--------------------------------------------------------------
unique_ptr<LineFinder> PixelSortingThread::GetLineFinder(ORIENTATION_TYPE mode) {

	switch(mode) {
	case ORIENTATION_TYPE::HORIZONTAL:
		return make_unique<LineFinderHorizontal>(LineFinderHorizontal(orig_coords, orig_lines));
		break;
	case ORIENTATION_TYPE::VERTICAL:
		return make_unique<LineFinderVertical>(LineFinderVertical(orig_coords, orig_lines));
	default:
		return make_unique<LineFinderHorizontal>(LineFinderHorizontal(orig_coords, orig_lines));
	};
	

}
//--------------------------------------------------------------
void PixelSortingThread::threadedFunction()
{
	out_lines = vector<vector<ofColor>>(orig_lines);
	sortLines();
}

//--------------------------------------------------------------
void PixelSortingThread::sortLines() {
	uint64_t srtTime = ofGetSystemTimeMicros();

	for (auto & line : out_lines) {
		uint64_t lineTime = ofGetSystemTimeMicros();
		sortLine(line);

		lineExecutionTimes.push_back(ofGetSystemTimeMicros() - lineTime);
	}

	executionTime = ofGetSystemTimeMicros() - srtTime;
}
//--------------------------------------------------------------
void PixelSortingThread::sortLine(vector<ofColor> & line) {

	sorting = false;
	endOfLine = false;

	vector<ofColor> subLine;

	unsigned int srt;
	unsigned int end;
	unsigned int inc;
	unsigned int stp;
	unsigned int lineLength = line.size();;

	if (settings.getDirection() == DIRECTION_TYPE::POSITIVE) {
		srt = 0;
		end = lineLength;
		stp = end - 1;
		inc = 1;
	}
	else {
		srt = lineLength - 1;
		end = -1;
		stp = end + 1;
		inc = -1;
	}


	for (int i = srt; i != end; i += inc) {
		endOfLine |= (i == stp);

		// If already Sorting
		if (sorting) {
			// If force stop
			if (endOfLine || subLine.size() == settings.maxSeq) {
				sorting = false;

				if (subLine.size() > 1) {
					sortSubLine(subLine, line, i);
				}
			}
			else if (subLine.size() >= settings.minSeq) {
				if (sortFunctions.stopCondition->operator()(line[i], settings.downThresh)) {
					sorting = false;

					if (subLine.size() > 1) {
						sortSubLine(subLine, line, i);
					}
					
				}
				else {
					subLine.push_back(line[i]);
				}
			}
			else {
				subLine.push_back(line[i]);
			}
		}
		// If not already Sorting
		else {
			if (sortFunctions.startCondition->operator()(line[i], settings.upThresh)) {
				sorting = true;
				subLine.push_back(line[i]);
			}
		}
	}
};

void PixelSortingThread::sortSubLine(vector<ofColor> & subLine, vector<ofColor> & line, int & i) {
	std::sort(subLine.begin(), subLine.end(), std::ref(*sortFunctions.sortFunction));


	if (settings.getDirection() == DIRECTION_TYPE::POSITIVE) {
		std::copy(subLine.begin(), subLine.end(), line.begin() + i - subLine.size());
	}
	else {
		std::reverse(subLine.begin(), subLine.end());
		std::copy(subLine.begin(), subLine.end(), line.begin() + i);
	}

	subLine.clear();
}

//--------------------------------------------------------------
// Comparision types
//--------------------------------------------------------------

unique_ptr<Comparator> PixelSortingThread::GetSortFunction() {
	bool swap = settings.getSortDir() == SORT_DIR::POSITIVE;
	return GetComparitor(settings.getSortMode(), swap);
}

unique_ptr<Comparator> PixelSortingThread::GetTestCondition(bool start, bool swap) {

	COMPARATOR mode;
	if (start) {
		mode = static_cast<COMPARATOR>(settings.getStartMode());
	}
	else {
		mode = static_cast<COMPARATOR>(settings.getStopMode());
	}

	return GetComparitor(mode, swap);
}

unique_ptr<Comparator> PixelSortingThread::GetComparitor(COMPARATOR mode, bool swap) {
	switch (mode) {
	case COMPARATOR::BRIGHTNESS:
		return make_unique<CompareBrightness>(CompareBrightness(swap));
	case COMPARATOR::LIGHTNESS:
		return  make_unique<CompareLightness>(CompareLightness(swap));
	case COMPARATOR::SATURATION:
		return  make_unique<CompareSaturation>(CompareSaturation(swap));
	case COMPARATOR::HUE:
		return  make_unique<CompareHue>(CompareHue(swap));
	case COMPARATOR::REDNESS:
		return  make_unique<CompareRedness>(CompareRedness(swap));
	case COMPARATOR::BLUENESS:
		return  make_unique<CompareBlueness>(CompareBlueness(swap));
	case COMPARATOR::GREENESS:
		return  make_unique<CompareGreeness>(CompareGreeness(swap));
	case COMPARATOR::RANDOM:
		return  make_unique<CompareRandom>(CompareRandom(swap));
	case COMPARATOR::NONE:
	default:
		return make_unique<CompareNone>(CompareNone(swap));
	}
}