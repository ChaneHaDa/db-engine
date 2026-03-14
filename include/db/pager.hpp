#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace db {

class Pager {
public:
    static constexpr std::size_t kPageSize = 4096;

    explicit Pager(const std::filesystem::path& path);
    ~Pager();

    Pager(const Pager&) = delete;
    Pager& operator=(const Pager&) = delete;

    void write_page(std::uint32_t page_id, const std::vector<std::uint8_t>& data);
    std::vector<std::uint8_t> read_page(std::uint32_t page_id);

    std::uint32_t page_count() const;
    void flush();

private:
    std::filesystem::path path_;
    std::fstream file_;

    static std::streampos offset_for_page(std::uint32_t page_id);
    void ensure_open();
};

}  // namespace db
