#pragma once
#include "ofMain.h"

class LineFinder {
protected:
	vector<vector<tuple<unsigned int, unsigned int>>> * orig_coords;
	vector<vector<ofColor>> * orig_lines;

public:

	LineFinder(	vector<vector<tuple<unsigned int, unsigned int>>> & orig_coords,
				vector<vector<ofColor>> &orig_lines ) {

		this->orig_coords = &orig_coords;
		this->orig_lines  = &orig_lines;

	};

	virtual void findLines(const ofPixels & in, int threadNum) = 0;

};

class LineFinderHorizontal : public LineFinder {
public:
	LineFinderHorizontal(vector<vector<tuple<unsigned int, unsigned int>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }


	void findLines(const ofPixels & in, int threadNum) override {
		int nCores = std::thread::hardware_concurrency();

		int nLines = std::floor(in.getHeight() / nCores);
		int remLines = in.getHeight() % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		int lineLength = in.getWidth();

		for (unsigned int y = srtLine; y < endLine; y++) {
			vector<ofColor> line;
			vector<tuple<unsigned int, unsigned int>> orig_coord;
			for (unsigned int x = 0; x < in.getWidth(); x++) {
				orig_coord.push_back(make_tuple(x, y));
				line.push_back(in.getColor(x, y));
			}
			orig_coords->push_back(orig_coord);
			orig_lines->push_back(line);
		}
	}
};

class LineFinderVertical : public LineFinder {
public:
	LineFinderVertical(vector<vector<tuple<unsigned int, unsigned int>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }


	void findLines(const ofPixels & in, int threadNum) override {
		int nCores = std::thread::hardware_concurrency();

		int nLines = std::floor(in.getWidth() / nCores);
		int remLines = in.getWidth() % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		int lineLength = in.getWidth();

		for (unsigned int x = srtLine; x < endLine; x++) {
			vector<ofColor> line;
			vector<tuple<unsigned int, unsigned int>> orig_coord;
			for (unsigned int y = 0; y < in.getHeight(); y++) {
				orig_coord.push_back(make_tuple(x, y));
				line.push_back(in.getColor(x, y));
			}
			orig_coords->push_back(orig_coord);
			orig_lines->push_back(line);
		}
	}
};