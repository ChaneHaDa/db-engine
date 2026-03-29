#include "db/pager.hpp"

#include <stdexcept>

namespace db {

Pager::Pager(const std::filesystem::path& path) : path_(path) {
}

void Pager::write_page(std::uint32_t, const Page&) {
    throw std::logic_error("TODO: implement Pager::write_page in stage 2");
}

Page Pager::read_page(std::uint32_t) {
    throw std::logic_error("TODO: implement Pager::read_page in stage 2");
}

std::uint32_t Pager::page_count() const {
    throw std::logic_error("TODO: implement Pager::page_count in stage 2");
}

void Pager::flush() {
    throw std::logic_error("TODO: implement Pager::flush in stage 2");
}

std::uint64_t Pager::offset_for_page(std::uint32_t page_id) {
    return static_cast<std::uint64_t>(page_id) * Page::kPageSize;
}

}  // namespace db
