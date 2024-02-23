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

// fwd _decl
enum class ELogLevel;

/**
 *	Context Object. Provide logging API.
 */
struct ENGINE_API FConsoleLogger {

	static void Log(ELogLevel Level, FString const& Fmt, ...);
};

/**
 *	Context Object. Provide logging API.
 */
struct ENGINE_API FFileLogger {

	static void Push(FString const& Fmt, ...);
};

/**
 *	State Object.
 */
enum class ENGINE_API ELogLevel
{
	LogFatal = 0,
	LogError,
	LogWarning,
	LogDebug,
	LogTrace,
	LogMessage
};

#ifdef DEBUGGING_ENABLED

	// enable logging
	#define CONSOLE_LOG(Level, Fmt, ...)  FConsoleLogger::Log(Level, Fmt, __VA_ARGS__)
#endif
