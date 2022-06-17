#include "employee.h"

int employeeCount;
employee* employees;
HANDLE* handleReadyEvents;
CRITICAL_SECTION cs;
bool *empIsModifying;
int employeeSize = sizeof(employee);

const std::string pipeName = "\\\\.\\pipe\\pipe_name";
const int bufferLength = 10;
const int messageLength = 10;
char buffer[bufferLength];

int generateClientsNumber() {
    srand(time(0));
    return (rand() / 5 + 3) % 5 + 2;
}

employee* findEmployee(const int ID) {
    employee key;
    key.num = ID;
    return (employee*) bsearch(&key, employees,
                               employeeCount, employeeSize, EmployeeComparator);
}

void sortEmployees() {
    qsort(employees, employeeCount, employeeSize, EmployeeComparator);
}

void writeData(std::string fileName) {
    std::fstream fin(fileName.c_str(), std::ios::out | std::ios::binary);
    fin.write(reinterpret_cast<const char *>(employees), employeeSize * employeeCount);

    std::cout << "Data has been written.\n";
    fin.close();
}

void readDataSTD() {
    employees = new employee[employeeCount];

    std::cout << "Input ID, name and working hours of each employee: ";
    for (int i = 0; i < employeeCount; ++i){
        std::cout << "№" << i + 1 << ": ";
        std::cin >> employees[i].num >> employees[i].name >> employees[i].hours;
    }
}

void startPocesses(const int COUNT) {
    for (int i = 0; i < COUNT; ++i) {
        std::string cmdArgs = "..\\..\\Client\\cmake-build-debug\\Client.exe ";
        std::string eventName = "READY_EVENT_";
        itoa(i + 1, buffer, bufferLength);

        eventName += buffer;
        cmdArgs += eventName;

        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        si.cb = sizeof(STARTUPINFO);
        ZeroMemory(&si, sizeof(STARTUPINFO));

        handleReadyEvents[i] = CreateEvent(NULL, TRUE,
                                           FALSE, eventName.c_str());

        char tempArg[60];
        strcat(tempArg, cmdArgs.c_str());

        if (CreateProcess(NULL, tempArg,
                          NULL, NULL,
                          FALSE, CREATE_NEW_CONSOLE,
                          NULL, NULL,
                          &si, &pi) == false) {
            std::cout << "Creation process error.\n";

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
    }
}

DWORD WINAPI messaging(LPVOID p) {
    employee* errorEmp = new employee;
    errorEmp->num = -1;

    HANDLE hPipe = (HANDLE)p;
    while(1) {
        DWORD readBytes;
        char message[messageLength];

        bool isRead = ReadFile(hPipe, message,
                               messageLength, &readBytes, NULL);

        if (isRead == false) {
            if (ERROR_BROKEN_PIPE == GetLastError()) {
                std::cout << "Client disconnected." << std::endl;
            }
            else {
                std::cerr << "Error in reading a message." << std::endl;
            }
            break;
        }

        if (strlen(message) != 0) {
            char command = message[0];
            message[0] = ' ';
            int id = atoi(message);

            DWORD bytesWritten;
            EnterCriticalSection(&cs);
            employee* empToSend = findEmployee(id);
            LeaveCriticalSection(&cs);

            if (NULL == empToSend){
                empToSend = errorEmp;
            }
            else {
                int ind = empToSend - employees;

                if(empIsModifying[ind]) {
                    empToSend = errorEmp;
                }
                else{
                    if(command == 'r') {
                        std::cout << "Requested to read ID " << id << ".";
                    } else if(command == 'w') {
                        std::cout << "Requested to modify ID " << id << ".";
                        empIsModifying[ind] = true;
                    } else {
                        std::cout << "Unknown request. ";
                    }
                }
            }
            bool isSent = WriteFile(hPipe, empToSend,
                                    employeeSize, &bytesWritten, NULL);
            if (isSent == true) {
                std::cout << "Answer is sent.\n";
            }
            else {
                std::cout << "Error in sending answer.\n";
            }

            if (empToSend != errorEmp && 'w' == command) {
                isRead = ReadFile(hPipe, empToSend,
                                  employeeSize, &readBytes, NULL);
                if(isRead == false) {
                    std::cerr << "Error in reading a message." << std::endl;
                    break;
                }
                else {
                    std::cout << "Employee record changed.\n";

                    empIsModifying[empToSend - employees] = false;
                    EnterCriticalSection(&cs);
                    sortEmployees();
                    LeaveCriticalSection(&cs);
                }
            }
        }
    }
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    delete errorEmp;
    return 0;
}

void openPipes(int clientCount) {
    HANDLE hPipe;
    HANDLE* hThreads = new HANDLE[clientCount];
    for(int i = 0; i < clientCount; ++i){
        hPipe = CreateNamedPipe(pipeName.c_str(), PIPE_ACCESS_DUPLEX,
                                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                                PIPE_UNLIMITED_INSTANCES,0,
                                0,INFINITE, NULL);
        if (!ConnectNamedPipe(hPipe, NULL)){
            std::cout << "No connected clients.\n";
            break;
        }
        if (INVALID_HANDLE_VALUE == hPipe){
            std::cerr << "Create named pipe failed.\n";
            getch();
            return;
        }
        hThreads[i] = CreateThread(NULL, 0,
                                   messaging, (LPVOID)hPipe,
                                   0,NULL);
    }
    std::cout << "Clients connected to pipe.\n";
    WaitForMultipleObjects(clientCount, hThreads, TRUE, INFINITE);
    std::cout << "All clients are disconnected.\n";
    delete[] hThreads;
}

int main() {
    std::string filename;
    std::cout << "Input name of file: ";
    std::cin >> filename;
    std::cout << "Input count of employees: ";
    std::cin >> employeeCount;

    readDataSTD();
    writeData(filename);
    sortEmployees();

    int countOfClient = generateClientsNumber();
    empIsModifying = new bool[employeeCount];

    for(int i = 0; i < employeeCount; ++i) {
        empIsModifying[i] = false;
    }

    InitializeCriticalSection(&cs);
    HANDLE handleStartALL = CreateEvent(NULL, TRUE,
                                        FALSE, "START_ALL");

    handleReadyEvents = new HANDLE[countOfClient];
    startPocesses(countOfClient);

    WaitForMultipleObjects(countOfClient, handleReadyEvents,
                           TRUE, INFINITE);
    std::cout << "All processes are ready.Starting.\n";

    SetEvent(handleStartALL);

    openPipes(countOfClient);

    for(int i = 0; i < employeeCount; ++i) {
        employees[i].print();
    }

    std::cout << "Press any key to exit...\n";
    getch();
    DeleteCriticalSection(&cs);

    delete[] empIsModifying;
    delete[] handleReadyEvents;
    delete[] employees;

    return 0;
}