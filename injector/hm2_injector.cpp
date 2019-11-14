#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <psapi.h>

uint32_t get_process_id(std::string process_name) {
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (snapshot == INVALID_HANDLE_VALUE) {
		printf("[!] failed grabbing process list\n");
		return 0;
	}

	PROCESSENTRY32 process_entry;
	process_entry.dwSize = sizeof(PROCESSENTRY32);

	while (Process32Next(snapshot, &process_entry)) {
		if (process_name == process_entry.szExeFile)
			return process_entry.th32ProcessID;
	} 

	return NULL;
}

int main() {
	SetConsoleTitleA("Hitman 2 Gear Editor Injector");

	if (!std::experimental::filesystem::exists("tool.dll")) {
		printf("[!] couldn't find tool.dll");
		Sleep(4000);
		return 1;
	}

	auto process_id = get_process_id("HITMAN2.exe");

	if (!process_id) {
		printf("[!] failed getting process id, make sure hitman is running\n");
		Sleep(4000);
		return 1;
	}

	printf("[+] process id: %i\n", process_id);

	auto process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
	if (!process) {
		printf("[!] failed opening handle to process!\n");
		Sleep(4000);
		return 1;
	}

	char full_path[MAX_PATH];
	GetFullPathNameA("tool.dll", MAX_PATH, full_path, nullptr);

	auto load_library = reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA"));
	auto remote_string = VirtualAllocEx(process, nullptr, strlen(full_path), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(process, remote_string, full_path, strlen(full_path), nullptr);

	auto thread = CreateRemoteThread(process, nullptr, 0, load_library, remote_string, NULL, nullptr);
	
	if (!thread) {
		printf("[!] error creating thread (%i)", GetLastError());
		Sleep(4000);
		return 1;
	}
	
	printf("[+] finished loading, press insert to open the menu!");
	CloseHandle(process);

	Sleep(5000);
	return 1;
}