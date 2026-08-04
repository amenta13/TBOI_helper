#pragma once
#include <string>
#include <vector>
#include "ItemDB.hpp"

class SpinDown {
public:
    static int spinDownById(int id);
    static std::string spinDownByName(const std::string& name);
    static std::vector<const Item*> nextN(const Item* start, int count, bool challengeMode, bool dailyMode);
    static bool isValid(const Item* item, bool challengeMode, bool dailyMode);

};
