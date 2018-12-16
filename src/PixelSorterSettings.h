#pragma once
#include "ofMain.h"


enum class ORIENTATION_TYPE {
	HORIZONTAL,
	VERTICAL,
	DIAGONAL,
	ANTIDIAGONAL

};
const vector<string> orientationNames = { "horizontal", "vertical", "diagonal", "anti-diagonal" };

enum class DIRECTION_TYPE {
	POSITIVE,
	NEGATIVE
};
const  vector<string> directionNames = { "positive", "negative" };

enum class SORT_DIR {
	POSITIVE,
	NEGATIVE
};
const vector<string> sortDirNames = { "positive", "negative" };

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
const vector<string> comparitorNames = { 
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

		ofLogNotice() << "Here";

		orientation.set("Orientation", (int)ORIENTATION_TYPE::DIAGONAL, (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::ANTIDIAGONAL);
		direction.set("Direction",     (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::POSITIVE, (int)DIRECTION_TYPE::NEGATIVE);
		sortDir.set("Sort Direction",  (int)SORT_DIR::POSITIVE, (int)SORT_DIR::POSITIVE, (int)SORT_DIR::NEGATIVE);
		sortMode.set("Sort Modes",  (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);
		startMode.set("Start Mode", (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);
		stopMode.set("Stop Mode",   (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::BRIGHTNESS, (int)COMPARATOR::NONE);

		upSwap.set("Up Swap", false);
		downSwap.set("Down Swap", false);

		upThresh.set("Up Thresh", 0.5, 0.0, 1.0);
		downThresh.set("Down Thesh", 0.5, 0.0, 1.0);

		maxSeq.set("Max Length", 5120, 0, 5120);
		minSeq.set("Min Length", 0, 0, 5120);

		AddUpdateListeners();
		AddThreadSetupListeners();
	}


	string toString() {
		ostringstream stream;
		stream << "\n";
		stream << "Orientation: "    << orientationNames[(int)orientation] << "\n";
		stream << "Direction: "      << directionNames[(int)direction] << "\n";
		stream << "Sort Direction: " << sortDirNames[(int)sortDir] << "\n";
		stream << "Sort Mode: "     << comparitorNames[(int)sortMode] << "\n";
		stream << "Start Mode: "     << comparitorNames[(int)startMode] << "\n";
		stream << "Stop Mode: "     << comparitorNames[(int)stopMode] << "\n";

		stream << "Up Swap: "   << ofToString(upSwap) << "\n";
		stream << "Down Swap: " << ofToString(downSwap) << "\n";

		stream << "Up thresh: " << ofToString(upThresh) << "\n";
		stream << "Down Thresh: " << ofToString(downThresh) << "\n";

		stream << "Max Length: " << ofToString(maxSeq) << "\n";
		stream << "Min Length: " << ofToString(minSeq) << "\n";

		return stream.str();
	}

	ORIENTATION_TYPE getOrientation() const {
		return (ORIENTATION_TYPE)orientation.get();
	}

	DIRECTION_TYPE getDirection() const {
		return (DIRECTION_TYPE)direction.get();
	}

	SORT_DIR getSortDir()  const {
		return (SORT_DIR)sortDir.get();
	}

	COMPARATOR getSortMode()  const {
		return (COMPARATOR)sortMode.get();
	}

	COMPARATOR getStartMode()  const {
		return (COMPARATOR)startMode.get();
	}

	COMPARATOR getStopMode()  const {
		return (COMPARATOR)stopMode.get();
	}

	unsigned int getMaxSeq() const {
		return maxSeq;
	}
	unsigned int getMinSeq()  const {
		return minSeq;
	}

	bool getUpSwap()  const {
		return upSwap;
	}	
	
	bool getDownSwap()  const {
		return downSwap;
	}

	float getUpThresh() const {
		return upThresh;
	}

	bool getDownThresh()  const {
		return downThresh;
	}

	void setOrientation(const ORIENTATION_TYPE orientation) {
		setIfChanged(this->orientation, orientation);
	};
	void setDirection(const DIRECTION_TYPE direction) {
		setIfChanged(this->direction, (int)direction);
	};
	void setSortDir(const SORT_DIR sortDir) {
		setIfChanged(this->sortDir, (int)sortDir);
	};
	void setSortMode(const COMPARATOR sortMode) {
		setIfChanged(this->sortMode, (int)sortMode);
	};
	void setStartMode(const COMPARATOR startMode) {
		setIfChanged(this->startMode, (int)startMode);
	};
	void setStopMode(const COMPARATOR stopMode) {
		setIfChanged(this->stopMode, (int)stopMode);
	};
	void setUpSwap(const bool upSwap) {
		setIfChanged(this->upSwap,  upSwap);
	};
	void setDownSwap(const bool downSwap) {
		setIfChanged(this->downSwap,  downSwap);
	};


	void setUpThresh(const float upThresh) {
		setIfChanged(this->upThresh,  upThresh);
	};
	void setDownThresh(const float downThresh) {
		setIfChanged(this->downThresh,  downThresh);
	};
	void incUpThresh(float inc) {
		this->upThresh += inc;
	};
	void incDownThresh(float inc) {
		this->downThresh += inc;
	};


	void setMaxSeq(const unsigned int maxSeq) {
		setIfChanged(this->maxSeq,  maxSeq);
	};
	void setMinSeq(const unsigned int minSeq) {
		setIfChanged(this->minSeq, minSeq);	
	};

	template<	class ParameterType, typename NewValueType>
	typename std::enable_if_t<std::is_enum<NewValueType>::value> setIfChanged(ParameterType parameter, const NewValueType newValue) {
		if (	parameter != (int)newValue &&
				(int)newValue >= parameter.getMin() &&
				(int)newValue <= parameter.getMax()			
			) parameter = (int)newValue;
	}

	template<	class ParameterType, typename NewValueType>
	typename std::enable_if_t<!std::is_enum<NewValueType>::value> setIfChanged(ParameterType parameter, const NewValueType newValue) {
		if (	parameter != newValue &&
				newValue >= parameter.getMin() &&
				newValue <= parameter.getMax()
			) parameter = newValue;
	}

	ofEvent<bool> onUpdateRequired;
	ofEvent<bool> onThreadSetupRequired;
	
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

	ofParameter<int> maxSeq;
	ofParameter<int> minSeq;

private:

	ofEventListeners _onUpdateRequired;
	ofEventListeners _onThreadSetupRequired;

	void updateRequired() {
		bool update = true;
		ofLogNotice() << "Update required";
		ofNotifyEvent(onUpdateRequired, update, this);
	}

	void threadSetupRequired() {
		bool update = true;
		ofNotifyEvent(onThreadSetupRequired, update, this);
	}


	void AddUpdateListeners() {
		_onUpdateRequired.push(orientation.newListener([&](int&) { updateRequired(); }));

		_onUpdateRequired.push(direction.newListener([&](int&) {updateRequired(); }));
		_onUpdateRequired.push(sortDir.newListener([&](int&) {updateRequired(); }));
		_onUpdateRequired.push(sortMode.newListener([&](int&) {updateRequired(); }));
		_onUpdateRequired.push(startMode.newListener([&](int&) {updateRequired(); }));
		_onUpdateRequired.push(stopMode.newListener([&](int&) {updateRequired(); }));

		_onUpdateRequired.push(upSwap.newListener([&](bool&) {updateRequired(); }));
		_onUpdateRequired.push(downSwap.newListener([&](bool&) {updateRequired(); }));

		_onUpdateRequired.push(upThresh.newListener([&](float&) {updateRequired(); }));
		_onUpdateRequired.push(downThresh.newListener([&](float&) {updateRequired(); }));

		_onUpdateRequired.push(maxSeq.newListener([&](int&) {updateRequired(); }));
		_onUpdateRequired.push(minSeq.newListener([&](int&) {updateRequired(); }));
	}

	void AddThreadSetupListeners() {
		_onThreadSetupRequired.push(orientation.newListener([&](int&) {threadSetupRequired(); }));
	}

};