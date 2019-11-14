#include "pch.h"

/*
	d3d11
*/

ID3D11Device* g_d3d11_device = nullptr;
ID3D11DeviceContext* g_d3d11_context = nullptr;

directx_present_func original_d3d11_present = nullptr;
HRESULT __stdcall hooked_d3d11_present(IDXGISwapChain* swap_chain, unsigned int sync_interval, unsigned int flags) {
	static std::once_flag initialize;
	std::call_once(initialize, [&] {
		/*
			initialize devices and imgui
		*/

		swap_chain->GetDevice(__uuidof(g_d3d11_device), reinterpret_cast<void**>(&g_d3d11_device));
		g_d3d11_device->GetImmediateContext(&g_d3d11_context);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplDX11_Init(g_d3d11_device, g_d3d11_context);
		ImGui_ImplWin32_Init(g_this_hwnd);
		ImGui::GetIO().ImeWindowHandle = g_this_hwnd;

		ImGui_ImplDX11_CreateDeviceObjects();
		
		apply_menu_style();
	});

	/*
		run imgui
	*/
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (g_menu_open)
		run_menu();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return original_d3d11_present(swap_chain, sync_interval, flags);
}

/*
	d3d12
	[!] experimental, seems to crash because of the imgui dx12 implementation
*/

ID3D12Device* g_d3d12_device = nullptr;
IDXGISwapChain3* g_d3d12_swapchain = nullptr;

directx_present_func original_d3d12_present = nullptr;
HRESULT __stdcall hooked_d3d12_present(IDXGISwapChain3* swap_chain, unsigned int sync_interval, unsigned int flags) {
	static std::once_flag initialize;
	static ID3D12DescriptorHeap* srv_desc_heap;
	static ID3D12GraphicsCommandList* command_list;
	static ID3D12CommandAllocator* command_allocator;
	static ID3D12CommandQueue* cmd_queue;

	std::call_once(initialize, [&] {
		/*
			set up device and imgui, grab a bunch of d3d12 interfaces needed for drawing
		*/
		swap_chain->GetDevice(__uuidof(g_d3d12_device), reinterpret_cast<void**>(&g_d3d12_device));
		g_d3d12_swapchain = swap_chain;

		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.NumDescriptors = 1;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		D3D12_COMMAND_QUEUE_DESC queueDesc;
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.NodeMask = 0;
		
		g_d3d12_device->CreateDescriptorHeap(&desc, __uuidof(ID3D12DescriptorHeap), (void**)&srv_desc_heap);
		g_d3d12_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)& command_allocator);
		g_d3d12_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator, NULL, __uuidof(ID3D12GraphicsCommandList), (void**)& command_list);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui_ImplWin32_Init(g_this_hwnd);

		ImGui_ImplDX12_Init(g_d3d12_device, 3,
			DXGI_FORMAT_R8G8B8A8_UNORM, srv_desc_heap,
			srv_desc_heap->GetCPUDescriptorHandleForHeapStart(),
			srv_desc_heap->GetGPUDescriptorHandleForHeapStart());


		ImGui::GetIO().ImeWindowHandle = g_this_hwnd;
		ImGui_ImplDX11_CreateDeviceObjects();

		apply_menu_style();
	});

	/*
		run imgui
	*/
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (g_menu_open)
		run_menu();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), command_list);
	return original_d3d12_present(swap_chain, sync_interval, flags);
}