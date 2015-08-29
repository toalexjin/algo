/**
 * Test case for algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"
#include <limits.h>


// Test case for algorithms.
class test_algorithm_t : public test_case_t {
public:
	test_algorithm_t() : test_case_t("test_algorithm_t") {}
	virtual bool run();

public:
	enum { ISLANDS_ROW_SIZE = 11, ISLANDS_COLUMN_SIZE = 10 };
	enum { DIJKSTRA_NODE_COUNT = 6 };
	enum { X = INT_MAX };

private:
	bool test_number_combinations();
	bool test_island_size();

private:
	static const int st_islands[ISLANDS_ROW_SIZE][ISLANDS_COLUMN_SIZE];
	static const int st_dijkstra[DIJKSTRA_NODE_COUNT][DIJKSTRA_NODE_COUNT];
};

