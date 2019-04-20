#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include <curl/curl.h>
#include <stdexcept>
#include <memory>
#include <string>

namespace frcst
{
class Request
{
    public:
    Request();
    ~Request();
    class Request_exception : public std::runtime_error
    {
        public:
        Request_exception() : std::runtime_error("Error during request") {}
    };

    std::string http_post(const std::string &url, const std::string &post_fields);
    std::string http_get(const std::string &url);
    /*
    *   Callback function for CURLOPT_WRITEFUNCTION, writes the response to 
    *   string pointed to by user_data
    */
    size_t write_callback(char *content, size_t size, size_t nmemb, void *user_data);

    private:
    std::unique_ptr<CURL> curl;

};
} // namespace frcst

#endif // REQUEST_HPP_