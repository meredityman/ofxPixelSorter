#pragma once
#include "ofMain.h"
#include "Comparisons.h"
#include "PixelSorterSettings.h"
#include "LineFinder.h"

using namespace PixelComparisons;

class PixelSortingThread : public ofThread
{
public:
	void setSettings(PixelSorterSettings settings);
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

	unique_ptr<Comparator> GetTestCondition(bool start, bool swap);
	unique_ptr<Comparator> GetSortFunction();
	unique_ptr<Comparator> GetComparitor(PixelSorterSettings::COMPARATOR mode, bool swap);

	unique_ptr<LineFinder> GetLineFinder(PixelSorterSettings::ORIENTATION_TYPE mode);


	bool sorting = false;
	bool endOfLine = false;

	PixelSorterSettings settings;
};