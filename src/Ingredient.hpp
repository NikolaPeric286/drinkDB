#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#define OZ_TO_ML 29.5735
#define ML_TO_OZ 0.033814

class Ingredient {
public:
    enum class units {
        imperial,
        metric
    };

    Ingredient();
    Ingredient(std::string _name, double _quantity, units unit = units::metric ); 

    std::string getName() const;
    double getQuantity(units unit = units::metric) const;
   
private:
    std::string name;
    double quantity; // stored in metric units and can be converted
};