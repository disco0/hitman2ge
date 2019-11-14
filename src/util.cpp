#include "pch.h"

/*
	log functions with different prefixes
*/

void ilog(const char* fmt, ...) {
#ifdef _DEBUG
	char buffer[0xFF];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	if (GetConsoleWindow() != nullptr)
		printf("[+] %s\n", buffer);
#endif
}

void wlog(const char* fmt, ...) {
#ifdef _DEBUG
	char buffer[0xFF];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	if (GetConsoleWindow() != nullptr)
		printf("[!] %s\n", buffer);
#endif
}

void slog(const char* fmt, ...) {
#ifdef _DEBUG
	char buffer[0xFF];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	if (GetConsoleWindow() != nullptr)
		printf("[*] %s\n", buffer);
#endif
}

void log(const char* fmt, ...) {
#ifdef _DEBUG
	char buffer[0xFF];
	va_list args;
	va_start(args, fmt);
	vsprintf_s(buffer, fmt, args);
	va_end(args);

	if (GetConsoleWindow() != nullptr)
		printf("%s\n", buffer);
#endif
}

/*
	sig scan functions
*/

bool compare_bytes(const uint8_t * current_bytes, const uint8_t * compare_with, const char* mask) {
	for (; *mask; ++current_bytes, ++compare_with, ++mask) {
		if (*mask == 'x' && *current_bytes != *compare_with)
			return false;
	}

	return (*mask == 0);
}

uintptr_t find_signature(const char* bytes, const char* mask) {
	static const auto start_address = (uintptr_t)GetModuleHandleA(nullptr);
	static const auto dos_header = (IMAGE_DOS_HEADER*)start_address;
	static const auto nt_headers = (IMAGE_NT_HEADERS*)((const uint8_t*)dos_header + dos_header->e_lfanew);
	static const auto end_address = start_address + nt_headers->OptionalHeader.SizeOfCode;

	for (uintptr_t current_address = start_address; current_address < end_address; current_address++) {
		uint8_t* current_bytes = (uint8_t*)current_address;
		if (compare_bytes(current_bytes, (uint8_t*)bytes, mask))
			return current_address;
	}

	return NULL;
}

/*
	wrapper functions for uuid stuff
*/

UUID uuid_from_str(const char* str) {
	UUID id;
	UuidFromStringA((RPC_CSTR)str, &id);
	return id;
}

std::string uuid_to_str(UUID uuid) {
	RPC_CSTR uuid_str;
	UuidToStringA(&uuid, &uuid_str);
	return (char*)uuid_str;
}

/*
	wrapper functions for minhook
*/

MH_STATUS create_hook(void* func_address, void* detour_address, void** original) {
	const auto status = MH_CreateHook(func_address, detour_address, original);

	if (status == MH_OK) {
		MH_EnableHook(func_address);
	}

	return status;
}

void remove_hook(void* func_address) {
	MH_DisableHook(func_address);
	MH_RemoveHook(func_address);
}

void disable_all_hooks() {
	MH_DisableHook(MH_ALL_HOOKS);
}