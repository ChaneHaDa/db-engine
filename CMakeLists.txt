cmake_minimum_required(VERSION 3.16)
project(db_engine_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(db_engine
    src/db/pager.cpp
)

target_include_directories(db_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(pager_test
    tests/pager_test.cpp
)

target_link_libraries(pager_test PRIVATE db_engine)

include(CTest)
enable_testing()
add_test(NAME pager_test COMMAND pager_test)
