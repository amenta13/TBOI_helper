#include <iostream>
#include "SpinDown.hpp"

int SpinDown(std::string item_name) {

    int id = 1; // Replace with searching for item ID from name
    if (id == 668)
        std::cout << "Dad's Note cannot be Spun Down!";
    else if (id-1 < 1)
        std::cout << "Sad Onion cannot be Spun Down!";
    else
        std::cout << id-1;// Replace with searching item name from ID
    
    return 1;
}