#include "Employee.h"
#include <string>
#include <Windows.h>
#include <sstream>

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

int main() {
    std::string input_filename;
    int num_records;

    std::cout << "Enter binary file name: ";
    std::cin >> input_filename;
    std::cout << "Enter number of records in this file: ";
    std::cin >> num_records;

    std::string creator = "creator.exe";
    std::string command_line_creator = input_filename + " " + to_string(num_records);
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(STARTUPINFO));
    si.cb=sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    CreateProcess(creator.c_str(), const_cast<char *>(command_line_creator.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    employee e;
    std::ifstream in(input_filename.c_str(), std::ios::binary);
    while (in.read((char*)&e, sizeof(employee))) {
        std::cout << e.num << " " << e.name << " " << e.hours << " " << e.hours << '\n';
    }

    std::string output_filename;
    double wage;
    std::cout << "Enter report file name: ";
    std::cin >> output_filename;
    std::cout << "Enter wage: ";
    std::cin >> wage;

    std::string reporter = "reporter.exe";
    std::string command_line_reporter = input_filename + " " + output_filename + " " + to_string(wage);
    CreateProcess(reporter.c_str(), const_cast<char *>(command_line_reporter.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    std::string s;
    std::ifstream input_report(output_filename.c_str());
    while (getline(input_report, s))
        std::cout << s << '\n';

    system("pause");
    return 0;
}