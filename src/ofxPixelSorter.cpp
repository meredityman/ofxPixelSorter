#include "ofxPixelSorter.h"
#include "PixelSortingThread.h"

//--------------------------------------------------------------
PixelSorter::PixelSorter()
{
}


//--------------------------------------------------------------
PixelSorter::~PixelSorter()
{
}

//--------------------------------------------------------------
void PixelSorter::setup(const ofPixels & in)
{
	setupParams();
	setImage(in);
}
//--------------------------------------------------------------
void PixelSorter::setupParams() {
	// Parameters
	params = ofParameterGroup("Pixel sorting params");

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

	params.add(maxSeq.set("Max sequence length", 400, 0, maxLineLength));
	params.add(minSeq.set("Min sequence length", 0, 0, maxLineLength));

	ofAddListener(params.parameterChangedE(), this, &PixelSorter::parameterChanged);
}


//--------------------------------------------------------------
void PixelSorter::setImage(const ofPixels & in)
{
	this->in = in;
	out.allocate(in.getWidth(), in.getHeight(), in.getImageType());
	update();
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
	uint64_t srtTime = ofGetSystemTimeMillis();

	int nCores = std::thread::hardware_concurrency();

	if (static_cast<ORIENTATION_TYPE>(orientation.get()) == ORIENTATION_TYPE::VERTICAL) {
		in.rotate90To(out, 1);
	}
	else {
		out = in;
	}


	vector<unique_ptr<PixelSortingThread>> threads;
	int nLines = std::floor(out.getHeight() / nCores);
	int remLines = out.getHeight() % nCores;


	for (int i = 0; i < nCores; i++) {

		int srtLine  = i * nLines;
		int endLine  = srtLine +  nLines;

		if (i == nCores - 1) {
			endLine += remLines;
		}

		unique_ptr<PixelSortingThread> newThread = make_unique<PixelSortingThread>();
		newThread->setLines(srtLine, endLine, out);
		newThread->setParams(params);

		threads.push_back(std::move(newThread));
		threads.back()->startThread();		
	}

	uint64_t getLinesTime = ofGetSystemTimeMillis();

	// Wait for threads to finish

	for (auto &t : threads) {
		t->waitForThread(false, -1);

		ofLogNotice() << "Exec time " << t->executionTime << " Time/line " << t->timePerLines();

		for (size_t y = t->srtLine; y < t->endLine; y++) {
			
			for (size_t x = 0; x < out.getWidth(); x++) {
				out.setColor(x, y, t->getColor(x, y));
			}
		}
	}

	uint64_t sortingTime = ofGetSystemTimeMillis();


	if (static_cast<ORIENTATION_TYPE>(orientation.get()) == ORIENTATION_TYPE::VERTICAL) {
		out.rotate90(3);
	}

	ofLogNotice() << "GetLines time: " << getLinesTime - srtTime << "ms";
	ofLogNotice() << "Sorting time: " << sortingTime - getLinesTime << "ms";
	ofLogNotice() << "Total Execution time: " << ofGetSystemTimeMillis() - srtTime << "ms";
}


//--------------------------------------------------------------
//
//--------------------------------------------------------------
ofPixels& PixelSorter::getPixels() { 
	frameIsNew = false;
	return out; 
}
//--------------------------------------------------------------



