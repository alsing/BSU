#include <sstream>
#include "employee.h"

const int commandLength = 12;
const int waitingTime = 2000;
const std::string ipName = "START_ALL";
const std::string pipeName = "\\\\.\\pipe\\pipe_name";

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

void errorMessage(std::string message) {
    std::cerr <<  message;
    getch();
}

void messaging(HANDLE handlePipe) {
    std::cout << "If you want to quit, press Ctrl+C...\n";

    while(true) {
        std::cout << "Input r to read or w to write command and ID of employee: ";
        char command[commandLength];
        std::cin.getline(command, commandLength, '\n');

        if(std::cin.eof()) {
            errorMessage("File is empty... \n");
            return;
        }

        bool isSent;
        DWORD bytesWritten;
        isSent = WriteFile(handlePipe, command, commandLength,
                           &bytesWritten, NULL);

        if(!isSent) {
            errorMessage("Message cannot be sent...\n");
            return;
        }

        bool isRead;
        DWORD readBytes;
        employee tempEmployee;
        isRead = ReadFile(handlePipe, &tempEmployee,
                          sizeof(tempEmployee), &readBytes, NULL);

        if(!isRead) {
            errorMessage("Receiving answer error...\n");
            continue;
        }

        if(tempEmployee.num < 0) {
            errorMessage("Employee not found or had being modified.\n");
            continue;
        }

        tempEmployee.print();

        if ('w' == command[0]) {
            std::cout << "Input ID of employee: ";
            std::cin >> tempEmployee.num;
            std::cout << "Input name of employee: ";
            std::cin >> tempEmployee.name;
            std::cout << "Input working hours of employee: ";
            std::cin >> tempEmployee.hours;

            std::cin.ignore(2, '\n');

            isSent = WriteFile(handlePipe, &tempEmployee,
                               sizeof(tempEmployee), &bytesWritten, NULL);

            if (!isSent) {
                errorMessage("Sending error...\n");
                break;
            }

            std::cout << "New record has been sent.\n";
        }
    }
}

int main(int argc, char** argv) {
    HANDLE handleReadyEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, argv[1]);
    HANDLE handleStartEvent = OpenEvent(SYNCHRONIZE, FALSE, ipName.c_str());

    if (handleStartEvent == NULL || handleReadyEvent == NULL){
        std::cerr << "Event action error...\n";
        getch();
        return GetLastError();
    }

    SetEvent(handleReadyEvent);
    WaitForSingleObject(handleStartEvent, INFINITE);
    HANDLE handlePipe;

    std::cout << "Process is started.\n";

    while(1) {
        handlePipe = CreateFile(pipeName.c_str(), GENERIC_WRITE | GENERIC_READ,
                                FILE_SHARE_READ, NULL,
                                OPEN_EXISTING, 0, NULL);

        const bool FLAG = WaitNamedPipe(pipeName.c_str(), waitingTime)
                          + (INVALID_HANDLE_VALUE != handlePipe);

        if (FLAG) {
            if(INVALID_HANDLE_VALUE != handlePipe) {
                break;
            }
            errorMessage(to_string(waitingTime) + "timed out...\n");
            return 0;
        }
    }
    std::cout << "Pipe has been connecting...\n";
    messaging(handlePipe);
    return 0;
}