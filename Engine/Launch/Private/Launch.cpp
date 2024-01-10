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

#include "Core/Public/CoreMinimal.h"

extern int32_t EnginePreInit() {

	int32_t ErrorLevel = 0;
	// load required library

}

extern int32_t EngineInit() {

	int32_t ErrorLevel = 0;
	// create a window application

}

extern void EngineTick() {

	// tick engine

}

extern void EnginePreExit() {

	// flush resources, subsystems, etc...

}

extern void EngineExit() {

	// close libraries

}

// cross-platform entry point to engine startup
int32_t GuardedMain() {

	// handle library loading for engine
	int32_t ErrorLevel = EnginePreInit();

	// handle system initialization
	ErrorLevel = EngineInit();

	// TODO @gdemers 2024-01-09 Inspect Error level and react properly to value - Check level meaning online

	// handle engine tick
	EngineTick();

	// handle flushing resources acquired at runtime
	EnginePreExit();

	// handle releasing library modules, dll
	EngineExit();

	return ErrorLevel;
};