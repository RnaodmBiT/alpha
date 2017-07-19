
file(GLOB_RECURSE SOURCE *.cpp *.hpp)

add_library(system ${SOURCE})
target_include_directories(system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

