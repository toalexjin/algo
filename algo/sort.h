/**
 * Sorting algorithm.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <assert.h>
#include <functional>
#include <iterator>


namespace algo {

template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline void bubble_sort(Iterator first, Iterator last, const Less& less = Less()) {
	for (typename std::iterator_traits<Iterator>::difference_type i = 0; i < last - first - 1; ++i) {
		for (auto k = first; k < last - 1 - i; ++k) {
			if (less(*(k + 1), *k)) {
				const auto tmp(*k);
				*k = *(k + 1);
				*(k + 1) = tmp;
			}
		}
	}
}

template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline void selection_sort(Iterator first, Iterator last, const Less& less = Less()) {
	for (typename std::iterator_traits<Iterator>::difference_type i = 0; i < last - first - 1; ++i) {
		auto min = first + i;

		for (auto k = first + i + 1; k < last; ++k) {
			if (less(*k, *min)) {
				min = k;
			}
		}

		if (min != first + i) {
			const auto tmp(*min);
			*min = *(first + i);
			*(first + i) = tmp;
		}
	}
}

template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline void quick_sort(Iterator first, Iterator last, const Less& less = Less()) {
	if (last - first <= 1) {
		return;
	}

	auto front = first;
	auto back = last - 1;
	const auto key = *front;

	while (true) {
		for (; front < back; --back) {
			if (less(*back, key)) {
				break;
			}
		}

		for (; front < back; ++front) {
			if (less(key, *front)) {
				break;
			}
		}

		if (front >= back) {
			break;
		}

		const auto tmp(*front);
		*front = *back;
		*back = tmp;
	}

	*first = *front;
	*front = key;

	quick_sort(first, front, less);
	quick_sort(front + 1, last, less);
}


enum sort_algo_t {
	SORT_ALGO_MIN = 1,
	SORT_ALGO_MAX = 3,

	// Bubble sort.
	SORT_ALGO_BUBBLE = 1,

	// Selection sort.
	SORT_ALGO_SELECTION = 2,

	// Quick sort.
	SORT_ALGO_QUICK = 3
};

/**
 * Sorting algorithm.
 *
 * The range is [first, last).
 *
 * @param algo [in] A value of sort_algo_t.
 * @param first [in] First iterator.
 * @param last [in] Last iterator.
 * @param less [in] Element comparison functor.
 */
template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
inline void sort(sort_algo_t algo, Iterator first, Iterator last, const Less& less = Less()) {
	switch (algo) {
	case SORT_ALGO_BUBBLE:
		return bubble_sort(first, last, less);

	case SORT_ALGO_SELECTION:
		return selection_sort(first, last, less);

	case SORT_ALGO_QUICK:
		return quick_sort(first, last, less);

	default:
		assert(false);
		break;
	}
}


} // namespace algo
