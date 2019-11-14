#ifndef PCH_H
#define PCH_H

#include <windows.h>
#include <winternl.h>

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <array>
#include <psapi.h>
#include <sstream>
#include <iterator>
#include <cstdint>
#include <memory>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>
#include <fstream>
#include <intrin.h>

#include <D3d12.h>
#include <dxgi.h>
#include <dxgi1_4.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/reader.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/memorystream.h>

#include <MinHook.h>

#pragma comment(lib, "D3d12.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "Rpcrt4.lib")

#include "ug.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_dx12.h"
#include "imgui_impl_win32.h"
#include "directx.h"
#include "menu.h"

#include "signatures.h"
#include "hooks.h"
#include "wnd_proc.h"

#include "util.h"
#include "item_repo.h"
#include "items.h"
#include "globals.h"

#endif 
