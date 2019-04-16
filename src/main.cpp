#include <curl/curl.h>
#include <iostream>

int main(int argc, char **argv)
{
    // init here for now?
    curl_global_init(CURL_GLOBAL_ALL);
    std::cout << "Hello world!\n";

    // clean up here for now?
    
    return 0;
}