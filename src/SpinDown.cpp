#include "SpinDown.hpp"
#include "ItemDB.hpp"

// Spindown by ID
int SpinDown::spinDownById(int id) {
    // Special cases
    if (id == 668)   // Dad's Note
        return -1;

    return id - 1;
}

// Spindown by item name
std::string SpinDown::spinDownByName(const std::string& name) {
    // Access global singleton DB
    ItemDatabase& db = ItemDatabase::instance();

    // Normalize input
    std::string key = standardize(name);

    // Lookup original item
    const Item* item = db.getByName(key);
    if (!item)
        return "Item not found";

    int id = item->id;

    // Perform spindown
    int newId = spinDownById(id);
    if (newId <= 0)
        return "Cannot be spun down";

    // Lookup new item
    const Item* newItem = db.getById(newId);
    if (!newItem)
        return "invalid spindown result";

    // Return titlecased name for UI
    return newItem->name;
}

// Return the next N Spindowns
std::vector<const Item*> SpinDown::nextN(const Item* start, int count, bool challengeMode, bool dailyMode) {
    std::vector<const Item*> results;
    int id = start->id;
    for (int i = 0; i < count; i++) {
        while(true) {
            id = spinDownById(id);
            if (id <= 0)
                return results;

            const Item* item = ItemDatabase::instance().getById(id);
            if (!item)
                return results;

            if (SpinDown::isValid(item, challengeMode, dailyMode)) {
                results.push_back(item);
                break;
            }
        }
    }

    return results;
}

bool SpinDown::isValid(const Item* item, bool challengeMode, bool dailyMode) {
    if (!item)
        return false;
    if (challengeMode && item->bannedInChallenge)
        return false;
    if (dailyMode && item->bannedInChallenge)
        return false;
    
    return true;
}