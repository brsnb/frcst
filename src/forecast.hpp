#ifndef FORECAST_HPP_
#define FORECAST_HPP_

#include <ctime>
#include <string>
#include "location.hpp"

namespace frcst
{

class Forecast
{
    public:
    Forecast();
    Forecast(const Location &location);
    ~Forecast();

    Location        get_location() const {return location;}
    float           get_temp_c() const {return temperature_c;}
    float           get_temp_f() const {return temperature_f;}

    private:
    Location        location;
    std::time_t     current_time;
    float           temperature_f;
    float           temperature_c;
};

} // namespace frcst

#endif // WEATHER_HPP_