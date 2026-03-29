#include "db/page.hpp"

#include <cassert>
#include <cstddef>
#include <iostream>

namespace {

void test_new_page_is_zero_initialized() {
    db::Page page;

    for (std::size_t i = 0; i < db::Page::kPageSize; ++i) {
        assert(page.data()[i] == 0);
    }
}

void test_page_can_store_bytes() {
    db::Page page;
    page.data()[0] = 7;
    page.data()[1] = 8;
    page.data()[2] = 9;

    assert(page.data()[0] == 7);
    assert(page.data()[1] == 8);
    assert(page.data()[2] == 9);
}

void test_page_reset_clears_data() {
    db::Page page;
    page.data()[0] = 42;
    page.data()[db::Page::kPageSize - 1] = 24;

    page.reset();

    for (std::size_t i = 0; i < db::Page::kPageSize; ++i) {
        assert(page.data()[i] == 0);
    }
}

}  // namespace

int main() {
    test_new_page_is_zero_initialized();
    test_page_can_store_bytes();
    test_page_reset_clears_data();

    std::cout << "page_test passed\n";
    return 0;
}
