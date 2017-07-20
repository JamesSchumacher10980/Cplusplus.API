#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

namespace James
{
    namespace Cpp
    {
        IAnsiString::~IAnsiString()
        {
        }

        SizeT IAnsiString::LengthOfCStyleStr(const AnsiChar * pString) throw()
        {
            const AnsiChar * pstrComp1 = pString;

            while (*pstrComp1 != 0)
            {
                ++pstrComp1;
            }

            return pstrComp1 - pString;
        }

        CAnsiString::CAnsiString() throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            const SizeT nDefaultCapacity = DetermineCapacity(0);

            if (nDefaultCapacity != 0)
            {
                try
                {
                    m_pStrData = AllocateChars(nDefaultCapacity);
                }
                catch(const CApiError & error)
                {
                    throw(error);
                }

                m_pStrData[0] = 0;
                m_nCapacity = nDefaultCapacity;
            }
        }

        CAnsiString::CAnsiString(const SizeT & nCapacity, const SizeT & nLength) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            if (nCapacity != 0)
            {
                try
                {
                    m_pStrData = AllocateChars(nCapacity);
                }
                catch(const CApiError & error)
                {
                    CApiError ourError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(ourError);
                }

                m_nCapacity = nCapacity;

                if (nLength >= nCapacity)
                {
                    m_nLength = nCapacity - 1;
                    m_pStrData[m_nLength] = 0;
                }
                else
                {
                    m_pStrData[nLength] = 0;
                    m_nLength = nLength;
                }
            }
            else if (nLength != 0)
            {
                // Need to throw an exception here!
                CApiError error("Invalid parameter inside CAnsiString constructor. Paramater \'nLength\' was non-zero when nCapacity was 0.",
                                __FILE__, __FUNCTION__, __LINE__);

                throw(error);
            }
        }

        CAnsiString::CAnsiString(AnsiChar ch, SizeT nCount) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            const SizeT nAlloc = DetermineCapacity(nCount);

            try
            {
                m_pStrData = AllocateChars(nAlloc);
            }
            catch(const CApiError & error)
            {
                CApiError ourError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                throw(ourError);
            }

            m_nCapacity = nAlloc;

            for (SizeT x = 0; x < nCount; ++x)
            {
                m_pStrData[x] = ch;
            }

            m_pStrData[nCount] = 0;

            m_nLength = nCount;
        }

        CAnsiString::CAnsiString(const AnsiChar * pString) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            if (pString != nullptr)
            {
                const SizeT nLength = LengthOfCStyleStr(pString);

                const SizeT nCapacity = DetermineCapacity(nLength);

                try
                {
                    m_pStrData = AllocateChars(nCapacity);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                m_nCapacity = nCapacity;

                for (SizeT x = 0; x < nLength; ++x)
                {
                    m_pStrData[x] = pString[x];
                }

                m_pStrData[nLength] = 0;
                m_nLength = nLength;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }
        }

        CAnsiString::CAnsiString(const AnsiChar * pString, SizeT nStart, SizeT nCount) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            if (pString != nullptr)
            {
                const SizeT nAlloc = DetermineCapacity(nCount);

                try
                {
                    m_pStrData = AllocateChars(nAlloc);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                m_nCapacity = nAlloc;

                for (SizeT x = 0, y = nStart; x < nCount; ++x, ++y)
                {
                    m_pStrData[x] = pString[y];
                }

                m_pStrData[nCount] = 0;
                m_nLength = nCount;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }
        }

        CAnsiString::CAnsiString(const CAnsiString & str) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            const SizeT nLength = str.GetLength();

            const SizeT nAlloc = DetermineCapacity(nLength);

            try
            {
                m_pStrData = AllocateChars(nAlloc);
            }
            catch(const CApiError & error)
            {
                CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                throw(memError);
            }

            m_nCapacity = nAlloc;

            for (SizeT x = 0; x < nLength; ++x)
            {
                m_pStrData[x] = str.m_pStrData[x];
            }

            m_pStrData[nLength] = 0;
            m_nLength = nLength;
        }

        CAnsiString::CAnsiString(const CAnsiString & str, SizeT nStart, SizeT nCount) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            const SizeT nLength = str.GetLength();

            if (nStart < nLength)
            {
                const SizeT nRemaining = nLength - nStart;
                const SizeT nCharsToCopy = nCount < nRemaining ? nCount : nRemaining;

                const SizeT nAlloc = DetermineCapacity(nCharsToCopy);

                try
                {
                    m_pStrData = AllocateChars(nAlloc);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                m_nCapacity = nAlloc;

                for (SizeT x = 0, y = nStart; x < nCharsToCopy; ++x, ++y)
                {
                    m_pStrData[x] = str.m_pStrData[y];
                }

                m_pStrData[nCharsToCopy] = 0;

                m_nLength = nCharsToCopy;
            }
            else if (nStart == 0)
            {
                const SizeT nAlloc = DetermineCapacity(0);

                try
                {
                    m_pStrData = AllocateChars(nAlloc);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                m_nCapacity = nAlloc;

                m_pStrData[0] = 0;
            }
            else
            {
                CApiError memError("Index into string was out of bounds. Argument \'nStart\' was too high.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::IndexOutOfRange);

                throw(memError);
            }
        }

        CAnsiString::CAnsiString(const CAnsiString * pStrings, SizeT nStringCount) throw(CApiError) : m_pStrData(nullptr), m_nCapacity(0), m_nLength(0)
        {
            if (pStrings != nullptr)
            {
                SizeT nTotalLength = 0;

                for (SizeT x = 0; x < nStringCount; ++x)
                {
                    const SizeT nStringLength = pStrings[x].GetLength();

                    nTotalLength += nStringLength;
                }

                const SizeT nAlloc = DetermineCapacity(nTotalLength);

                try
                {
                    m_pStrData = AllocateChars(nAlloc);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                m_nCapacity = nAlloc;

                SizeT destX = 0;

                for (SizeT x = 0; x < nStringCount; ++x)
                {
                    const SizeT nStringLength = pStrings[x].GetLength();
                    const AnsiChar * pStrData = pStrings[x].GetData();

                    for (SizeT i = 0; i < nStringLength; ++i, ++destX)
                    {
                        m_pStrData[destX] = pStrData[i];
                    }
                }

                m_pStrData[nTotalLength] = 0;
                m_nLength = nTotalLength;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }
        }

        CAnsiString::CAnsiString(CAnsiString && strToMove) throw() : m_pStrData(strToMove.m_pStrData),
            m_nCapacity(strToMove.m_nCapacity), m_nLength(strToMove.m_nLength)
        {
            strToMove.m_pStrData = nullptr;
            strToMove.m_nCapacity = 0;
            strToMove.m_nLength = 0;
        }

        CAnsiString::~CAnsiString() throw()
        {
            if (m_pStrData != nullptr)
            {
                DeleteChars(m_pStrData);
            }
        }

        SizeT CAnsiString::GetCount() const throw()
        {
            return GetLength();
        }

        SizeT CAnsiString::GetMaxCount() const throw()
        {
            if (m_nCapacity != 0)
            {
                return m_nCapacity - 1;
            }
            else
            {
                return 0;
            }
        }

        SizeT CAnsiString::DetermineCapacity(SizeT nLength) const throw()
        {
            SizeT nRequiredSize = 0;

            const SizeT nMinSize = nLength + 1;

            SizeT nBlockCount = nLength / 4096;
            const SizeT nLeftOver = nLength % 4096;

            if (nBlockCount == 0 || nLeftOver != 0)
            {
                ++nBlockCount;
            }

            const SizeT arSizes[10] = { 16, 32, 64, 128, 256, 512, 1024, 2048, nBlockCount * 4096 };

            for (SizeT x = 0; x < 10; ++x)
            {
                if (nMinSize < arSizes[x])
                {
                    nRequiredSize = arSizes[x];
                    break;
                }
            }

            return nRequiredSize;
        }

        AnsiChar * CAnsiString::AllocateChars(SizeT nLength) throw(CApiError)
        {
            if (nLength == 0)
            {
                CApiError error("Invalid parameter. \'nLength\' was zero.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::InvalidParameter);

                throw(error);
            }

            AnsiChar * pRetValue = new AnsiChar[nLength];

            if (pRetValue == nullptr)
            {
                CApiError outOfMemory("Unable to allocate the requested amount of memory.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::OutOfMemory);

                throw(outOfMemory);
            }

            return pRetValue;
        }

        void CAnsiString::DeleteChars(AnsiChar * pstrChars) throw(CApiError)
        {
            if (pstrChars != nullptr)
            {
                delete[] pstrChars;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }
        }

        void CAnsiString::Clear() throw()
        {
            if (m_pStrData != nullptr)
            {
                m_pStrData[0] = 0;
                m_nLength = 0;
            }
        }

        void CAnsiString::Reserve(SizeT nCapacity, bool bKeepData) throw(CApiError)
        {
            if (bKeepData == false)
            {
                m_nLength = 0;
            }

            if (nCapacity > m_nCapacity)
            {
                AnsiChar * pstrTemp = nullptr;

                try
                {
                    pstrTemp = AllocateChars(nCapacity);
                }
                catch(const CApiError & error)
                {
                    CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                    throw(memError);
                }

                if (m_pStrData != nullptr)
                {
                    for (SizeT x = 0; x < m_nLength; ++x)
                    {
                        pstrTemp[x] = m_pStrData[x];
                    }

                    DeleteChars(m_pStrData);
                }

                pstrTemp[m_nLength] = 0;
                m_pStrData = pstrTemp;
                m_nCapacity = nCapacity;
            }
        }

        CAnsiString & CAnsiString::operator= (const AnsiChar & ch) throw(CApiError)
        {
            if (ch != 0)
            {
                if (m_nCapacity < 2)
                {
                    const SizeT nAlloc = DetermineCapacity(1);

                    if (m_pStrData != nullptr)
                    {
                        DeleteChars(m_pStrData);
                        m_pStrData = nullptr;
                        m_nCapacity = 0;
                        m_nLength = 0;
                    }

                    try
                    {
                        m_pStrData = AllocateChars(nAlloc);
                    }
                    catch(const CApiError & error)
                    {
                        CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                        throw(memError);
                    }

                    m_nCapacity = nAlloc;
                }

                m_pStrData[0] = ch;
                m_pStrData[1] = 0;
                m_nLength = 1;
            }
            else
            {
                Clear();
            }

            return *this;
        }

        CAnsiString & CAnsiString::operator= (const AnsiChar * pString) throw(CApiError)
        {
            if (pString != nullptr)
            {
                const SizeT nLength = LengthOfCStyleStr(pString);

                if (nLength >= m_nCapacity)
                {
                    const SizeT nAlloc = DetermineCapacity(nLength);

                    if (m_pStrData != nullptr)
                    {
                        DeleteChars(m_pStrData);
                        m_pStrData = nullptr;
                        m_nCapacity = 0;
                        m_nLength = 0;
                    }

                    try
                    {
                        m_pStrData = AllocateChars(nAlloc);
                    }
                    catch(const CApiError & error)
                    {
                        CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                        throw(memError);
                    }

                    m_nCapacity = nAlloc;
                }

                for (SizeT x = 0; x < nLength; ++x)
                {
                    m_pStrData[x] = pString[x];
                }

                m_pStrData[nLength] = 0;
                m_nLength = nLength;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument. Argument \'pString\' was null.", __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }

            return *this;
        }

        CAnsiString & CAnsiString::operator= (const CAnsiString & str) throw(CApiError)
        {
            if (this != &str)
            {
                const SizeT nLength = str.GetLength();

                if (nLength >= m_nCapacity)
                {
                    const SizeT nAlloc = DetermineCapacity(nLength);

                    if (m_pStrData != nullptr)
                    {
                        DeleteChars(m_pStrData);
                        m_pStrData = nullptr;
                        m_nCapacity = 0;
                        m_nLength = 0;
                    }

                    try
                    {
                        m_pStrData = AllocateChars(nAlloc);
                    }
                    catch(const CApiError & error)
                    {
                        CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, memError.GetErrorCode());

                        throw(memError);
                    }

                    m_nCapacity = nAlloc;
                }

                for (SizeT x = 0; x < nLength; ++x)
                {
                    m_pStrData[x] = str.m_pStrData[x];
                }

                m_pStrData[nLength] = 0;
                m_nLength = nLength;
            }

            return *this;
        }

        CAnsiString & CAnsiString::operator+= (const AnsiChar & ch) throw(CApiError)
        {
            if (ch != 0)
            {
                const SizeT nNewLength = m_nLength + 1;

                if (nNewLength >= m_nCapacity)
                {
                    const SizeT nCapacity = DetermineCapacity(nNewLength);

                    try
                    {
                        Reserve(nCapacity, true);
                    }
                    catch(const CApiError & error)
                    {
                        CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                        throw(memError);
                    }
                }

                m_pStrData[m_nLength] = ch;
                ++m_nLength;
                m_pStrData[m_nLength] = 0;
            }

            return *this;
        }

        CAnsiString & CAnsiString::operator+= (const AnsiChar * pString) throw(CApiError)
        {
            if (pString != nullptr)
            {
                const SizeT nAddLength = LengthOfCStyleStr(pString);

                if (nAddLength != 0)
                {
                    const SizeT nNewLength = m_nLength + nAddLength;

                    if (nNewLength >= m_nCapacity)
                    {
                        const SizeT nAlloc = DetermineCapacity(nNewLength);

                        try
                        {
                            Reserve(nAlloc, true);
                        }
                        catch(const CApiError & error)
                        {
                            CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                            throw(memError);
                        }
                    }

                    for (SizeT x = 0, y = m_nLength; x < nAddLength; ++x, ++y)
                    {
                        m_pStrData[y] = pString[x];
                    }

                    m_pStrData[nNewLength] = 0;
                    m_nLength = nNewLength;
                }
            }
            else
            {
                const AnsiChar * pstrErrorMessage = "A null pointer was encountered as an argument. Argument \'pString\' was null.";

                CApiError nullError(pstrErrorMessage, __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }

            return *this;
        }

        CAnsiString & CAnsiString::operator+= (const CAnsiString & str) throw(CApiError)
        {
            if (this != &str)
            {
                const SizeT nAddLength = str.GetLength();

                if (nAddLength != 0)
                {
                    const SizeT nNewLength = m_nLength + nAddLength;

                    if (nNewLength >= m_nCapacity)
                    {
                        const SizeT nAlloc = DetermineCapacity(nNewLength);

                        try
                        {
                            Reserve(nAlloc, true);
                        }
                        catch(const CApiError & error)
                        {
                            CApiError memError(error.GetErrorMessage(), __FILE__, __FUNCTION__, __LINE__, error.GetErrorCode());

                            throw(memError);
                        }
                    }

                    for (SizeT x = 0, y = m_nLength; x < nAddLength; ++x, ++y)
                    {
                        m_pStrData[y] = str.m_pStrData[x];
                    }

                    m_pStrData[nNewLength] = 0;
                    m_nLength = nNewLength;
                }
            }

            return *this;
        }

        CAnsiString CAnsiString::operator+ (const AnsiChar & ch) const throw(CApiError)
        {
            if (ch != 0)
            {
                const SizeT nNewLength = m_nLength + 1;
                const SizeT nAlloc = DetermineCapacity(nNewLength);

                // an exception will be thrown on failure to allocate
                // in this constructor
                CAnsiString strRet(static_cast<SizeT>(nAlloc), nNewLength);

                for (SizeT x = 0; x < m_nLength; ++x)
                {
                    strRet.m_pStrData[x] = m_pStrData[x];
                }

                strRet.m_pStrData[m_nLength] = ch;
                strRet.m_pStrData[nNewLength] = 0;

                // no need to set the length, it was set in the constructor

                return strRet;
            }
            else
            {
                // if this copy constructor fails, the exception will be thrown from it.
                const CAnsiString strCopy(*this);

                return strCopy;
            }
        }

        CAnsiString CAnsiString::operator+ (const AnsiChar * pString) const throw(CApiError)
        {
            if (pString != nullptr)
            {
                const SizeT nAddLength = LengthOfCStyleStr(pString);

                if (nAddLength != 0)
                {
                    const SizeT nNewLength = m_nLength + nAddLength;
                    const SizeT nAlloc = DetermineCapacity(nNewLength);
                    CAnsiString strRet(static_cast<SizeT>(nAlloc), nNewLength);

                    SizeT destX = 0;

                    for (SizeT i = 0; i < m_nLength; ++i, ++destX)
                    {
                        strRet.m_pStrData[destX] = m_pStrData[i];
                    }

                    for (SizeT x = 0; x < m_nLength; ++x,++destX)
                    {
                        strRet.m_pStrData[destX] = pString[x];
                    }

                    strRet.m_pStrData[nNewLength] = 0;

                    return strRet;
                }
                else
                {
                    const CAnsiString strCopy(*this);

                    return strCopy;
                }
            }
            else
            {
                const AnsiChar * pstrErrorMessage = "A null pointer was encountered as an argument. Argument \'pString\' was null.";

                CApiError nullError(pstrErrorMessage, __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                throw(nullError);
            }
        }

        CAnsiString CAnsiString::operator+ (const CAnsiString & str) const throw(CApiError)
        {
            const SizeT nAddLength = str.GetLength();

            if (nAddLength != 0)
            {
                const SizeT nNewLength = m_nLength + nAddLength;

                const SizeT nAlloc = DetermineCapacity(nNewLength);

                CAnsiString strRet(static_cast<SizeT>(nAlloc), nNewLength);

                SizeT destX = 0;

                for (SizeT i = 0; i < m_nLength; ++i, ++destX)
                {
                    strRet.m_pStrData[destX] = m_pStrData[i];
                }

                for (SizeT x = 0; x < nAddLength; ++x, ++destX)
                {
                    strRet.m_pStrData[destX] = str.m_pStrData[x];
                }

                strRet.m_pStrData[nNewLength] = 0;

                return strRet;
            }
            else
            {
                const CAnsiString strCopy(*this);

                return strCopy;
            }
        }

        CAnsiString operator+ (const AnsiChar & ch, const CAnsiString & str) throw(CApiError)
        {
            if (ch != 0)
            {
                const SizeT nAddLength = str.GetLength();

                if (nAddLength != 0)
                {
                    const SizeT nNewLength = nAddLength + 1;
                    const SizeT nAlloc = nNewLength + 1;

                    // Exception will be thrown here on failure
                    CAnsiString strRet(static_cast<SizeT>(nAlloc), nNewLength);

                    SizeT destX = 0;

                    strRet.m_pStrData[destX] = ch;
                    ++destX;

                    for (SizeT x = 0; x < nAddLength; ++x, ++destX)
                    {
                        strRet.m_pStrData[destX] = str.m_pStrData[x];
                    }

                    strRet.m_pStrData[nNewLength] = 0;

                    return strRet;
                }
                else
                {
                    // Exception will be thrown here on failure!
                    const CAnsiString strChar(ch, 1);

                    return strChar;
                }
            }
            else
            {
                // Exception will be thrown on failure!
                const CAnsiString strCopy(str);

                return strCopy;
            }
        }

        CAnsiString operator+ (const AnsiChar * pString, const CAnsiString & str) throw(CApiError)
        {
            if (pString != nullptr)
            {
                // It's not null, try and get the length. Let's hope it's valid and null terminated (the 0 code value in this case, not a pointer)
                const SizeT nLength = IAnsiString::LengthOfCStyleStr(pString);

                if (nLength != 0)
                {
                    // The left argument's length is not 0

                    // get the right arguments's length
                    const SizeT nAddLength = str.GetLength();

                    if (nAddLength != 0)
                    {
                        // The right argument's length is not 0
                        const SizeT nNewLength = nLength + nAddLength; // calculate the total required length (not including null)

                        // add one to the new length to get the minimum buffer size (account for null terminator)
                        const SizeT nAlloc = nNewLength + 1;

                        // Create the return value object, with the appropriate constructor
                        // it will throw an exception on failure
                        CAnsiString strRet(static_cast<SizeT>(nAlloc), nNewLength); // had to use static_cast because it's an explicit only constructor

                        // declare the variable to store the destination buffer's current index
                        SizeT destX = 0;

                        // Copy the contents of the left string into the destination buffer
                        for (SizeT x = 0; x < nLength; ++x, ++destX) // Loop nLength times, copying from 0 to (nLength - 1) indices of pString
                        {
                            // note that destX starts at 0, and will be incremented just like x is, but destX remains valid outside of this loop
                            strRet.m_pStrData[destX] = pString[x];
                        }

                        // Copy the contents of the right string into the destination buffer
                        for (SizeT y = 0; y < nAddLength; ++y, ++destX)
                        {
                            strRet.m_pStrData[destX] = str.m_pStrData[y];
                        }

                        // null terminate the buffer
                        strRet.m_pStrData[nNewLength] = 0; // note that destX should be equal to nNewLength

                        // return the string object
                        return strRet;
                    }
                    else
                    {
                        // the right argument's length is 0, return a copy of the left argument
                        // note that an exception will be thrown if an error occurs
                        const CAnsiString strLeftCopy(pString, 0, nLength); // Call the range constructor, we know it's length!

                        return strLeftCopy;
                    }
                }
                else
                {
                    // the left argument's length is 0, return a copy of the right argument
                    // note that an exception will be thrown if an error occurs
                    const CAnsiString strCopy(str);

                    return strCopy;
                }
            }
            else
            {
                // the pointer to the null terminated char array was null, it isn't pointing at valid memory
                // This could happen even if it's not null, but if you are careful it shouldn't, but could happen

                // declare the error message string
                const AnsiChar * pstrErrorMessage = "A null pointer was encountered as an argument. Argument \'pString\' was null.";

                // create the exception object, calling it's constructor
                CApiError nullError(pstrErrorMessage, __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                // throw the exception
                throw(nullError);
            }
        }

        bool CAnsiString::operator== (const AnsiChar & ch) const throw()
        {
            if (ch != 0)
            {
                return m_nLength == 1 && m_pStrData[0] == ch;
            }
            else
            {
                return m_nLength == 0;
            }
        }

        bool CAnsiString::operator== (const AnsiChar * pString) const throw(CApiError)
        {
            // Compare this string object for equality against the contents of a char array pointed at by pString

            // check to see if the pointer is NOT null
            if (pString != nullptr)
            {
                // it's not null, we can compare it. (HOPEFULLY)
                // get the length to see if we are even supposed to check for equality

                const SizeT nLength = LengthOfCStyleStr(pString);

                if (nLength != m_nLength)
                {
                    // Lengths are not equal, so obviously there is no reason to check the contents
                    return false;
                }
                else
                {
                    // declare a variable to store whether they are equal or not
                    bool bEqual = true; // assume they are equal, and the first that is not equal, set it to false and break out of the loop

                    for (SizeT x = 0; x < nLength; ++x)
                    {
                        // check if the chars at index x are NOT equal
                        if (m_pStrData[x] != pString[x])
                        {
                            // they aren't equal, set the value to false and break out of the loop
                            bEqual = false;
                            break;
                        }

                        // if they are entirely equal, we will loop through the whole nLength times
                    }

                    // return the value

                    return bEqual;
                }
            }
            else
            {
                // don't want null pointers, throw an exception!
                CApiError nullError("A null pointer was encountered as an argument. Argument \'pString\' was null.",
                                    __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                // throw the exception
                throw(nullError);
            }
        }

        bool CAnsiString::operator== (const CAnsiString & str) const throw()
        {
            // check to see if this is the same object or not
            if (this != &str)
            {
                // it's not, we need to do comparison
                // check the lengths
                if (m_nLength == str.GetLength())
                {
                    bool bEqual = true; // assume they are equal, like above function

                    for (SizeT x = 0; x < m_nLength; ++x)
                    {
                        if (m_pStrData[x] != str.m_pStrData[x])
                        {
                            bEqual = false;
                            break;
                        }
                    }

                    return bEqual;
                }
                else
                {
                    // return false, lengths are not equal
                    return false;
                }
            }
            else
            {
                // it is, just return true
                return true;
            }
        }

        bool CAnsiString::operator!= (const AnsiChar & ch) const throw()
        {
            bool bNotEqual = false;

            if (ch != 0)
            {
                bNotEqual = m_nLength != 1 || m_pStrData[0] != ch;
            }
            else
            {
                bNotEqual = m_nLength != 0;
            }

            return bNotEqual;
        }

        bool CAnsiString::operator!= (const AnsiChar * pString) const throw(CApiError)
        {
            bool bNotEqual = false;

            if (pString != nullptr)
            {
                // get the length of the c style string
                const SizeT nCompareLength = LengthOfCStyleStr(pString);

                if (m_nLength != nCompareLength)
                {
                    bNotEqual = true;
                }
                else
                {
                    for (SizeT x = 0; x < nCompareLength; ++x)
                    {
                        if (m_pStrData[x] != pString[x])
                        {
                            bNotEqual = true;
                            break;
                        }
                    }
                }

                return bNotEqual;
            }
            else
            {
                CApiError nullError("A null pointer was encountered as an argument. Argument \'pString\' was null.",
                                    __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                // throw the exception
                throw(nullError);
            }
        }

        bool CAnsiString::operator!= (const CAnsiString & str) const throw()
        {
            bool bNotEqual = false;

            if (this != &str)
            {
                const SizeT nCompareLength = str.GetLength();

                if (m_nLength != nCompareLength)
                {
                    bNotEqual = true;
                }
                else
                {
                    for (SizeT x = 0; x < nCompareLength; ++x)
                    {
                        if (m_pStrData[x] != str.m_pStrData[x])
                        {
                            bNotEqual = true;
                            break;
                        }
                    }
                }
            }

            return bNotEqual;
        }
    }
}
