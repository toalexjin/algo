/**
 * Test case for Tower of Hanoi.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_hanoi.h"
#include "algo/hanoi.h"
#include <iostream>


namespace {

test_hanoi_t st_test_hanoi;

} // unnamed namespace.


bool test_hanoi_t::run() {
	std::vector<size_t> numbers({1, 2, 3, 4, 5});

	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		if (!this->run_single(*it)) {
			return false;
		}

		std::cout << std::endl;
	}

	return true;
}

bool test_hanoi_t::run_single(size_t n) {
	std::cout << "Number: " << n << std::endl;

	auto steps = algo::hanoi(n, 'A', 'B', 'C',
		[](char from, char to) {
			std::cout << from << " -> " << to << std::endl;
		}
	);

	if (steps != size_t((1 << n) - 1)) {
		return false;
	}

	return true;
}
