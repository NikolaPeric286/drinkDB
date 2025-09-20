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

    Ingredient::Ingredient();
    Ingredient::Ingredient(std::string _name, double _quantity, units unit = units::metric ); 

    std::string getName();
    std::string getQuantity_imp();
    std::string getQuantity_met();
private:
    std::string name;
    double quantity; // stored in metric units and can be converted
};