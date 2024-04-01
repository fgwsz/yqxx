#ifndef __SYSTEM_EXT_H__
#define __SYSTEM_EXT_H__
#include<string>//std::string
#include<filesystem>//std::filesystem::path
namespace system_ext{
int shell_exec(std::string const& command);
void set_clipboard(std::string const& utf8_text);
void open_url(std::string const& url);
bool create_file(std::filesystem::path const& file_path);
bool clean_file(std::filesystem::path const& file_path);
std::string read_file(std::filesystem::path const& file_path);
}//namespace system_ext
#endif//__SYSTEM_EXT_H__
