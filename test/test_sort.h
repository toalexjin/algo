/**
* Test case for sort algorithm.
*
* Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
*/

#pragma once

#include "test/test.h"
#include "algo/sort.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>


// Test case for sort algorithm.
class test_sort_t : public test_case_t {
public:
	virtual bool run();

private:
	template <class Ctner, class Less = std::less<typename Ctner::value_type>>
	bool run_single(const Ctner& raw, const Less& less = Less()) {

		// Bubble sort.
		Ctner bubble(raw);
		algo::bubble_sort(bubble.begin(), bubble.end(), less);
		this->dump(bubble.begin(), bubble.end());
		
		if (bubble.size() != raw.size()
			|| !this->verify(bubble.begin(), bubble.end(), less)) {
			return false;
		}

		return true;
	}

	template <class Iterator>
	void dump(Iterator first, Iterator last) {
		std::cout << "Sort result: ";
		std::copy(first, last, std::ostream_iterator<typename std::iterator_traits<Iterator>::value_type>(std::cout, ","));
		std::cout << std::endl;
	}

	template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
	bool verify(Iterator first, Iterator last, const Less& less = Less()) {
		if (first == last) {
			return true;
		}

		for (auto it = first; it < last - 1; ++it) {
			if (less(*(it + 1), *it)) {
				return false;
			}
		}

		return true;
	}
};
