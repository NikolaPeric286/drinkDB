#include <fstream>
#include <iostream>
#include "../external/json.hpp"
#include "Recipe.hpp"
#include "Ingredient.hpp"

using json = nlohmann::json;


int main(){

    std::ifstream file("files/data.json");

    if(!file.is_open()){
        std::cerr << "file failed to open!\n";
        return EXIT_FAILURE;
    }

    json data = json::parse(file);


    auto recipes = data["recipes"];
    
    for( auto& [recipeName, reciepeData] : recipes.items()){
        std::cout << "Recipe: " << recipeName << "\n";

        auto ingredients = reciepeData["ingredients"];
        for (auto& ingredient : ingredients) {
            for (auto& [name, amount] : ingredient.items()) {
                std::cout << "  " << name << " : " << amount << "\n";
            }
        }

    }
    


    return EXIT_SUCCESS;
}