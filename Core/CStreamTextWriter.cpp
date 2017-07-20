#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

namespace James
{
    namespace Cpp
    {
        // ITextWriter destructor
        ITextWriter::~ITextWriter() throw()
        {
        }

        ///////////////////////////////////////////////////
        /// CStreamTextWriter
        ///////////////////////////////////////////////////

        CStreamTextWriter::CStreamTextWriter() throw() : m_pStream(nullptr), m_bOwnStream(false)
        {
        }

        CStreamTextWriter::CStreamTextWriter(IStream * pStream, bool bOwnStream) throw(CApiError) : m_pStream(pStream),
            m_bOwnStream(bOwnStream)
        {
            if (pStream == nullptr)
            {
                CApiError nullError("A null pointer was encountered as an argument. Argument \'pStream\' was null.",
                                    __FILE__, __FUNCTION__, __LINE__, CApiError::ErrorCodes::NullPointer);

                // throw the exception
                throw(nullError);
            }
        }

        CStreamTextWriter::~CStreamTextWriter() throw()
        {
            if (m_pStream != nullptr && m_bOwnStream == true)
            {
                delete m_pStream;
            }
        }
    }
}
