/**
 * Sort algorithm.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

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

} // namespace algo
