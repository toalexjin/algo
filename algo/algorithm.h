/**
 * Algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <vector>
#include <utility>


namespace algo {

namespace number__ {

	template <class Functor>
	inline void number_combinations_i(int n, const Functor& functor,
		int* numbers, bool* flags, int index) {

		// End.
		if (index == n) {
			functor(numbers, n);
			return;
		}

		for (auto k = 0; k < n; ++k) {
			if (!flags[k]) {
				numbers[index] = k + 1;
				flags[k] = true;
				number_combinations_i(n, functor, numbers, flags, index + 1);
				flags[k] = false;
			}
		}
	}
}


/**
 * Calculate all possible number combinations.
 *
 * For instance: "n" is 3, then output will be "123", "132", "213", "231", "312", "321".
 *
 * Functor prototype: void functor(const int* numbers, int n);
 */
template <class Functor>
inline void number_combinations(int n, const Functor& functor) {
	int* numbers = new int[n];
	bool* flags = new bool[n];

	for (auto i = 0; i < n; ++i) {
		flags[i] = false;
	}

	number__::number_combinations_i(n, functor, numbers, flags, 0);

	delete[] numbers;
	delete[] flags;
}

enum search_strategy_t {
	// Breadth first search.
	SEARCH_STRATEGY_BFS,

	// Depth first search.
	SEARCH_STRATEGY_DFS
};

/**
 * Search single island area.
 *
 * "area" is a two dimensional array, 0 means sea and 1 means land.
 */
void search_single_island(
	search_strategy_t strategy,	const int* area,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area);

} // namespace algo

