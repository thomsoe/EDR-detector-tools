# EDRs detection tools
A collection of tools to detect EDRs functionalities

## Attached DLLs Identifier
Simple program to list DLLs attached to the program or a remote one, to be used to identify AV/EDR hooker DLLs. I add metadatas to it in order to make it legit to AVs.
1. Modify metadatas as you want in `ressource.rc`
2. Convert the file to object file :\
  `windres ressource.rc -O coff -o ressource.o`
3. Compile the program with :\
  `g++ main.cpp ressource.o -o main.exe -Os`
3. `Usage: main self|remote`
### TODO
- [ ] EnumProcessModules (PSAPI) flagged as malicious, to evade => not required
- [ ] OpenProcess with PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, to evade => not required
- [x] Add ressources : icon, infos and description
