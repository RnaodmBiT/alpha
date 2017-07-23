
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCE *.cpp *.hpp)
add_executable(alpha ${SOURCE})

target_link_libraries(alpha LINK_PUBLIC system logic SDL2-static SDL2main assimp glew ${OPENGL_LIBRARIES}) # Add extra third party libraries here

