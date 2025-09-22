#include "Recipe.hpp"




Recipe::Recipe() : name("NO_NAME"){}

Recipe::Recipe(std::string _name) {
    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;
}


void Recipe::printRecipe(Ingredient::units unit) const{
    std::cout << name << ": \n";
    std::cout << "Ingredients:\n";
    for(auto it = ingredient_vector.begin(); it != ingredient_vector.end(); it++){

        std::cout << "\t" << std::round( it->getQuantity(unit) ) << (unit == Ingredient::units::metric ? "ml" : "oz" )<< " of " << it->getName() << "\n";
    }

}