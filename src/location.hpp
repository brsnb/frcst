#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>

namespace frcst
{

class Location
{
    public:
    Location() = delete;
    Location(std::string city_name, 
             std::string state_name, 
             std::string country_name);
    Location(const float latitude, const float longitude);

    std::string     get_city() const {return city;}
    std::string     get_country() const {return country;}
    std::string     get_state() const {return state;}
    std::string     get_latitude() const {return latitude;}
    std::string     get_longitude() const {return longitude;}

    private:
    std::string     city;
    std::string     state;
    std::string     country;
    std::string     latitude, longitude;
};

} // namespace frcst

#endif // LOCATION_HPP_