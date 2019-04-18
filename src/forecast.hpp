#ifndef FORECAST_HPP_
#define FORECAST_HPP_

#include <string>
#include "location.hpp"

namespace frcst
{

class Forecast
{
    public:
    Forecast() = delete;
    Forecast(const Location &loc);

    Location        get_location() const {return location;}
    float           get_temp_c() const {return temperature_c;}
    float           get_temp_f() const {return temperature_f;}
    std::string     get_detailed() const {return detailed;}

    private:
    Location        location;
    float           temperature_f;
    float           temperature_c;
    std::string     detailed;
};

} // namespace frcst

#endif // WEATHER_HPP_