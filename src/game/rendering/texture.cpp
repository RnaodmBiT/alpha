#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <chaiscript.hpp>


// 2D Texture

Texture* Texture::LoadResource(const std::string& filename) {
    Texture* texture = new Texture;
    texture->FromFile(filename);
    return texture;
}


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


// Cube Map

CubeMap* CubeMap::LoadResource(const std::string& filename) {
    json::JSON node = json::JSON::Load(File::Read(filename));

    std::string path = File::GetPath(filename);
    std::string left = path + node["left"].to_string();
    std::string right = path + node["right"].to_string();
    std::string top = path + node["top"].to_string();
    std::string bottom = path + node["bottom"].to_string();
    std::string front = path + node["front"].to_string();
    std::string back = path + node["back"].to_string();

    CubeMap* cube = new CubeMap;
    cube->FromFiles(left, right, top, bottom, front, back);

    return cube;
}


void CubeMap::FromFiles(const std::string& left, const std::string& right, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back) {

    int x, y, n;
    unsigned char* data;

    std::string files[] = { left, right, top, bottom, front, back };
    GLenum sides[] = { GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                       GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                       GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                       GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                       GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                       GL_TEXTURE_CUBE_MAP_POSITIVE_Z };


    for (int i = 0; i < 6; ++i) {
        data = stbi_load(files[i].c_str(), &x, &y, &n, 4);
        if (!data) {
            printf("Error: loading cube map side '%s'\n", files[i].c_str());
            continue;
        }

        SetData(sides[i], x, y, data);
        stbi_image_free(data);
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}
