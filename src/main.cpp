#include <iostream>
#include <fstream>
#include <sstream>
#include "SpinDown.hpp"
#include "ItemDB.hpp"
#include <filesystem>


int main(){
    
    //std::cout << "Working directory: " << std::filesystem::current_path() << "\n";    // DEBUG

    ItemDatabase db;
    if (!db.loadFromCSV("data/isaac_items.csv")) {
        std::cout << "Failed to load CSV\n";
        return 1;
    }
    std::cout << "Loaded " << db.byId.size() << " items\n";

    // Get user input
    int userID;
    std::cout << "Enter Item ID: ";
    std::cin >> userID;

    // Search for userID
    const Item& it = db.getById(userID);

    // Return the item with the userID and its characteristics
    std::cout << "ID: " << it.id << "\n";
    std::cout << "Name: " << it.name << "\n";
    std::cout << "Types:\n";
    for (const auto& a : it.type)
        std::cout << " - " << a << "\n";

    // Lookup by name
    // Get user input
    std::string user_str;
    std::cout << "Enter Item Name: ";
    std::cin >> user_str;

    // Search for user_str
    const Item& it2 = db.getByName(user_str);

    // Return the item with the user_str and its characteristics
    std::cout << "ID: " << it2.id << "\n";
    std::cout << "Name: " << it2.name << "\n";
    std::cout << "Quality: " << it2.quality << "\n";
    std::cout << "Types:\n";
    for (const auto& b : it2.type)
        std::cout << " - " << b << "\n";

    return 0;
}