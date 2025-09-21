#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Recipe.hpp"
#include "Ingredient.hpp"
#include "../external/json.hpp"

#define OZ_TO_ML 29.5735
#define TBSP_TO_ML 14.7868
#define L_TO_ML 1000
#define TSP_TO_ML 4.92892

using json = nlohmann::json;

class DataManager{

public:
    //singleton code
    DataManager(const DataManager&) = delete;
    DataManager operator=(DataManager& ) = delete;
    static DataManager& getInstance(){
        static DataManager DataManager_instance = DataManager();
        return DataManager_instance;
    }

    void LoadJson();
    void SetPath(const std::string& path);

private:
    DataManager(std::string path = "files/data.json") : file_path(path){}

    std::string file_path;
    std::vector<Recipe> recipe_vector;


};

