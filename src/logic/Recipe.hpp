#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "Ingredient.hpp"
#include "trailing_zeros.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Recipe{
    Recipe();
    Recipe(std::string _name);
    std::string name;
    std::vector<Ingredient> ingredient_vector;
    std::string garnish;
    std::string glass;
    std::string extra_notes;

    void printRecipe(Ingredient::units unit = Ingredient::units::metric) const;

    json getJsonObject() const;

    bool operator==(const Recipe& other) const {
        return 
               name == other.name
            && garnish == other.garnish
            && glass == other.glass
            && extra_notes ==  other.extra_notes
            && ingredient_vector == other.ingredient_vector;
    }

};