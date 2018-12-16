#pragma once
#include "ofMain.h"
#include "Comparisons.h"
#include "LineFinder.h"
#include "PixelSorterSettings.h"

using namespace PixelComparisons;

class PixelSortingThread : public ofThread
{
public:
	void setSettings(const PixelSorterSettings &settings);
	void setLines(const ofPixels & in, int threadNum);
	void readOutPixels(ofPixels & out);
	void threadedFunction();

	ofColor getColor(int x, int y) const {
		return out_lines[y - srtLine][x];
	}

	float timePerLines() {
		return 1.0 * std::accumulate(lineExecutionTimes.begin(), lineExecutionTimes.end(), 0LL) / lineExecutionTimes.size();
	}

	unsigned int srtLine;
	unsigned int endLine;

	uint64_t executionTime;
	vector<uint64_t> lineExecutionTimes;

private:
	vector<vector<tuple<unsigned int, unsigned int>>> orig_coords;
	vector<vector<ofColor>> orig_lines;
	vector<vector<ofColor>> out_lines;

	void sortLines();
	void sortLine(vector<ofColor> & line);
	void sortSubLine(vector<ofColor> & subLine, vector<ofColor> & line, int & i);

	struct SortFunctions {
		unique_ptr<Comparator> sortFunction;
		unique_ptr<Comparator> startCondition;
		unique_ptr<Comparator> stopCondition;
	};
	SortFunctions sortFunctions;

	unique_ptr<LineFinder> lineFinder;

	unique_ptr<Comparator> GetTestCondition(bool swap, COMPARATOR mode);
	unique_ptr<Comparator> GetSortFunction(SORT_DIR sortDir, COMPARATOR mode);
	unique_ptr<Comparator> GetComparitor(COMPARATOR mode, bool swap);

	unique_ptr<LineFinder> GetLineFinder(ORIENTATION_TYPE mode);

	DIRECTION_TYPE direction;
	ORIENTATION_TYPE orientation;

	unsigned int maxSeq;
	unsigned int minSeq;

	float upThresh;
	float downThresh;

	bool sorting = false;
	bool endOfLine = false;

};