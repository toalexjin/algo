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
#include <algorithm>


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
		if (!this->run_single_i(ctner, std::less<typename Ctner::value_type>(), true)) {
			return false;
		}

		// Descending order.
		if (!this->run_single_i(ctner, std::greater<typename Ctner::value_type>(), false)) {
			return false;
		}

		return true;
	}

	template <class Ctner, class Compare>
	bool run_single_i(const Ctner& ctner, const Compare& compare, bool is_less) {
		const auto ascending = "-->: ";
		const auto descending = "<--: ";

		algo::rbtree_t<typename Ctner::value_type, Compare> tree(compare);
		tree.insert(ctner.begin(), ctner.end());
		std::cout << "RB-Tree Size: " << tree.size() << std::endl;
		this->dump(is_less ? ascending : descending, tree.begin(), tree.end());
		this->dump(is_less ? descending : ascending, tree.rbegin(), tree.rend());

		std::cout << "<Copy constructor>" << std::endl;
		auto v1(tree);
		this->dump(is_less ? ascending : descending, v1.begin(), v1.end());
		this->dump(is_less ? descending : ascending, v1.rbegin(), v1.rend());

		std::cout << "<Swap>" << std::endl;
		algo::rbtree_t<typename Ctner::value_type, Compare> v2(compare);
		std::swap(v1, v2);
		this->dump(is_less ? ascending : descending, v1.begin(), v1.end());
		this->dump(is_less ? descending : ascending, v1.rbegin(), v1.rend());
		this->dump(is_less ? ascending : descending, v2.begin(), v2.end());
		this->dump(is_less ? descending : ascending, v2.rbegin(), v2.rend());
		
		return true;
	}

	template <class Iterator>
	void dump(const char* prefix, Iterator first, Iterator last) {
		std::cout << prefix; // (ascending ? "-->: " : "<--: ");
		std::copy(first, last, std::ostream_iterator<typename std::iterator_traits<Iterator>::value_type>(std::cout, ","));
		std::cout << std::endl;
	}
};
