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

// stl headers
#include <memory>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "Core/Public/Misc/CoreAsserts.h"
#include "Core/Public/Misc/CoreLogger.h"
#include "Core/Public/Misc/StringMisc.h"

// TODO @gdemers 2024-02-23 REwork all of this, and do proper investigation on Template creation and metaprogramming
// RValue Reference vs Universal Reference, etc... Also create custom allocator and template container type

template<typename TKey, typename TValue>
using TMap = std::unordered_map<TKey, TValue>;

template<typename T>
using TSet = std::set<T>;

template<typename T>
using TUniquePtr = std::unique_ptr<T>;

template<typename T, typename ...Args>
TUniquePtr<T> MakeUnique(Args&&... args) {

	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using TSharedPtr = std::shared_ptr<T>;

template<typename T, typename ...Args>
TSharedPtr<T> MakeShared(Args&&... args) {

	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T>
using TWeakPtr = std::weak_ptr<T>;

template<typename T, typename Arg>
T StaticCast(Arg&& Value)
{
	return static_cast<T>(Value);
}

template<typename T>
T&& Forward(T& Value)
{
	return std::forward<T>(Value);
}

template<typename T>
T&& Forward(T&& Value)
{
	return std::forward<T>(Value);
}

