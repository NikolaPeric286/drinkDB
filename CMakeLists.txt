cmake_minimum_required(VERSION 3.28.3)

project(drinkDB)



set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wpedantic -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../output")

# Force wxWidgets configuration BEFORE adding it as a subdir
# (CACHE+FORCE so the wx subproject actually sees these)
set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(wxBUILD_TESTS OFF CACHE BOOL "" FORCE)

if(UNIX)
  set(wxBUILD_TOOLKIT gtk3 CACHE STRING "" FORCE)
endif()

set(wxUSE_PRECOMP ON CACHE BOOL "" FORCE)
set(wxUSE_NET OFF CACHE BOOL "" FORCE)
set(wxUSE_WEBREQUEST OFF CACHE BOOL "" FORCE)


find_package(wxWidgets COMPONENTS wx::core wx::base )

if(NOT wxWidgets_FOUND)
  message("wxWidgets not found")
  add_subdirectory(external/wxWidgets)
endif()
add_subdirectory(external/json)


add_subdirectory(src)

add_executable(drinkDB src/gui/App.cpp )

if(WIN32)
  target_sources(drinkDB PRIVATE src/resource.rc)
endif()


target_link_libraries(drinkDB PRIVATE
  logic          # from src/CMakeLists.txt
  gui
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/files DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/output)