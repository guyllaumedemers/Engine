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

#include "Engine/Public/EngineLoop.h"

// g_func
extern bool			IsEngineExitRequested();
extern void			BeginExitRequest();

// g_var
extern FEngineLoop	GEngineLoop;

namespace
{
	static int EnginePreInit() {

		const int ErrorLevel = GEngineLoop.PreInit();

		return ErrorLevel;
	}

	static int EngineInit() {

		const int ErrorLevel = GEngineLoop.Init();

		return ErrorLevel;
	}

	static void EngineTick() {

		GEngineLoop.Tick();

	}

	static void EnginePreExit() {

		GEngineLoop.PreExit();

	}

	static void EngineExit() {

		GEngineLoop.Exit();

	}
}

// impl engine main
int GuardedMain() {

	// preinit platform setup
	int ErrorLevel = EnginePreInit();

	// early exit for preinit failure
	if (ErrorLevel < 0)
	{
		return ErrorLevel;
	}

	// init platform and application
	ErrorLevel = EngineInit();

	// handle application loop
	while (!IsEngineExitRequested()) {

		// handle engine tick
		EngineTick();
	}

	// handle flushing resources acquired at runtime
	EnginePreExit();

	// handle releasing library modules, dll
	EngineExit();

	return ErrorLevel;
}
