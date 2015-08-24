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
	std::vector<std::vector<int>> numbers;

	numbers.push_back(std::vector<int>());
	numbers.push_back(std::vector<int>({ 1 }));
	numbers.push_back(std::vector<int>({ 2, 1 }));
	numbers.push_back(std::vector<int>({ 2, 1, 2 }));
	numbers.push_back(std::vector<int>({ 3, 6, 2, 1, 8, 10, 9, 4, 7, 5, 3, 6, 2, 1, 8, 10, 9, 4, 7, 5 }));
	numbers.push_back(std::vector<int>({ 12, 13, 3, 19, 7, 20, 2, 18, 1, 17, 16, 9, 15, 10, 14, 8, 4, 11, 6, 5 }));

	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		if (!this->run_single(*it)) {
			return false;
		}
	}

	return true;
}
