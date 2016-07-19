#include "parameters.h"
#include <iterator>
#include <algorithm>

Parameters toBccParameters(const Parameters parameters) {
	Parameters result;
	std::copy(std::begin(parameters), std::end(parameters), std::back_inserter(result));
	return result;
}
