#include<cstdlib>//std::exit
#include<string>//std::string std::getline
#include<iostream>//std::cin std::cout
#include<unordered_map>//std::unordered_map
#include"system_ext.h"
#include"handle_info.h"
void callback_handle_a_city_info_text(void);
void callback_handle_a_province_info_text(void);
void callback_data_file_make(void);
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
    {std::string("hc" ),&callback_handle_a_city_info_text},
    {std::string("hp" ),&callback_handle_a_province_info_text},
    {std::string("fm" ),&callback_data_file_make},
    {std::string("fo" ),&callback_data_file_open},
    {std::string("act"),&callback_add_a_city_info_text},
    {std::string("aci"),&callback_add_a_city_info_image},
    {std::string("rc" ),&callback_remove_a_city_info},
    {std::string("apt"),&callback_add_a_province_info_text},
    {std::string("api"),&callback_add_a_province_info_image},
    {std::string("rp" ),&callback_remove_a_province_info},
    {std::string("tt" ),&callback_total_today_infos},
    {std::string("tts"),&callback_total_today_infos_and_set_clipboard},
    {std::string("tr" ),&callback_total_date_range_infos},
    {std::string("trs"),&callback_total_date_range_infos_and_set_clipboard},
    {std::string("q"  ),&callback_quit}
};
std::string const callback_info_string=
R"(Take ./input.txt as program input file.
====command==callback===========================================================
    hc       handle a city info text(input text read from input file)
    hp       handle a province info text(input text read from input file)
    fm       data file make
    fo       data file open
    act      add a city info text(input from clipboard,output to data file)
    aci      add a city info image(input from clipboard,output to data file)
    rc       remove a city info(in data file)
    apt      add a province info text(input from clipboard,output to data file)
    api      add a province info image(input from clipboard,output to data file)
    rp       remove a province info(in data file)
    tt       total today infos(in data file)
    tts      total today infos(in data file)and set clipboard
    tr       total date range infos(in data file)
    trs      total date range infos(in data file)and set clipboard
    q        quit
================================================================================
)";
static std::filesystem::path root_path;
static std::filesystem::path input_path;
int main(int argc,char** argv){
    root_path=std::filesystem::path(argv[0]).parent_path();
    input_path=root_path/"input.txt";
    if(!system_ext::create_file(input_path)){
        return -1;
    }
    std::string command;
    while(true){
        command.clear();
        system_ext::shell_exec("cls");
        std::cout
            <<callback_info_string
            <<"input command> "
        ;
        std::getline(std::cin,command);
        if(callback_map.count(command)>0){
            (callback_map.at(command))();
        }
        std::cout<<"press a key to continue ··· ···";
        std::getline(std::cin,command);
    }
    return 0;
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
void callback_data_file_make(void){
    system_ext::shell_exec("python "+(root_path/"data_file_make.py").string());
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
