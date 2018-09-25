#pragma once


struct PixelSorterSettings {

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

	ORIENTATION_TYPE orientation;
	DIRECTION_TYPE direction;
	SORT_DIR sortDir;
	COMPARATOR sortMode;
	COMPARATOR startMode;
	COMPARATOR stopMode;

	bool upSwap;
	bool downSwap;

	float upThresh;
	float downThresh;

	unsigned int maxSeq;
	unsigned int minSeq;

	PixelSorterSettings() {

		// Set defaults
		orientation = ORIENTATION_TYPE::VERTICAL;
		direction   = DIRECTION_TYPE::POSITIVE;
		sortDir     = SORT_DIR::POSITIVE;
		sortMode    = COMPARATOR::BRIGHTNESS;
		startMode   = COMPARATOR::BRIGHTNESS;;
		stopMode    = COMPARATOR::BRIGHTNESS;;

		upSwap   = false;
		downSwap = false;

		upThresh   = 0.5;
		downThresh = 0.5;

		maxSeq = 5120;
		minSeq = 0;
	}
};