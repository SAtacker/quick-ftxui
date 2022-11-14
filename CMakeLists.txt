cmake_minimum_required(VERSION 3.14)
project(quick-ftxui
    LANGUAGES CXX
    VERSION 0.1.0
)

find_package(Boost REQUIRED COMPONENTS regex)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)

if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------
if(QUICK_FTXUI_TESTS)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.0.1 # or a later release
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable(tests tests/test1.cpp)
    target_link_libraries(tests 
        PRIVATE Catch2::Catch2WithMain
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
    )
    target_include_directories(tests PRIVATE include)
    include(CTest)
    include(Catch)
    catch_discover_tests(tests)
endif()

add_executable(quick-ftxui src/quick-ftxui.cpp)
target_include_directories(quick-ftxui 
    PRIVATE include 
    PRIVATE ${Boost_INCLUDE_DIR} 
    PRIVATE ${ftxui_SOURCE_DIR}
)

target_link_libraries(quick-ftxui
    PRIVATE ${Boost_LIBRARIES}
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component # Not needed for this example.
)

target_compile_options(quick-ftxui PRIVATE -fsanitize=address)
target_link_options(quick-ftxui PRIVATE -fsanitize=address)

install(TARGETS quick-ftxui RUNTIME DESTINATION "bin")
