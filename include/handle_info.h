#ifndef __HANDLE_INFO_H__
#define __HANDLE_INFO_H__
#include<string>//std::string
struct HandleResult{
    std::string title;
    std::string url;
};
HandleResult handle_city_info(std::string const& city_info);
HandleResult handle_province_info(std::string const& province_info);
#endif//__HANDLE_INFO_H__
