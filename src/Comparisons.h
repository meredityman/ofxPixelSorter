#pragma once
#include "ofMain.h"

namespace PixelComparisons {

	enum class ORIENTATION_TYPE {
		HORIZONTAL,
		VERTICAL
	};

	enum class DIRECTION_TYPE {
		POSITIVE,
		NEGATIVE
	};

	enum class SORT_DIR {
		POSITIVE,
		NEGATIVE
	};

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


	class Comparator {
	protected:
		bool _swap;
	public:
		Comparator(bool swap) : _swap(swap) {}

		virtual bool operator()(ofColor a, ofColor b) const = 0;
		virtual bool operator()(ofColor a, float b) const   = 0;
	};

	class CompareBrightness : public Comparator {
	public:
		CompareBrightness(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getBrightness() > b.getBrightness();
			}
			else {
				return a.getBrightness() < b.getBrightness();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getBrightness() >= b * 255;
			}
			else {
				return a.getBrightness() <= b * 255;
			}
		}
	};

	class CompareLightness : public Comparator {
	public:
		CompareLightness(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getLightness() > b.getLightness();
			}
			else {
				return a.getLightness() < b.getLightness();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getLightness() >= b * 255;
			}
			else {
				return a.getLightness() <= b * 255;
			}
		}
	};

	class CompareSaturation : public Comparator {
	public:
		CompareSaturation(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getSaturation() > b.getSaturation();
			}
			else {
				return a.getSaturation() < b.getSaturation();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getSaturation() >= b * 255;
			}
			else {
				return a.getSaturation() <= b * 255;
			}
		}
	};

	class CompareHue : public Comparator {
	public:
		CompareHue(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.getHue() > b.getHue();
			}
			else {
				return a.getHue() < b.getHue();
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.getHue() >= b * 255;
			}
			else {
				return a.getHue() <= b * 255;
			}
		}
	};
	class CompareRedness : public Comparator {
	public:
		CompareRedness(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.r > b.r;
			}
			else {
				return a.r < b.r;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.r >= b * 255;
			}
			else {
				return a.r <= b * 255;
			}
		}
	};
	class CompareGreeness : public Comparator {
	public:
		CompareGreeness(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.g > b.g;
			}
			else {
				return a.g < b.g;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.g >= b * 255;
			}
			else {
				return a.g <= b * 255;
			}
		}
	};
	class CompareBlueness : public Comparator {
	public:
		CompareBlueness(bool swap) : Comparator(swap) {}

		bool operator()(ofColor a, ofColor b)  const {
			if (_swap) {
				return a.b > b.b;
			}
			else {
				return a.b < b.b;
			}
		}

		bool operator()(ofColor a, float b)  const {
			if (_swap) {
				return a.b >= b * 255;
			}
			else {
				return a.getBrightness() <= b * 255;
			}
		}
	};

	class CompareNone : public Comparator {
	public:
		CompareNone(bool swap) : Comparator(swap) {}

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

		bool operator()(ofColor a, ofColor b)  const {
			return _swap;
		}

		bool operator()(ofColor a, float b)  const {
				if (_swap) {
					return ofRandomuf() > b;
				}
				else {
					return ofRandomuf() < b;
				}
		}
	};
}