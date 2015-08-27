/**
 * Test case for number calculation.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_number.h"
#include "algo/number.h"
#include <iostream>
#include <algorithm>
#include <iterator>


namespace {

test_number_t st_test;

} // unnamed namespace.


bool test_number_t::run() {

	for (auto i = 0; i <= 3; ++i) {
		std::cout << "Number: " << i << std::endl;

		algo::number_combinations(i, [](const int* numbers, int n) {
			std::cout << "=> ";
			std::copy(numbers, numbers + n, std::ostream_iterator<int>(std::cout, ","));
			std::cout << std::endl;
		});
	}

	return true;
}
