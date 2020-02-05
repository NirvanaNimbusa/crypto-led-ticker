cmake_minimum_required(VERSION 3.8.2)
project(CRYPTO_LED_TICKER VERSION 0.1.0.0 LANGUAGES CXX)

option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(THREADS_PREFER_PTHREAD_FLAG ON)

include(cimg)
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Documentation)
include(httplib)
include(LTO)
include(Misc)
include(rpi-rgb-led-matrix)
include(Warnings)

find_lto(CXX)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

set(SOURCES          # All .cpp files in src/
    src/crypto_compare_api.cpp
        )

set(LIBRARY_NAME engine)  # Default name for the library built from src/*.cpp (change if you wish)

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})
target_include_directories(${LIBRARY_NAME} PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIBRARY_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${LIBRARY_NAME} PUBLIC httplib)
target_link_libraries(${LIBRARY_NAME} PUBLIC cimg)
target_link_libraries(${LIBRARY_NAME} PUBLIC rpi-rgb-led-matrix)
target_link_libraries(${LIBRARY_NAME} PUBLIC ${OPENSSL_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} PUBLIC Threads::Threads)
target_set_warnings(${LIBRARY_NAME} ENABLE ALL AS_ERROR ALL DISABLE Annoying)

add_executable(main app/main.cpp)   # Name of exec. and location of file.
target_link_libraries(main PRIVATE ${LIBRARY_NAME})  # Link the executable to library (if it uses it).
target_set_warnings(main ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
target_enable_lto(main optimized)  # enable link-time-optimization if available for non-debug configurations


set_target_properties(
    ${LIBRARY_NAME} main 
      PROPERTIES 
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED YES 
        CXX_EXTENSIONS NO
)

add_subdirectory(third_party/nlohmann_json)
