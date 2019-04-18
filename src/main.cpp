#include <curl/curl.h>
#include <iostream>
#include <vector>

#include <boost/program_options.hpp>

#include "location.hpp"
#include "frcst_util.hpp"
#include "forecast.hpp"

int main(int argc, char **argv)
{
    // location variables
    std::string city, state, country;
    std::vector<std::string> coordinates;

    // alias boost namespace
    namespace po = boost::program_options;

    // set up command line options
    po::options_description desc{"Options"};
    desc.add_options()
    (",h", "Show help message")
    (",c", po::value<std::string>(), "Add city to query")
    (",s", po::value<std::string>(), "Add state to query")
    (",n", po::value<std::string>(), "Add nation/country to query")
    (",l", po::value<std::string>(), "LAT:LON Add coordinates to query");

    // parse command line options
    try
    {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);

    if(vm.count("-h"))
    {
        std::cout << desc << '\n';
        return 0;
    }

    po::notify(vm);

    if(vm.count("-c"))
    {
        city = vm["-c"].as<std::string>();
    }
    if(vm.count("-s"))
    {
        state = vm["-s"].as<std::string>();
    }
    if(vm.count("-n"))
    {
        country = vm["-n"].as<std::string>();
    }
    if(vm.count("-l"))
    {
        std::string s = vm["-l"].as<std::string>();
        coordinates = frcst::util::split(s, ':');
    }

    }
    catch(const po::error &e)
    {
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
    }
    catch(const std::exception &e)
    {
      std::cerr << "Unhandled exception: " << e.what() << std::endl << std::endl; 
      std::cerr << desc << std::endl; 
    }

    // init curl
    curl_global_init(CURL_GLOBAL_ALL);

    frcst::Location loc{city, state, country};
    frcst::Forecast f{loc};
    std::cout << "Location: " << loc.get_city() << ", " << loc.get_state() << ", " << loc.get_country() << std::endl;
    std::cout << "Coordinates: " << loc.get_latitude() << ", " << loc.get_longitude() << std::endl;
    std::cout << "Temp: " << f.get_temp_f() << 'F' << " | " << f.get_temp_c() << 'C' << std::endl;
    std::cout << "Details: " << f.get_detailed() << std::endl;

    // clean up curl
    curl_global_cleanup();

    return 0;
}