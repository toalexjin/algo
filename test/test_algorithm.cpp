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


const int test_algorithm_t::st_islands[const_islands_row_size][const_islands_column_size] = {
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


const int test_algorithm_t::st_dijkstra[const_dijkstra_node_size][const_dijkstra_node_size] = {
	{ 0, 6, 2, 5, 9, X }, // 0
	{ 6, 0, 2, X, 1, X }, // 1
	{ 2, 2, 0, X, X, 4 }, // 2
	{ 5, X, X, 0, X, 6 }, // 3
	{ 9, 1, X, X, 0, X }, // 4
	{ X, X, 4, 6, X, 0 }  // 5
};

bool test_algorithm_t::run() {
	typedef bool (test_algorithm_t::*mem_func_t)();

	mem_func_t functions[] = {
		&test_algorithm_t::test_number_combinations,
		&test_algorithm_t::test_island_size,
		&test_algorithm_t::test_dijkstra
	};

	for (size_t i = 0; i < sizeof(functions)/sizeof(functions[0]); ++i) {
		auto ptr = functions[i];

		if (!(this->*ptr)()) {
			return false;
		}
	}

	return true;
}

bool test_algorithm_t::test_number_combinations() {

	std::cout << "test_algorithm_t::" << __func__ << "():" << std::endl;

	for (auto i = 0; i <= 3; ++i) {
		std::cout << "Number: " << i << std::endl;

		algo::number_combinations(i, [](const std::vector<int>& numbers) {
			std::cout << "=> ";
			std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout, ","));
			std::cout << std::endl;
		});
	}
	std::cout << std::endl;

	return true;
}

bool test_algorithm_t::test_island_size() {

	std::cout << "test_algorithm_t::" << __func__ << "():" << std::endl;

	std::vector<std::pair<int, int>> numbers;

	numbers.push_back(std::pair<int, int>(0, 0));
	numbers.push_back(std::pair<int, int>(1, 1));
	numbers.push_back(std::pair<int, int>(5, 5));
	numbers.push_back(std::pair<int, int>(8, 8));
	numbers.push_back(std::pair<int, int>(9, 9));

	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		std::cout << "Island Position: " << (*it).first << "," << (*it).second << std::endl;

		std::vector<std::pair<int, int>> result[2];
		algo::search_single_island(algo::SEARCH_STRATEGY_BFS, (const int*)st_islands,
			const_islands_row_size, const_islands_column_size, (*it).first, (*it).second, &result[0]);

		std::vector<std::pair<int, int>> v2;
		algo::search_single_island(algo::SEARCH_STRATEGY_DFS, (const int*)st_islands,
			const_islands_row_size, const_islands_column_size, (*it).first, (*it).second, &result[1]);

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
	std::cout << std::endl;

	return true;
}

bool test_algorithm_t::test_dijkstra() {

	std::cout << "test_algorithm_t::" << __func__ << "():" << std::endl;
	
	std::map<int, algo::distance_t> paths;

	for (int from = 0; from < (int)const_dijkstra_node_size; ++from) {
		algo::dijkstra((const int*)st_dijkstra, const_dijkstra_node_size, from, &paths);

		for (auto it = paths.begin(); it != paths.end(); ++ it) {
			std::cout << "[" << from << " => " << (*it).first << "] = ";

			if ((*it).second.m_distance == algo::distance_t::const_unreachable) {
				std::cout << "X";
			}
			else {
				std::cout << (*it).second.m_distance << " ";

				const auto path((*it).second.m_paths);
				std::cout << "[ " << from << " -> ";
				std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " -> "));
				std::cout << (*it).first << " ]";
			}

			std::cout << std::endl;
		}
	}

	std::cout << std::endl;

	return true;
}
