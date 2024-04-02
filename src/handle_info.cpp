#include"handle_info.h"
#include"string_ext.h"
#include<cctype>//std::isspace
HandleResult handle_a_city_info_text(std::string const& city_info){
    std::regex const url_pattern(R"(https?://[^\s/$.?#].[^\s]*)");
    auto match_ret=string_ext::match_all(city_info,url_pattern);
    if(match_ret.empty()){
        return {};
    }
    auto const& match_item=match_ret.at(0);
    std::string const& url=match_item.str;
    std::string title;
    for(size_t index=0;auto ch:city_info){
        if(
            index<match_item.pos||
            index>=match_item.pos+url.length()
        ){
            title.push_back(ch);
        }
        ++index;
    }
    // 删除标题中的无效信息
    // 要删除的内容：
    // 1.空白字符和换行符
    string_ext::remove_all(
        title,
        [](char ch)->bool{
            return std::isspace(ch);
        }
    );
    // 2.删除单位信息，以免造成属地信息干扰
    string_ext::remove_all(
        title,
        std::string("单位：山东省德州市平原县委宣传部")
    );
    // 查找属地信息
    std::string const location_list[]={
        "德城",
        "陵城",
        "禹城",
        "乐陵",
        "临邑",
        "平原",
        "夏津",
        "武城",
        "庆云",
        "宁津",
        "齐河",
        "天衢"
    };
    std::string const location_default={"德州"};
    std::string location=location_default;
    for(size_t location_count=0;auto const& location_item:location_list){
        if(title.find(location_item)!=title.npos){
            if(location_count==0){
                location=location_item;
            }else{
                location.append("、").append(location_item);
            }
            ++location_count;
        }
    }
    // 删除标题中的无效信息
    // 3.标题：and 链接：and （如果能找到摘要的话）摘要：以及该行之后的全部信息
    string_ext::remove_all(title,std::string("标题："));
    string_ext::remove_all(title,std::string("链接："));
    do{
        std::size_t index=title.find("摘要：");
        if(index!=title.npos){
            title.erase(index,title.npos);
        }
    }while(0);
    // 处理结束返回标题和链接
    return {location+"："+title,url};
}
HandleResult handle_a_province_info_text(std::string const& province_info){
    std::regex const url_pattern(R"(https?://[^\s/$.?#].[^\s]*)");
    auto match_ret=string_ext::match_all(province_info,url_pattern);
    if(match_ret.empty()){
        return {};
    }
    auto const& match_item=match_ret.at(0);
    std::string const& url=match_item.str;
    std::string title;
    for(size_t index=0;auto ch:province_info){
        if(
            index<match_item.pos||
            index>=match_item.pos+url.length()
        ){
            title.push_back(ch);
        }
        ++index;
    }
    // 删除标题中的无效信息
    // 要删除的内容：
    // 1.空白字符和换行符
    string_ext::remove_all(
        title,
        [](char ch)->bool{
            return std::isspace(ch);
        }
    );
    // 2.删除单位信息，以免造成属地信息干扰
    string_ext::remove_all(
        title,
        std::string("单位：山东省德州市平原县委宣传部")
    );
    // 删除标题中的无效信息
    // 3.标题：and 链接：and （如果能找到摘要的话）摘要：以及该行之后的全部信息
    string_ext::remove_all(title,std::string("标题："));
    string_ext::remove_all(title,std::string("链接："));
    do{
        std::size_t index=title.find("摘要：");
        if(index!=title.npos){
            title.erase(index,title.npos);
        }
    }while(0);
    // 处理结束返回标题和链接
    return {title,url};
}
