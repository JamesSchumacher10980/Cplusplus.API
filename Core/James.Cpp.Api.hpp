#ifndef JAMES_CPP_API_HPP_INCLUDED
#define JAMES_CPP_API_HPP_INCLUDED

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

#ifdef CPP_API_OS_WINDOWS
    #ifdef __CPP_API_DLL_BUILD__
        #define CPP_API_DLL_EXPORT __declspec(dllexport)
    #else
        #define CPP_API_DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define CPP_API_DLL_EXPORT
#endif

#define CPP_API_CLASS       CPP_API_DLL_EXPORT
#define CPP_API_FUNCTION    CPP_API_DLL_EXPORT

namespace James
{
    namespace Cpp
    {
        typedef char AnsiChar, SByte, Int8;
        typedef unsigned char Byte, UByte, UInt8;
        typedef wchar_t UniChar, WideChar;
        typedef short Int16, Short;
        typedef unsigned short UInt16, UShort;
        typedef int Integer;
        typedef unsigned int UInteger;
        typedef long Int32, Long32;
        typedef unsigned long UInt32, ULong32;
        typedef long long Int64, Long64;
        typedef unsigned long long UInt64, ULong64;
        typedef float Real32, FPV32, Single;
        typedef double Real64, FPV64, Double;

#if !defined(size_t)
    #if defined(CPP_API_PLATFORM_32BITS)
        typedef unsigned int size_t;
    #elif defined (CPP_API_PLATFORM_64BITS)
        typedef unsigned __int64 size_t;
    #endif
#endif

        typedef size_t SizeT;

        CPP_API_FUNCTION void * AllocateMemory(SizeT nSize) throw();
        CPP_API_FUNCTION bool FreeMemory(void * lpBuffer) throw();
    }
}

inline void * operator new(James::Cpp::SizeT nSize) throw()
{
    return James::Cpp::AllocateMemory(nSize);
}

inline void operator delete(void * lpBuffer) throw()
{
    James::Cpp::FreeMemory(lpBuffer);
}

inline void * operator new[](James::Cpp::SizeT nSize) throw()
{
    return James::Cpp::AllocateMemory(nSize);
}

inline void operator delete[](void * lpBuffer) throw()
{
    James::Cpp::FreeMemory(lpBuffer);
}

inline void * operator new(James::Cpp::SizeT nSize, void * lpAddress) throw()
{
    return lpAddress;
}

inline void operator delete(void * lpBuffer, void * lpAddress) throw()
{
    // just for matching the placement new operator
}

namespace James
{
    namespace Cpp
    {
        class CPP_API_CLASS CBase
        {
        public:
            CBase() throw();
            CBase(const CBase & obj) throw();
            virtual ~CBase() throw();

            CBase & operator= (const CBase & obj) throw();

            static void * operator new(SizeT nSize) throw();
            static void operator delete(void * lpBuffer) throw();
            static void * operator new[](SizeT nSize) throw();
            static void operator delete[](void * lpBuffer) throw();
        };

        class CPP_API_CLASS CException : public CBase
        {
        public:
            CException() throw();
            CException(const AnsiChar * pstrErrorMessage) throw();
            CException(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName, const AnsiChar * pstrFunctionName, ULong32 nLineNumber) throw();
            CException(const CException & ex) throw();
            virtual ~CException() throw();

            inline const AnsiChar * GetErrorMessage() const throw() { return m_pstrErrorMessage; }
            inline const AnsiChar * GetFileName() const throw() { return m_pstrFileName; }
            inline const AnsiChar * GetFunctionName() const throw() { return m_pstrFunctionName; }
            inline ULong32 GetLineNumber() const throw() { return m_nLineNumber; }

            CException & operator= (const CException & ex) throw();
            bool operator== (const CException & ex) const throw();
            bool operator!= (const CException & ex) const throw();
        protected:
            const AnsiChar * m_pstrErrorMessage;
            const AnsiChar * m_pstrFileName;
            const AnsiChar * m_pstrFunctionName;
            ULong32 m_nLineNumber;
        };

