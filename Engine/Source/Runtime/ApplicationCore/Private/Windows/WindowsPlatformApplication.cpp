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
#include "Core/Public/CoreMinimal.h"

// g_func
extern void			BeginExitRequest();

// g_var
extern HINSTANCE	HInstance;
extern WCHAR		EngineClass[];

// global_func
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			CONSOLE_LOG("Window Creation Success!");
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
			if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
			{
				CONSOLE_LOG("Window Close Success!");
				DestroyWindow(hwnd);
			}
		}
		return 0;
	case WM_DESTROY:
		{
			CONSOLE_LOG("Window Destroy Begin!");
			PostQuitMessage(0);
			BeginExitRequest();
		}
		break;
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

bool FWindowsPlatformApplication::MakeWindow(FGenericWindowDefinition const& InDefinition, TSharedPtr<FGenericWindow>& OutWindow)
{
	auto const Window = MakeShared<FWindowsWindow>();
	// TODO @gdemers 2024-02-10 Run assertion failure
	Window->Setup(InDefinition);

	auto const OutPair	= Windows.insert(Window);
	OutWindow			= *OutPair.first;

	return OutPair.second;
}

void FWindowsPlatformApplication::PumpMessages() const
{
	MSG OutMsg{};
	BOOL bResult{0};

	while ((bResult = GetMessage(&OutMsg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&OutMsg);
		DispatchMessage(&OutMsg);
	}

	// -1 result in an error, while 0 exit
	if(bResult < 0)
	{
		// TODO @gdemers 2024-02-10 Process error logs
		DWORD ErrorMsg = GetLastError();
		//CONSOLE_LOG("PeekMessage Failure! Error Code:?");
	}
}

#endif
