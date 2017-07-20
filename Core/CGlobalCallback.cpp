#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

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
