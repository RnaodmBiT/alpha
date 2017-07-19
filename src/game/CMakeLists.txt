
file(GLOB_RECURSE SOURCE *.cpp *.hpp)
add_executable(alpha ${SOURCE})

target_link_libraries(alpha LINK_PUBLIC system logic) # Add extra third party libraries here

