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
void inline bubble_sort(Iterator first, Iterator last, const Less& less = Less()) {
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
void inline selection_sort(Iterator first, Iterator last, const Less& less = Less()) {
	for (typename std::iterator_traits<Iterator>::difference_type i = 0; i < last - first - 1; ++i) {
		auto min = first + i;

		for (auto k = first + i + 1; k < last; ++k) {
			if (less(*k, *min)) {
				min = k;
			}
		}

		if (min != first + i) {
			auto tmp = *min;
			*min = *(first + i);
			*(first + i) = tmp;
		}
	}
}


enum sort_algo_t {
	SORT_ALGO_BUBBLE,
	SORT_ALGO_SELECTION
};

template <class Iterator, class Less = std::less<typename std::iterator_traits<Iterator>::value_type>>
void inline sort(sort_algo_t algo, Iterator first, Iterator last, const Less& less = Less()) {
	switch (algo) {
	case SORT_ALGO_BUBBLE:
		return bubble_sort(first, last, less);

	case SORT_ALGO_SELECTION:
		return selection_sort(first, last, less);

	default:
		assert(false);
		break;
	}
}


} // namespace algo
