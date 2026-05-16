#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Item {
    int id;
    std::string name;
    int quality;
    std::vector<std::string> type;

    // Future Implementations
    //---------------------------------
    //std::vector<std::string> pools;
    //std::string description;
    //std::vector<std::string> tags;
    //std::string unlock_method;
};

class ItemDatabase {
public:
    // Primary Index (by ID Numbers)
    std::unordered_map<int, Item> byId;

    // Secondary Index (by Item Name)
    std::unordered_map<std::string, int> byName;

    // Load data from CSV
    bool loadFromCSV(const std::string& path);

    // Lookup functions
    const Item& getById(int id) const;
    const Item& getByName(const std::string& name) const;
};