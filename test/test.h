/**
 * Test framework for algo.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include <string>
#include <map>
#include <vector>


// Test case.
class test_case_t {
public:
	explicit test_case_t(const std::string& name);
	virtual ~test_case_t();

	const std::string& get_name() const {
		return this->m_name;
	}

	virtual bool run() = 0;

private:
	const std::string m_name;
};


// Test manager.
class test_manager_t {
private:
	typedef std::map<std::string, test_case_t*> ctner_t;

public:
	static test_manager_t& instance();

public:
	void add(test_case_t* test);
	std::vector<std::string> get_names() const;

	bool run();
	bool run(const std::string& name);

private:
	test_manager_t();
	bool run_i(ctner_t::iterator first, ctner_t::iterator last);

private:
	ctner_t m_tests;
};

