#include "db/pager.hpp"

#include <algorithm>
#include <stdexcept>

namespace db {

Pager::Pager(const std::filesystem::path& path) : path_(path) {
    ensure_open();
}

Pager::~Pager() {
    flush();
    if (file_.is_open()) {
        file_.close();
    }
}

void Pager::write_page(std::uint32_t page_id, const std::vector<std::uint8_t>& data) {
    if (data.size() > kPageSize) {
        throw std::invalid_argument("page data exceeds page size");
    }

    std::vector<std::uint8_t> page(kPageSize, 0);
    std::copy(data.begin(), data.end(), page.begin());

    file_.seekp(offset_for_page(page_id));
    file_.write(reinterpret_cast<const char*>(page.data()), static_cast<std::streamsize>(page.size()));

    if (!file_) {
        throw std::runtime_error("failed to write page");
    }
}

std::vector<std::uint8_t> Pager::read_page(std::uint32_t page_id) {
    std::vector<std::uint8_t> page(kPageSize, 0);

    file_.seekg(offset_for_page(page_id));
    file_.read(reinterpret_cast<char*>(page.data()), static_cast<std::streamsize>(page.size()));

    const std::streamsize bytes_read = file_.gcount();
    if (bytes_read < static_cast<std::streamsize>(kPageSize)) {
        file_.clear();
        std::fill(page.begin() + std::max<std::streamsize>(0, bytes_read), page.end(), 0);
    }

    if (!file_ && !file_.eof()) {
        throw std::runtime_error("failed to read page");
    }

    return page;
}

std::uint32_t Pager::page_count() const {
    if (!std::filesystem::exists(path_)) {
        return 0;
    }

    const auto size = std::filesystem::file_size(path_);
    return static_cast<std::uint32_t>((size + kPageSize - 1) / kPageSize);
}

void Pager::flush() {
    if (file_.is_open()) {
        file_.flush();
    }
}

std::streampos Pager::offset_for_page(std::uint32_t page_id) {
    return static_cast<std::streampos>(page_id) * static_cast<std::streampos>(kPageSize);
}

void Pager::ensure_open() {
    if (!std::filesystem::exists(path_)) {
        std::ofstream bootstrap(path_, std::ios::binary);
        if (!bootstrap) {
            throw std::runtime_error("failed to create pager file");
        }
    }

    file_.open(path_, std::ios::binary | std::ios::in | std::ios::out);
    if (!file_.is_open()) {
        throw std::runtime_error("failed to open pager file");
    }
}

}  // namespace db
