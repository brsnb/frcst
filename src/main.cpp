#include <curl/curl.h>
#include <iostream>

#include "location.hpp"

int main(int argc, char **argv)
{
    // init here for now?
    curl_global_init(CURL_GLOBAL_ALL);
    std::cout << "Hello world!\n";

    frcst::Location loc{std::string{"Las Vegas"}, std::string{"Nevada"}, std::string{"United States"}};

    std::cout << "City: " << loc.get_city() << std::endl;
    std::cout << "coords: " << loc.get_coords().first << ", " << loc.get_coords().second << std::endl;

    // clean up here for now?
    curl_global_cleanup();
    return 0;
}