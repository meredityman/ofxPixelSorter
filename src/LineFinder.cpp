#include "LineFinder.h"

size_t LineFinder::getSeqLength(float seq){
	return floor(seq * maxLength );
}
