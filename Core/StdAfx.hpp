#ifndef __JAMES_CPP_API_STDAFX_HPP__
#define __JAMES_CPP_API_STDAFX_HPP__

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
