//Copyright(c) 2024 gdemers
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#pragma once

#include "Core/Public/Misc/CoreDefines.h"
#include "Core/Public/Misc/StringMisc.h"

/**
 *	Context Object. Abstract LogInfo from exported symbols.
 */
struct ENGINE_API FDebug
{
	static void LogVerifyCheckFailed(FString const& Fmt, ...);
	static void LogAssertFailed		(FString const& Fmt, ...);
};

#ifdef ASSERT_ENABLED

	// DEBUG MODE
	#ifdef _MSC_VER
		#include <intrin.h>
		#define PLATFORM_BREAK() (__debugbreak())
	#else
		#define PLATFORM_BREAK() (__builtin_trap())
	#endif

	#define CHECK_IMPL(expr, fmt, ...)						\
		if(expr) {											\
		}													\
		else {												\
			FDebug::LogVerifyCheckFailed(fmt, __VA_ARGS__);	\
			PLATFORM_BREAK();								\
		}

	// Runtime-time assertion w/ debug_break
	#define Check(expr, fmt, ...) CHECK_IMPL(expr, fmt, __VA_ARGS__)

#else
	#define Check(expr, fmt, ...)
#endif

#ifdef __cpp_static_assert

	// Compile-time assertion
	#define Verify(expr, fmt, ...)											\
		{																	\
			static_assert(expr, FDebug::LogAssertFailed(fmt, __VA_ARGS__));	\
		}

#else
	#error "CppRuntime library doesn't support compile-time assertion symbols! Curr_version < C++11."
	#define Verify(expr, fmt, ...)	
#endif