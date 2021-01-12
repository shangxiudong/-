#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::string hello("ss送信済みdd");
    /*{
        bool ret = std::regex_match("ddinbox", std::regex(".*Inbox.*", std::regex::icase));
        if (ret)
            std::cout << "matched" << std::endl;
        else
            std::cout << "no_matched" << std::endl;
    }*/
    /*{
        std::string pattern(".*Inbox.*");
        std::regex r(pattern, std::regex::icase);
        bool ret = std::regex_match("ddinbox", r);
        if (ret)
            std::cout << "matched" << std::endl;
        else
            std::cout << "no_matched" << std::endl;
    }*/
    if (std::regex_match(hello, std::regex(".*inbox.*", std::regex::icase))) {
        std::cout << "inbox" << std::endl;
    } else if (std::regex_match(hello, std::regex(".*(draft|下書き|임시보관함|Entwürfe).*", std::regex::icase))) {
        std::cout << "draft" << std::endl;
    } else if (std::regex_match(hello, std::regex(".*(sent|outbox|送信済み|보낸편지함|Gesendet).*", std::regex::icase))) {
        std::cout << "outbox" << std::endl;
    } else if(std::regex_match(hello, std::regex(".*(trash|已删除|ゴミ箱|휴지통|Papierkorb).*", std::regex::icase))) {
        std::cout << "trash" << std::endl;
    }
    
    return 0;
}