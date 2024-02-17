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

char const* GetTimestamp()
{
	return "h:m:s";
}

void FConsoleLogger::Log(ELogLevel Level, char const* Fmt, ...)
{
	static constexpr char const* const LogLevels[] = { "FATAL", "ERROR", "WARNING", "MESSAGE", "DEBUG", "TRACE" };

	int constexpr	MaxBufferSize				= 32000;
	char			OutputBuffer[MaxBufferSize] = { 0 };

	va_list Argv;
	// TODO @gdemers 2024-02-14 Add timestamp information
	// TODO @gdemers 2024-02-14 Target Console Context in which we output - a custom process is built for that in our GenericOutputConsole
	char const* Timestamp = GetTimestamp();

	try
	{
		va_start(Argv, Fmt);
		bool const bResult = vsnprintf_s(OutputBuffer, MaxBufferSize, Fmt, Argv);
		va_end(Argv);
	}
	catch (std::exception const& Exception)
	{
		char OutputTrace[MaxBufferSize] = { 0 };

		bool const bResult = sprintf_s(OutputTrace, "[%s][%s] : %s, line:%i, exception_type:%s", Timestamp,
			LogLevels[StaticCast<int>(ELogLevel::LogFatal)],
			__FILE__,
			__LINE__,
			Exception.what());

		FFileLogger::Push(OutputTrace);
		va_end(Argv);

		return;
	}

	char OutputBuffer2[MaxBufferSize] = { 0 };
	try
	{
		bool const bResult = sprintf_s(OutputBuffer2, "[%s][%s] : %s", Timestamp, LogLevels[StaticCast<int>(Level)], OutputBuffer);
	}
	catch (std::exception const& Exception)
	{
		char OutputTrace[MaxBufferSize] = { 0 };

		bool const bResult = sprintf_s(OutputTrace, "[%s][%s] : %s, line:%i, exception_type:%s", Timestamp,
			LogLevels[StaticCast<int>(ELogLevel::LogFatal)],
			__FILE__,
			__LINE__,
			Exception.what());

		FFileLogger::Push(OutputTrace);

		return;
	}

	// output formatted message to platform console
	FGenericPlatformOutputConsole::Get().WriteOutputConsole(Level, OutputBuffer2);

	// output formatted message to trace file
	FFileLogger::Push(OutputBuffer2);
}

void FFileLogger::Push(char const* Fmt, ...)
{
	// TODO @gdemers 2024-02-17 Capture message and add it to Queue so we can write to input stream once on exit or before crash
}
