#pragma once

#include <cstdint>
#include <filesystem>

#include "db/page.hpp"

namespace db {

class Pager {
public:
    explicit Pager(const std::filesystem::path& path);

    Pager(const Pager&) = delete;
    Pager& operator=(const Pager&) = delete;

    void write_page(std::uint32_t page_id, const Page& page);
    Page read_page(std::uint32_t page_id);

    std::uint32_t page_count() const;
    void flush();

private:
    std::filesystem::path path_;

    static std::uint64_t offset_for_page(std::uint32_t page_id);
};

}  // namespace db
