#include"system_ext.h"
#include<cstdlib>//std::system
#include<iostream>//std::cerr
#include<fstream>//std::ofstream std::ifstream
#include<windows.h>
namespace system_ext{
int shell_exec(std::string const& command){
    return std::system(command.c_str());
}
void set_clipboard(std::string const& utf8_text){
    if (!::OpenClipboard(nullptr)){
        std::cerr<<"open clipboard error!\n";
        return;
    }
    ::EmptyClipboard();
    // 将UTF-8文本转换为多字节文本
    int requiredSize=::MultiByteToWideChar(CP_UTF8,0,utf8_text.c_str(),-1,nullptr, 0);
    wchar_t* wideText=new wchar_t[requiredSize];
    ::MultiByteToWideChar(CP_UTF8,0,utf8_text.c_str(),-1,wideText,requiredSize);
    // 分配内存以存储多字节文本
    HGLOBAL hClipboardData=::GlobalAlloc(GMEM_MOVEABLE,requiredSize*sizeof(wchar_t));
    if(hClipboardData!=nullptr){
        // 锁定全局内存并获取指向它的指针
        wchar_t* pClipboardData=static_cast<wchar_t*>(::GlobalLock(hClipboardData));
        if (pClipboardData!=nullptr){
            // 将多字节文本复制到全局内存
            ::wcscpy(pClipboardData,wideText);
            // 解锁全局内存
            ::GlobalUnlock(hClipboardData);
            // 将全局内存设置到剪贴板
            ::SetClipboardData(CF_UNICODETEXT,hClipboardData);
        }
    }
    delete[] wideText;
    // 关闭剪贴板
    ::CloseClipboard();
}
void open_url(std::string const& url){
    shell_exec("powershell.exe \"Start-Process '"+url+"'\"");
}
bool create_file(std::filesystem::path const& file_path){
    if(std::filesystem::exists(file_path)){
        return true;
    }
    std::ofstream ofs(file_path);
    if(ofs){
        ofs.close();
        return true;
    }
    return false;
}
bool clean_file(std::filesystem::path const& file_path){
    std::ofstream ofs(file_path,std::ios::trunc);
    if(ofs){
        ofs.close();
        return true;
    }
    return false;
}
std::string read_file(std::filesystem::path const& file_path){
    std::ifstream ifs(file_path);
    std::string ret;
    if(ifs){
        ret=std::string(
            (std::istreambuf_iterator<char>(ifs)),
            std::istreambuf_iterator<char>()
        );
        ifs.close();
    }
    return ret;
}
}//namespace system_ext
