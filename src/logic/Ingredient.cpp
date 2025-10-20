#include "Ingredient.hpp"


Ingredient::Ingredient() : name("NONAME"), quantity(-1), present(false), quantity_string("NULL") {}

Ingredient::Ingredient(std::string _name, bool _present): present(_present){
    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;
}

Ingredient::Ingredient(std::string _name, std::string _quantity_string) : present(true), quantity(-1){
    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;
    std::transform(_quantity_string.begin(), _quantity_string.end(), _quantity_string.begin(), tolower);
    quantity_string = _quantity_string;
}

Ingredient::Ingredient(std::string _name, double _quantity, units unit) : quantity_string("NULL") {

    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;

    if(_quantity > 0){
        present = true;
    }


    switch(unit){
    case units::imperial:
        quantity = OZ_TO_ML * _quantity;
        break;
    case units::metric:
        quantity = _quantity;
        break;
    }

}

double Ingredient::getQuantity(units unit) const{
    switch(unit){
    case units::metric:
        return quantity;
    case units::imperial:
        return quantity * ML_TO_OZ;
    }
}

std::string Ingredient::getName() const{
    return name;
}
