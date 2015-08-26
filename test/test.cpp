/**
 * Test framework for algo.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test.h"
#include <iostream>
#include <typeinfo>


// Add itself to test manager automatically.
test_case_t::test_case_t(const std::string& name) : m_name(name) {
	test_manager_t::instance().add(this);
}

test_case_t::~test_case_t() {
}



test_manager_t& test_manager_t::instance() {
	static test_manager_t instance;

	return instance;
}

void test_manager_t::add(test_case_t* test) {
	this->m_tests[test->get_name()] = test;
}

std::vector<std::string> test_manager_t::get_names() const {
	std::vector<std::string> names;

	for (auto it = this->m_tests.begin(); it != this->m_tests.end(); ++it) {
		names.push_back((*it).first);
	}

	return names;
}

bool test_manager_t::run() {
	return this->run_i(m_tests.begin(), m_tests.end());
}

bool test_manager_t::run(const std::string& name) {
	auto it = this->m_tests.find(name);
	
	if (it == this->m_tests.end()) {
		return false;
	}
	
	return this->run_i(it, ++ctner_t::iterator(it));
}

bool test_manager_t::run_i(test_manager_t::ctner_t::iterator first, test_manager_t::ctner_t::iterator last) {
	size_t success = 0;
	size_t failed = 0;

	for (auto it = first; it != last; ++it) {
		auto test_ptr = (*it).second;

		std::cout << "----------- Begin <" << test_ptr->get_name() << "> -----------" << std::endl;
		const auto result = test_ptr->run();
		std::cout << "----------- End <" << test_ptr->get_name() << ">: " << (result ? "Success" : "Failed") << " -----------" << std::endl;
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

	return failed == 0;
}

test_manager_t::test_manager_t() {
}
