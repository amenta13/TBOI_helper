#include "SpinDown.hpp"
#include "ItemDB.hpp"

// Spindown by ID
int SpinDown::byId(int id) {
    // Special cases
    if (id == 668)   // Dad's Note
        return -1;

    if (id <= 1)     // Sad Onion
        return -1;

    return id - 1;
}

// Spindown by item name
std::string SpinDown::byName(const std::string& name) {
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
    int newId = byId(id);
    if (newId < 0)
        return "Cannot be spun down";

    // Lookup new item
    const Item* newItem = db.getById(newId);
    if (!newItem)
        return "invalid spindown result";

    // Return titlecased name for UI
    return newItem->name;
}

// Return the next N Spindowns
std::vector<const Item*> SpinDown::nextN(const Item* start, int count) {
    std::vector<const Item*> results;
    int id = start->id;

    for (int i = 0; i < count; i++) {
        id = byId(id);
        if (id < 0) break;

        const Item* item = ItemDatabase::instance().getById(id);
        if (!item) break;

        results.push_back(item);
    }

    return results;
}