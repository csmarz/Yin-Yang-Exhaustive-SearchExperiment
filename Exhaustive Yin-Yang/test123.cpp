#include <iostream>
using namespace std;

bool string_compare(string s)
{
    return ((s.compare("0000") == 0) || (s.compare("1111") == 0) || (s.compare("0110") == 0) || (s.compare("1001") == 0));
}

int main()
{
    cout << "hello world" << endl;
    string s = "0000";
    if (string_compare(s))
    {
        cout << "found" << endl;
    }
    else
    {
        cout << "no" << endl;
    }
    return 0;
}