        class CPP_API_CLASS CApiError : public CException
        {
        public:
            enum ErrorCodes : ULong32
            {
                Success = 0,
                InvalidParameter = 0x00000001,
                NullPointer = 0x00000002,
                IndexOutOfRange = 0x00000003,
                AccessViolation = 0xC0000005,
                OutOfMemory = 0xFFFFFFFE,
                UnknownError = 0xFFFFFFFF
            };

            CApiError() throw();
            CApiError(const AnsiChar * pstrErrorMessage) throw();
            CApiError(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName, const AnsiChar * pstrFunctionName, ULong32 nLineNumber) throw();
            CApiError(ULong32 nErrorCode) throw();
            CApiError(const AnsiChar * pstrErrorMessage, const AnsiChar * pstrFileName, const AnsiChar * pstrFunctionName, ULong32 nLineNumber, ULong32 nErrorCode) throw();
            CApiError(const CApiError & error) throw();
            virtual ~CApiError() throw();

            inline ULong32 GetErrorCode() const { return m_nErrorCode; }

            CApiError & operator= (const CApiError & ex) throw();
            bool operator== (const CApiError & ex) const throw();
            bool operator!= (const CApiError & ex) const throw();

#ifdef CPP_API_OS_WINDOWS
            static void Translate_SEH_Exception(UInteger nExceptionCode, struct _EXCEPTION_POINTERS * pPointers);
            static void SetExceptionTranslator();
#endif
        protected:
            // Member Variables
            ULong32 m_nErrorCode;
        };

        class CPP_API_CLASS IDelegate
        {
        public:
            virtual ~IDelegate() throw();

            virtual void Delete() throw() = 0;
            virtual void Invoke(void * lpArgs) throw() = 0;
            virtual ULong32 GetID() const throw() = 0; // Get the ID value of this delegate
                                                       // This is used to remove specific delegates and groups of delegates
        };

        class CPP_API_CLASS ICallback : public IDelegate
        {
        public:
            virtual ~ICallback() throw();

            virtual void Invoke() throw() = 0;
        };

        template <typename ArgType> class TGlobalDelegate : public IDelegate
        {
        public:
            typedef void (*GlobalCallback)(ArgType *);

            TGlobalDelegate(GlobalCallback pfnCallback, ULong32 dwID, bool bDynamic) throw() : m_pfnCallback(pfnCallback), m_dwID(dwID), m_bDynamic(bDynamic)
            {
            }

            virtual ~TGlobalDelegate()
            {
            }

            virtual void Delete() throw()
            {
                if (m_bDynamic == true)
                {
                    delete this;
                }
            }

            virtual void Invoke(void * lpArgs) throw()
            {
                if (m_pfnCallback != nullptr)
                {
                    ArgType * pArgs = reinterpret_cast<ArgType *>(lpArgs);

                    (*m_pfnCallback)(pArgs);
                }
            }

            virtual ULong32 GetID() const throw()
            {
                return m_dwID;
            }
        protected:
            GlobalCallback m_pfnCallback;
            ULong32 m_dwID;
            bool m_bDynamic;
        };

        template <typename Type, typename ArgType> class TDelegate : public IDelegate
        {
        public:
            typedef void (Type::*MemberCallback)(ArgType *);

            TDelegate(Type * pObject, MemberCallback pfnCallback, ULong32 dwID, bool bDynamic) throw() : m_pObject(pObject),
                m_dwID(dwID), m_pfnCallback(pfnCallback), m_bDynamic(bDynamic)
            {
            }

            virtual ~TDelegate()
            {
            }

            virtual void Delete() throw()
            {
                if (m_bDynamic == true)
                {
                    delete this;
                }
            }

            virtual void Invoke(void * lpArgs) throw()
            {
                if (m_pObject != nullptr && m_pfnCallback != nullptr)
                {
                    ArgType * pArgs = reinterpret_cast<ArgType *>(lpArgs);

                    (m_pObject->*m_pfnCallback)(lpArgs);
                }
            }

            virtual ULong32 GetID() const throw()
            {
                return m_dwID;
            }
        protected:
            Type * m_pObject;
            MemberCallback m_pfnCallback;
            ULong32 m_dwID;
            bool m_bDynamic;
        };

