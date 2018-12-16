#pragma once
#include "ofMain.h"

namespace PixelComparisons {

	class Comparator {
	protected:
		bool _swap;
		virtual bool operator()(ofColor a, ofColor b) const = 0;
		virtual bool operator()(ofColor a, float b) const   = 0;

	public:
		Comparator(bool swap) : _swap(swap) {}

		virtual void sort(vector<ofColor> & subLine) {
			std::sort(subLine.begin(), subLine.end(), [this](ofColor a, ofColor b) { return operator()(a, b); });
		};

		virtual bool compare(const ofColor & col, const float thresh) {
			return operator()(col, thresh);
		}

	};

	class CompareBrightness : public Comparator {
	public:
		CompareBrightness(bool swap) : Comparator(swap) {}

	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getBrightness() < b.getBrightness();
			}
			else {
				return a.getBrightness() > b.getBrightness();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getBrightness() < b * 256;
			}
			else {
				return a.getBrightness() > b * 256;
			}
		}
	};

	class CompareLightness : public Comparator {
	public:
		CompareLightness(bool swap) : Comparator(swap) {}
	
	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getLightness() < b.getLightness();
			}
			else {
				return a.getLightness() > b.getLightness();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getLightness() < b * 256;
			}
			else {
				return a.getLightness() > b * 256;
			}
		}
	};

	class CompareSaturation : public Comparator {
	public:
		CompareSaturation(bool swap) : Comparator(swap) {}
	
	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getSaturation() < b.getSaturation();
			}
			else {
				return a.getSaturation() > b.getSaturation();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getSaturation() < b * 256;
			}
			else {
				return a.getSaturation() > b * 256;
			}
		}
	};

	class CompareHue : public Comparator {
	public:
		CompareHue(bool swap) : Comparator(swap) {}
	
	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getHue() < b.getHue();
			}
			else {
				return a.getHue() > b.getHue();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getHue() < b * 256;
			}
			else {
				return a.getHue() > b * 256;
			}
		}
	};
	class CompareRedness : public Comparator {
	public:
		CompareRedness(bool swap) : Comparator(swap) {}

	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.r < b.r;
			}
			else {
				return a.r > b.r;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.r < b * 256;
			}
			else {
				return a.r > b * 256;
			}
		}
	};
	class CompareGreeness : public Comparator {
	public:
		CompareGreeness(bool swap) : Comparator(swap) {}
	
	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.g < b.g;
			}
			else {
				return a.g > b.g;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.g < b * 256;
			}
			else {
				return a.g > b * 256;
			}
		}
	};
	class CompareBlueness : public Comparator {
	public:
		CompareBlueness(bool swap) : Comparator(swap) {}
	
	protected:
		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.b < b.b;
			}
			else {
				return a.b > b.b;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.b < b * 256;
			}
			else {
				return a.b > b * 256;
			}
		}
	};

	class CompareNone : public Comparator {
	public:
		CompareNone(bool swap) : Comparator(swap) {}	

	protected:
		bool operator()(ofColor a, ofColor b)  const {
			return _swap;
		}

		bool operator()(ofColor a, float b)  const {
			return _swap;
		}
	};


	class CompareRandom: public Comparator {
	public:
		CompareRandom(bool swap) : Comparator(swap) {}

		virtual void sort(vector<ofColor> & subLine) override {
			std::random_shuffle(subLine.begin(), subLine.end());
		}
	

	protected:

		bool operator()(ofColor a, ofColor b)  const {

			return true;
		}

		bool operator()(ofColor a, float b)  const {
				if (_swap) {
					return ofNoise(ofGetElapsedTimef() * 1000.0) < b;
				}
				else {
					return ofNoise(ofGetElapsedTimef() * 1000.0) > b;
				}
		}
	};
}