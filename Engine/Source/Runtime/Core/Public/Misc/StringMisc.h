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

#include "Core/Public/Misc/CoreDefines.h"

// TODO @gdemers 2024-02-17 Update once we tackle allocators
// g_var
static constexpr int MaxBufferSize = 32000;

/**
 *	Basic type. Handle ANSI, UNICODE encoding.
 */
class FString {

public:
	// TODO @gdemers 2024-02-17 Expect to be able to react to platform encoding changes and process
	// string literals in logs without problem!
	FString(ANSICHAR const* String);
	FString(WIDECHAR const* String);

	int Length() const;

	TCHAR const* operator*() const noexcept
	{
		return Data;
	}

private:
	TCHAR Data[32];
};