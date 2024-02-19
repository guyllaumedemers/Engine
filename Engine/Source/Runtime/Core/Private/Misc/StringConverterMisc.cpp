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

#include "StringConverterMisc.h"

// TODO @gdemers 2024-02-17 Remove reference to C++ lib and handle string length calculation
// differently
#include <cstring>
#include <stdlib.h>

extern int MaxBufferSize;

WIDECHAR* FStringMisc::Convert(ANSICHAR const* Source)
{
	size_t const Size = strnlen_s(Source, MaxBufferSize) + 1;

	WIDECHAR* Dest = new WIDECHAR[MaxBufferSize];
	size_t TotalCharConverted = 0;

	mbstowcs_s(&TotalCharConverted, Dest, Size, Source, _TRUNCATE);

	return Dest;
}

WIDECHAR* FStringMisc::Convert(WIDECHAR const* Source)
{
	return const_cast<WIDECHAR*>(Source);
}
