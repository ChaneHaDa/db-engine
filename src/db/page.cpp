#include "db/page.hpp"

#include <cstring>

namespace db {

Page::Page() : bytes_{} {
}

std::uint8_t* Page::data() {
    return bytes_;
}

const std::uint8_t* Page::data() const {
    return bytes_;
}

void Page::reset() {
    std::memset(bytes_, 0, sizeof(bytes_));
}

}  // namespace db
