#include <fstream>
#include <iostream>
#include "../external/json/include/nlohmann/json.hpp"
#include "logic/Recipe.hpp"
#include "logic/Ingredient.hpp"
#include "logic/DataManager.hpp"




int main(){

    DataManager::getInstance().LoadRecipes();
    DataManager::getInstance().LoadStock();
    DataManager::getInstance().PrintAvailableRecipes();


    


    return EXIT_SUCCESS;
}