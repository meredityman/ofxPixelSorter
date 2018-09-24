#pragma once
#include "ofMain.h"
#include "Comparisons.h"
#include "PixelSorterSettings.h"

using namespace PixelComparisons;

class PixelSortingThread : public ofThread
{
public:

	void setLines(int _srtLine, int _endLine, const ofPixels & out);
	void setSettings(PixelSorterSettings settings);

	void threadedFunction();

	ofColor getColor(int x, int y) const {
		return out_lines[y - srtLine][x];
	}

	float timePerLines() {
		return 1.0 * std::accumulate(lineTimes.begin(), lineTimes.end(), 0LL) / lineTimes.size();
	}

	int srtLine;
	int endLine;

	uint64_t executionTime;

	vector<uint64_t> lineTimes;

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
	unique_ptr<Comparator> GetComparitor(PixelSorterSettings::COMPARATOR mode, bool swap);

	unsigned int srt;
	unsigned int end;
	unsigned int inc;
	unsigned int stp;
	unsigned int lineLength;

	bool sorting = false;
	bool endOfLine = false;

	PixelSorterSettings settings;
};