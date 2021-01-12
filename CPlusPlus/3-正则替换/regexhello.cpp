#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
    string local_path("INBOX/hello");
    string str("/home/sxd/.local/share/deepin/deepin-mail/mail/maildata/nomalconfig/imapcache/imap.163.com/wangzi24678@163.com/INBOX/.backup_mark");
    regex r("(.*[[:alnum:]]+@[[:alnum:]]+\\.com/)(.*)", std::regex::icase);
    string fmt = "$1" + local_path;
    cout << regex_replace(str, r, fmt) << endl;
    return 0;
}
