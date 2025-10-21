#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

#define OZ_TO_ML 30
#define ML_TO_OZ 0.03333

class Ingredient {
public:
    enum class units {
        imperial,
        metric
    };

    Ingredient();
    Ingredient(std::string _name, double _quantity, units unit = units::metric ); 
    Ingredient(std::string _name, bool _present);
    Ingredient(std::string _name, std::string _quantity_string);

    std::string getName() const;
    double getQuantity(units unit = units::metric) const;
    
    std::string getQuantityString() const {return quantity_string;}
    bool present;

    bool operator==(const Ingredient& other) const{
        return 
               name == other.name
            && quantity == other.quantity
            && quantity_string == other.quantity_string;
    } 
private:
    std::string name;
    double quantity; // stored in metric units and can be converted
    std::string quantity_string;
    
};