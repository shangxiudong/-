#include <iostream>
#include <list>
#include <time.h>
#include <string>
#include <algorithm>
#include <QHash>

using namespace std;
//打印时间
const std::string current_time()
{
    time_t now = time(nullptr);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}
//查询的结构体
struct Mail {
    Mail(string msgid = "0000", int mailid = 0, string folderId = "")
        : m_msgid(msgid)
        , m_mailid(mailid)
        , m_folderId(folderId)
    {
    }
    Mail(const Mail &oldmail)
        : m_msgid(oldmail.m_msgid)
        , m_subject(oldmail.m_subject)
        , m_mailid(oldmail.m_mailid)
        , m_folderId(oldmail.m_folderId)
    {
    }
    string m_msgid;
    string m_subject;
    int m_mailid;
    string m_folderId;
};
//定义==运算符
bool operator==(const Mail &compare_mail1, const Mail &compare_mail2)
{
    return (compare_mail1.m_msgid == compare_mail2.m_msgid
            && compare_mail1.m_mailid == compare_mail2.m_mailid
            && compare_mail1.m_folderId == compare_mail2.m_folderId);
}

int main()
{
    list<Mail> counta;
    list<Mail> countb;
    for (int i = 0; i < 10000; ++i) {
        Mail mail(std::to_string(i), i, string("uid") + std::to_string(i));
        counta.push_back(mail);
    }
    for (int i = 0; i < 10000; ++i) {
        Mail mail(std::to_string(i), i, string("uid") + std::to_string(i));
        countb.push_back(mail);
    }
    //1.两个for 循环 查找
    cout << current_time() << endl;
    for (Mail &i : counta) {
        for (Mail &j : countb) {
            if (i == j) {
                Mail mail(i);
            }
        }
    }
    cout << current_time() << endl;

    //2. 使用库函数find_if查找
    cout << "find_if " << current_time() << endl;
    for (Mail &i : counta) {
        auto it = find_if(countb.begin(), countb.end(), [i](const Mail &j) {
            return i.m_msgid == j.m_msgid && i.m_mailid == j.m_mailid && i.m_folderId == j.m_folderId;
        });
    }
    cout << "find_if " << current_time() << endl;

    //构建一个哈希表
    QHash<QString, Mail *> hashmail;
    for (Mail &i : counta) {
        hashmail.insert(QString::fromStdString(i.m_msgid + string("-") + std::to_string(i.m_mailid) + string("-") + i.m_folderId),
                        &i);
    }
    //使用哈希查找
    cout << "qhash " << current_time() << endl;
    for (auto i : countb) {
        auto it = hashmail.find(QString::fromStdString(i.m_msgid + string("-") + std::to_string(i.m_mailid) + string("-") + i.m_folderId));
        if (it != hashmail.end()) {
            //            cout << it.value()->m_msgid << " ";
            ;
        }
    }
    cout << "qhash " << current_time() << endl;
    return 0;
}
