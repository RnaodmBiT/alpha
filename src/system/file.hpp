#pragma once

#include <string>
#include <fstream>
#include <streambuf>

namespace File {

    static std::string Read(const std::string& filename) {
        std::ifstream t(filename);
        return std::string((std::istreambuf_iterator<char>(t)),
                           std::istreambuf_iterator<char>());
    }


    static std::string GetExtension(const std::string& filename) {
        auto index = filename.find_last_of(".");
        auto slash = filename.find_last_of("/");

        if (index == std::string::npos || index < slash) {
            return std::string();
        }

        return filename.substr(index + 1);
    }


    static std::string GetPath(const std::string& filename) {
        auto slash = filename.find_last_of("/");

        if (slash == std::string::npos) {
            return std::string();
        }

        return filename.substr(0, slash + 1);
    }

}
