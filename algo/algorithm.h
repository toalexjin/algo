/**
 * Algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <limits.h>
#include <vector>
#include <utility>
#include <map>


namespace algo {

namespace number__ {

	template <class Functor>
	inline void number_combinations_i(int n, const Functor& functor,
		std::vector<int>& numbers, std::vector<bool>& flags, int index) {

		// End.
		if (index == n) {
			functor(numbers);
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
 * Functor prototype: void functor(const std::vector<int>& numbers);
 */
template <class Functor>
inline void number_combinations(int n, const Functor& functor) {
	std::vector<int> numbers(n);
	std::vector<bool> flags(n, false);

	number__::number_combinations_i(n, functor, numbers, flags, 0);
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
 * "matrix" is a 2d array, 0 means sea and 1 means land.
 * Island position is zero-based.
 *
 * @param strategy [in] A value of search_strategy_t.
 * @param matrix [in] A 2d array of "row_size * column_size" elements.
 * @param row_size [in] Number of rows.
 * @param column_size [in] Number of columns.
 * @param row_position [in] Island position (zero based index).
 * @param column_position [in] Island position (zero based index).
 * @param island_area [out] Island area.
 */
void search_single_island(
	search_strategy_t strategy, const int* matrix,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area);


struct distance_t {
	distance_t() : m_distance(0) {
	}

	explicit distance_t(int distance) : m_distance(distance) {
	}

	enum { const_unreachable = INT_MAX };

	// INT_MAX means unreachable.
	int m_distance;
	std::vector<int> m_paths;
};


/**
 * Dijkstra shortest path algorithm.
 *
 * Note that node number is zero-based.
 *
 * @param matrix [in] A 2d array of "node_size ^ 2" elements.
 * @param node_size [in] Number of nodes.
 * @param from [in] The source node (zero based index).
 * @param paths [out] The shortest paths from the source node to the rest of other nodes.
 */
void dijkstra(const int* matrix, int node_size, int from, std::map<int, distance_t>* paths);


/**
 * Calculate prime numbers in range [1, max_number].
 *
 * @param max_number [in] Max number.
 * @param prime_numbers [out] Prime numbers.
 */
void calc_prime_numbers(int max_number, std::vector<int>* prime_numbers);


} // namespace algo

