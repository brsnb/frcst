#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <string>

namespace frcst
{
namespace request
{
    std::string http_post(const std::string &url, const std::string &post_fields);

    std::string http_get(const std::string &url);

    /*
    *   Callback function for CURLOPT_WRITEFUNCTION, writes the response to 
    *   string pointed to by user_data
    */
    size_t write_callback(char *content, size_t size, size_t nmemb, void *user_data);


} // namespace request
} // namespace frcst

#endif // REQUEST_HPP_