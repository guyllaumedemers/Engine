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

#include "ApplicationCore/Public/GenericWindow.h"

#include "Core/Public/Misc/CoreDefines.h"

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

/**
 *	Context Details. Impl specific to Windows platform but can be forward
 *	declared and used externally.
 */
struct FWindowDetails
{
	// TODO @gdemers 2024-02-10 Keep size relevant ordering for optimized cache access
	HWND HWindow = nullptr;
};

/**
 *	Context Details. Impl specific to Windows platform but can be forward
 *	declared and used externally.
 */
struct FGenericWindowDefinition
{
	DWORD		ExStyle			= 0;
	LPCWSTR		WindowClassName = L"";
	LPCWSTR		WindowName		= L"";
	DWORD		Style			= 0;		// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
	int			X, Y			= 0;
	int			W, H			= 0;
	HWND		HWindowParent	= nullptr;
	HMENU		HMenu			= nullptr;	// https://learn.microsoft.com/en-us/windows/win32/menurc/using-menus
	HINSTANCE	HInstance		= nullptr;
	LPVOID		Param			= nullptr;	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/managing-application-state-
};

/**
 *	Context Object. Define a 'Window' context for the Windows platform.
 */
class FWindowsWindow : public FGenericWindow {

public:
	FWindowsWindow()									= default;
	FWindowsWindow(FWindowsWindow const&)				= delete;
	FWindowsWindow(FWindowsWindow&&)					= default;
	FWindowsWindow& operator=(FWindowsWindow const&)	= delete;
	FWindowsWindow& operator=(FWindowsWindow&&)			= default;

	virtual bool Setup(FGenericWindowDefinition const& InDefinition) override;

private:
	// Context details
	FWindowDetails Details;
};

#endif