/**
 * Test case for number calculation.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"


// Test case for number calculation.
class test_number_t : public test_case_t {
public:
	test_number_t() : test_case_t("test_number_t") {}
	virtual bool run();
};
