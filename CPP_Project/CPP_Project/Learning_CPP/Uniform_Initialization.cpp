#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    int a = 1;
    vector<string> vecString{"double", "int", "float"};
    map<string, string> capitals = {
        {"Japan", "Tokyo"}, {"Korean", "Seuoul"}, {"Canada", "Toronto"}
    };

    for (map<string, string>::const_iterator it = capitals.begin(); it!= capitals.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }
    cin.get();
    return 0;
}