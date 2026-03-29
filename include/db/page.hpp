#pragma once

#include <cstddef>
#include <cstdint>

namespace db {

class Page {
public:
    static constexpr std::size_t kPageSize = 4096;

    Page();

    std::uint8_t* data();
    const std::uint8_t* data() const;
    void reset();

private:
    std::uint8_t bytes_[kPageSize];
};

}  // namespace db
