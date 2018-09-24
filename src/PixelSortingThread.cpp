#include "PixelSortingThread.h"


void PixelSortingThread::setLines(int _srtLine, int _endLine, const ofPixels & out) {
	lineLength = out.getWidth();

	srtLine = _srtLine;
	endLine = _endLine;

	for (int y = srtLine; y < endLine; y++) {
		vector<ofColor> line;
		for (size_t x = 0; x < out.getWidth(); x++) {
			line.push_back(out.getColor(x, y));
		}
		orig_lines.push_back(line);
	}
}

void PixelSortingThread::setParams(ofParameterGroup &params) {
	orientation = static_cast<ORIENTATION_TYPE>(params.getInt("Orientation").get());
	direction   = static_cast<DIRECTION_TYPE>(params.getInt("Direction").get());
	sortDir     = static_cast<SORT_DIR>(params.getInt("Sort direction").get());
	sortMode    = static_cast<COMPARATOR>(params.getInt("Sort mode").get());
	startMode   = static_cast<COMPARATOR>(params.getInt("Start mode").get());
	stopMode    = static_cast<COMPARATOR>(params.getInt("Stop mode").get());

	upSwap   = params.getBool("Up swap").get();
	downSwap = params.getBool("Down swap").get();

	upThresh   = params.getFloat("Up threshold").get();
	downThresh = params.getFloat("Down threshold").get();

	maxSeq = params.getInt("Max sequence length").get();
	minSeq = params.getInt("Min sequence length").get();


	if (direction == DIRECTION_TYPE::POSITIVE) {
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

	sortFunctions.sortFunction   = GetSortFunction();
	sortFunctions.startCondition = GetTestCondition(true, upSwap);
	sortFunctions.stopCondition  = GetTestCondition(false, downSwap);

}

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

		lineTimes.push_back(ofGetSystemTimeMicros() - lineTime);
	}

	executionTime = ofGetSystemTimeMicros() - srtTime;
}
//--------------------------------------------------------------
void PixelSortingThread::sortLine(vector<ofColor> & line) {

	sorting = false;
	endOfLine = false;

	vector<ofColor> subLine;
	for (int i = srt; i != end; i += inc) {
		endOfLine |= (i == stp);

		// If already Sorting
		if (sorting) {
			// If force stop
			if (endOfLine || subLine.size() == maxSeq) {
				sorting = false;

				if (subLine.size() > 1) {
					sortSubLine(subLine, line, i);
				}
			}
			else if (subLine.size() >= minSeq) {
				if (sortFunctions.stopCondition->operator()(line[i], downThresh)) {
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
			if (sortFunctions.startCondition->operator()(line[i], upThresh)) {
				sorting = true;
				subLine.push_back(line[i]);
			}
		}
	}
};

void PixelSortingThread::sortSubLine(vector<ofColor> & subLine, vector<ofColor> & line, int & i) {
	std::sort(subLine.begin(), subLine.end(), std::ref(*sortFunctions.sortFunction));


	if (direction == DIRECTION_TYPE::POSITIVE) {
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
	bool swap = sortDir == SORT_DIR::POSITIVE;
	return GetComparitor(sortMode, swap);
}

unique_ptr<Comparator> PixelSortingThread::GetTestCondition(bool start, bool swap) {

	COMPARATOR mode;
	if (start) {
		mode = static_cast<COMPARATOR>(startMode);
	}
	else {
		mode = static_cast<COMPARATOR>(stopMode);
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