/**
* Test case for sorting algorithm.
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

		for (int i = algo::SORT_ALGO_BUBBLE; i <= (int)algo::SORT_ALGO_SELECTION; ++i) {
			Ctner clone;

			// ascending order.
			clone = raw;
			algo::sort((algo::sort_algo_t)i, clone.begin(), clone.end(), std::less<typename Ctner::value_type>());
			this->dump(true, clone.begin(), clone.end());

			if (clone.size() != raw.size()
				|| !this->verify(clone.begin(), clone.end(), std::less<typename Ctner::value_type>())) {
				return false;
			}

			// descending order.
			clone = raw;
			algo::sort((algo::sort_algo_t)i, clone.begin(), clone.end(), std::greater<typename Ctner::value_type>());
			this->dump(false, clone.begin(), clone.end());

			if (clone.size() != raw.size()
				|| !this->verify(clone.begin(), clone.end(), std::greater<typename Ctner::value_type>())) {
				return false;
			}
		}

		return true;
	}

	template <class Iterator>
	void dump(bool ascending, Iterator first, Iterator last) {
		std::cout << (ascending ? "-->: " : "<--: ");
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
