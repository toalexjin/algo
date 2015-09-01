/**
 * Test case for hash_table_t.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#include "test/test_hash_table.h"
#include <iostream>


namespace {

test_hash_table_t st_test;

} // unnamed namespace.


bool test_hash_table_t::run() {

	my_table_t table(3);

	std::string key;

	for (auto ch = 'A'; ch <= 'Z'; ++ch) {
		key.clear();
		key.push_back(ch);
		table[key] = key + " value";
	}

	(*table.begin()).second += "  #First";
	(*table.rbegin()).second += "  #Last";

	this->dump_4(&table);

	table.insert("A", "A value #2");
	table.erase("A");
	table.erase("C");
	table.erase("G");
	table.erase("H");

	this->dump_4(&table);

	auto v2(table);
	this->dump_4(&v2);

	v2 = table;
	this->dump_4(&v2);

	my_table_t v3({ { "11", "11 value" }, { "22", "22 value" }, { "33", "33 value" } });
	v3.insert({ { "44", "44 value" },{ "55", "55 value" },{ "66", "66 value" } });
	this->dump_4(&v3);

	return true;
}

void test_hash_table_t::dump_4(test_hash_table_t::my_table_t* table) {
	dump((my_table_t*)table, false);
	std::cout << std::endl;
	dump((const my_table_t*)table, false);
	std::cout << std::endl;
	dump((my_table_t*)table, true);
	std::cout << std::endl;
	dump((const my_table_t*)table, true);
}
