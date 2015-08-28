/**
 * Test case for algorithm.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_algorithm.h"
#include "algo/algorithm.h"
#include "algo/sort.h"
#include <iostream>
#include <algorithm>
#include <iterator>


namespace {

test_algorithm_t st_test;

} // unnamed namespace.


const int test_algorithm_t::st_area[AREA_ROW_SIZE][AREA_COLUMN_SIZE] = {
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 0
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 1
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 2
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 3
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 4
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 5
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 6
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 7
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 8
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }, // 9
	{ 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 }  // 10
};


bool test_algorithm_t::run() {
	typedef bool (test_algorithm_t::*mem_func_t)();

	mem_func_t functions[2] = {
		&test_algorithm_t::test_number_combinations,
		&test_algorithm_t::test_island_size };

	for (auto i = 0; i < 2; ++i) {
		auto ptr = functions[i];

		if (!(this->*ptr)()) {
			return false;
		}
	}

	return true;
}

bool test_algorithm_t::test_number_combinations() {

	for (auto i = 0; i <= 3; ++i) {
		std::cout << "Number: " << i << std::endl;

		algo::number_combinations(i, [](const int* numbers, int n) {
			std::cout << "=> ";
			std::copy(numbers, numbers + n, std::ostream_iterator<int>(std::cout, ","));
			std::cout << std::endl;
		});
	}

	return true;
}

bool test_algorithm_t::test_island_size() {

	std::vector<std::pair<int, int>> numbers;

	numbers.push_back(std::pair<int, int>(0, 0));
	numbers.push_back(std::pair<int, int>(1, 1));
	numbers.push_back(std::pair<int, int>(5, 5));
	numbers.push_back(std::pair<int, int>(8, 8));
	numbers.push_back(std::pair<int, int>(9, 9));

	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		std::cout << "Island Position: " << (*it).first << "," << (*it).second << std::endl;

		std::vector<std::pair<int, int>> result[2];
		algo::search_single_island(algo::SEARCH_STRATEGY_BFS, (int*)st_area,
			AREA_ROW_SIZE, AREA_COLUMN_SIZE, (*it).first, (*it).second, &result[0]);

		std::vector<std::pair<int, int>> v2;
		algo::search_single_island(algo::SEARCH_STRATEGY_DFS, (int*)st_area,
			AREA_ROW_SIZE, AREA_COLUMN_SIZE, (*it).first, (*it).second, &result[1]);

		// Less function.
		auto less = [](const std::pair<int, int>& n1, const std::pair<int, int>& n2) -> bool {
			if (n1.first < n2.first) {
				return true;
			}

			if (n1.first > n2.first) {
				return false;
			}

			return n1.second < n2.second;
		};

		for (auto k = 0; k < 2; ++k) {
			algo::sort(algo::SORT_ALGO_QUICK, result[k].begin(), result[k].end(), less);

			std::cout << "Island Size: " << result[k].size() << std::endl;
			std::cout << "Island Area: ";

			for (auto ptr = result[k].begin(); ptr != result[k].end(); ++ptr) {
				std::cout << "[" << (*ptr).first << "," << (*ptr).second << "] ";
			}
			std::cout << std::endl;
		}

		if (result[0] != result[1]) {
			std::cout << "BFS and DFS' results are different!!" << std::endl;
			return false;
		}
	}

	return true;
}
