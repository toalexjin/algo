#include "test/test.h"


int main() {
	test_manager_t::instance().run_all();

	return 0;
}
