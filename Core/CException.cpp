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
        namespace DllData
        {
            const AnsiChar * g_pstrDefaultExceptionMessage = "An unknown exception has occurred.";
        }

        CException::CException() throw() : CBase(), m_pstrErrorMessage(DllData::g_pstrDefaultExceptionMessage), m_pstrFileName(nullptr),
            m_pstrFunctionName(nullptr), m_nLineNumber(0)
        {
        }

        CException::CException(const AnsiChar * pstrErrorMessage) throw() : CBase(), m_pstrErrorMessage(pstrErrorMessage), m_pstrFileName(nullptr),
            m_pstrFunctionName(nullptr), m_nLineNumber(0)
        {
        }

        CException::CException(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName,const AnsiChar * pstrFunctionName,
            ULong32 nLineNumber) throw() : CBase(), m_pstrErrorMessage(pstrErrorMessage),
            m_pstrFileName(pstrFileName), m_pstrFunctionName(pstrFunctionName), m_nLineNumber(nLineNumber)
        {
        }

        CException::CException(const CException & ex) throw() : CBase(ex), m_pstrErrorMessage(ex.m_pstrErrorMessage), m_pstrFileName(ex.m_pstrFileName),
           m_pstrFunctionName(ex.m_pstrFunctionName), m_nLineNumber(ex.m_nLineNumber)
        {
        }

        CException::~CException() throw()
        {
        }

        CException & CException::operator= (const CException & ex) throw()
        {
            if (this != &ex)
            {
                CBase::operator= (ex);

                m_pstrErrorMessage = ex.m_pstrErrorMessage;
                m_pstrFileName = ex.m_pstrFileName;
                m_pstrFunctionName = ex.m_pstrFunctionName;
                m_nLineNumber = ex.m_nLineNumber;
            }

            return *this;
        }

        bool CException::operator== (const CException & ex) const throw()
        {
            if (this != &ex)
            {
                return m_pstrErrorMessage == ex.m_pstrErrorMessage && m_pstrFileName == ex.m_pstrFileName &&
                    m_pstrFunctionName == ex.m_pstrFunctionName && m_nLineNumber == ex.m_nLineNumber;
            }
            else
            {
                return true;
            }
        }

        bool CException::operator!= (const CException & ex) const throw()
        {
            if (this != &ex)
            {
                return m_pstrErrorMessage != ex.m_pstrErrorMessage || m_pstrFileName != ex.m_pstrFileName ||
                m_pstrFunctionName != ex.m_pstrFunctionName || m_nLineNumber != ex.m_nLineNumber;
            }
            else
            {
                return false;
            }
        }
    }
}
