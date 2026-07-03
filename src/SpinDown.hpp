#pragma once
#include <string>

class SpinDown {
public:
    static int byId(int id);
    static std::string byName(const std::string& name);
};
