/**
 * Tower of Hanoi.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <stddef.h>


namespace algo {


/**
 * Tower of Hanoi.
 *
 * The goal is to move all disks from A to C.
 * 
 * Functor prototype: void functor(char from, char to);
 *
 * @return Number of steps.
 */
template <class Functor>
inline size_t hanoi(size_t n, char a, char b, char c, const Functor& functor) {
	if (n == 0) {
		return 0;
	}

	if (n == 1) {
		functor(a, c);
		return 1;
	}
	else {
		auto steps = hanoi(n - 1, a, c, b, functor);
		
		functor(a, c);
		++steps;
		steps += hanoi(n - 1, b, a, c, functor);

		return steps;
	}
}

} // namespace algo
