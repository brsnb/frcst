cmake_minimum_required(VERSION 3.14)

project(frcst)

add_compile_options(-W -Wall -Wpedantic)

find_package(nlohmann_json 3.6.1 REQUIRED)
find_package(CURL REQUIRED)

add_executable(frcst
    src/forecast.hpp
    src/forecast.cpp
    src/location.hpp
    src/location.cpp
    src/request.hpp
    src/request.cpp
    src/main.cpp
    )

target_link_libraries(frcst PRIVATE nlohmann_json::nlohmann_json
                            PRIVATE curl
    )
