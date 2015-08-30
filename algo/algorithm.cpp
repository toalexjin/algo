/**
 * Algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "algo/algorithm.h"
#include <assert.h>


namespace {

const int st_move[4][2] = {
	{-1, 0},
	{0, -1},
	{0, 1},
	{1, 0}
};

void search_single_island_bfs(
	const int* matrix,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	auto index = row_position * column_size + column_position;

	// If the current node is not land, then return immediately.
	if (matrix[index] == 0) {
		return;
	}

	// Indicates if a node has been visited or not.
	std::vector<bool> flags(row_size * column_size, false);

	// Add first node.
	island_area->push_back(std::pair<int, int>(row_position, column_position));
	flags[index] = true;

	int head = 0;
	int tail = 1;

	while (head < tail) {
		const auto row_current = (*island_area)[head].first;
		const auto column_current = (*island_area)[head].second;

		for (auto i = 0; i < 4; ++i) {
			const auto row_next = row_current + st_move[i][0];
			const auto column_next = column_current + st_move[i][1];
			const auto index_next = row_next * column_size + column_next;

			if (row_next < 0
				|| row_next >= row_size
				|| column_next < 0
				|| column_next >= column_size
				|| matrix[index_next] == 0
				|| flags[index_next]) {
				continue;
			}

			island_area->push_back(std::pair<int, int>(row_next, column_next));
			flags[index_next] = true;

			++tail;
		}

		++head;
	}
}

void search_single_island_dfs_i(
	const int* matrix,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<bool>& flags, std::vector<std::pair<int, int>>* island_area) {

	// Set visited flag.
	flags[row_position * column_size + column_position] = true;
	island_area->push_back(std::pair<int, int>(row_position, column_position));

	for (auto i = 0; i < 4; ++i) {
		const auto row_next = row_position + st_move[i][0];
		const auto column_next = column_position + st_move[i][1];

		if (row_next < 0
			|| row_next >= row_size
			|| column_next < 0
			|| column_next >= column_size
			|| matrix[row_next * column_size + column_next] == 0
			|| flags[row_next * column_size + column_next]) {
			continue;
		}

		search_single_island_dfs_i(matrix, row_size, column_size, row_next, column_next, flags, island_area);
	}
}

void search_single_island_dfs(
	const int* matrix,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	if (matrix[row_position * column_size + column_position] == 0) {
		return;
	}

	// Indicates if a node has been visited or not.
	std::vector<bool> flags(row_size * column_size, false);

	search_single_island_dfs_i(matrix, row_size, column_size,
		row_position, column_position, flags, island_area);
}

} // unnamed namespace.



namespace algo {

void search_single_island(
	search_strategy_t strategy, const int* matrix,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	assert(matrix != 0 || row_size == 0 || column_size == 0);
	assert(row_size >= 0);
	assert(column_size >= 0);
	assert(row_position >= 0);
	assert(column_position >= 0);
	assert(island_area != 0);

	// Clear data.
	island_area->clear();

	// If the matrix is empty, then return immediately.
	if (row_size <= 0 || column_size <= 0) {
		return;
	}

	if (strategy == SEARCH_STRATEGY_BFS) {
		search_single_island_bfs(matrix, row_size, column_size, row_position, column_position, island_area);
	}
	else {
		search_single_island_dfs(matrix, row_size, column_size, row_position, column_position, island_area);
	}
}

void dijkstra(const int* matrix, int node_size,
	int from, std::map<int, distance_t>* paths) {

	assert(matrix != 0 || node_size == 0);
	assert(node_size >= 0);
	assert(from >= 0);
	assert(paths != 0);

	// Clear data.
	paths->clear();

	// If the matrix is empty, then return immediately.
	if (node_size <= 0) {
		return;
	}

	std::vector<distance_t> distance;
	distance.reserve(node_size);

	for (auto i = 0; i < node_size; ++ i) {
		distance.push_back(distance_t(matrix[from * node_size + i]));
	}

	// Indicates if a node has been processed or not.
	std::vector<bool> flags(node_size, false);

	// Mark the source node as processed.
	flags[from] = true;

	// Besides the source node, there are "node_size - 1" nodes,
	// so we need to loop "node_size - 1" times.
	for (auto i = 0; i < node_size - 1; ++i) {
		int min_index = -1;
		int min_value = distance_t::const_unreachable;

		// Find which node is the closest to the source node.
		for (auto k = 0; k < node_size; ++k) {
			if (!flags[k]
				&& distance[k].m_distance != distance_t::const_unreachable
				&& distance[k].m_distance < min_value) {
				min_index = k;
				min_value = distance[k].m_distance;
			}
		}

		if (min_value == distance_t::const_unreachable) {
			break;
		}

		flags[min_index] = true;

		for (auto k = 0; k < node_size; ++k) {
			// If the node has been finalized, then skip.
			if (flags[k]) {
				continue;
			}

			if (matrix[min_index * node_size + k] != distance_t::const_unreachable) {
				if (distance[k].m_distance > min_value + matrix[min_index * node_size + k]) {
					distance[k].m_distance = min_value + matrix[min_index * node_size + k];
					distance[k].m_paths = distance[min_index].m_paths;
					distance[k].m_paths.push_back(min_index);
				}
			}
		}
	}

	for (int index = 0; index < (int)distance.size(); ++index) {
		(*paths)[index] = distance[index];
	}
}


void calc_prime_numbers(int max_number, std::vector<int>* prime_numbers) {

	assert(max_number >= 0);
	assert(prime_numbers != 0);

	// Clear data.
	prime_numbers->clear();

	// If max number is too small, then return immediately.
	if (max_number <= 1) {
		return;
	}

	std::vector<bool> flags(max_number + 1, true);

	for (int i = 2; i * i <= max_number; ++i) {
		if (!flags[i]) {
			continue;
		}

		for (int k = 2 * i; k <= max_number; k += i) {
			flags[k] = false;
		}
	}

	for (int i = 2; i <= max_number; ++i) {
		if (flags[i]) {
			prime_numbers->push_back(i);
		}
	}
}


} // namespace algo.
