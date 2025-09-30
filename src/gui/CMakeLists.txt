add_library(gui App.cpp MainFrame.cpp MainFrame_Events.cpp)
target_link_libraries(gui PUBLIC wx::core wx::base logic)