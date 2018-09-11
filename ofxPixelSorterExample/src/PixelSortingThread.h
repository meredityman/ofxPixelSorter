#pragma once
#include "ofMain.h"
#include "Comparisons.h"

using namespace PixelComparisons;

class PixelSortingThread : public ofThread
{
public:

	void setLines(int _srtLine, int _endLine, const ofPixels & out);
	void setParams(ofParameterGroup &params);

	void threadedFunction();

	ofColor getColor(int x, int y) const {
		return out_lines[y - srtLine][x];
	}

	int srtLine;
	int endLine;

	uint64_t executionTime;

	vector<uint64_t> lineTimes;

	float timePerLines() {
		return 1.0 * std::accumulate(lineTimes.begin(), lineTimes.end(), 0LL) / lineTimes.size();
	}

private:
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

	unique_ptr<Comparator> GetTestCondition(bool start, bool swap);
	unique_ptr<Comparator> GetSortFunction();
	unique_ptr<Comparator> GetComparitor(COMPARATOR mode, bool swap);

	int srt;
	int end;
	int inc;
	int stp;
	int lineLength;

	bool sorting = false;
	bool endOfLine = false;

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

	int maxSeq;
	int minSeq;

};