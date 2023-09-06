cmake_minimum_required(VERSION 3.14)

add_executable(quick_ftxui_example example.cpp)
target_link_libraries(quick_ftxui_example
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

target_include_directories(quick_ftxui_example
    PRIVATE ../include
)