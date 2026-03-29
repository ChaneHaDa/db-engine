cmake_minimum_required(VERSION 3.16)
project(db_engine_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(db_engine
    src/db/page.cpp
    src/db/pager.cpp
)

target_include_directories(db_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(page_test
    tests/page_test.cpp
)

target_link_libraries(page_test PRIVATE db_engine)

include(CTest)
enable_testing()
add_test(NAME page_test COMMAND page_test)
