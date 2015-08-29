/**
 * Test case for algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"
#include "algo/algorithm.h"


// Test case for algorithms.
class test_algorithm_t : public test_case_t {
public:
	test_algorithm_t() : test_case_t("test_algorithm_t") {}
	virtual bool run();

public:
	enum { const_islands_row_size = 11, const_islands_column_size = 10 };
	enum { const_dijkstra_node_size = 6 };
	enum { X = algo::distance_t::const_unreachable };

private:
	bool test_number_combinations();
	bool test_island_size();
	bool test_dijkstra();

private:
	static const int st_islands[const_islands_row_size][const_islands_column_size];
	static const int st_dijkstra[const_dijkstra_node_size][const_dijkstra_node_size];
};

