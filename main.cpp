#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
using namespace std;

int main() {
    ifstream file("/proc/stat");
    string cpu;
    long user, nice, system, idle;

    if(file.is_open()){
        file >> cpu >> user >> nice >> system >> idle;
        cout << "User : " << user << endl;
        cout << "System : " << system << endl;
        cout << "Idle : " << idle << endl;
    }

    return 0;
}
