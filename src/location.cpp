#include "location.hpp"

#include <algorithm>
#include <sstream>
#include <string>

#include <nlohmann/json.hpp>
#include "request.hpp"

namespace frcst
{

Location::Location(const std::string &city_name, 
                   const std::string &state_name,
                   const std::string &country_name)
{
    std::string url = "https://nominatim.openstreetmap.org/search";

    // make post fields string
    std::ostringstream oss;
    oss << "q=";
    if(!city.empty())
    {
        std::string city_url = city_name;
        std::replace(city_url.begin(), city_url.end(), ' ', '%');
        oss << city_url << ",+";
    }
    else if(!state.empty())
    {
        std::string state_url = state_name;
        std::replace(state_url.begin(), state_url.end(), ' ', '%');
        oss << state_url << ",+";
    }
    else if(!country.empty())
    {
        std::string country_url = country_name;
        std::replace(country_url.begin(), country_url.end(), ' ', '%');
        oss << country_url << ",+";
    }

    std::string post_fields = oss.str();

    // send request / receive response
    std::string response = request::http_post(url, post_fields);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    latitude =  res_json["lat"].get<std::string>();
    longitude = res_json["lon"].get<std::string>();

    // finish initialization
    city = city_name;
    state = state_name;
    country = country_name;
}

Location::Location(const float latitude, const float longitude)
{
    std::string url = "https://nominatim.openstreetmap.org/reverse";

    // make post fields string
    std::ostringstream oss;
    oss << "format=jsonv2?" << "lat=" << latitude << "?" << "long=" << longitude;
    std::string post_fields = oss.str();

    // send request / receive response
    std::string response = request::http_post(url, post_fields);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    city =    res_json["city"].get<std::string>();
    state =   res_json["state"].get<std::string>();
    country = res_json["country"].get<std::string>();
}

} // namespace frcst