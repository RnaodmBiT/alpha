#include "cache.hpp"

ResourceCache Cache;

void ResourceCache::AddLoader(const std::string& filetype, ResourceLoader loader) {
    loaders[filetype] = loader;
}


void ResourceCache::Load(const std::string& key, const std::string& filename) {
    std::string ext = GetExtension(filename);
    if (loaders.count(ext)) {
        cache[key].reset(loaders[ext](filename));
    } else {
        printf("Error: no loader for file '%s'\n", filename.c_str());
    }
}


std::string ResourceCache::GetExtension(const std::string& filename) {
    auto index = filename.find_last_of(".");
    return index == std::string::npos ? std::string() : filename.substr(index + 1);
}


void ResourceCache::Clear() {
    cache.clear();
}

