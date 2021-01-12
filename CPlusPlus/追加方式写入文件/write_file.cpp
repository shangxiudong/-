#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(int argc, char **argv)
{
    string path = argv[1];
    string str = argv[2];
    ofstream out;
    out.open(path, ofstream::app);
    out << str << endl;
    out.close();
    return 0;
}
