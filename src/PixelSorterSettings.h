#pragma once
#include "ofMain.h"

#define USE_OFXGUI

#ifdef USE_OFXGUI
#include "ofxGui.h"
#endif

enum class ORIENTATION_TYPE {
	HORIZONTAL,
	VERTICAL
};
const string orientationNames[] = { "horizontal", "vertical" };

enum class DIRECTION_TYPE {
	POSITIVE,
	NEGATIVE
};
const string directionNames[] = { "positive", "negative" };

enum class SORT_DIR {
	POSITIVE,
	NEGATIVE
};
const string sortDirNames[] = { "positive", "negative" };

enum class  COMPARATOR {
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
const string comparitorNames[] = { 
	"brightness", 
	"lightness",
	"saturation",
	"hue",
	"redness",
	"blueness",
	"greeness",
	"random",
	"none"
};

struct PixelSorterSettings {

	PixelSorterSettings() {
		orientation.set("Orientation", (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::VERTICAL);
		direction.set("Direction",     (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::NEGATIVE);
		sortDir.set("Sort Direction",  (int)SORT_DIR::POSITIVE, (int)SORT_DIR::POSITIVE, (int)SORT_DIR::NEGATIVE);
		sortMode.set("Sort Modes",  (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);
		startMode.set("Start Mode", (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);
		stopMode.set("Stop Mode",   (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);

		upSwap.set("Up Swap", false);
		downSwap.set("Down Swap", false);

		upThresh.set("Up Thresh", false);
		downThresh.set("Down Thesh", false);

		maxSeq.set("Max Length", 5120, 0, 5120);
		minSeq.set("Min Length", 0, 0, 5120);

		orientation.addListener(this, &PixelSorterSettings::updateOrientationName);


	}
#ifdef USE_OFXGUI
	void AddParamsToPanel (ofxPanel &panel) {
		panel.add(orientation);
		panel.add(direction);
		panel.add(sortDir);
		panel.add(sortMode);
		panel.add(startMode);
		panel.add(stopMode);

		panel.add(upSwap);
		panel.add(downSwap);

		panel.add(upThresh);
		panel.add(downThresh);

		panel.add(maxSeq);
		panel.add(minSeq);
	}
#endif

	string toString() {
		ostringstream stream;

		stream << "Orientation: "    << orientationNames[(int)orientation];
		stream << "Direction: "      << directionNames[(int)direction];
		stream << "Sort Direction: " << sortDirNames[(int)sortDir];
		stream << "Sort Modes: "     << comparitorNames[(int)sortMode];
		stream << "Start Mode: "     << comparitorNames[(int)startMode];
		stream << "Stop Modes: "     << comparitorNames[(int)stopMode];

		stream << "Up Swap: "   << ofToString(upSwap);
		stream << "Down Swap: " << ofToString(downSwap);

		stream << "Up thresh: " << ofToString(upThresh);
		stream << "Down Thresh: " << ofToString(downThresh);

		stream << "Max Length: " << ofToString(maxSeq);
		stream << "Min Length: " << ofToString(minSeq);

		return stream.str();
	}

	void updateOrientationName(const void * sender, int &value) {
		((ofParameter<int>*)sender)->setName("");

	}

	ORIENTATION_TYPE getOrientation() {
		return (ORIENTATION_TYPE)orientation.get();
	}

	DIRECTION_TYPE getDirection() {
		return (DIRECTION_TYPE)direction.get();
	}

	SORT_DIR getSortDir() {
		return (SORT_DIR)sortDir.get();
	}

	COMPARATOR getSortMode() {
		return (COMPARATOR)sortMode.get();
	}

	COMPARATOR getStartMode() {
		return (COMPARATOR)startMode.get();
	}

	COMPARATOR getStopMode() {
		return (COMPARATOR)stopMode.get();
	}

	void setOrientation(const ORIENTATION_TYPE orientation) {
		this->orientation = (int) orientation;
	};
	void setDirection(const DIRECTION_TYPE direction) {
		this->direction = (int)direction;
	};
	void setSortDir(const SORT_DIR sortDir) {
		this->sortDir = (int)sortDir;
	};
	void setSortMode(const COMPARATOR sortMode) {
		this->sortMode = (int)sortMode;
	};
	void setStartMode(const COMPARATOR startMode) {
		this->startMode = (int)startMode;
	};
	void setStopMode(const COMPARATOR stopMode) {
		this->stopMode = (int)stopMode;
	};
	void setUpSwap(const bool upSwap) {
		this->upSwap = upSwap;
	};
	void setDownSwap(const bool downSwap) {
		this->downSwap = downSwap;
	};
	void setUpThresh(const float upThresh) {
		this->upThresh = upThresh;
	};
	void setDownThresh(const float downThresh) {
		this->downThresh = downThresh;
	};
	void setMaxSeq(const unsigned int maxSeq) {
		this->maxSeq = maxSeq;
	};
	void setMinSeq(const unsigned int minSeq) {
		this->minSeq = minSeq;
	};

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
};