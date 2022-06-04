#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>

CRITICAL_SECTION cs;
HANDLE* readyEvents;
const int messageSize = 20;

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

int LaunchSenders(int n_senders, std::string filename) {
    readyEvents = new HANDLE[n_senders];

    for(int i = 0; i < n_senders; ++i){
        std::string event_name = "sender";
        event_name += to_string(i);
        readyEvents[i] = CreateEvent(NULL, TRUE, FALSE, event_name.c_str());
        if (readyEvents[i] == NULL) {
            std::cout << "Creation of the event failed!\n";
            return GetLastError();
        }

        std::string exe = "sender.exe";
        exe += filename + " " + event_name;

        STARTUPINFO startup_information;
        PROCESS_INFORMATION process_information;
        ZeroMemory(&startup_information, sizeof(STARTUPINFO));
        startup_information.cb = sizeof(STARTUPINFO);
        char* lp_arguments = (char*)(exe.c_str());
        if (!CreateProcess(NULL, lp_arguments, NULL, NULL, FALSE,
                           CREATE_NEW_CONSOLE, NULL, NULL, &startup_information, &process_information)) {
            std::cout << "Process creation error!\n";
            CloseHandle(process_information.hProcess);
            CloseHandle(process_information.hThread);
        }
    }
    std::cout << "Receiver process created " << n_senders << " senders\n";
}
