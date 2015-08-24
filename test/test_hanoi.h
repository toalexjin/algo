/**
 * Test case for Tower of Hanoi.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"
#include <stddef.h>


// Test case for Tower of Hanoi.
class test_hanoi_t : public test_case_t {
public:
	virtual bool run();

private:
	bool run_single(size_t n);
};
