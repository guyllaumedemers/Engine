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

#include "ApplicationCore/Public/Windows/WindowsWindow.h"

#include "Core/Public/Misc/CoreDefines.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

void FWindowsWindow::Setup(FGenericWindowDefinition const& InDefinition)
{
	// TODO @gdemers 2024-02-05 Complete Window Creation using win32 api
	LPCWSTR WindowClassName = L"";
	LPCWSTR WindowName = L"";
	DWORD Style = 0;
	int X = 0;
	int Y = 0;
	int Width = 0;
	int Height = 0;
	HWND Parent = nullptr;
	HMENU Menu = nullptr;
	HINSTANCE Instance = nullptr;
	LPVOID Param = nullptr;

	HWND HWindow = CreateWindow(
		WindowClassName,
		WindowName,
		Style,
		X, Y,
		Width, Height,
		Parent,
		Menu,
		Instance,
		Param
	);
}

#endif