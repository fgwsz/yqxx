#ifndef __HANDLE_INFO_H__
#define __HANDLE_INFO_H__
#include<string>//std::string
struct HandleResult{
    std::string title;
    std::string url;
};
HandleResult handle_a_city_info_text(std::string const& city_info);
HandleResult handle_a_province_info_text(std::string const& province_info);
#endif//__HANDLE_INFO_H__
