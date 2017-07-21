#pragma once

#include <string>
#include <fstream>
#include <streambuf>

namespace file {

    std::string read(const std::string& filename) {
        std::ifstream t(filename);
        return std::string((std::istreambuf_iterator<char>(t)),
                           std::istreambuf_iterator<char>());
    }

}
