/**
 * Algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "algo/algorithm.h"


namespace algo {

static std::vector<std::pair<int, int>> island_size_bfs(
	const int* area,
	int row_size, int column_size,
	int row_position, int column_position) {

	std::vector<std::pair<int, int>> result;

	return result;
}

static std::vector<std::pair<int, int>> island_size_dfs(
	const int* area,
	int row_size, int column_size,
	int row_position, int column_position) {

	std::vector<std::pair<int, int>> result;

	return result;
}


std::vector<std::pair<int, int>> island_size(
	search_type_t type, const int* area,
	int row_size, int column_size,
	int row_position, int column_position) {

	if (type == search_type_bfs) {
		return island_size_bfs(area, row_size, column_size, row_position, column_position);
	}
	else {
		return island_size_dfs(area, row_size, column_size, row_position, column_position);
	}
}

} // namespace algo

