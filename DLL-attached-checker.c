#include <windows.h>
#include <stdio.h>
#include <psapi.h>

// décommenter si Visual Code
// #pragma comment(lib, "psapi.lib")

void PrintLoadedModules() {
    HMODULE tabModules[1024];
    HANDLE hProcess;
    DWORD bytesNeeded;
    unsigned int i;

    // Obtenir le handle du processus actuel
    hProcess = GetCurrentProcess();

    printf("--- DLLs loaded ---\n");

    // Enumerer tous les modules (DLLs) attachés
    if (EnumProcessModules(hProcess, tabModules, sizeof(tabModules), &bytesNeeded)){
        for (i = 0; i < (bytesNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];

            // Obtenir le chemin complet du module
            if (GetModuleFileNameEx(hProcess, tabModules[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                // Afficher le nom du module et son adresse de base
                printf("[%u] %s (Base: %p)\n", i, szModName, tabModules[i]);
            }
        }
    }

    CloseHandle(hProcess);
}

int main() {
    PrintLoadedModules();
    
    printf("\nPress a key to exit...");
    getchar(); // Garde la console ouverte pour voir les resultats
    return 0;
}