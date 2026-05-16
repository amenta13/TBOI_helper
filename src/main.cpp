#include <iostream>
#include <fstream>
#include <sstream>
#include "SpinDown.hpp"
#include "ItemDB.hpp"
#include <filesystem>


int main(){
    
    std::cout << "Working directory: " << std::filesystem::current_path() << "\n";
    ItemDatabase db;
    if (!db.loadFromCSV("data/isaac_items.csv")) {
        std::cout << "Failed to load CSV\n";
        return 1;
    }
    std::cout << "Loaded " << db.byId.size() << " items\n";

    // Test lookup by ID
    const Item& it = db.getById(1);
    std::cout << "ID 1: " << it.name << "\n";
    std::cout << "Quality: " << it.quality << "\n";
    std::cout << "Types:\n";
    for (const auto& t : it.type)
        std::cout << " - " << t << "\n";

    // Test lookup by name
    const Item& it2 = db.getByName("The Sad Onion");
    std::cout << "\nLookup by name: " << it2.name << "\n";

    return 0;
}