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

#include "ApplicationCore/Public/Windows/WindowsPlatformOutputConsole.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

FWindowsPlatformOutputConsole::FWindowsPlatformOutputConsole()
{
	Check(AllocConsole(), "Console Malloc Failure!");
}

FWindowsPlatformOutputConsole::~FWindowsPlatformOutputConsole()
{
	Check(FreeConsole(), "Console MemFree Failure!");
}

void FWindowsPlatformOutputConsole::Create()
{
	PlatformOutputConsole = MakeUnique<FWindowsPlatformOutputConsole>();
}

void FWindowsPlatformOutputConsole::WriteOutputConsole(ELogLevel Level, FString const& Buffer)
{
	HANDLE const HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if(HConsole == nullptr)
	{
		return;
	}

	CONSOLE_SCREEN_BUFFER_INFO PreviousBufferInfo{};
	GetConsoleScreenBufferInfo(HConsole, &PreviousBufferInfo);

	WORD BufferAttributes{};
	switch (Level)
	{
	case ELogLevel::LogFatal:
	case ELogLevel::LogError:
		BufferAttributes = FOREGROUND_RED;
		break;
	case ELogLevel::LogWarning:
		BufferAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN;
		break;
	case ELogLevel::LogMessage:
	case ELogLevel::LogDebug:
	case ELogLevel::LogTrace:
		BufferAttributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
		break;
	}

	// set expected color attributes
	SetConsoleTextAttribute(HConsole, BufferAttributes);

	DWORD const	Length				= (DWORD)Buffer.Length();
	LPDWORD		TotalCharWritten	= nullptr;

	// https://learn.microsoft.com/en-us/windows/console/writeconsole
	WriteConsole(HConsole, *Buffer, Length, TotalCharWritten, nullptr);

	// revert color attributes
	SetConsoleTextAttribute(HConsole, PreviousBufferInfo.wAttributes);
}

#endif
