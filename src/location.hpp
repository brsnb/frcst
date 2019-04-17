#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>

namespace frcst
{

class Location
{
    public:
    Location() = delete;
    Location(const std::string &city_name, 
             const std::string &state_name, 
             const std::string &country_name);
    Location(const float latitude, const float longitude);
    ~Location();

    private:
    std::string     city;
    std::string     state;
    std::string     country;
    std::string     latitude, longitude;
};

} // namespace frcst

#endif // LOCATION_HPP_