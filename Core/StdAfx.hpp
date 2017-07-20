#ifndef __JAMES_CPP_API_STDAFX_HPP__
#define __JAMES_CPP_API_STDAFX_HPP__

#if defined(_WIN32) || defined(WIN32)
    #define CPP_API_OS_WINDOWS
    #define CPP_API_PLATFORM_32BITS
#elif defined(_WIN64) || defined(WIN64)
    #define CPP_API_OS_WINDOWS
    #define CPP_API_PLATFORM_64BITS
#endif

#ifdef CPP_API_OS_WINDOWS
    #include <windows.h>
#endif

#endif // __JAMES_CPP_API_STDAFX_HPP__
