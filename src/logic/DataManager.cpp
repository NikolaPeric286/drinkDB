#include "DataManager.hpp"



void DataManager::LoadRecipes(){

    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "ERROR Failed to open file " << file_path << " \n";
        return ;
    }
    std::cout << "Opened " << file_path << " loading recipes ...\n";
    json data = json::parse(file);


    auto recipes = data["recipes"];  
    
    

    for( auto& [recipeName, reciepeData] : recipes.items()){

        std::cout << "Loaded " << recipeName << "\n";
        Recipe temp_recipe(recipeName);


        auto ingredients = reciepeData["ingredients"];
        for (auto& ingredient : ingredients) {
            for (auto& [name, amount] : ingredient.items()) {
                
                if(amount.is_boolean()){
                    temp_recipe.ingredient_vector.emplace_back(name, true);
                    continue;
                }
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
                    try{
                        temp_amount = std::stod(amount_str.erase(amount_str.length() - 2));
                    }
                    catch(std::invalid_argument& e){
                        std::cerr << "ERROR Invalid argument -> " << amount_str << " \n"; 
                    }
                }
                temp_recipe.ingredient_vector.emplace_back(name, temp_amount);
                //std::cout << "  " << name << " : " << amount << "\n";
            }
        }
        recipe_vector.push_back(temp_recipe);
    }
    std::cout << "done\n";
}


void DataManager::LoadStock(){
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr << "ERROR Failed to open file " << file_path << " \n";
        return ;
    }
    std::cout << "Opened " << file_path << " Loading stock ...\n";
    json data = json::parse(file);

    auto stock = data["stock"];

    bool temp_bool;

    for(auto item : stock){
        for(auto [ingredient_name, Ingredient_data] : item.items()){

                std::cout << "loaded " << ingredient_name << " \n";

                temp_bool = Ingredient_data;
                stock_vector.emplace_back(ingredient_name, temp_bool);
        }
    }

    

    std::cout << "done\n";
}


void DataManager::PrintAvailableRecipes() {
    std::vector<Recipe*> available_recipe_vector;
    
    for(auto it = recipe_vector.begin(); it != recipe_vector.end(); it++){
        for(auto it1 = it->ingredient_vector.begin(); it1 != it->ingredient_vector.end(); it1++){
            if(IsInStock(it1->getName())){
                available_recipe_vector.push_back(&(*it)); 
            }
        }
    }

    for(auto it = available_recipe_vector.begin(); it != available_recipe_vector.end(); it++){
        (*it)->printRecipe(Ingredient::units::metric );
    }
}

bool DataManager::IsInStock(const std::string& ingredient_name) const{
    for(auto it = stock_vector.begin(); it != stock_vector.end(); it++){
        if(it->getName() == ingredient_name){
            return true;
        }
    }
    return false;
 }