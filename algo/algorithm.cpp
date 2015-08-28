/**
 * Algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "algo/algorithm.h"


namespace {

const int st_move[4][2] = {
	{-1, 0},
	{0, -1},
	{0, 1},
	{1, 0}
};

void search_single_island_bfs(
	const int* area,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	// Clear array.
	island_area->clear();

	auto index = row_position * column_size + column_position;

	// If the current node is not land, then return immediately.
	if (area[index] == 0) {
		return;
	}

	// Indicates if a node has been visited or not.
	bool* flags = new bool[row_size * column_size];
	for (auto i = 0; i < row_size * column_size; ++i) {
		flags[i] = false;
	}

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
				|| area[index_next] == 0
				|| flags[index_next]) {
				continue;
			}

			island_area->push_back(std::pair<int, int>(row_next, column_next));
			flags[index_next] = true;

			++tail;
		}

		++head;
	}

	delete[] flags;
	flags = 0;
}

void search_single_island_dfs_i(
	const int* area,
	int row_size, int column_size,
	int row_position, int column_position,
	bool* flags, std::vector<std::pair<int, int>>* island_area) {

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
			|| area[row_next * column_size + column_next] == 0
			|| flags[row_next * column_size + column_next]) {
			continue;
		}

		search_single_island_dfs_i(area, row_size, column_size, row_next, column_next, flags, island_area);
	}
}

void search_single_island_dfs(
	const int* area,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	// Clear array.
	island_area->clear();

	if (area[row_position * column_size + column_position] == 0) {
		return;
	}

	// Indicates if a node has been visited or not.
	bool* flags = new bool[row_size * column_size];
	for (auto i = 0; i < row_size * column_size; ++i) {
		flags[i] = false;
	}

	search_single_island_dfs_i(area, row_size, column_size, row_position, column_position, flags, island_area);

	delete[] flags;
	flags = 0;
}

} // unnamed namespace.


namespace algo {

void search_single_island(
	search_strategy_t strategy, const int* area,
	int row_size, int column_size,
	int row_position, int column_position,
	std::vector<std::pair<int, int>>* island_area) {

	if (strategy == SEARCH_STRATEGY_BFS) {
		search_single_island_bfs(area, row_size, column_size, row_position, column_position, island_area);
	}
	else {
		search_single_island_dfs(area, row_size, column_size, row_position, column_position, island_area);
	}
}

} // namespace algo.


