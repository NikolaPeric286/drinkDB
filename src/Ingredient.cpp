#include "Ingredient.hpp"


Ingredient::Ingredient() : name("NONAME"), quantity(-1) {

}
Ingredient::Ingredient(std::string _name, double _quantity, units unit)  {

    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;

    switch(unit){
    case units::imperial:
        quantity = OZ_TO_ML * _quantity;
        break;
    case units::metric:
        quantity = _quantity;
        break;
    }

}

std::string Ingredient::getName(){

}
std::string Ingredient::getQuantity_imp(){

}
std::string Ingredient::getQuantity_met(){

}