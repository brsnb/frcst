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

std::string http_post(const std::string &url, const std::string &post_fields)
{
    CURL *curl = curl_easy_init();

    // debug
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // url
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // user agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl 7.64.1 (x86_64-pc-linux-gnu) libcurl/7.64.1");

    // post fields
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    // callback
    std::string callback;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &callback);

    CURLcode res =  curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(res != CURLE_OK)
    {
        std::cout << "Something happened in http_post\n";
        exit(EXIT_FAILURE);
    }

    return callback;
}

std::string http_get(const std::string &url)
{
    CURL *curl = curl_easy_init();

    // debug
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    // url
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // user agent
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl 7.64.1 (x86_64-pc-linux-gnu) libcurl/7.64.1");

    // etc
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

    // callback
    std::string callback;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &callback);

    CURLcode res =  curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    if(res != CURLE_OK)
    {
        std::cout << "Something happened in http_post\n";
        exit(EXIT_FAILURE);
    }

    return callback;
}

} // namespace request
} // namespace frcst