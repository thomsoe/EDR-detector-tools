# EDRs detection tools
A collection of tools to detect EDRs functionalities

## Attached DLLs Identifier
Simple program to list DLLs attached to the program or a remote one, to be used to identify AV/EDR hooker DLLs.
1. Compile with :\
  `g++ main.cpp -o main.exe`
3. `Usage: main self|remote`
### TODO
- EnumProcessModules (PSAPI) flagged as malicious, to evade
- OpenProcess with PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, to evade
- Add ressources : icon, infos and description
