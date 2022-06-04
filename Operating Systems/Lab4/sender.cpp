#include "message.h"

int main(int argc, char** argv) {
    char* filename = argv[1];
    char* event_name = argv[2];
    std::ofstream output_file(filename, std::ios::binary);
    if (!output_file.is_open()) {
        std::cout << "File can not be open!\n";
        return -1;
    }

    HANDLE ready_event = OpenEvent(EVENT_MODIFY_STATE, FALSE, event_name);
    HANDLE start_all = OpenEvent(SYNCHRONIZE, FALSE, "START_ALL");

    if (ready_event == NULL || start_all == NULL) {
        std::cout << "Failed to open the event!\n";
        return GetLastError();
    }

    SetEvent(ready_event);
    std::cout << "Started...\n";

    HANDLE file_mutex = OpenMutex(SYNCHRONIZE, FALSE, "FILE_ACCESS");
    if (file_mutex == NULL){
        std::cout << "Failed to open mutex!\n";
        return GetLastError();
    }

    HANDLE sender_semaphore = OpenSemaphore(SEMAPHORE_MODIFY_STATE, FALSE, "MESSAGES_COUNT_SEM");
    HANDLE read_event = OpenEvent(EVENT_ALL_ACCESS, FALSE, "MESSAGE_READ");
    if (sender_semaphore == NULL || read_event == NULL)
        return GetLastError();

    WaitForSingleObject(start_all, INFINITE);

    std::string message;
    std::cout << "Enter your message: ";

    while(true) {
        std::cin >> message;

        if(std::cin.eof())
            break;

        WaitForSingleObject(file_mutex, INFINITE);
        CustomSendMessage(output_file, message, filename);
        ReleaseMutex(file_mutex);

        if(ReleaseSemaphore(sender_semaphore, 1, NULL) == FALSE){
            std::cout << "Message file is full. Waiting for receiver.\n";
            ResetEvent(read_event);
            WaitForSingleObject(read_event, INFINITE);
            ReleaseSemaphore(sender_semaphore, 1, NULL);
        }
        std::cout << "Message has been sent.\n";
    }

    output_file.close();

    return 0;
}