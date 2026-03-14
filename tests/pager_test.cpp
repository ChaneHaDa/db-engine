#include "db/pager.hpp"

#include <cassert>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

void test_write_and_read_same_page() {
    const auto tmp = std::filesystem::temp_directory_path() / "db_engine_pager_test_1.bin";
    std::filesystem::remove(tmp);

    db::Pager pager(tmp);
    std::vector<std::uint8_t> input = {1, 2, 3, 4, 5};
    pager.write_page(0, input);
    pager.flush();

    const auto output = pager.read_page(0);
    assert(output.size() == db::Pager::kPageSize);
    assert(output[0] == 1);
    assert(output[1] == 2);
    assert(output[2] == 3);
    assert(output[3] == 4);
    assert(output[4] == 5);
    assert(output[5] == 0);

    std::filesystem::remove(tmp);
}

void test_sparse_page_read_returns_zeroed_page() {
    const auto tmp = std::filesystem::temp_directory_path() / "db_engine_pager_test_2.bin";
    std::filesystem::remove(tmp);

    db::Pager pager(tmp);
    const auto page = pager.read_page(3);

    assert(page.size() == db::Pager::kPageSize);
    for (const auto byte : page) {
        assert(byte == 0);
    }

    std::filesystem::remove(tmp);
}

void test_page_count_after_non_contiguous_write() {
    const auto tmp = std::filesystem::temp_directory_path() / "db_engine_pager_test_3.bin";
    std::filesystem::remove(tmp);

    db::Pager pager(tmp);
    pager.write_page(2, {9, 9, 9});
    pager.flush();

    assert(pager.page_count() == 3);

    std::filesystem::remove(tmp);
}

void test_write_too_large_page_throws() {
    const auto tmp = std::filesystem::temp_directory_path() / "db_engine_pager_test_4.bin";
    std::filesystem::remove(tmp);

    db::Pager pager(tmp);
    std::vector<std::uint8_t> oversized(db::Pager::kPageSize + 1, 7);

    bool threw = false;
    try {
        pager.write_page(0, oversized);
    } catch (const std::invalid_argument&) {
        threw = true;
    }

    assert(threw);
    std::filesystem::remove(tmp);
}

}  // namespace

int main() {
    test_write_and_read_same_page();
    test_sparse_page_read_returns_zeroed_page();
    test_page_count_after_non_contiguous_write();
    test_write_too_large_page_throws();

    std::cout << "pager_test passed\n";
    return 0;
}
