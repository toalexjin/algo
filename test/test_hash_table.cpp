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


typedef algo::hash_table_t<std::string, std::string> my_table_t;


template <class TablePointer>
inline void dump(TablePointer table, bool reverse) {
	std::cout << "dump " << (reverse ? "(reverse)" : "") << ": " << table->size() << std::endl;

	if (reverse) {
		for (auto it = table->rbegin(); it != table->rend(); ++it) {
			std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
		}
	}
	else {
		for (auto it = table->begin(); it != table->end(); ++it) {
			std::cout << "table[" << (*it).first << "] = " << (*it).second << std::endl;
		}
	}

	std::cout << std::endl;
}

inline void dump_4(my_table_t* table) {
	dump((my_table_t*) table, false);
	dump((const my_table_t*) table, false);
	dump((my_table_t*) table, true);
	dump((const my_table_t*) table, true);
}

}


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

	dump_4(&table);

	table.insert("A", "A value #2");
	table.erase("A");
	table.erase("C");
	table.erase("G");
	table.erase("H");

	dump_4(&table);

	auto v2(table);
	dump_4(&v2);

	v2 = table;
	dump_4(&v2);

	return true;
}

