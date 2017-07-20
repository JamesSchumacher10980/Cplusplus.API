#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

/////////////////////////////////////////////
//// (C) 2017 James Bernard Schumacher III
/////////////////////////////////////////////

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
