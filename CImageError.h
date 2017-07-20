//:Header:4, "CImageError", 41504ef0
//
// $File:CImageError.h$
//
// Copyright (C) 2008 SlapWare, All rights reserved.
//
// $History$
// 10th March 2008, Stephen La Pierre 
//
//:---------------------------------------------------------------------------

#if !defined(_INC_CIMAGEERROR)
#define _INC_CIMAGEERROR

//:Custom
#pragma once
//:End Custom
#ifdef _DEBUG
#define _RWCONFIG 15s
#else
#define _RWCONFIG 12s
#endif


#include <fstream>

//:Include
#if !defined(_INC_STRING)
#include <string>
#endif

#if !defined(_INC_SSTREAM)
#include <sstream>
#endif
#include <rw/rwfile.h>

#include "Markup.h"

#include "time.h"

//:Special
#define _ThisClass		CImageError
#define _NumBaseClass	0

//:Custom
using namespace std;
//:End Custom

//:>                 +-------------------------------------+
//:>-----------------|    CImageError Class Declaration    |------------------
//:>                 +-------------------------------------+
//:Class
namespace slapware {    // begin SlapWare namespace
    class CImageError
    {

    public:

        CImageError(string plog);                   // log file information from ImageGlobals

        CImageError();

        CImageError(const _ThisClass& rhs_);        // Existing object being copied

        ~CImageError();

        void Close();

        void Complete(
                     const long& pCompleted,
                     const long& pSkipped,
                     const long& pFailed);

        void Entry(
                  const string& pType,            // Error type
                  const string& pError,
                  const string& pFileName,
                  const string& pLongName,
                  const long& pRecord,
                  const string& pISBN);

        void Entry(const string& pxmlError);

        bool IsValidTime();

        _ThisClass& operator =(const _ThisClass& rhs_);        // right-hand-side of assignment

        // private:
    protected:

        string m_log;

        char szPath[_MAX_PATH];

        string m_xmlError;                  // XML error's for file generation.

        string FileTime(void);
        string theTime();
    };
}   // end SlapWare namespace


//:Special
#undef _ThisClass
#undef _NumBaseClass

#endif  								// _INC_CIMAGEERROR

