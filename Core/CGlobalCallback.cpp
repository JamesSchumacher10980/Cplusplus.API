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
        CGlobalCallback::CGlobalCallback(PFN_GlobalCallback pfnCallback, ULong32 dwID, bool bDynamic) throw() : m_pfnCallback(pfnCallback),
            m_dwID(dwID), m_bDynamic(bDynamic)
        {
        }

        CGlobalCallback::~CGlobalCallback() throw()
        {
        }

        void CGlobalCallback::Delete() throw()
        {
            if (m_bDynamic == true)
            {
                delete this;
            }
        }

        void CGlobalCallback::Invoke(void * lpArgs) throw()
        {
            Invoke();
        }

        ULong32 CGlobalCallback::GetID() const throw()
        {
            return m_dwID;
        }

        void CGlobalCallback::Invoke() throw()
        {
            if (m_pfnCallback != nullptr)
            {
                (*m_pfnCallback)();
            }
        }
    }
}
