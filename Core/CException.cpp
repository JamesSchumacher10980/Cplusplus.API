#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

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
