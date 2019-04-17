#include <curl/curl.h>
#include <iostream>
#include <curl/curl.h>

int main(int argc, char **argv)
{
    // init here for now?
    curl_global_init(CURL_GLOBAL_ALL);
    std::cout << "Hello world!\n";

    // clean up here for now?
    curl_global_cleanup();
    return 0;
}