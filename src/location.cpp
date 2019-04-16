#include "location.hpp"

#include <sstream>
#include <string>

#include "nlohmann/json.hpp"
#include "request.hpp"

namespace frcst
{

Location::Location(const std::string &city, 
                   const std::string &state, 
                   const std::string &country)
{
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
    json cb_json = json::parse(response);

    cb_json["city"].get<std::string>();
    cb_json["state"].get<std::string>();
    cb_json["country"].get<std::string>();
}

} // namespace frcst