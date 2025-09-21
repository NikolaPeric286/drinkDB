#include <fstream>
#include <iostream>
#include "../external/json.hpp"
#include "logic/Recipe.hpp"
#include "logic/Ingredient.hpp"
#include "logic/DataManager.hpp"

using json = nlohmann::json;


int main(){

    DataManager::getInstance().LoadJson();

    


    return EXIT_SUCCESS;
}