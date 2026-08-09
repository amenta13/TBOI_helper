#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "ItemDB.hpp"

ItemDatabase& ItemDatabase::instance() {
    static ItemDatabase db;
    return db;
}

// Parse string
std::vector<std::string> split(const std::string& original_str, char delimiter){
    std::vector<std::string> parsed_str;
    std::stringstream ss(original_str);
    std::string part;

    while (std::getline(ss, part, delimiter)) {
        if (!part.empty())
            parsed_str.push_back(part);
    }
    return parsed_str;
}

std::string stripQuotes(const std::string& quoted_str) {
    if (quoted_str.size() >= 2 && quoted_str.front() == '"' && quoted_str.back() == '"')
        return quoted_str.substr(1, quoted_str.size() - 2);
    return quoted_str;
}

// Load data from csv file
bool ItemDatabase::loadFromCSV(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::string line;
    int challenge_list[] = {161, 311, 332, 482, 636};
    int daily_list[] = {482, 636};

    // Skip header rows
    std::getline(file, line);
    std::getline(file, line);

    while (std::getline(file, line)) {

        // Check for blank line and skip
        if (line.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;
        //std::cout << "LINE: " << line << "\n";   // DEBUG

        std::stringstream ss(line);
        std::string idStr, name, qualityStr, typeStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, qualityStr, ',');
        std::getline(ss, typeStr);

        //std::cout << "  idStr=" << idStr << "  qualityStr=" << qualityStr << "\n";  // DEBUG

        Item item;
        item.id = std::stoi(idStr);
        item.name = name;
        item.quality = std::stoi(qualityStr);
        item.type = split(stripQuotes(typeStr), ',');

        if (inList(item.id, challenge_list, sizeof(challenge_list) / sizeof(challenge_list[0])))
            item.bannedInChallenge = true;

        if (inList(item.id, daily_list, sizeof(daily_list) / sizeof(daily_list[0])))
            item.bannedInDaily = true;

        // Make 3 Digit ID#
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << item.id;
        std::string id3 = oss.str();
        item.imagePath = "src/images/item" + id3 + ".png";

        byId[item.id] = item;
        std::string key = standardize(item.name);
        byName[key] = item.id;
    }

    return true;
}

const Item* ItemDatabase::getById(int id) const {
    auto it = byId.find(id);
    if (it == byId.end())
        return nullptr;
    return &it->second;
}

const Item* ItemDatabase::getByName(const std::string& name) const {
    std::string key = standardize(name);

    auto item_name = byName.find(key);
    if (item_name == byName.end())
        return nullptr;

    int id = item_name->second;

    auto item_id = byId.find(id);
    if (item_id == byId.end())
        return nullptr;

    return &item_id->second;
}

// Creates a list of all item names
std::vector<std::string> ItemDatabase::getAllItemNames() const {
    std::vector<std::string> names;
    names.reserve(byId.size());

    for (const auto& [id, item] : byId)
        names.push_back(item.name);

    return names;
}

// Prints out every item by ID order
void ItemDatabase::printAll() const {
    std::vector<int> ids;
    ids.reserve(byId.size());

    for (const auto& [id, _] : byId)
        ids.push_back(id);

    std::sort(ids.begin(), ids.end());

    for (int id : ids) {
        const Item& item = byId.at(id);

        std::cout << id << " - " << titlecase(item.name)
                  << " - Q" << item.quality << "\n";

        for (const auto& t : item.type)
            std::cout << "    - " << titlecase(t) << "\n";

        std::cout << "\n";
    }
}

// Search as you type function 
std::vector<const Item*> ItemDatabase::searchByPrefix(const std::string& query) const {
    std::vector<const Item*> results;

    std::string key = standardize(query);

    for (const auto& [id, item] : byId) {
        std::string nameKey = standardize(item.name);

        if (nameKey.rfind(key, 0) == 0) { // starts with
            results.push_back(&item);
        }
    }

    return results;
}


// Convert string to all lowercase characters, remove punctuation, whitespaces, leading articles
std::string standardize(const std::string& input_str) {
    std::string out;
    out.reserve(input_str.size());

    // Lowercase everything
    for (char c : input_str)
        out += std::tolower(static_cast<unsigned char>(c));

    // Remove punctuation
    out.erase(std::remove_if(out.begin(), out.end(), [](unsigned char c) {return std::ispunct(c);}), out.end());

    // Collapse whitespace
    std::string collapsed;
    collapsed.reserve(out.size());
    bool inSpace = false;

    for (char c : out) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!inSpace)
                collapsed += ' ';
            inSpace = true;
        } else {
            collapsed += c;
            inSpace = false;
        }
    }

    // Trim leading/trailing spaces
    size_t start = collapsed.find_first_not_of(' ');
    size_t end = collapsed.find_last_not_of(' ');

    if (start == std::string::npos)
        return "";

    std::string trimmed = collapsed.substr(start, end - start + 1);

    // Remove leading "the " or "a "
    if (trimmed.rfind("the ", 0) == 0)
        trimmed = trimmed.substr(4);
    else if (trimmed.rfind("a ", 0) == 0)
        trimmed = trimmed.substr(2);

    // Remove all spaces entirely
    trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(), [](unsigned char c) {return std::isspace(c);}), trimmed.end());

    return trimmed;
}

// Convert string to titlecase (Following convention of how titles are capitalized)
std::string titlecase(const std::string& input_str) {
    std::string cap_str = input_str;
    for (size_t i = 0; i < cap_str.size(); i++) {
        if (i == 0 || cap_str[i - 1] == ' ')
            cap_str[i] = std::toupper(static_cast<unsigned char>(cap_str[i]));
        else 
            cap_str[i] = std::tolower(static_cast<unsigned char>(cap_str[i]));
    }
    return cap_str;
}

bool inList(int target, const int *list, int size) {
    for (int i = 0; i < size; i ++) {
        if (list[i] == target)
            return true;
    }
    return false;
}