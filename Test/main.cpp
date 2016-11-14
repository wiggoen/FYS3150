#include <iostream>
#include <string>

using namespace std;

int main()//int argc, char *argv[])
{
    string str = "testing.txt";
    const char* chr = str.c_str();
    cout << "Hello World!" << endl;
    /*
    cout << argc << endl;
    cout << &argv << endl;
    cout << "     " << &argv[1] << endl;
    cout << chr << endl;
    string strr = "string.txt";
    char* chrt = strdup(strr.c_str());
    cout << chrt << endl;
    cout << &strr << endl;
    cout << &chrt << endl;
    */
    char* argv[] = "testing.txt";
    cout << argv << endl;


    return 0;
}
