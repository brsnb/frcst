cmake_minimum_required(VERSION 3.14)

project(frcst)

add_compile_options(-W -Wall)

find_package(nlohmann_json 3.6.1 REQUIRED)
find_package(CURL 7.64 REQUIRED)
find_package(Boost 1.69  REQUIRED COMPONENTS program_options)

add_executable(frcst
    src/forecast.hpp
    src/forecast.cpp
    src/frcst_util.hpp
    src/location.hpp
    src/location.cpp
    src/request.hpp
    src/request.cpp
    src/main.cpp
    )

target_compile_features(frcst PUBLIC cxx_std_17)

target_link_libraries(frcst PRIVATE nlohmann_json::nlohmann_json
                            PRIVATE curl
                            PRIVATE Boost::program_options
    )
