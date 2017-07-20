
include_directories(../system)
file(GLOB_RECURSE SOURCE *.cpp *.hpp)

add_library(logic ${SOURCE})
target_include_directories(logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


