#include<cstdlib>//std::exit
#include<string>//std::string std::getline
#include<iostream>//std::cin std::cout
#include<unordered_map>//std::unordered_map
#include"system_ext.h"
#include"handle_info.h"
void data_file_make(void);
void callback_handle_a_city_info_text(void);
void callback_handle_a_province_info_text(void);
void callback_data_file_open(void);
void callback_add_a_city_info_text(void);
void callback_add_a_city_info_image(void);
void callback_remove_a_city_info(void);
void callback_add_a_province_info_text(void);
void callback_add_a_province_info_image(void);
void callback_remove_a_province_info(void);
void callback_total_today_infos(void);
void callback_total_today_infos_and_set_clipboard(void);
void callback_total_date_range_infos(void);
void callback_total_date_range_infos_and_set_clipboard(void);
void callback_quit(void);
std::unordered_map<std::string,void(*)(void)>const callback_map={
    {std::string("o" ),&callback_data_file_open},
    {std::string("ch"),&callback_handle_a_city_info_text},
    {std::string("ct"),&callback_add_a_city_info_text},
    {std::string("ci"),&callback_add_a_city_info_image},
    {std::string("cr"),&callback_remove_a_city_info},
    {std::string("ph"),&callback_handle_a_province_info_text},
    {std::string("pt"),&callback_add_a_province_info_text},
    {std::string("pi"),&callback_add_a_province_info_image},
    {std::string("pr"),&callback_remove_a_province_info},
    {std::string("t" ),&callback_total_today_infos},
    {std::string("ts"),&callback_total_today_infos_and_set_clipboard},
    {std::string("r" ),&callback_total_date_range_infos},
    {std::string("rs"),&callback_total_date_range_infos_and_set_clipboard},
    {std::string("q" ),&callback_quit}
};
std::string const callback_info_string=
R"(+command-callback-----------------------------------------------------------+
|o      |today data file open(./${date}.docx)                               |
|ch     |handle a city info text(read from ./input.txt)                     |
|ct     |add a city info text(input from clipboard,output to data file)     |
|ci     |add a city info image(input from clipboard,output to data file)    |
|cr     |remove a city info(in data file)                                   |
|ph     |handle a province info text(read from ./input.txt)                 |
|pt     |add a province info text(input from clipboard,output to data file) |
|pi     |add a province info image(input from clipboard,output to data file)|
|pr     |remove a province info(in data file)                               |
|t      |total today infos(in data file)                                    |
|ts     |total today infos(in data file)and set clipboard                   |
|r      |total date range infos(in data file)                               |
|rs     |total date range infos(in data file)and set clipboard              |
|q      |quit                                                               |
+command-callback-----------------------------------------------------------+
)";
static std::filesystem::path root_path;
static std::filesystem::path input_path;
int main(int argc,char** argv){
    root_path=std::filesystem::path(argv[0]).parent_path();
    input_path=root_path/"input.txt";
    if(!system_ext::create_file(input_path)){
        return -1;
    }
    data_file_make();
    std::string command;
    std::string last_command;
    while(true){
        command.clear();
        std::cout
            <<callback_info_string
            <<"last command: "<<last_command<<"\n"
            <<"input command> "
        ;
        std::getline(std::cin,command);
        last_command=command;
        if(callback_map.count(command)>0){
            (callback_map.at(command))();
        }
        std::cout<<"press a key to continue ··· ··· ";
        std::getline(std::cin,command);
    }
    return 0;
}
void data_file_make(void){
    system_ext::shell_exec("python "+(root_path/"data_file_make.py").string());
}
void callback_handle_a_city_info_text(){
    std::string input_string=system_ext::read_file(input_path);
    if(input_string.empty()){
        std::cout<<__func__<<":"<<"input_string is empty.\n";
        return;
    }
    auto result=handle_a_city_info_text(input_string);
    std::string output_string=
        result.title+"\n"+
        result.url+"\n";
    system_ext::open_url(result.url);
    system_ext::set_clipboard(output_string);
    if(!system_ext::clean_file(input_path)){
        std::cout<<__func__<<":"<<"clean input file error.\n";
        return;
    }
}
void callback_handle_a_province_info_text(){
    std::string input_string=system_ext::read_file(input_path);
    if(input_string.empty()){
        std::cout<<__func__<<":"<<"input_string is empty.\n";
        return;
    }
    auto result=handle_a_province_info_text(input_string);
    std::string output_string=
        result.title+"\n"+
        result.url+"\n";
    system_ext::open_url(result.url);
    system_ext::set_clipboard(output_string);
    if(!system_ext::clean_file(input_path)){
        std::cout<<__func__<<":"<<"clean input file error.\n";
        return;
    }
}
void callback_data_file_open(void){
    system_ext::shell_exec("python "+(root_path/"data_file_open.py").string());
}
void callback_add_a_city_info_text(void){
    system_ext::shell_exec("python "+(root_path/"add_a_city_info_text.py").string());
}
void callback_add_a_city_info_image(void){
    system_ext::shell_exec("python "+(root_path/"add_a_city_info_image.py").string());
}
void callback_remove_a_city_info(void){
    system_ext::shell_exec("python "+(root_path/"remove_a_city_info.py").string());
}
void callback_add_a_province_info_text(void){
    system_ext::shell_exec("python "+(root_path/"add_a_province_info_text.py").string());
}
void callback_add_a_province_info_image(void){
    system_ext::shell_exec("python "+(root_path/"add_a_province_info_image.py").string());
}
void callback_remove_a_province_info(void){
    system_ext::shell_exec("python "+(root_path/"remove_a_provinece_info.py").string());
}
void callback_total_today_infos(void){
    system_ext::shell_exec("python "+(root_path/"total_today_infos.py").string());
}
void callback_total_today_infos_and_set_clipboard(void){
    system_ext::shell_exec("python "+(root_path/"total_today_infos_and_set_clipboard.py").string());
}
void callback_total_date_range_infos(void){
    system_ext::shell_exec("python "+(root_path/"total_date_range_infos.py").string());
}
void callback_total_date_range_infos_and_set_clipboard(void){
    system_ext::shell_exec("python "+(root_path/"total_date_range_infos_and_set_clipboard.py").string());
}
void callback_quit(void){
    std::exit(0);
}
