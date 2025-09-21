add_subdirectory(logic)


add_executable(drinkDB main.cpp )
target_link_libraries( drinkDB PRIVATE logic)
