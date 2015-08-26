/**
 * Test case for rbtree_t.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"
#include "algo/rbtree.h"
#include <iostream>
#include <string>


// Test case for rbtree_t.
class test_rbtree_t : public test_case_t {
public:
	test_rbtree_t() : test_case_t("test_rbtree_t") {}
	virtual bool run();

private:
	template <class Ctner>
	bool run_single(const Ctner& ctner) {
		// RAW.
		this->dump("RAW: ", ctner.begin(), ctner.end());

		// Ascending order.
		do {
			algo::rbtree_t<typename Ctner::value_type> tree_less;
			tree_less.insert(ctner.begin(), ctner.end());
			std::cout << "RB-Tree Size: " << tree_less.size() << std::endl;
			this->dump("-->: ", tree_less.begin(), tree_less.end());
			this->dump("<--: ", tree_less.rbegin(), tree_less.rend());
		} while (0);

		// Descending order.
		do {
			algo::rbtree_t<typename Ctner::value_type, std::greater<typename Ctner::value_type>> tree_greater;
			tree_greater.insert(ctner.begin(), ctner.end());
			std::cout << "RB-Tree Size: " << tree_greater.size() << std::endl;
			this->dump("<--: ", tree_greater.begin(), tree_greater.end());
			this->dump("-->: ", tree_greater.rbegin(), tree_greater.rend());
		} while (0);

		return true;
	}

	template <class Iterator>
	void dump(const char* prefix, Iterator first, Iterator last) {
		std::cout << prefix; // (ascending ? "-->: " : "<--: ");
		std::copy(first, last, std::ostream_iterator<typename std::iterator_traits<Iterator>::value_type>(std::cout, ","));
		std::cout << std::endl;
	}
};
