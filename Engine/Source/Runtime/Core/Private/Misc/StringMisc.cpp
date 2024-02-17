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

#include "Core/Public/Misc/StringMisc.h"

// TODO @gdemers 2024-02-17 Remove reference to C++ lib and handle string length calculation
// differently
#include <cstring>
#ifdef UNICODE

#define STRLEN(Buffer, MaxCount) wcsnlen_s(Buffer, MaxCount)
#define STRCPY(Dest, Src) wcscpy_s(Dest, Src)

#else

#define STRLEN(Buffer, MaxCount) strnlen_s(Buffer, MaxCount)
#define STRCPY(Dest, Src) strcpy_s(Dest, Src)

#endif

FString::FString(ANSICHAR const* String)
{
	// TODO @gdemers 2024-02-17 Need for dynamic arrays here. Otherwise will require rework
	// https://learn.microsoft.com/en-us/cpp/text/how-to-convert-between-various-string-types?view=msvc-170
}

FString::FString(WIDECHAR const* String)
{
	STRCPY(Data, String);
}

int FString::Length() const
{
	return STRLEN(Data, MaxBufferSize);
}
