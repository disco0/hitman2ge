#ifndef __UG_H__
#define __UG_H__

#include <stdint.h>
#include <Windows.h>
#include <assert.h>
#include <iostream>
#include <mutex>

#include <d3d9.h>
#include <dxgi.h>

#include <d3d10_1.h>
#include <d3d10.h>

#include <dxgi.h>
#include <d3d11.h>

#include <dxgi.h>
#include <d3d12.h>

#include <gl/GL.h>

//#include "minhook.h"

#define UG_DEBUG 1
static int UG_DEBUG_INIT = 0;

#define DEBUG_INIT \
			do { if (UG_DEBUG && !UG_DEBUG_INIT) { \
			AllocConsole(); \
			freopen("CONOUT$", "w", stdout); \
			UG_DEBUG_INIT = 1; }} while (0)

#define DEBUG_PRINT(fmt, ...) \
            do { if (UG_DEBUG && UG_DEBUG_INIT) std::cout << fmt << std::endl; } while (0)

#ifdef _UNICODE
# define UG_TEXT(text) L##text
#else
# define UG_TEXT(text) text
#endif

#define UG_ARRAY_SIZE(arr) ((size_t)(sizeof(arr)/sizeof(arr[0])))

#define UG_ARCH_X64 0
#define UG_ARCH_X86 0

#if defined(_M_X64)	
# undef  UG_ARCH_X64
# define UG_ARCH_X64 1
#else
# undef  UG_ARCH_X86
# define UG_ARCH_X86 1
#endif

#if UG_ARCH_X64
typedef uint64_t uint_t;
#else
typedef uint32_t uint_t;
#endif

namespace ug
{
	enum Status
	{
		UnknownError = -1,
		NotSupportedError = -2,
		ModuleNotFoundError = -3,

		AlreadyInitializedError = -4,
		NotInitializedError = -5,

		MHError = -6,

		NotImplemented = -7,

		Success = 0,
	};

	enum GraphicsType
	{
		Unknown,

		D3D9,
		D3D10,
		D3D11,
		D3D12,

		GDI,
		GDIPLUS,

		OpenGL,
		Vulkan,

		Auto
	};

	Status init(GraphicsType _renderType = GraphicsType::Auto);
	void shutdown();

	Status bind(uint16_t index, void** original, void* function);
	void unbind(uint16_t index);

	GraphicsType getRenderType();
	uint_t* getMethodsTable();
}

#endif // __UG_H__