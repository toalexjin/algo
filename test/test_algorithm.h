/**
 * Test case for algorithms.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"


#define AREA_ROW_SIZE		11
#define AREA_COLUMN_SIZE	10


// Test case for algorithms.
class test_algorithm_t : public test_case_t {
public:
	test_algorithm_t() : test_case_t("test_algorithm_t") {}
	virtual bool run();

private:
	bool test_number_combinations();
	bool test_island_size();

private:
	static const int st_area[AREA_ROW_SIZE][AREA_COLUMN_SIZE];
};
