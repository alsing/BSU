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
            std::cout << "Failed to create the event!\n";
            return GetLastError();
        }

        std::string exe = "Sender.exe";
        exe += " " + filename + " " + event_name;

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

std::string ReadMessage(std::string filename) {
    std::ifstream input_file(filename.c_str(), std::ios::binary | std::ios::in);
    if(!input_file.is_open()){
        return "Failed to open the file!\n";
    }

    long file_size;
    input_file.seekg(0, std::ios::end);
    file_size = input_file.tellg();
    if(!file_size)
        return "Message file is empty!\n";

    char result[messageSize];
    input_file.seekg(0, std::ios::end);
    input_file.read(result, messageSize);

    char* buffer = new char[file_size];
    input_file.seekg(0, std::ios::end);
    input_file.read(buffer, file_size);

    std::ofstream output_file(filename.c_str(), std::ios::binary | std::ios::out);
    output_file.write(buffer + messageSize, file_size - messageSize);

    input_file.close();
    output_file.close();
    delete[] buffer;

    return result;
}

int main() {
    std::string filename;
    std::cout <<"Enter binary file name: ";
    std::cin >> filename;
    std::fstream input_file(filename.c_str(), std::ios::binary | std::ios::out);

    int n_senders;
    std::cout << "Enter number of sender processes: ";
    std::cin >> n_senders;

    InitializeCriticalSection(&cs);
    HANDLE start_all = CreateEvent(NULL, TRUE, FALSE, "START_ALL");
    HANDLE file_mutex = CreateMutex(NULL, FALSE, "FILE_ACCESS");

    if(file_mutex == NULL) {
        std::cout << "Failed to create Mutex!\n";
        return GetLastError();
    }

    HANDLE sender_semaphore = CreateSemaphore(NULL, 0, n_senders, "MESSAGES_COUNT_SEM");
    HANDLE read_event = CreateEvent(NULL, FALSE, FALSE, "MESSAGE_READ");
    if (sender_semaphore == NULL || read_event == NULL)
        return GetLastError();

    LaunchSenders(n_senders, filename);
    WaitForMultipleObjects(n_senders, readyEvents, TRUE, INFINITE);
    std::cout << "All senders are ready. Starting...\n";
    SetEvent(start_all);
    char buffer[messageSize];
    char message[messageSize];

    while(true) {
        std::cin >> buffer;
        if(std::cin.eof())
            break;
        std::cout << "Waiting for a message...\n";
        WaitForSingleObject(sender_semaphore, INFINITE);
        WaitForSingleObject(file_mutex, INFINITE);
        std::cout << ReadMessage(filename);
        ReleaseMutex(file_mutex);
        SetEvent(read_event);
    }

    input_file.close();
    delete[] readyEvents;
    DeleteCriticalSection(&cs);
}