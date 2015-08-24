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


// Test case for sorting algorithm.
class test_sort_t : public test_case_t {
public:
	virtual bool run();

private:
	template <class Ctner, class Less = std::less<typename Ctner::value_type>>
	bool run_single(const Ctner& raw, const Less& less = Less()) {

		std::cout << "RAW: ";
		std::copy(raw.begin(), raw.end(), std::ostream_iterator<typename Ctner::value_type>(std::cout, ","));
		std::cout << std::endl;

		for (int i = algo::SORT_ALGO_MIN; i <= (int)algo::SORT_ALGO_MAX; ++i) {
			Ctner clone;

			// ascending order.
			clone = raw;

			// We sort the array twice because we want to know what will happen
			// if it tries to sort an already-sorted array.
			for (auto times = 0; times < 2; ++times) {
				algo::sort((algo::sort_algo_t)i, clone.begin(), clone.end(), std::less<typename Ctner::value_type>());
				this->dump(true, clone.begin(), clone.end());

				if (clone.size() != raw.size()
					|| !this->verify(clone.begin(), clone.end(), std::less<typename Ctner::value_type>())) {
					return false;
				}
			}

			// descending order.
			clone = raw;
			for (auto times = 0; times < 2; ++times) {
				algo::sort((algo::sort_algo_t)i, clone.begin(), clone.end(), std::greater<typename Ctner::value_type>());
				this->dump(false, clone.begin(), clone.end());

				if (clone.size() != raw.size()
					|| !this->verify(clone.begin(), clone.end(), std::greater<typename Ctner::value_type>())) {
					return false;
				}
			}

			// ascending order.
			clone = raw;
			for (auto times = 0; times < 2; ++times) {
				algo::sort((algo::sort_algo_t)i, clone.rbegin(), clone.rend(), std::less<typename Ctner::value_type>());
				this->dump(true, clone.rbegin(), clone.rend());

				if (clone.size() != raw.size()
					|| !this->verify(clone.rbegin(), clone.rend(), std::less<typename Ctner::value_type>())) {
					return false;
				}
			}

			// descending order.
			clone = raw;
			for (auto times = 0; times < 2; ++times) {
				algo::sort((algo::sort_algo_t)i, clone.rbegin(), clone.rend(), std::greater<typename Ctner::value_type>());
				this->dump(false, clone.rbegin(), clone.rend());

				if (clone.size() != raw.size()
					|| !this->verify(clone.rbegin(), clone.rend(), std::greater<typename Ctner::value_type>())) {
					return false;
				}
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
