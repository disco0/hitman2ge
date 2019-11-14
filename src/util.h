#pragma once

void ilog(const char* fmt, ...);

void wlog(const char* fmt, ...);

void slog(const char* fmt, ...);

void log(const char* fmt, ...);

bool compare_bytes(const uint8_t* current_bytes, const uint8_t* compare_with, const char* mask);

uintptr_t find_signature(const char* bytes, const char* mask);

UUID uuid_from_str(const char* str);

std::string uuid_to_str(UUID uuid);

MH_STATUS create_hook(void* func_address, void* detour_address, void** original);

void remove_hook(void* func_address);

void disable_all_hooks();