#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <iostream>
#include <vector>

void ListModules(HANDLE hProcess, DWORD processID){
    HMODULE tabModules[1024];
    DWORD bytesNeeded;

    printf("--- DLLs loaded ---\n");
    // 2. Enumérer les modules (LIST_MODULES_ALL permet de voir les DLL 32 et 64 bits)
    if (EnumProcessModulesEx(hProcess, tabModules, sizeof(tabModules), &bytesNeeded, LIST_MODULES_ALL)) {
        int count = bytesNeeded / sizeof(HMODULE);
        std::cout << "[+] " << count << " modules found in the PID " << processID << ":" << std::endl;

        for (int i = 0; i < count; i++) {
            TCHAR moduleName[MAX_PATH];

            // 3. Obtenir le chemin de chaque DLL
            if (GetModuleFileNameEx(hProcess, tabModules[i], moduleName, sizeof(moduleName) / sizeof(TCHAR))) {
		printf("  [%u] %s (Base address: %p)\n", i, moduleName, tabModules[i]);
            }
        }
    } else {
        std::cerr << "[-] Erreur EnumProcessModulesEx: " << GetLastError() << std::endl;
    }

}

void ListSelfModules() {
    HANDLE hProcess = GetCurrentProcess();
    DWORD myPid = GetCurrentProcessId();
    ListModules(hProcess,myPid);
    CloseHandle(hProcess);
}

void ListRemoteModules(DWORD processID) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

    if (NULL == hProcess) {
        std::cerr << "[-] Can't open the process. Error: " << GetLastError() << std::endl;
        return;
    }

    ListModules(hProcess,processID);
    CloseHandle(hProcess);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " self|remote" << std::endl;
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "self"){
        ListSelfModules();
        return 0;
    }
    else if (mode == "remote"){
        DWORD pid; 
        printf("[?] Type the remote pid : "); // Type a number and press enter
        std::cin >> pid; // Get user input from the keyboard
	ListRemoteModules(pid);
    }

    return 0;
}