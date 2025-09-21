#include "Recipe.hpp"




Recipe::Recipe() : name("NO_NAME"){}

Recipe::Recipe(std::string _name) {
    std::transform(_name.begin(), _name.end(), _name.begin(), tolower);
    name = _name;
}