#include "StdAfx.hpp"

//////////////////////////////////////////////////
//// (C) 2017 James Bernard Schumacher III
//////////////////////////////////////////////////

#ifdef CPP_API_OS_WINDOWS

extern "C" BOOL APIENTRY DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved) throw()
{
    switch(dwReason)
    {
    case DLL_PROCESS_ATTACH:
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

#endif // CPP_API_OS_WINDOWS
