#pragma once
#include <string>
#include <vector>
#include "ItemDB.hpp"

class SpinDown {
public:
    static int byId(int id);
    static std::string byName(const std::string& name);
    static std::vector<const Item*> nextN(const Item* start, int count);
};
