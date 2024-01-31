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

// fwd _decl
extern void BeginExitRequest();
extern bool IsEngineExitRequested();

namespace
{
	inline static int GErrorLevel = 0;

	static int EnginePreInit() {

		// load required library

		if (GErrorLevel < 0)
		{
			BeginExitRequest();
		}

		return GErrorLevel;
	}

	static int EngineInit() {

		// create a window application
		return GErrorLevel;
	}

	static void EngineTick() {

		// tick engine

	}

	static void EnginePreExit() {

		// flush resources, subsystems, etc...

	}

	static void EngineExit() {

		// close libraries

	}
}

// impl engine main
int GuardedMain() {

	// handle library loading for engine
	GErrorLevel = EnginePreInit();

	// handle system initialization
	GErrorLevel = EngineInit();

	// TODO @gdemers 2024-01-09 Inspect Error level and react properly to value - Check level meaning online

	// handle application loop
	while (!IsEngineExitRequested()) {

		// handle engine tick
		EngineTick();
	}

	// handle flushing resources acquired at runtime
	EnginePreExit();

	// handle releasing library modules, dll
	EngineExit();

	return GErrorLevel;
}
