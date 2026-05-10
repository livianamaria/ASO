#include <windows.h>
#include <iostream>
#include <vector>

int main()
{
    SC_HANDLE hSCManager = OpenSCManager(
        NULL,
        NULL,
        SC_MANAGER_ENUMERATE_SERVICE
    );

    if (hSCManager == NULL)
    {
        std::cout << "Eroare la deschiderea Service Control Manager.\n";
        return 1;
    }

    DWORD bytesNeeded = 0;
    DWORD servicesReturned = 0;
    DWORD resumeHandle = 0;

    //apel initial pentru a afla memoria necesara
    EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        NULL,
        0,
        &bytesNeeded,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    std::vector<BYTE> buffer(bytesNeeded);

    //apel real pentru citirea serviciilor active
    BOOL result = EnumServicesStatusEx(
        hSCManager,
        SC_ENUM_PROCESS_INFO,
        SERVICE_WIN32,
        SERVICE_ACTIVE,
        buffer.data(),
        bytesNeeded,
        &bytesNeeded,
        &servicesReturned,
        &resumeHandle,
        NULL
    );

    if (!result)
    {
        std::cout << "Eroare la enumerarea serviciilor.\n";
        CloseServiceHandle(hSCManager);
        return 1;
    }

    ENUM_SERVICE_STATUS_PROCESS* services =
        (ENUM_SERVICE_STATUS_PROCESS*)buffer.data();

    std::cout << "Servicii care ruleaza pe sistem:\n\n";

    for (DWORD i = 0; i < servicesReturned; i++)
    {
        std::wcout << L"Nume serviciu: "
                   << services[i].lpServiceName << std::endl;

        std::wcout << L"Nume afisat: "
                   << services[i].lpDisplayName << std::endl;

        std::wcout << L"PID: "
                   << services[i].ServiceStatusProcess.dwProcessId
                   << std::endl;

        std::wcout << L"-----------------------------\n";
    }

    CloseServiceHandle(hSCManager);

    return 0;
}