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

// g_var
extern "C"
{
	HINSTANCE HInstance;
}

// g_var
extern "C" {

	WCHAR EngineClass[] = L"Engine";
}

// global_func
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT Output = 0;

	//// TODO @gdemers handle message pump by operating system
	switch (uMsg)
	{
	case WM_SIZE: // Handle window resizing
		break;
	default:
		break;
	}

	return Output;
}

FWindowsPlatformApplication::FWindowsPlatformApplication()
{

	WNDCLASS WindowClass;
	WindowClass.lpfnWndProc		= WindowProc;
	WindowClass.hInstance		= HInstance;
	WindowClass.lpszClassName	= EngineClass;

	RegisterClass(&WindowClass);
}

TSharedPtr<FGenericPlatformApplication> FWindowsPlatformApplication::CreatePlatformApplication()
{
	return MakeShared<FWindowsPlatformApplication>();
}

TSharedPtr<FGenericWindow> FWindowsPlatformApplication::MakeWindow() const
{
	return MakeShared<FWindowsWindow>();
}

void FWindowsPlatformApplication::SetupWindowContext(TSharedPtr<FGenericWindow> InWindow, FGenericWindowDefinition const& InDefinition)
{
	// setup context details on the object instance
	InWindow->Setup(InDefinition);
	// cache instance
	Windows.insert(InWindow);
}

#endif