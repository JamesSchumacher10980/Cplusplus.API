#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

/////////////////////////////////////////////////
//// (C) 2017 James Bernard Schumacher III
/////////////////////////////////////////////////

/*
   Copyright (C) 2017 James Bernard Schumacher III
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

namespace James
{
    namespace Cpp
    {
        void * AllocateMemory(SizeT nSize) throw()
        {
            void * lpBuffer = 0;
#ifdef CPP_API_OS_WINDOWS

            HANDLE hHeap = ::GetProcessHeap();

            lpBuffer = ::HeapAlloc(hHeap, 0, nSize);

#endif // CPP_API_OS_WINDOWS

            return lpBuffer;
        }

        bool FreeMemory(void * lpBuffer) throw()
        {
            bool bFreed = false;

#ifdef CPP_API_OS_WINDOWS

            HANDLE hHeap = ::GetProcessHeap();

            bFreed = ::HeapFree(hHeap, 0, lpBuffer) == TRUE;
#endif // CPP_API_OS_WINDOWS

            return bFreed;
        }

        CBase::CBase() throw()
        {
        }

        CBase::CBase(const CBase & obj) throw()
        {
        }

        CBase::~CBase() throw()
        {
        }

        CBase & CBase::operator= (const CBase & obj) throw()
        {
            return *this;
        }

        void * CBase::operator new(SizeT nSize) throw()
        {
            return AllocateMemory(nSize);
        }

        void CBase::operator delete(void * lpBuffer) throw()
        {
            FreeMemory(lpBuffer);
        }

        void * CBase::operator new[](SizeT nSize) throw()
        {
            return AllocateMemory(nSize);
        }

        void CBase::operator delete[](void * lpBuffer) throw()
        {
            FreeMemory(lpBuffer);
        }
    }
}
