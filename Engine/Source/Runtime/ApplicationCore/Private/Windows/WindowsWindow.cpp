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

// g_var
extern int			CmdShow;

bool FWindowsWindow::Setup(FGenericWindowDefinition const& InDefinition)
{
	DWORD		ExStyle			= InDefinition.ExStyle;
	LPCWSTR		WindowClassName	= InDefinition.WindowClassName;
	LPCWSTR		WindowName		= InDefinition.WindowName;
	DWORD		Style			= InDefinition.Style;
	int			X				= InDefinition.X;
	int			Y				= InDefinition.Y;
	int			W				= InDefinition.W;
	int			H				= InDefinition.H;
	HWND		Parent			= InDefinition.HWindowParent;
	HMENU		Menu			= InDefinition.HMenu;
	HINSTANCE	Instance		= InDefinition.HInstance;
	LPVOID		Param			= InDefinition.Param;

	Details.HWindow = CreateWindowEx(
		ExStyle,
		WindowClassName,
		WindowName,
		Style,
		X, Y,
		W, H,
		Parent,
		Menu,
		Instance,
		Param
	);

	if(Details.HWindow == nullptr)
	{
		return FALSE;
	}

	ShowWindow(Details.HWindow, CmdShow);
	return TRUE;
}

#endif