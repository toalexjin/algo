/**
 * Test framework for algo.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <vector>


// Test case.
class test_case_t {
public:
	test_case_t();
	virtual ~test_case_t();

	virtual bool run() = 0;
};


// Test manager.
class test_manager_t {
public:
	static test_manager_t& instance();

public:
	void add(test_case_t* test);
	void run_all();

private:
	test_manager_t();

private:
	std::vector<test_case_t*> m_tests;
};

