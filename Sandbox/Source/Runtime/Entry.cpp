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

#include <Core/Public/Misc/CoreDefines.h>

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

// fwd _decl
extern ENGINE_API int  LaunchWindowStartup(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow);
extern ENGINE_API void LaunchWindowShutdown();

// TODO @gdemers 2024-01-27 WinMain should exist under LaunchWindow.cpp according to Unreal
// standard. However, compilation of the Sandbox executable require a Main to be accessible
// to compile, link. Figure out how their C# build tool handle that - See: UEToolchain.cs and more.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {

	// understanding how the CRT invoke Main (Console App) or WinMain (Window App)
	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point
	const int bErrorlevel = LaunchWindowStartup(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	LaunchWindowShutdown();
	return bErrorlevel;
}

#endif