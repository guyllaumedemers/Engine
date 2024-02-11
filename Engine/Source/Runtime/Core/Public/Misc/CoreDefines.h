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

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

	// create macro for caching platform target
	#ifndef PLATFORM_WINDOWS
	#define PLATFORM_WINDOWS
	#endif

	// TODO @gdemers 2024-02-11 Determine where UNICODE or ANSI has to be set
	// might not be platform specific ?
	#ifndef UNICODE
	#define UNICODE
	#endif

	#if DCLSPEC_EXPORT
	#define ENGINE_API __declspec(dllexport)
	#else
	#define ENGINE_API __declspec(dllimport)	
	#endif

#else
	#error "Platform currently not supported! Only Windows x64 can run the following project." 
#endif

#if defined(_DEBUG) || defined(__DEBUG__) || defined(DEBUG)

	// enable assertion flag
	#define ASSERT_ENABLED

	// enable debugging flag
	#define DEBUGGING_ENABLED

#endif