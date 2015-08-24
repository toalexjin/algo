/**
 * Test case for sort algorithm.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_sort.h"
#include "algo/sort.h"
#include <string>
#include <vector>


namespace {

test_sort_t st_test_sort;

} // unnamed namespace.


bool test_sort_t::run() {
	const std::vector<int> raw1;
	if (!this->run_single(raw1)) {
		return false;
	}

	const std::vector<int> raw2 = { 12, 13, 3, 19, 7, 20, 2, 18, 1, 17, 16, 9, 15, 10, 14, 8, 4, 11, 6, 5 };
	if (!this->run_single(raw2)) {
		return false;
	}

	return true;
}
