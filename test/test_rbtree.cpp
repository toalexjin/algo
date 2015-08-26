/**
 * Test case for rbtree_t.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_rbtree.h"
#include "algo/rbtree.h"
#include <string>
#include <vector>


namespace {

test_rbtree_t st_test;

} // unnamed namespace.


bool test_rbtree_t::run() {
	std::vector<std::vector<int>> numbers;

	numbers.push_back(std::vector<int>());
	numbers.push_back(std::vector<int>({ 1 }));
	numbers.push_back(std::vector<int>({ 2, 1 }));
	numbers.push_back(std::vector<int>({ 2, 1, 3 }));
	numbers.push_back(std::vector<int>({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
	numbers.push_back(std::vector<int>({ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }));
	numbers.push_back(std::vector<int>({ 3, 6, 2, 1, 8, 10, 9, 4, 7, 5, 3, 6, 2, 1, 8, 10, 9, 4, 7, 5 }));
	numbers.push_back(std::vector<int>({ 12, 13, 3, 19, 7, 20, 2, 18, 1, 17, 16, 9, 15, 10, 14, 8, 4, 11, 6, 5 }));
	
	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		if (!this->run_single(*it)) {
			return false;
		}
	}

	return true;
}
