cmake_minimum_required(VERSION 3.14)
project(quick-ftxui
    LANGUAGES CXX
    VERSION 0.1.0
)

set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

# --- Fetch boost --------------------------------------------------------------
option(QUICK_FTXUI_FETCH_BOOST "Enable boost fetching from GitHub" OFF)

include(FetchContent)

if(QUICK_FTXUI_FETCH_BOOST)
    FetchContent_Declare(Boost
        URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.gz
        TLS_VERIFY true
    )
    FetchContent_Populate(Boost)

    set(EX_PRC "Execute process" CACHE STRING "Used by command line tool.")
    set(EX_PRC_INTERNAL "" CACHE INTERNAL "for internal use only; do not modify")

    if(NOT EX_PRC STREQUAL EX_PRC_INTERNAL)
        if(WIN32)
            execute_process(COMMAND cmd /C "cd ${CMAKE_BINARY_DIR}\\_deps\\boost-src && .\\bootstrap.bat && .\\b2 headers" OUTPUT_VARIABLE RESULT)
        else()
            execute_process(COMMAND sh -c "cd ${CMAKE_BINARY_DIR}/_deps/boost-src && ./bootstrap.sh && ./b2 headers" OUTPUT_VARIABLE RESULT)
        endif()

        set(Boost_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/boost-src")
        set(EX_PRC_INTERNAL ${EX_PRC} CACHE INTERNAL "for internal use only; do not modify")
    endif()
else()
    find_package(Boost REQUIRED)
endif()

# --- Fetch FTXUI --------------------------------------------------------------
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v4.0.0
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
    target_include_directories(tests
        PRIVATE include
        PRIVATE ${Boost_INCLUDE_DIR}
    )
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
    PRIVATE ftxui::component
)

if (QUICK_FTXUI_EXAMPLES)
    add_subdirectory(cpp_examples)
endif()

if(WIN32)
else()
    target_compile_options(quick-ftxui PRIVATE -fsanitize=address)
    target_link_options(quick-ftxui PRIVATE -fsanitize=address)
endif()

install(TARGETS quick-ftxui RUNTIME DESTINATION "bin")
