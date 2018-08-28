#pragma once
#include "ofMain.h"

namespace PixelComparisons {


	bool CompareBrightness(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.getBrightness() > b.getBrightness();
		}
		else {
			return a.getBrightness() < b.getBrightness();
		}
	}
	bool CompareBrightness(ofColor a, float b, bool swap) {
		if (swap) {
			return a.getBrightness() >= b * 255;
		}
		else {
			return a.getBrightness() <= b * 255;
		}
	}

	//--------------------------------------------------------------

	bool CompareLightness(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.getLightness() > b.getLightness();
		}
		else {
			return a.getLightness() < b.getLightness();
		}
	}

	bool CompareLightness(ofColor a, float b, bool swap) {
		if (swap) {
			return a.getLightness() >= b * 255;
		}
		else {
			return a.getLightness() <= b * 255;
		}
	}

	//--------------------------------------------------------------


	bool CompareSaturation(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.getSaturation() > b.getSaturation();
		}
		else {
			return a.getSaturation() < b.getSaturation();
		}
	}

	bool CompareSaturation(ofColor a, float b, bool swap) {
		if (swap) {
			return a.getSaturation() >= b * 255;
		}
		else {
			return a.getSaturation() <= b * 255;
		}
	}

	//--------------------------------------------------------------


	bool CompareHue(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.getHue() > b.getHue();
		}
		else {
			return a.getHue() < b.getHue();
		}
	}

	bool CompareHue(ofColor a, float b, bool swap) {
		if (swap) {
			return a.getHue() >= b * 255;
		}
		else {
			return a.getHue() <= b * 255;
		}
	}

	//--------------------------------------------------------------

	bool CompareRedness(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.r > b.r;
		}
		else {
			return a.r < b.r;
		}
	}

	bool CompareRedness(ofColor a, float b, bool swap) {
		if (swap) {
			return a.r >= b;
		}
		else {
			return a.r <= b;
		}
	}

	//--------------------------------------------------------------

	bool CompareGreeness(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.g > b.g;
		}
		else {
			return a.g < b.g;
		}
	}

	bool CompareGreeness(ofColor a, float b, bool swap) {
		if (swap) {
			return a.r >= b;
		}
		else {
			return a.r <= b;
		}
	}
	//--------------------------------------------------------------

	bool CompareBlueness(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.b > b.b;
		}
		else {
			return a.b < b.b;
		}
	}

	bool CompareBlueness(ofColor a, float b, bool swap) {
		if (swap) {
			return a.b >= b;
		}
		else {
			return a.b <= b;
		}
	}

	//--------------------------------------------------------------

	bool CompareRandom(ofColor a, ofColor b, bool swap) {
		if (swap) {
			return a.b > b.b; // BROKEN!!!!
		}
		else {
			return a.b < b.b;
		}
	}

	bool CompareRandom(ofColor a, float b, bool swap) {
		if (swap) {
			return ofRandomuf() > b;
		}
		else {
			return ofRandomuf() < b;
		}

	}

	//--------------------------------------------------------------
	bool CompareNone(ofColor a, float b, bool swap) {
		return swap;
	}
}