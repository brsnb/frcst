#include "location.hpp"

#include <algorithm>
#include <sstream>
#include <string>

#include <nlohmann/json.hpp>
#include "request.hpp"

namespace frcst
{

Location::Location(std::string city_name, 
                   std::string state_name,
                   std::string country_name)
{
    // build url
    std::ostringstream oss;
    oss << "https://nominatim.openstreetmap.org/search?q=";

    if(!city_name.empty())
    {
        city = city_name;
        std::replace(city_name.begin(), city_name.end(), ' ', '+');
        oss << city_name << ",+";
    }
    if(!state_name.empty())
    {
        state = state_name;
        std::replace(state_name.begin(), state_name.end(), ' ', '+');
        oss << state_name << ",+";
    }
    if(!country_name.empty())
    {
        country = country_name;
        std::replace(country_name.begin(), country_name.end(), ' ', '+');
        oss << country_name << ",+";
    }

    oss << "&format=jsonv2";
    std::string url = oss.str();

    // send request / receive response
    Request request{};
    std::string response = request.http_get(url);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    // finish initialization
    latitude =  res_json[0]["lat"].get<std::string>();
    longitude = res_json[0]["lon"].get<std::string>();

}

Location::Location(const float latitude, const float longitude)
{
    // build url
    std::ostringstream oss;
    oss << "https://nominatim.openstreetmap.org/reverse"
        << "?format=json&" << "lat=" << latitude << "&" << "lon=" << longitude;
    std::string url = oss.str();

    // send request / receive response
    Request request{};
    std::string response = request.http_get(url);

    // parse JSON
    using json = nlohmann::json;
    json res_json = json::parse(response);

    city =    res_json["address"]["city"].get<std::string>();
    state =   res_json["address"]["state"].get<std::string>();
    country = res_json["address"]["country"].get<std::string>();

}

} // namespace frcst