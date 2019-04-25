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

    Request(const Request&) = delete;
    Request& operator=(const Request*) = delete;
    Request(Request&&) = delete;
    Request& operator=(Request&&) = delete;

    class Request_exception : public std::runtime_error
    {
        public:
        Request_exception() : std::runtime_error("Error during request") {}
    };

    /*
    *   Wrapper for a simple http_post request with set post fields that returns the response
    */
    std::string   http_post(const std::string &url, const std::string &post_fields);

    /*
    *   Wrapper for a simple get request to url that returns the response
    */ 
    std::string   http_get(const std::string &url);

    /*
    *   Clear and reinit curl if using the same handle for multiple requests
    */
    void          clear();


    private:
    /*
    *   Callback function for CURLOPT_WRITEFUNCTION, writes the response to 
    *   string pointed to by user_data
    */
    static size_t write_callback(char *content, size_t size, size_t nmemb, void *user_data);

    /*
    *   Custom deleter for the CURL unique_ptr
    */
    struct CURL_cleanup
    {
        void operator()(CURL *c) const
        {
            if (c)
            {
                curl_easy_cleanup(c);
            }
        }
    };

    std::unique_ptr<CURL, CURL_cleanup> curl;
};
} // namespace frcst

#endif // REQUEST_HPP_