        class CPP_API_CLASS CGlobalCallback : public ICallback
        {
        public:
            typedef void (*PFN_GlobalCallback)();

            CGlobalCallback(PFN_GlobalCallback pfnCallback, ULong32 dwID, bool bDynamic) throw();
            virtual ~CGlobalCallback() throw();

            virtual void Delete() throw();
            virtual void Invoke(void * lpArgs) throw();
            virtual ULong32 GetID() const throw();
            virtual void Invoke() throw();
        protected:
            PFN_GlobalCallback m_pfnCallback;
            ULong32 m_dwID;
            bool m_bDynamic;
        };

        template <typename Type> class TArray
        {
        public:
            TArray() throw(CApiError) : m_pArrayData(nullptr), m_nCapacity(0), m_nCount(0), m_nBlockSize(16)
            {
                // An exception will be thrown here if AllocateBuffer() fails.
                m_pArrayData = AllocateBuffer(m_nBlockSize);

                m_nCapacity = m_nBlockSize;
            }

            explicit TArray(const SizeT & nCapacity, const SizeT & nCount, const SizeT & nBlockSize) throw(CApiError) : m_pArrayData(nullptr), m_nCapacity(0),
                m_nCount(0), m_nBlockSize(nBlockSize)
            {
                if (nCapacity != 0)
                {
                    // AllocateBuffer() throws an exception if it fails
                    m_pArrayData = AllocateBuffer(nCapacity);

                    m_nCapacity = nCapacity;

                    const SizeT nConstructCount = nCount < nCapacity ? nCount : nCapacity;

                    // This will also throw the exception
                    // if a constructor does, but it cleans up before doing so
                    DefaultConstructArray(m_pArrayData, 0, nConstructCount);

                    m_nCount = nConstructCount;
                }
            }

            virtual ~TArray() throw()
            {
                if (m_pArrayData != nullptr)
                {
                    if (m_nCount != 0)
                    {
                        DestructArray(m_pArrayData,0, m_nCount);
                    }

                    FreeBuffer(m_pArrayData);
                }
            }
        protected:
            Type * m_pArrayData;
            SizeT m_nCapacity;
            SizeT m_nCount;
            mutable SizeT m_nBlockSize;

            SizeT DetermineCapacity(SizeT nCount) const throw()
            {
                if (m_nBlockSize == 0)
                {
                    m_nBlockSize = 16;
                }

                SizeT nBlockCount = nCount / m_nBlockSize;
                const SizeT nLeftOver = nCount % m_nBlockSize;

                if (nBlockCount == 0 || nLeftOver != 0)
                {
                    ++nBlockCount;
                }

                return nBlockCount * m_nBlockSize;
            }

            static Type * AllocateBuffer(SizeT nCapacity) throw(CApiError)
            {
                const SizeT nAlloc = nCapacity * sizeof(Type);

                Type * pBuffer = reinterpret_cast<Type *>(AllocateMemory(nAlloc));

                if (pBuffer == nullptr)
                {
                    CApiError memError("Unable to allocate enough memory for array buffer.",
                                       __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                    throw(memError);
                }

                return pBuffer;
            }

            static void FreeBuffer(Type * pBuffer) throw()
            {
                FreeMemory(pBuffer);
            }

            static void DefaultConstruct(Type * pObject) throw(CApiError)
            {
                new (pObject) Type();
            }

            static void CopyConstruct(Type * pObject, const Type & obj) throw(CApiError)
            {
                new (pObject) Type(obj);
            }

            static void MoveConstruct(Type * pObject, Type && obj) throw()
            {
                new (pObject) Type(static_cast<Type &&>(obj));
            }

            static void DefaultConstructArray(Type * pBuffer, SizeT nDestStart, SizeT nCount) throw(CApiError)
            {
                Type * pObject = &pBuffer[nDestStart];

                for (SizeT x = 0; x < nCount; ++x)
                {
                    try
                    {
                        new (pObject) Type();
                    }
                    catch(const CApiError & error)
                    {
                        for (SizeT y = x; ; --y)
                        {
                            Type * pObjectToDestroy = &pBuffer[y];

                            pObjectToDestroy->~Type();

                            if (y == nDestStart)
                            {
                                break;
                            }
                        }

                        throw;
                    }

                    ++pObject;
                }
            }

            static void CopyConstructArray(Type * pBuffer, SizeT nDestStart, const Type * pSource, SizeT nSourceStart, SizeT nCount) throw(CApiError)
            {
                Type * pObject = &pBuffer[nDestStart];
                const Type * pSourceObject = &pSource[nSourceStart];

                for (SizeT x = 0; x < nCount; ++x)
                {
                    try
                    {
                        new (pObject) Type(*pSourceObject);
                    }
                    catch(const CApiError & error)
                    {
                        for (SizeT y = x; ; --y)
                        {
                            Type * pObjectToDestroy = &pBuffer[y];

                            pObjectToDestroy->~Type();

                            if (y == nDestStart)
                            {
                                break;
                            }
                        }

                        throw;
                    }

                    ++pObject;
                    ++pSourceObject;
                }
            }

            static void MoveConstructArray(Type * pBuffer, SizeT nDestStart, const Type * pSource, SizeT nSourceStart, SizeT nCount) throw()
            {
                Type * pObject = &pBuffer[nDestStart];
                const Type * pSourceObject = &pSource[nSourceStart];

                for (SizeT x = 0; x < nCount; ++x)
                {
                    new (pObject) Type(static_cast<Type &&>(*pSourceObject));

                    ++pObject;
                    ++pSourceObject;
                }
            }

            static void Destruct(Type * pObject) throw()
            {
                pObject->~Type();
            }

            static void DestructArray(Type * pArray, SizeT nStart, SizeT nCount) throw()
            {
                for (SizeT x = 0; x < nCount; ++x)
                {
                    pArray[nStart + x].~Type();
                }
            }
        };

        class CPP_API_CLASS IAnsiString : public CBase
        {
        public:
            virtual ~IAnsiString();

            virtual SizeT GetCount() const throw() = 0;
            virtual SizeT GetMaxCount() const throw() = 0;
            virtual SizeT DetermineCapacity(SizeT nLength) const throw() = 0;
            virtual AnsiChar * AllocateChars(SizeT nCount) throw(CApiError) = 0;
            virtual void DeleteChars(AnsiChar * pstrChars) throw(CApiError) = 0;
            virtual void Clear() throw() = 0;
            virtual void Reserve(SizeT nCapacity, bool bKeepData) throw(CApiError) = 0;

            static SizeT LengthOfCStyleStr(const AnsiChar * pstrFileName) throw();
        };

        class CPP_API_CLASS CAnsiString : public IAnsiString
        {
        public:
            // Construction/Destruction
            CAnsiString() throw(CApiError);
            explicit CAnsiString(const SizeT & nCapacity, const SizeT & nLength) throw(CApiError);
            CAnsiString(AnsiChar ch, SizeT nCount) throw(CApiError);
            CAnsiString(const AnsiChar * pString) throw(CApiError);
            CAnsiString(const AnsiChar * pString, SizeT nStart, SizeT nCount) throw(CApiError);

            CAnsiString(const CAnsiString & str) throw(CApiError);
            CAnsiString(const CAnsiString & str, SizeT nStart, SizeT nCount) throw(CApiError);
            CAnsiString(const CAnsiString * pStrings, SizeT nCount) throw(CApiError);
            CAnsiString(CAnsiString && strToMove) throw();
            virtual ~CAnsiString() throw();
            // IAnsiString
            virtual SizeT GetCount() const throw();
            virtual SizeT GetMaxCount() const throw();
            virtual SizeT DetermineCapacity(SizeT nLength) const throw();
            virtual AnsiChar * AllocateChars(SizeT nCount) throw(CApiError);
            virtual void DeleteChars(AnsiChar * pstrChars) throw(CApiError);
            virtual void Clear() throw();
            virtual void Reserve(SizeT nCapacity, bool bKeepData) throw(CApiError);
            // Member Functions
            inline AnsiChar * GetBuffer() { return m_pStrData; }
            inline const AnsiChar * GetData() const { return m_pStrData; }
            inline SizeT GetCapacity() const { return m_nCapacity; }
            inline SizeT GetLength() const { return m_nLength; }
            inline void SetLength(SizeT nLength) throw()
            {
                if (nLength < m_nCapacity)
                {
                    m_pStrData[nLength] = 0;
                    m_nLength = nLength;
                }
            }

            // Overloaded operators
            CAnsiString & operator= (const AnsiChar & ch) throw(CApiError);
            CAnsiString & operator= (const AnsiChar * pString) throw(CApiError);
            CAnsiString & operator= (const CAnsiString & str) throw(CApiError);

            CAnsiString & operator+= (const AnsiChar & ch) throw(CApiError);
            CAnsiString & operator+= (const AnsiChar * pString) throw(CApiError);
            CAnsiString & operator+= (const CAnsiString & str) throw(CApiError);

            CAnsiString operator+ (const AnsiChar & ch) const throw(CApiError);
            CAnsiString operator+ (const AnsiChar * pString) const throw(CApiError);
            CAnsiString operator+ (const CAnsiString & str) const throw(CApiError);

            CPP_API_FUNCTION friend CAnsiString operator+ (const AnsiChar & ch, const CAnsiString & str) throw(CApiError);
            CPP_API_FUNCTION friend CAnsiString operator+ (const AnsiChar * pString, const CAnsiString & str) throw(CApiError);

            bool operator== (const AnsiChar & ch) const throw();
            bool operator== (const AnsiChar * pString) const throw(CApiError);
            bool operator== (const CAnsiString & str) const throw();

            bool operator!= (const AnsiChar & ch) const throw();
            bool operator!= (const AnsiChar * pString) const throw(CApiError);
            bool operator!= (const CAnsiString & str) const throw();

        protected:
            AnsiChar * m_pStrData;
            SizeT m_nCapacity;
            SizeT m_nLength;
        };

        class CPP_API_CLASS IBaseStream
        {
        public:
            virtual ~IBaseStream() throw();

            virtual bool IsOpen() const throw() = 0;
            virtual void Close() throw() = 0;
        };

        class CPP_API_CLASS IReadableStream
        {
        public:
            virtual ~IReadableStream() throw();

            // Interface Methods
            virtual SizeT Read(void * lpBuffer, SizeT nByteCount) throw(CApiError) = 0;
            virtual void ReadByte(Byte * pByte) throw(CApiError) = 0;
        };

        class CPP_API_CLASS IWritableStream
        {
        public:
            virtual ~IWritableStream() throw();

            virtual SizeT Write(const void * lpBuffer, SizeT nByteCount) throw(CApiError) = 0;
            virtual void WriteByte(Byte ucValue) throw(CApiError) = 0;
        };

        class CPP_API_CLASS ISeekableStream
        {
        public:
            virtual ~ISeekableStream() throw();

            enum SeekMode : ULong32
            {
                SeekFromBeginning = 1,
                SeekFromCurrentPos = 2,
                SeekFromEnd = 3
            };

            virtual Int64 GetPosition() const throw() = 0;
            virtual void SetPosition(Int64 nPosition) throw(CApiError) = 0;
            virtual Int64 Seek(Int64 nMovement,SeekMode enSeekMode) throw(CApiError) = 0;
        };

        class CPP_API_CLASS IStream : public IBaseStream, public IReadableStream, public IWritableStream, public ISeekableStream
        {
        public:
            virtual ~IStream() throw();

            virtual Int64 GetSize() const throw() = 0;
            virtual void SetSize(Int64 nLength) throw(CApiError) = 0;
        };

        class CPP_API_CLASS ITextWriter
        {
        public:
            virtual ~ITextWriter() throw();
        };

        class CPP_API_CLASS CStreamTextWriter : public ITextWriter
        {
        public:
            CStreamTextWriter() throw();
            CStreamTextWriter(IStream * pStream, bool bOwnStream) throw(CApiError);
            virtual ~CStreamTextWriter() throw();

        protected:
            IStream * m_pStream;
            bool m_bOwnStream;
        };
    }
}

#endif // JAMES_CPP_API_HPP_INCLUDED
