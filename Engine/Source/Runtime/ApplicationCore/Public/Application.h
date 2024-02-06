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

// fwd decl
class FGenericPlatformApplication;

/**
 *	Core Application. Handle the creation context for the 'Window' Application and
 *	interface with platform abstraction layer.
 */
class FApplication {

public:
	FApplication() = default;
	FApplication(const FApplication&) = delete;
	FApplication(FApplication&&) = delete;
	FApplication& operator=(const FApplication&) = delete;
	FApplication& operator=(FApplication&&) = delete;

	// TODO @gdemers 2024-02-04 Provide impl for SharedRef. Require being safe noexcept ?
	static FApplication&	Get() { return (*Application); }
	static void				Create();
	void					MakeWindow();

private:
	static void				Create(TSharedPtr<FGenericPlatformApplication> InPlatform);

	TSharedPtr<FGenericPlatformApplication> Platform;
	static TSharedPtr<FApplication>			Application;
};