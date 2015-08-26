/**
 * Test case for hash_table_t.
 *
 * Copyright (c) 2015 Alex Jin (toalexjin@hotmail.com)
 */

#pragma once

#include "test/test.h"
#include "algo/hash_table.h"
#include <iostream>
#include <string>


// Test case for hash_table_t.
class test_hash_table_t : public test_case_t {
private:
	typedef algo::hash_table_t<std::string, std::string> my_table_t;

public:
	test_hash_table_t() : test_case_t("test_hash_table_t") {}
	virtual bool run();

private:
	template <class TablePointer>
	void dump(TablePointer table, bool reverse) {
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
	}

	void dump_4(my_table_t* table);
};
