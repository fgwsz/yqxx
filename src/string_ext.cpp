#include"string_ext.h"
namespace string_ext{
void replace_all(
    std::string& str,
    std::string const& from,
    std::string const& to
){
    size_t start_pos=0;
    while((start_pos=str.find(from,start_pos))!=std::string::npos){
        str.replace(start_pos,from.length(),to);
        start_pos+=to.length();
    }
}
void replace_all(
    std::string& str,
    std::regex const& pattern,
    std::string const& to
){
    str=std::regex_replace(str,pattern,to);
}
std::vector<MatchItem> match_all(
    std::string const& str,
    std::regex const& pattern
){
    std::vector<MatchItem> ret;
    std::smatch match;
    if(!std::regex_search(str,match,pattern)){
        return ret;
    }
    for(size_t index=0;index<match.size();++index){
        ret.push_back(
            MatchItem{
                static_cast<size_t>(match.position(index)),
                match.str(index)
            }
        );
    }
    return ret;
}
void remove_all(
    std::string& str,
    std::string const& substr
){
    replace_all(str,substr,"");
}
void remove_all(
    std::string& str,
    std::regex const& pattern
){
    replace_all(str,pattern,"");
}
void remove_all(
    std::string& str,
    std::function<bool(char)>const& func
){
    std::string temp;
    for(auto const ch:str){
        if(!func(ch)){
            temp.push_back(ch);
        }
    }
    str=temp;
}
}//namespace string_ext
