/**
 * Test program.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test.h"
#include <iostream>


namespace {

void help() {
	std::cout << "Usage: testalgo -a" << std::endl;
	std::cout << "       testalgo <test-case-name>" << std::endl;
	std::cout << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "       -a    Run all test cases" << std::endl;
	std::cout << std::endl;
	std::cout << "Test Case Names:" << std::endl;

	const auto names = test_manager_t::instance().get_names();
	for (auto it = names.begin(); it != names.end(); ++it) {
		std::cout << "       " << *it << std::endl;
	}
	std::cout << std::endl;
}

} // unnamed namespace


int main(int argc, char* argv[]) {

	if (argc != 2) {
		help();
		exit(1);
	}

	bool result = false;
	std::string arg1 = argv[1];

	if (arg1 == "-a") {
		result = test_manager_t::instance().run();
	}
	else {
		result = test_manager_t::instance().run(arg1);
	}

	return result ? 0 : 2;
}
