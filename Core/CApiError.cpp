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
        CApiError::CApiError() throw() : CException(), m_nErrorCode(ErrorCodes::Success)
        {
        }

        CApiError::CApiError(const AnsiChar * pstrMessage) throw() : CException(pstrMessage), m_nErrorCode(ErrorCodes::UnknownError)
        {
        }

        CApiError::CApiError(ULong32 nErrorCode) throw() : CException(), m_nErrorCode(nErrorCode)
        {
        }

        CApiError::CApiError(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName, const AnsiChar * pstrFunctionName, ULong32 nLineNumber) throw() : CException(pstrErrorMessage, pstrFileName, pstrFunctionName, nLineNumber), m_nErrorCode(ErrorCodes::UnknownError)
        {
        }

        CApiError::CApiError(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName, const AnsiChar * pstrFunctionName, ULong32 nLineNumber, ULong32 nErrorCode) throw() : CException(pstrErrorMessage, pstrFileName, pstrFunctionName, nLineNumber),
            m_nErrorCode(nErrorCode)
        {
        }

        CApiError::CApiError(const CApiError & ex) throw() : CException(ex), m_nErrorCode(ex.m_nErrorCode)
        {
        }

        CApiError::~CApiError() throw()
        {
        }

        CApiError & CApiError::operator= (const CApiError & ex) throw()
        {
            if (this != &ex)
            {
                CException::operator= (ex);

                m_nErrorCode = ex.m_nErrorCode;
            }

            return *this;
        }

        bool CApiError::operator== (const CApiError & ex) const throw()
        {
            if (this != &ex)
            {
                const bool bBaseEqual = CException::operator== (ex);

                if (bBaseEqual == true)
                {
                    return m_nErrorCode == ex.m_nErrorCode;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }

        bool CApiError::operator!= (const CApiError &ex) const throw()
        {
            if (this != &ex)
            {
                const bool bNotEqual = CException::operator!= (ex);

                if (bNotEqual == true)
                {
                    return bNotEqual;
                }
                else
                {
                    return m_nErrorCode != ex.m_nErrorCode;
                }
            }
            else
            {
                return false;
            }
        }
    }
}
