#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char **argv)
{
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    vector<string> vs;
    vector<string> outvs;
    while(in) {
        string tmpstr;
        getline(in, tmpstr);
        vs.push_back(tmpstr);
    }

    regex r(".*\\[Debug\\ \\ \\](.*)");
    for(const string &s :vs) {
        smatch result;
        if(regex_match(s, result, r)) {
            outvs.push_back(result.str(1));
        }
    }
    for(auto s:outvs) {
        out << s << endl;
    }
    return 0;
}
