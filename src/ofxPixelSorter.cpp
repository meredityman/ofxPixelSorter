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
void PixelSorter::setup(const ofPixels in)
{
	setImage(in);

	params = ofParameterGroup("Pixel sorting params");

	// Parameters
	params.add(orientation.set("Orientation", (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::VERTICAL));
	params.add(direction.set("Direction", (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::NEGATIVE));
	params.add(sortDir.set("Sort direction", (int)SORT_DIR::POSITIVE, (int)SORT_DIR::POSITIVE, (int)SORT_DIR::NEGATIVE));
	params.add(sortMode.set("Sort mode", (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::NONE));
	params.add(startMode.set("Start mode", (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::NONE));
	params.add(stopMode.set("Stop mode", (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::BRIGHTNESS, (int)COMPARITOR::NONE));

	params.add(upSwap.set("Up swap", true));
	params.add(downSwap.set("Down swap", false));

	params.add(upThresh.set("Up threshold", 0.5, 0, 1.0));
	params.add(downThresh.set("Down threshold", 0.5, 0, 1.0));

	params.add(maxSeq.set("Max sequence length", 200, 0, maxLineLength));
	params.add(minSeq.set("Min sequence length", 20, 0, maxLineLength));

	params.parameterChangedE();

	ofAddListener(params.parameterChangedE(), this, &PixelSorter::parameterChanged);

	update();
}

//--------------------------------------------------------------
void PixelSorter::setImage(const ofPixels in)
{
	this->in = in;
	out.allocate(in.getWidth(), in.getHeight(), in.getImageType());
}

//--------------------------------------------------------------
void PixelSorter::update()
{
	pixelSort();
	frameIsNew = true;
}

//--------------------------------------------------------------
void PixelSorter::pixelSort()
{
	vector<ofColor> line;

	sortFunction   = GetSortFunction();
	startCondition = GetTestCondition(true, upSwap);
	stopCondition  = GetTestCondition(false, downSwap);


	switch (static_cast<ORIENTATION_TYPE>(orientation.get())) {
		case ORIENTATION_TYPE::VERTICAL:
			for (unsigned int x = 0; x<in.getWidth(); x++) {

				for (unsigned int y = 0; y<in.getHeight(); y++) {
					line.push_back(in.getColor(x, y));
				}

				sortLine(line);

				for (unsigned int y = 0; y<in.getHeight(); y++) {
					out.setColor(x, y, line[y]);
				}
				line.clear();
			}
			break;
		case ORIENTATION_TYPE::HORIZONTAL:
			for (unsigned int y = 0; y<in.getHeight(); y++) {

				for (unsigned int x = 0; x < in.getWidth(); x++) {
					line.push_back(in.getColor(x, y));
				}

				sortLine(line);

				for (unsigned int x = 0; x < in.getWidth(); x++) {
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

	if (static_cast<DIRECTION_TYPE>(direction.get()) == DIRECTION_TYPE::POSITIVE) {
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
			//sorting = testStartCondition(line[i], startCondition);
			sorting = startCondition->operator()(line[i], upThresh);
		}
		else {
			if (seqSmallerThanMax(&subLine) && seqLargerThanMin(&subLine) && !endOfLine) {
				sorting = stopCondition->operator()(line[i], downThresh);
			}
		}

		if (sorting) {
			subLine.push_back(line[i]);
		} else {
			//ofSort(subLine, CompareBrightness(true));
			ofSort(subLine, std::ref(*sortFunction));

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
ofPixels& PixelSorter::getPixels() { 
	frameIsNew = false;
	return out; 
}
//--------------------------------------------------------------


//--------------------------------------------------------------
// Comparision types
//--------------------------------------------------------------

unique_ptr<Comparator> PixelSorter::GetSortFunction() {
	bool swap = static_cast<SORT_DIR>(sortDir.get()) == SORT_DIR::POSITIVE;
	return GetComparitor(static_cast<COMPARITOR>(sortMode.get()), swap);
}

unique_ptr<Comparator> PixelSorter::GetTestCondition(bool start, bool swap) {

	COMPARITOR mode;
	if (start) {
		mode = static_cast<COMPARITOR>(startMode.get());
	}
	else {
		mode = static_cast<COMPARITOR>(stopMode.get());
	}

	return GetComparitor(mode, swap);
}

bool PixelSorter::seqSmallerThanMax(const vector<ofColor> * subLine) {
	if (maxSeq == 0) return true;
	else return subLine->size() < maxSeq;
}
bool PixelSorter::seqLargerThanMin(const vector<ofColor> * subLine) {
	if (minSeq == 0) return true;
	else return subLine->size() > minSeq;
}


unique_ptr<Comparator> PixelSorter::GetComparitor(COMPARITOR mode, bool swap) {
	switch (mode) {
		case COMPARITOR::BRIGHTNESS:
			return make_unique<CompareBrightness>(CompareBrightness(swap));
		case COMPARITOR::LIGHTNESS:
			return  make_unique<CompareLightness>(CompareLightness(swap));
		case COMPARITOR::SATURATION:
			return  make_unique<CompareSaturation>(CompareSaturation(swap));
		case COMPARITOR::HUE:
			return  make_unique<CompareHue>(CompareHue(swap));
		case COMPARITOR::REDNESS:
			return  make_unique<CompareRedness>(CompareRedness(swap));
		case COMPARITOR::BLUENESS:
			return  make_unique<CompareBlueness>(CompareBlueness(swap));
		case COMPARITOR::GREENESS:
			return  make_unique<CompareGreeness>(CompareGreeness(swap));
		case COMPARITOR::RANDOM:
			return  make_unique<CompareRandom>(CompareRandom(swap));
		case COMPARITOR::NONE:
		default:
			return make_unique<CompareNone>(CompareNone(swap));
	}
}
