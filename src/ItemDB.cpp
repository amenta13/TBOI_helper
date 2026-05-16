#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "ItemDB.hpp"



// Parse string
static std::vector<std::string> split(const std::string& original_str, char delimiter){
    std::vector<std::string> parsed_str;
    std::stringstream ss(original_str);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        if (!part.empty())
            parsed_str.push_back(part);
    }
    return parsed_str;
}

// Load data from csv file
bool ItemDatabase::loadFromCSV(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::string line;

    // Skip header rows
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line)) {
        //std::cout << "LINE: " << line << "\n";   // DEBUG

        std::stringstream ss(line);
        std::string idStr, name, qualityStr, typeStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qualityStr, ',');
        std::getline(ss, typeStr, ',');

        //std::cout << "  idStr=" << idStr << "  qualityStr=" << qualityStr << "\n";  // DEBUG

        Item item;
        item.id = std::stoi(idStr);
        item.name = name;
        item.quality = std::stoi(qualityStr);
        item.type = split(typeStr, ',');   // split TYPE, not quality

        byId[item.id] = item;
        byName[item.name] = item.id;
    }

    return true;
}

const Item& ItemDatabase::getById(int id) const {
    return byId.at(id);
}

const Item& ItemDatabase::getByName(const std::string& name) const {
    return byId.at(byName.at(name));
}