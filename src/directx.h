#pragma once

using directx_present_func = HRESULT(__stdcall*)(IDXGISwapChain*, unsigned int, unsigned int);

/*
	d3d11
*/
extern ID3D11Device* g_d3d11_device;
extern ID3D11DeviceContext* g_d3d11_context;

extern directx_present_func original_d3d11_present;

HRESULT __stdcall hooked_d3d11_present( IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags );

/*
	d3d12
*/

extern ID3D12Device* g_d3d12_device;
extern IDXGISwapChain3* g_d3d12_swapchain;

extern directx_present_func original_d3d12_present;

HRESULT __stdcall hooked_d3d12_present( IDXGISwapChain3* swap_chain, UINT sync_interval, UINT flags);
