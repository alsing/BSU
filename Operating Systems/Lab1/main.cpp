#include "Employee.h"
#include <string>
#include <Windows.h>
#include <sstream>

template <typename T>
string to_string(T value) {
    ostringstream os ;
    os << value ;
    return os.str() ;
}

int main() {
    string fname;
    int num;

    cout << "Enter binary file name: ";
    cin >> fname;
    cout << "Enter number of records in this file: ";
    cin >> num;

    string creator = "Creator.cpp";
    string commandLineForCreator = fname + " " + to_string(num);
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb=sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    CreateProcess(creator.c_str(), const_cast<char *>(commandLineForCreator.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    employee e;
    ifstream in(fname.c_str(), ios::binary);
    while (in.read((char*)&e, sizeof(employee))) {
        cout << e.num << " " << e.name << " " << e.hours << " " << e.hours * wage << '\n';
    }
    return 0;
}
