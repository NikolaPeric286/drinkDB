#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include "Ingredient.hpp"

struct Recipe{
    Recipe();
    Recipe(std::string _name);
    std::string name;
    std::vector<Ingredient> ingredient_vector;

    void printRecipe(Ingredient::units unit = Ingredient::units::metric) const;

};