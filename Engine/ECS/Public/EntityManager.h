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

#include "../../Core/CoreMinimal.h"

struct FEntityData;

// An ENGINE class that provide api calls to Create, Read, Update and Destroy
// Entities Object (C.R.U.D). 
class FEntityManager {
public:
	// TODO @gdemers 2024-01-07 Update function signature to reflect actual requirements for CRUD api (placeholder for now)
	static uint32_t Create();
	static FEntityData const& Read(uint32_t Id);
	static void Update(uint32_t Id);
	static bool Destroy(uint32_t Id);

protected:
	static TUniquePtr<FEntityManager>& Get();

private:
	inline static TUniquePtr<FEntityManager> Singleton = nullptr;
	TMap<uint32_t, FEntityData> Entities;
};