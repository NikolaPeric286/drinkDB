#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Ingredient.hpp"

struct Recipe{
    Recipe();
    Recipe(std::string _name);
    std::string name;
    std::vector<Ingredient> ingredient_vector;


};