#include "pch.h"
#include "imgui_impl_win32.h"

WNDPROC original_window_process = nullptr;
IMGUI_IMPL_API LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT APIENTRY window_process(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	g_this_hwnd = hwnd;

	if (umsg == WM_KEYDOWN && wparam == VK_INSERT) {
		g_menu_open = !g_menu_open;

		/*
			this is quite a bad method for blocking game input, but 
			i couldn't come up with one that works more consistently
		*/
		if (!g_menu_open)
			PostMessageA(g_this_hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
		else
			PostMessageA(g_this_hwnd, WM_ACTIVATE, WA_INACTIVE, 0);
	}

	if (g_menu_open) {
		/*
			imgui input handler
		*/
		if (ImGui_ImplWin32_WndProcHandler(hwnd, umsg, wparam, lparam))
			return true;
	}

	return CallWindowProcA(original_window_process, hwnd, umsg, wparam, lparam);
}