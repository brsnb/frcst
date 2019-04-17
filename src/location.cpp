#include "location.hpp"

#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>

#include <nlohmann/json.hpp>
#include "request.hpp"

namespace frcst
{

Location::Location(const std::string &city_name, 
                   const std::string &state_name,
                   const std::string &country_name)
                   : city{city_name}, state{state_name}, country{country_name}
{
    // make url
    std::ostringstream oss;
    oss << "https://nominatim.openstreetmap.org/search?q=";
    if(!city.empty())
    {
        std::string city_url = city_name;
        std::replace(city_url.begin(), city_url.end(), ' ', '+');
        oss << city_url << ",+";
    }
    if(!state.empty())
    {
        std::string state_url = state_name;
        std::replace(state_url.begin(), state_url.end(), ' ', '+');
        oss << state_url << ",+";
    }
    if(!country.empty())
    {
        std::string country_url = country_name;
        std::replace(country_url.begin(), country_url.end(), ' ', '+');
        oss << country_url << ",+";
    }
    oss << "&format=jsonv2";
    std::string url = oss.str();

    // send request / receive response
    std::string response = request::http_get(url);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    // finish initialization
    latitude =  res_json[0]["lat"].get<std::string>();
    longitude = res_json[0]["lon"].get<std::string>();
}

Location::Location(const float latitude, const float longitude)
{
    // make url
    std::ostringstream oss;
    oss << "https://nominatim.openstreetmap.org/reverse"
        << "?format=json&" << "lat=" << latitude << "&" << "lon=" << longitude;
    std::string url = oss.str();

    // send request / receive response
    std::string response = request::http_get(url);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    city =    res_json["address"]["city"].get<std::string>();
    state =   res_json["address"]["state"].get<std::string>();
    country = res_json["address"]["country"].get<std::string>();

}

} // namespace frcst