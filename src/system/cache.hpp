#pragma once
#include <string>
#include <map>
#include <functional>
#include <memory>

class IResource {
public:
    virtual ~IResource() { }
};


typedef std::function<IResource*(const std::string&)> ResourceLoader;

class ResourceCache {
public:

    void AddLoader(const std::string& filetype, ResourceLoader loader);

    void Load(const std::string& key, const std::string& filename);

    template <typename T>
    const T* Get(const std::string& key) {
        if (cache.count(key)) {
            return dynamic_cast<T*>(cache[key].get());
        }
        return nullptr;
    }

    void Clear();

public:

    std::string GetExtension(const std::string& filename);

    std::map<std::string, ResourceLoader> loaders;
    std::map<std::string, std::unique_ptr<IResource>> cache;
};


extern ResourceCache Cache;


