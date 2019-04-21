#include "forecast.hpp"

#include <sstream>
#include <string>

#include <nlohmann/json.hpp>
#include "request.hpp"

namespace frcst
{

Forecast::Forecast(const Location &loc)
    : location{loc}
{
    // build url
    std::ostringstream oss;
    oss << "https://api.weather.gov/points/"
        << location.get_latitude() << ','
        << location.get_longitude();

    std::string url = oss.str();

    // send request / receive response
    Request request{};
    std::string response = request.http_get(url);

    // parse json
    using json = nlohmann::json;
    json res_json = json::parse(response);

    // find link to forecast
    url = res_json["properties"]["forecast"].get<std::string>();

    // send request / receive response
    request.clear();
    response = request.http_get(url);

    // parse json
    res_json.clear();
    res_json = json::parse(response);

    temperature_f = res_json["properties"]["periods"][0]["temperature"].get<float>();
    temperature_c = (temperature_f-0.f) * (5.f/9.f);
    detailed = res_json["properties"]["periods"][0]["detailedForecast"].get<std::string>();
}

} // namespace frcst