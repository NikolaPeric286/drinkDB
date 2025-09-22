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

}