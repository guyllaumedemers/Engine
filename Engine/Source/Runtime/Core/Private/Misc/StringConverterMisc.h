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

#include "Core/Public/CoreMinimal.h"
#include "Core/Public/Misc/CoreDefines.h"

#ifdef UNICODE

#define FORMAT_VA_LIST(Buffer, Count, Format, Argv) vswprintf_s(Buffer, Count, Format, Argv)
#define FORMAT_LIST(Buffer, Count, Format, ...) swprintf_s(Buffer, Count, Format, __VA_ARGS__)

#else

#define FORMAT_VA_LIST(Buffer, Count, Format, Argv) vsnprintf_s(Buffer, Count, Format, Argv)
#define FORMAT_LIST(Buffer, Format, ...) sprintf_s(Buffer, Format, __VA_ARGS__)

#endif

/**
 *	 Helper Object. Offers ANSI, UNICODE encoding conversion api.
 */
class FStringMisc {

public:

	static WIDECHAR* Convert(ANSICHAR const* Source);

	template<typename ... TArgs>
	static int Format(TCHAR* OutBuffer, int MaxBufferSize, ANSICHAR const* Fmt, TArgs&&... Args)
	{
		return FORMAT_LIST(OutBuffer, MaxBufferSize, Convert(Fmt), Forward(Args)...);
	}

	template<typename ... TArgs>
	static int Format(TCHAR* OutBuffer, int MaxBufferSize, WIDECHAR const* Fmt, TArgs&&... Args)
	{
		return FORMAT_LIST(OutBuffer, MaxBufferSize, Fmt, Forward(Args)...);
	}
};