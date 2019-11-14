#include "pch.h"

unsigned long __stdcall main_thread(void* reserved) {
	/*
		allocate console for debug logs
	*/
	#ifdef _DEBUG
		AllocConsole();
		SetConsoleTitleA("hitman2ge - " __TIMESTAMP__);
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		freopen_s(&stream, "CONOUT$", "w", stderr);
	#endif

	ilog("initializing");

	/*
		hooking directx with universal graphics hook
		https://github.com/alxbrn/universal-graphics-hook/
	*/
	ug::init(ug::D3D11);

	/*
		detect if randomizer mod is enabled
	*/
	auto dinput_handle = GetModuleHandleA("DINPUT8.dll");
	char module_filename[128]; 
	GetModuleFileNameA(dinput_handle, module_filename, 128);

	if (!strstr(module_filename, "Windows\\SYSTEM32")) {
		wlog("randomizer mod detected: %s", module_filename);
		g_randomizer_mod_installed = true;
	}

	/*
		experimental dx12 hook:
			ug::bind(140, (void**)& original_d3d12_present, hooked_d3d12_present);
	*/
	auto dx_hook_status = ug::bind(8, (void**)& original_d3d11_present, hooked_d3d11_present);

	if (ug::getRenderType() != ug::D3D11 || dx_hook_status != ug::Success) {
		wlog("failed to hook directx! (%i)", dx_hook_status);
		MessageBoxA(NULL, "Failed to hook DirectX", NULL, NULL);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(reserved), 0);
	}

	slog("hooked dx11");

	/*
		set input hook and window handle
	*/
	g_this_hwnd = FindWindowA(NULL, "HITMAN 2");
	original_window_process = (WNDPROC)SetWindowLongPtrA(g_this_hwnd, GWLP_WNDPROC, (LONG_PTR)window_process);
	slog("hooked wndproc");

	/*
		fill item pool
	*/
	ilog("parsing item repo....");
	parse_item_repository();
	ilog("parsed item repository (%i items)", g_item_pool.size());

	/*
		hook push_item
	*/
	auto push_item_hook_status = create_hook(get_push_item_address(), &hooked_push_item, (void**)& original_push_item);

	if (push_item_hook_status != MH_OK) {
		wlog("failed to hook push_item! (%i)", push_item_hook_status);
		MessageBoxA(NULL, "Failed to hook push_item", NULL, NULL);

		std::this_thread::sleep_for(std::chrono::seconds(5));
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(reserved), 0);
	}

	slog("hooked push_item (0x%p)", get_push_item_address());

	/*
		experimental hook, used for testing non-equippable disguises:
				create_hook(get_can_apply_disguise_address(), &hooked_can_apply_disguise, (void**)& original_can_apply_disguise);
				slog("hooked can_apply_disguise (0x%p)", get_can_apply_disguise_address());
	*/

	ilog("finished hooking");

	while (!g_should_unload)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	wlog("unloading...");

	disable_all_hooks();

	if (original_window_process)
		SetWindowLongPtrA(g_this_hwnd, GWLP_WNDPROC, (LONG_PTR)original_window_process);

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(reserved), 0);
	return 0ul;
}

int __stdcall DllMain(HMODULE module, DWORD ul_reason_for_call, LPVOID) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		g_this_module = module;
		DisableThreadLibraryCalls(module);
		CreateThread(nullptr, THREAD_ALL_ACCESS, main_thread, module, 0, 0);
	}

	return true;
}

