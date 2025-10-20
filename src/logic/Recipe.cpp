#include "Recipe.hpp"




Recipe::Recipe() : name("NO_NAME"){}

Recipe::Recipe(std::string _name) {
    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;
}


void Recipe::printRecipe(Ingredient::units unit) const{
    std::cout << name << ": \n";
    std::cout << "\tIngredients:\n";

    
    for(auto it = ingredient_vector.begin(); it != ingredient_vector.end(); it++){
        std::cout << "\t\t";
        if(it->getQuantity() == -1 && it->present){
            std::cout << it->getQuantityString();
        }
        else{
            std::cout  <<  std::round(it->getQuantity(unit)*100)/100 << (unit == Ingredient::units::metric ? "ml" : "oz" );
        }


        std::cout << " of " << it->getName() << "\n";
    }

    std::cout << "\tGarnish: " << garnish << "\n";
    std::cout << "\tGlass: " << glass << "\n";
    std::cout << "\tExtra Notes: " << extra_notes << "\n";
}

json Recipe::getJsonObject()  const{
    json json_object;

    json temp_ingredient;
    
    double temp_quantity = 0;
    std::string temp_quantity_string = "";
    for(auto it = ingredient_vector.begin(); it != ingredient_vector.end(); it++){

        temp_quantity = std::round(it->getQuantity(Ingredient::units::imperial)*100)/100;
        
        temp_quantity_string = std::to_string( temp_quantity);
        remove_trailing_zeros(temp_quantity_string);

        
        if(temp_quantity > 0){
            temp_ingredient[it->getName()] = temp_quantity_string + "oz";
        }
        else{
            temp_ingredient[it->getName()] = it->getQuantityString();
        }
        

        json_object["ingredients"].push_back(temp_ingredient);   
        temp_ingredient.clear();
    }

    json_object["garnish"] = garnish;
    json_object["glass"] = glass;
    json_object["extra notes"] = extra_notes;

    return json_object;
}
   