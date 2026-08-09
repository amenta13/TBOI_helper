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
    std::string imagePath;

    // Tags
    bool bannedInChallenge = false;
    bool bannedInDaily = false;

    // Future Implementations
    //---------------------------------
    //std::vector<std::string> pools;
    //std::string description;
    //std::vector<std::string> tags;
    //std::string unlock_method;
};

class ItemDatabase {
public:
    // Singleton accessor
    static ItemDatabase& instance();

    // Load data from CSV
    bool loadFromCSV(const std::string& path);

    // Lookup functions
    const Item* getById(int id) const;
    const Item* getByName(const std::string& name) const;
    std::vector<const Item*> searchByPrefix(const std::string& query) const;

    // Create list of all items
    std::vector<std::string> getAllItemNames() const;

    // Print all items
    void printAll() const;

private:
    // Singleton: private constructor
    ItemDatabase() = default;

    // Primary Index (by ID Numbers)
    std::unordered_map<int, Item> byId;

    // Secondary Index (by Item Name)
    std::unordered_map<std::string, int> byName;
};

// Functions
std::vector<std::string> split(const std::string& original_str, char delimiter);
std::string stripQuotes(const std::string& s);
std::string standardize(const std::string& input_str);
std::string titlecase(const std::string& input_str);
bool inList(int target, const int *list, int size);