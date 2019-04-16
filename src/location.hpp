#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <string>

namespace frcst
{

class Location
{
    public:
    Location() = delete;
    Location(const std::string &city, 
             const std::string &state, 
             const std::string &country);
    Location(const float latitude, const float longitude);
    ~Location();

    private:
    std::string     city;
    std::string     state;
    std::string     country;
    float           latitude, longitude;
};

} // namespace frcst

#endif // LOCATION_HPP_