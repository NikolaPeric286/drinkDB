#include "DataManager.hpp"



void DataManager::LoadJson(){

    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "ERROR Failed to open file " << file_path << " \n";
        return ;
    }

    json data = json::parse(file);


    auto recipes = data["recipes"];  
    
    

    for( auto& [recipeName, reciepeData] : recipes.items()){

        std::cout << "Recipe: " << recipeName << "\n";
        Recipe temp_recipe(recipeName);


        auto ingredients = reciepeData["ingredients"];
        for (auto& ingredient : ingredients) {
            for (auto& [name, amount] : ingredient.items()) {
                
                std::string amount_str(amount.get<std::string>());
                std::transform(amount_str.begin(), amount_str.end(), amount_str.begin(), tolower); //forces all lowercase


                double temp_amount = -1; // should be metric units

                if (amount_str.find("oz") != std::string::npos){
                    temp_amount = OZ_TO_ML * std::stod(amount_str.erase(amount_str.length() - 2)); // erases last 2 characters from string then converts to double
                }
                else if (amount_str.find("ml") != std::string::npos){
                    temp_amount = std::stod(amount_str.erase(amount_str.length() - 2));
                }
                else if (amount_str.find("l") != std::string::npos){
                    temp_amount = L_TO_ML * std::stod(amount_str.erase(amount_str.length() - 1));
                }
                else if (amount_str.find("tbsp") != std::string::npos){
                    temp_amount = TBSP_TO_ML * std::stod(amount_str.erase(amount_str.length() - 4));
                }
                else if (amount_str.find("tsp") != std::string::npos){
                    temp_amount = TSP_TO_ML * std::stod(amount_str.erase(amount_str.length() - 3));
                }
                else{
                    temp_amount = std::stod(amount_str.erase(amount_str.length() - 2));
                }
                temp_recipe.ingredient_vector.emplace_back(name, temp_amount);
                std::cout << "  " << name << " : " << amount << "\n";
            }
        }

    }
}