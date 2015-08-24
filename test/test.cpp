/**
 * Test framework for algo.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test.h"
#include <iostream>
#include <typeinfo>


// Add itself to test manager automatically.
test_case_t::test_case_t() {
	test_manager_t::instance().add(this);
}

test_case_t::~test_case_t() {
}



test_manager_t& test_manager_t::instance() {
	static test_manager_t instance;

	return instance;
}

void test_manager_t::add(test_case_t* test) {
	this->m_tests.push_back(test);
}

void test_manager_t::run_all() {
	size_t success = 0;
	size_t failed = 0;

	for (auto it = m_tests.begin(); it != m_tests.end(); ++it) {
		const auto& info(typeid(*(*it)));

		std::cout << "----------- Begin <" << info.name() << "> -----------" << std::endl;
		const auto result = (*it)->run();
		std::cout << "----------- End <" << info.name() << ">: " << (result ? "Success" : "Failed") << " -----------" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		if (result) {
			++success;
		}
		else {
			++failed;
		}
	}

	std::cout << "Success: " << success << std::endl;
	std::cout << "Failed: " << failed << std::endl;
}

test_manager_t::test_manager_t() {
}
