#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <string>

namespace frcst
{
namespace request
{

/*
*   Callback function for CURLOPT_WRITEFUNCTION, writes the response to 
*   string pointed to by user_data
*/
size_t write_callback(char *content, size_t size, size_t nmemb, void *user_data);

/*
*   Performs a simple libcurl http post request
*/
std::string http_post(std::string url, std::string post_fields);

} // namespace request
} // namespace frcst

#endif // REQUEST_HPP_