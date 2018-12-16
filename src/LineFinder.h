#pragma once
#include "ofMain.h"

class LineFinder {
protected:
	vector<vector<tuple<size_t, size_t>>> * orig_coords;
	vector<vector<ofColor>> * orig_lines;

	size_t maxLength = 0;

public:
	virtual size_t getSeqLength(float seq);

	LineFinder(	vector<vector<tuple<size_t, size_t>>> & orig_coords,
				vector<vector<ofColor>> &orig_lines ) {

		this->orig_coords = &orig_coords;
		this->orig_lines  = &orig_lines;

	};

	virtual void findLines(const ofPixels & in, int threadNum) = 0;

};



class LineFinderHorizontal : public LineFinder {
public:
	LineFinderHorizontal(vector<vector<tuple<size_t, size_t>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }


	void findLines(const ofPixels & in, int threadNum) override {
		maxLength = in.getWidth();

		int nCores = std::thread::hardware_concurrency();

		int nLines = std::floor(in.getHeight() / nCores);
		int remLines = in.getHeight() % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		int lineLength = in.getWidth();

		for (size_t y = srtLine; y < endLine; y++) {
			vector<ofColor> line;
			vector<tuple<size_t, size_t>> orig_coord;
			for (size_t x = 0; x < in.getWidth(); x++) {
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
	LineFinderVertical(vector<vector<tuple<size_t, size_t>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }


	void findLines(const ofPixels & in, int threadNum) override {
		maxLength = in.getHeight();

		int nCores = std::thread::hardware_concurrency();

		int nLines = std::floor(in.getWidth() / nCores);
		int remLines = in.getWidth() % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		int lineLength = in.getWidth();

		for (size_t x = srtLine; x < endLine; x++) {
			vector<ofColor> line;
			vector<tuple<size_t, size_t>> orig_coord;
			for (size_t y = 0; y < in.getHeight(); y++) {
				orig_coord.push_back(make_tuple(x, y));
				line.push_back(in.getColor(x, y));
			}
			orig_coords->push_back(orig_coord);
			orig_lines->push_back(line);
		}
	}
};

class LineFinderAntidiagonal : public LineFinder {
public:
	LineFinderAntidiagonal(vector<vector<tuple<size_t, size_t>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }
		

	void findLines(const ofPixels & in, int threadNum) override {
		maxLength =  min(in.getWidth(), in.getHeight());

		int nCores = std::thread::hardware_concurrency();

		int totalNLines = in.getHeight() + in.getWidth() - 1;
		 
		int nLines = std::floor(totalNLines / nCores);
		int remLines = totalNLines % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		for (size_t l = srtLine; l < endLine; l++) {
			vector<ofColor> line;
			vector<tuple<size_t, size_t>> orig_coord;
			int py;
			int o = l - in.getWidth() + 1;

			for (int px = 0; px < in.getWidth(); px++) {
				py = px + o;

				if (py >= 0 && py < in.getHeight()) {
					orig_coord.push_back(make_tuple(px, py));
					line.push_back(in.getColor(px, py));
				}

			}

			orig_coords->push_back(orig_coord);
			orig_lines->push_back(line);
		}
	}
};

class LineFinderDiagonal : public LineFinder {
public:
	LineFinderDiagonal(vector<vector<tuple<size_t, size_t>>> & orig_coords,
		vector<vector<ofColor>> &orig_lines) : LineFinder(orig_coords, orig_lines) { }


	void findLines(const ofPixels & in, int threadNum) override {
		maxLength =  min(in.getWidth(), in.getHeight());

		int nCores = std::thread::hardware_concurrency();

		int totalNLines = in.getHeight() + in.getWidth() - 1;

		int nLines = std::floor(totalNLines / nCores);
		int remLines = totalNLines % nCores;

		size_t srtLine = threadNum * nLines;
		size_t endLine = srtLine + nLines;

		if (threadNum == nCores - 1) {
			endLine += remLines;
		}

		for (size_t l = srtLine; l < endLine; l++) {
			vector<ofColor> line;
			vector<tuple<size_t, size_t>> orig_coord;
			int py;
			int o = l;

			for (int px = 0; px < in.getWidth(); px++) {
				py = - px + o;

				if (py >= 0 && py < in.getHeight()) {
					orig_coord.push_back(make_tuple(px, py));
					line.push_back(in.getColor(px, py));
				}

			}

			orig_coords->push_back(orig_coord);
			orig_lines->push_back(line);
		}
	}
};
