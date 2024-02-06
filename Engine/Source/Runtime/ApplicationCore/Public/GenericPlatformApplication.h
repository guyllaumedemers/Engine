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
class	FGenericWindow;
struct	FGenericWindowDefinition;

/**
 *	Abstraction. Platform Application. Handle Creation Context for a 'Window' Application and platform messaging.
 */
class FGenericPlatformApplication {

public:
	virtual ~FGenericPlatformApplication() = default;

	static	TSharedPtr<FGenericPlatformApplication>		CreatePlatformApplication();
	virtual TSharedPtr<FGenericWindow>					MakeWindow() const { return nullptr; }
	virtual void										SetupWindowContext(TSharedPtr<FGenericWindow> InWindow, FGenericWindowDefinition const& InDefinition) {}

protected:
	TSet<TSharedPtr<FGenericWindow>>	Windows;
};

/**
 *	POD. Represent 'Window' context data. platform independent.
 */
struct FGenericWindowDefinition
{
	float PosX = 0.f;
	float PosY = 0.f;
	float Width = 0.f;
	float Height = 0.f;
};