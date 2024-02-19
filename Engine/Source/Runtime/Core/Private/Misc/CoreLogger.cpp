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

#include "Core/Public/Misc/CoreLogger.h"

#include <cstdarg>
#include <cstdio>

#include "Core/Public/CoreMinimal.h"

#ifdef PLATFORM_WINDOWS
#include "ApplicationCore/Public/Windows/WindowsPlatformOutputConsole.h"
#endif

#ifdef UNICODE

#define FORMAT_VA_LIST(Buffer, Count, Format, Argv) vswprintf_s(Buffer, Count, Format, Argv)
#define FORMAT_LIST(Buffer, Format, ...) swprintf_s(Buffer, Format, __VA_ARGS__)

namespace
{
	static TCHAR const** GetLogLevels()
	{
		static TCHAR const* LogLevels[] = { L"FATAL", L"ERROR", L"WARNING", L"MESSAGE", L"DEBUG", L"TRACE" };
		return LogLevels;
	}

	static TCHAR const* GetTimestamp()
	{
		return L"h:m:s";
	}
}

#else

#define FORMAT_VA_LIST(Buffer, Count, Format, Argv) vsnprintf_s(Buffer, Count, Format, Argv)
#define FORMAT_LIST(Buffer, Format, ...) sprintf_s(Buffer, Format, __VA_ARGS__)

namespace
{
	static TCHAR const** GetLogLevels()
	{
		static TCHAR const* LogLevels[] = { "FATAL", "ERROR", "WARNING", "MESSAGE", "DEBUG", "TRACE" };
		return LogLevels;
	}

	static TCHAR const* GetTimestamp()
	{
		return "h:m:s";
	}
}

#endif

namespace
{
	constexpr static int const MaxBufferSize = 3200;
}

void FConsoleLogger::Log(ELogLevel Level, FString const& Fmt, ...)
{
	static TCHAR const** LogLevels = GetLogLevels();

	TCHAR OutputBuffer[MaxBufferSize] = { 0 };

	va_list Argv;
	// TODO @gdemers 2024-02-14 Add timestamp information
	// TODO @gdemers 2024-02-14 Target Console Context in which we output - a custom process is built for that in our GenericOutputConsole
	TCHAR const* Timestamp = GetTimestamp();

	try
	{
		va_start(Argv, Fmt);
		{
			FORMAT_VA_LIST(OutputBuffer, MaxBufferSize, *Fmt, Argv);
		}
		va_end(Argv);
	}
	catch (std::exception const& Exception)
	{
		TCHAR OutputTrace[MaxBufferSize] = { 0 };

		bool const bResult = FORMAT_LIST(OutputTrace, L"[%s][%s] : %s, line:%i, exception_type:%s", Timestamp,
			*((LogLevels)+StaticCast<int>(ELogLevel::LogFatal) * sizeof(TCHAR)),
			__FILE__,
			__LINE__,
			Exception.what());

		if (bResult)
		{
			FFileLogger::Push(OutputTrace);
		}

		va_end(Argv);

		return;
	}

	TCHAR OutputBuffer2[MaxBufferSize] = { 0 };
	try
	{
		bool const bResult = FORMAT_LIST(OutputBuffer2, L"[%s][%s] : %s", Timestamp, *((LogLevels)+StaticCast<int>(Level) * sizeof(TCHAR)), OutputBuffer);
		if (bResult)
		{
			// output formatted message to platform console
			FGenericPlatformOutputConsole::Get().WriteOutputConsole(Level, OutputBuffer2);

			// output formatted message to trace file
			FFileLogger::Push(OutputBuffer2);
		}
	}
	catch (std::exception const& Exception)
	{
		TCHAR OutputTrace[MaxBufferSize] = { 0 };

		bool const bResult = FORMAT_LIST(OutputTrace, L"[%s][%s] : %s, line:%i, exception_type:%s", Timestamp,
			*((LogLevels)+StaticCast<int>(ELogLevel::LogFatal) * sizeof(TCHAR)),
			__FILE__,
			__LINE__,
			Exception.what());

		if (bResult)
		{
			FFileLogger::Push(OutputTrace);
		}

		return;
	}
}

void FFileLogger::Push(FString const& Fmt, ...)
{
	// TODO @gdemers 2024-02-17 Capture message and add it to Queue so we can write to input stream once on exit or before crash
}
