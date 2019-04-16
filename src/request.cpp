#include "request.hpp"

#include <cstdlib>
#include <iostream>
#include <curl/curl.h>

namespace frcst
{
namespace request
{

size_t write_callback(char *content, size_t size, size_t nmemb, void *user_data)
{
    ((std::string*)user_data)->append((char*)content, size * nmemb);
    return size * nmemb;
}

std::string http_post(std::string url, std::string post_fields)
{
    CURL *post = curl_easy_init();

    // url
    curl_easy_setopt(post, CURLOPT_URL, url.c_str());

    // post fields
    curl_easy_setopt(post, CURLOPT_POSTFIELDS, post_fields.c_str());

    // callback
    std::string callback;
    curl_easy_setopt(post, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(post, CURLOPT_WRITEDATA,     &callback);

    CURLcode res =  curl_easy_perform(post);
    curl_easy_cleanup(post);

    if(res != CURLE_OK)
    {
        std::cout << "Something happened in http_post\n";
        exit(EXIT_FAILURE);
    }

    return callback;
}

} // namespace request
} // namespace frcst