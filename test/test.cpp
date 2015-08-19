#include "test/test.h"


test_t::test_t() {
	test_manager_t::instance().add(this);
}



test_manager_t& test_manager_t::instance() {
	static test_manager_t instance;

	return instance;
}

void test_manager_t::add(test_t* test) {
	this->m_tests.push_back(test);
}

void test_manager_t::run_all() {
	for (auto it = m_tests.begin(); it != m_tests.end(); ++it) {
		(*it)->run();
	}
}

test_manager_t::test_manager_t() {
}
