#ifndef FRCST_UTIL_H
#define FRCST_UTIL_H

#include <iterator>
#include <string>
#include <sstream>
#include <vector>

namespace frcst
{
namespace util
{

template<typename T>
void split(const std::string &s, char delim, T result) {
    std::stringstream ss{s};
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

} // util
} // frcst


#endif // FRCST_UTIL_H