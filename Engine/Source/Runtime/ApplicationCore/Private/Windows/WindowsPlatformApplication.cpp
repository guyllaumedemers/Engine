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

#include "ApplicationCore/Public/Windows/WindowsPlatformApplication.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

#include "ApplicationCore/Public/Windows/WindowsWindow.h"
#include "ApplicationCore/Public/Windows/WindowsPlatformOutputConsole.h"
#include "Core/Public/CoreMinimal.h"

// g_func
extern void			BeginExitRequest();

// g_var
extern HINSTANCE	HInstance;
WCHAR				EngineClass[]			= L"Engine";
WCHAR				ApplicationWindowName[] = L"Application";

/**
 *	Context Object. Impl specific for Windows of a MessageBox dialogue.
 */
struct FGenericMessageBoxDefinition
{
	HWND	HWindow		= nullptr;
	LPCWSTR Text		= nullptr;
	LPCWSTR Caption		= nullptr;
	UINT	Type		= 0;
};

// global_func
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			CONSOLE_LOG(ELogLevel::LogMessage, L"Window Creation Success!");
		}
		break;
	case WM_PAINT:
		{
		}
		break;
	case WM_SIZE:
		{
		}
		break;
	case WM_CLOSE:
		{
			FGenericMessageBoxDefinition Definition;
			Definition.HWindow	= hwnd;
			Definition.Text		= L"Really quit?";
			Definition.Caption	= EngineClass;
			Definition.Type		= MB_OKCANCEL;

			if (FPlatformApplication::MakeMessageBox(Definition) == IDOK)
			{
				DestroyWindow(hwnd);
			}
		}
		return 0;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			BeginExitRequest();
		}
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

FWindowsPlatformApplication::FWindowsPlatformApplication()
{
	// TODO @gdemers 2024-02-07 Add support for Cursor and Application Icon
	WNDCLASS WindowClass{};
	WindowClass.lpfnWndProc		= WindowProc;
	WindowClass.hInstance		= HInstance;
	WindowClass.lpszClassName	= EngineClass;

	RegisterClass(&WindowClass);
}

FWindowsPlatformApplication::~FWindowsPlatformApplication()
{
	UnregisterClass(EngineClass, HInstance);
}

TSharedPtr<FGenericPlatformApplication> FWindowsPlatformApplication::CreatePlatformApplication()
{
	return MakeShared<FWindowsPlatformApplication>();
}

TSharedPtr<FGenericWindow> FWindowsPlatformApplication::MakeWindow()
{
	// TODO @gdemers 2024-02-10 For now, we only ever create a single window. Context Data provided here
	// represent the Application Window.
	// Move Context Detail generation outside this function so Window creation gets passed
	// details specific to the calling function and be configured from the caller point of View
	// i.e 'this' function call should ONLY create an empty context window
	// and be initialized AFTER
	// The interface for the Factory method that generate the required data should be platform agnostic
	FGenericWindowDefinition WindowDefinition{};
	WindowDefinition.ExStyle			= 0;
	WindowDefinition.WindowClassName	= EngineClass;
	WindowDefinition.WindowName			= ApplicationWindowName;
	WindowDefinition.Style				= WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
	WindowDefinition.X					= 100;
	WindowDefinition.Y					= 100;
	WindowDefinition.W					= 400;
	WindowDefinition.H					= 400;
	WindowDefinition.HWindowParent		= nullptr;
	WindowDefinition.HInstance			= HInstance;
	WindowDefinition.Param				= nullptr;

	auto const Window = MakeShared<FWindowsWindow>();
	Check(Window->Setup(WindowDefinition), "Window Malloc Failure!");

	auto const OutPair	= Windows.insert(Window);
	return *OutPair.first;
}

int FWindowsPlatformApplication::MakeMessageBox(FGenericMessageBoxDefinition const& InDefinition)
{
	return MessageBox(
		InDefinition.HWindow,
		InDefinition.Text,
		InDefinition.Caption,
		InDefinition.Type
	);
}

void FWindowsPlatformApplication::PumpMessages() const
{
	MSG OutMsg{};
	BOOL bResult{0};

	while ((bResult = PeekMessage(&OutMsg, nullptr,NULL, NULL, PM_REMOVE)) > 0)
	{
		TranslateMessage(&OutMsg);
		DispatchMessage(&OutMsg);
	}

	// -1 result in an error, while 0 exit
	if(bResult < 0)
	{
		CONSOLE_LOG(ELogLevel::LogMessage, "PeekMessage Failure! Error Code: {0}", GetLastError());
	}
}

#endif
