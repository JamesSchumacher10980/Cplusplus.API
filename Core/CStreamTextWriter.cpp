#include "StdAfx.hpp"
#include "James.Cpp.Api.hpp"

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
