#pragma once

extern WNDPROC original_window_process;
LRESULT APIENTRY window_process( HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam );