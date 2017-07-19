

# Build the third party libraries
add_subdirectory(libs/SDL2-2.0.4)
add_subdirectory(libs/glew)
add_subdirectory(libs/assimp-3.3.1)

include_directories(libs/SDL2-2.0.4/include
                    libs/glew
                    libs/stb)

# Build the individual game systems
add_subdirectory(system)
add_subdirectory(logic)
add_subdirectory(game)

