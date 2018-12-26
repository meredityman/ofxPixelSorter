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

		orientation.set( "Orientation",    (int)ORIENTATION_TYPE::DIAGONAL, (int)ORIENTATION_TYPE::HORIZONTAL, (int)ORIENTATION_TYPE::ANTIDIAGONAL);
		direction.set  ( "Direction",      (int)DIRECTION_TYPE::POSITIVE,   (int)DIRECTION_TYPE::POSITIVE,     (int)DIRECTION_TYPE::NEGATIVE);
		sortDir.set    ( "Sort Direction", (int)SORT_DIR::POSITIVE,         (int)SORT_DIR::POSITIVE,           (int)SORT_DIR::NEGATIVE);
		sortMode.set   ( "Sort Modes",     (int)COMPARATOR::BRIGHTNESS,     (int)COMPARATOR::BRIGHTNESS,       (int)COMPARATOR::NONE);
		startMode.set  ( "Start Mode",     (int)COMPARATOR::BRIGHTNESS,     (int)COMPARATOR::BRIGHTNESS,       (int)COMPARATOR::NONE);
		stopMode.set   ( "Stop Mode",      (int)COMPARATOR::BRIGHTNESS,     (int)COMPARATOR::BRIGHTNESS,       (int)COMPARATOR::NONE);

		startSwap.set("Start Swap" , false);
		stopSwap.set ("Stop Swap", false);

		startThresh.set("Start Thresh" , 0.5, 0.0, 1.0);
		stopThresh.set ("Stop Thesh", 0.5, 0.0, 1.0);

		maxSeq.set("Max Length", 1.0, 0.0, 1.0);
		minSeq.set("Min Length", 0.0, 0.0, 1.0);

		AddUpdateListeners();
		AddThreadSetupListeners();
	}


	string toString() {
		ostringstream stream;
		stream << "\n";
		stream << "Orientation: "    << orientationNames[(int)orientation] << "\n";
		stream << "Direction: "      << directionNames[(int)direction] << "\n";
		stream << "Sort Direction: " << sortDirNames[(int)sortDir] << "\n";
		stream << "Sort Mode: "      << comparitorNames[(int)sortMode] << "\n";
		stream << "Start Mode: "     << comparitorNames[(int)startMode] << "\n";
		stream << "Stop Mode: "      << comparitorNames[(int)stopMode] << "\n";

		stream << "Start Swap: "   << ofToString(startSwap) << "\n";
		stream << "Stop Swap: " << ofToString(stopSwap) << "\n";

		stream << "Start thresh: "   << ofToString(startThresh) << "\n";
		stream << "Stop Thresh: " << ofToString(stopThresh) << "\n";

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

	float getMaxSeq() const {
		return maxSeq;
	}
	float getMinSeq()  const {
		return minSeq;
	}

	bool getUpSwap()  const {
		return startSwap;
	}	
	
	bool getDownSwap()  const {
		return stopSwap;
	}

	float getUpThresh() const {
		return startThresh;
	}

	float getDownThresh()  const {
		return stopThresh;
	}

	bool isRandom() {
		return	( startMode == (int)COMPARATOR::RANDOM ||
				  startMode == (int)COMPARATOR::RANDOM ||
				  sortMode == (int)COMPARATOR::RANDOM     );
	}


	ofEvent<bool> onUpdateRequired;
	ofEvent<bool> onThreadSetupRequired;
	
	ofParameter<int> orientation;
	ofParameter<int> direction;
	ofParameter<int> sortDir;
	ofParameter<int> sortMode;
	ofParameter<int> startMode;
	ofParameter<int> stopMode;

	ofParameter<bool> startSwap;
	ofParameter<bool> stopSwap;

	ofParameter<float> startThresh;
	ofParameter<float> stopThresh;

	ofParameter<float> maxSeq;
	ofParameter<float> minSeq;

private:

	ofEventListeners _onUpdateRequired;
	ofEventListeners _onThreadSetupRequired;

	void updateRequired() {
		bool update = true;
		ofLogVerbose() << "Update required";
		ofNotifyEvent(onUpdateRequired, update, this);
	}

	void threadSetupRequired() {
		bool update = true;
		ofLogVerbose() << "Thread setup required";
		ofNotifyEvent(onThreadSetupRequired, update, this);
	}


	void AddUpdateListeners() {
		_onUpdateRequired.push( orientation.newListener([&](int&) { updateRequired(); }));
							    
		_onUpdateRequired.push( direction.newListener  ([&](int&) {updateRequired(); }));
		_onUpdateRequired.push( sortDir.newListener    ([&](int&) {updateRequired(); }));
		_onUpdateRequired.push( sortMode.newListener   ([&](int&) {updateRequired(); }));
		_onUpdateRequired.push( startMode.newListener  ([&](int&) {updateRequired(); }));
		_onUpdateRequired.push( stopMode.newListener   ([&](int&) {updateRequired(); }));
								 					  
		_onUpdateRequired.push( startSwap.newListener  ([&](bool&) {updateRequired(); }));
		_onUpdateRequired.push( stopSwap.newListener   ([&](bool&) {updateRequired(); }));
								 					  
		_onUpdateRequired.push( startThresh.newListener([&](float&) {updateRequired(); }));
		_onUpdateRequired.push( stopThresh.newListener ([&](float&) {updateRequired(); }));
							    
		_onUpdateRequired.push( maxSeq.newListener     ([&](float&) {updateRequired(); }));
		_onUpdateRequired.push( minSeq.newListener     ([&](float&) {updateRequired(); }));
	}

	void AddThreadSetupListeners() {
		_onThreadSetupRequired.push(orientation.newListener([&](int&) {threadSetupRequired(); }));
	}

};