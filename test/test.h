#pragma once

#include <vector>


class test_t {
public:
	test_t();

	virtual bool run() = 0;
};


class test_manager_t {
public:
	static test_manager_t& instance();

public:
	void add(test_t* test);
	void run_all();

private:
	test_manager_t();

private:
	std::vector<test_t*> m_tests;
};

