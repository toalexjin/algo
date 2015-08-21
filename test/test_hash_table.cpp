/**
 * Test case for hash_table_t.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_hash_table.h"
#include "algo/hash_table.h"
#include <iostream>
#include <string>


namespace {
	test_hash_table_t st_test_hash_table;
}


bool test_hash_table_t::run() {

	algo::hash_table_t<std::string, std::string> table(3);

	std::string key;

	for (auto ch = 'A'; ch <= 'Z'; ++ch) {
		key.clear();
		key.push_back(ch);
		table[key] = key + " value";
	}

	std::cout << "dump: " << table.size() << std::endl;
	for (auto it = table.begin(); it != table.end(); ++it) {
		std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
	}
	std::cout << std::endl;

	std::cout << "dump (reverse): " << table.size() << std::endl;
	for (auto it = table.rbegin(); it != table.rend(); ++it) {
		std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
	}
	std::cout << std::endl;

	table.insert("A", "A value #2");
	table.erase("A");
	table.erase("C");
	table.erase("G");
	table.erase("H");

	(*table.begin()).second += "  #begin() appended";
	(*table.rbegin()).second += "  #rbegin() appended";

	std::cout << "dump: " << table.size() << std::endl;
	for (auto it = table.begin(); it != table.end(); ++it) {
		std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
	}
	std::cout << std::endl;

	std::cout << "dump (reverse): " << table.size() << std::endl;
	for (auto it = table.rbegin(); it != table.rend(); ++it) {
		std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
	}
	std::cout << std::endl;

	return true;
}

