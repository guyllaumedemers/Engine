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

#include "ApplicationCore/Public/Application.h"

#ifdef PLATFORM_WINDOWS
#include "ApplicationCore/Public/Windows/WindowsPlatformApplication.h"
#endif

// g_var
TUniquePtr<FApplication> FApplication::Application = nullptr;

void FApplication::Create()
{
	Application				= MakeUnique<FApplication>();
	Application->Platform	= FPlatformApplication::CreatePlatformApplication();
}

void FApplication::MakeWindow()
{
	Window = Platform->MakeWindow();
}

void FApplication::Tick()
{
	// application delta time to use on 'this' frame
	float const Delta = GetDelta();

	// tick platform code so we can pump message and repaint application window
	TickPlatform(Delta);
}

float FApplication::GetDelta() const
{
	return 0.f;
}

void FApplication::TickPlatform(float const Delta)
{
	// pump platform messages
	Platform->PumpMessages();
}
