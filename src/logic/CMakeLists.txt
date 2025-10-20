add_library(logic DataManager.cpp Ingredient.cpp Recipe.cpp trailing_zeros.cpp)
target_link_libraries(logic PUBLIC nlohmann_json::nlohmann_json)