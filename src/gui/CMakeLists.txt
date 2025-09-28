add_library(gui App.cpp MainFrame.cpp)
target_link_libraries(gui PUBLIC wx::core wx::base logic)