#ifndef __STRING_EXT_H__
#define __STRING_EXT_H__
#include<cstddef>//size_t
#include<string>//std::string
#include<vector>//std::vector
#include<regex>//std::regex
#include<functional>//std::function
namespace string_ext{
void replace_all(
    std::string& str,
    std::string const& from,
    std::string const& to
);
void replace_all(
    std::string& str,
    std::regex const& pattern,
    std::string const& to
);
struct MatchItem{
    size_t pos;
    std::string str;
};
std::vector<MatchItem> match_all(
    std::string const& str,
    std::regex const& pattern
);
void remove_all(
    std::string& str,
    std::string const& substr
);
void remove_all(
    std::string& str,
    std::regex const& pattern
);
void remove_all(
    std::string& str,
    std::function<bool(char)>const& func
);
}//namespace string_ext
#endif//__STRING_EXT_H__
