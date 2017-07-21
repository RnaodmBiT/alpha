#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


void Texture::FromFile(const std::string& filename) {
    int x, y, n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 4);

    if (data) {
        SetData(x, y, data);
        stbi_image_free(data);
    } else {
        printf("Error loading texture: %s\n", filename.c_str());
    }
}

