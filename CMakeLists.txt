cmake_minimum_required(VERSION 3.4)

# Make sure that it is not built in root directory, build inside /build folder
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# CMake project description and project specific settings
project(quick-ftuxi)
enable_language(C)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Check for required packages
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# Specify Build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

######## SOURCES ########
# Add source files and header files
file(GLOB PROJECT_HEADERS include/*.h third-party/vec/*.h third-party/klib/*.h)
file(GLOB PROJECT_SOURCES src/*.c third-party/vec/*.c)
set(PROJECT_FILES
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES})
    
######## TARGETS ########
# Add bison and flex targets
bison_target(parser
            src/parser.y
            ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.c)
flex_target(lexer
            src/lexer.l
            ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.c)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

# Add executables
add_executable(${PROJECT_NAME} ${PROJECT_FILES} ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})
target_compile_definitions(${PROJECT_NAME} ${CMAKE_PROJECT_VERSION} PRIVATE INSTALL_PATH=${CMAKE_INSTALL_PREFIX} VERSION_NUMBER=${CMAKE_PROJECT_VERSION})
target_include_directories(${PROJECT_NAME} ${CMAKE_PROJECT_VERSION} PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third-party>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

######## INSTALL ########
# Install generated binaries
set(bin_destination "bin")
install(TARGETS ${PROJECT_NAME} DESTINATION ${bin_destination})

# Create symlink to remove version name and add install the symlink
install(CODE "execute_process(COMMAND ln -sf ${PROJECT_NAME} ${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})")
install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} DESTINATION ${bin_destination})

