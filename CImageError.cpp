//:Source:4, "CImageError", 41504ef0
//
// $File:CImageError.cpp$
//
// Copyright (C) 2004 SlapWare, All rights reserved.
//
// $History$
// 21 Sep 2004, stephen lapierre -- Generated 11:55:28 by Genitor OCS V4.50.915.2
//
//:---------------------------------------------------------------------------

#include "stdafx.h"

//:ClassInc
#include "CImageError.h"
#include ".\cimageerror.h"
//#include<boost/filesystem/operations.hpp>

//:Special
#define _ThisClass		CImageError
#define _NumBaseClass	0

//:>                  +-----------------------------------+
//:>------------------|    Member Function Definitions    |-------------------
//:>                  +-----------------------------------+

//::1
// +---------------+
// |  Constructor  |
// +---------------+

namespace slapware {    // begin SlapWare namespace
    CImageError::CImageError(string plog):                       // log file information from ImageGlobals
    //:>Private data initialization
    m_log(
         plog)                           // log file information from ImageGlobals
    {
		::GetCurrentDirectory (sizeof (szPath), szPath);
		m_log = szPath;
		m_log += "\\";
		m_log += plog;
        /////////////////////////////////////////////
        //If Log file exists rename to todays date.//
        /////////////////////////////////////////////
		RWFile p(m_log.c_str());
		if(p.Exists())
		{
			string newName =  m_log.substr(0, m_log.length() - 4);
			newName +=  "_" + FileTime() + ".xml";
			int iDid = rename(m_log.c_str(), newName.c_str());
		}
        //////////////////////////////////
        // Set up Error XML data file.  //
        //////////////////////////////////
		CMarkup errxml( "<?xml version=\"1.0\"?>\r\n" );
		errxml.AddElem("RUN_REPORT");
		errxml.IntoElem();
		errxml.AddElem("RUN_DATE");
		errxml.AddChildElem("NOW", theTime().c_str() );
		m_xmlError = errxml.GetDoc();
		errxml.Save(m_log.c_str() );
		m_xmlError.clear();
    }

//::2
// +---------------+
// |  Constructor  |
// +---------------+

    CImageError::CImageError()
    {
		::GetCurrentDirectory (sizeof (szPath), szPath);
		m_log = szPath;
		m_log += "\\FtpErrors_";
		m_log += FileTime();
		m_log += ".xml";
		//////////////////////////////////
		// Set up Error XML data file.  //
		//////////////////////////////////
		CMarkup errxml( "<?xml version=\"1.0\"?>\r\n" );
		errxml.AddElem("RUN_REPORT");
		errxml.IntoElem();
		errxml.AddElem("RUN_DATE");
		errxml.AddChildElem("NOW", theTime().c_str() );
		errxml.Save(m_log.c_str() );
		m_xmlError.clear();
    }

//::9
// +--------------------+
// |  Copy Constructor  |
// +--------------------+

    CImageError::CImageError(const _ThisClass& rhs_)             // Existing object being copied
    {
        m_log = rhs_.m_log;
        m_xmlError = rhs_.m_xmlError;
    }

//::6
// +--------------+
// |  Destructor  |
// +--------------+

    CImageError::~CImageError()
    {

    }

    void CImageError::Entry(
                           const string& pType,                // Error type
                           const string& pError,
                           const string& pFileName,
                           const string& pLongName,
                           const long& pRecord,
                           const string& pISBN)
    {
        std::string str;
        std::ostringstream strstrm;

		CMarkup errxml;
		if (!errxml.Load(m_log.c_str() ) )
		{
			return; 
		}

		errxml.FindElem("RUN_REPORT");
		errxml.IntoElem();
		errxml.AddElem("ERROR");
		errxml.AddChildElem("WHEN", theTime().c_str() );
		errxml.AddChildElem("TYPE", pType.c_str() );
		errxml.AddChildElem("CAUSE", pError.c_str() );
		errxml.AddChildElem("FileName", pFileName.c_str() );
		if (!pLongName.empty())
			errxml.AddChildElem("LONG_NAME", pLongName.c_str() );
		else
			errxml.AddChildElem("LONG_NAME", "Empty string" );

		string etmp;
		strstrm << pRecord;
		etmp = strstrm.str();    // copy stream to string
		strstrm.str("");         // clear stream
		errxml.AddChildElem("Record_ID", etmp.c_str() );
		errxml.AddChildElem("ISBN", pISBN.c_str() );

		m_xmlError = errxml.GetDoc();
		errxml.Save(m_log.c_str() );
		m_xmlError.clear();
    }

//::8
// +-----------+
// |  Entry()  |
// +-----------+

    void CImageError::Entry(const string& pxmlError)
    {
        std::string str;
        std::ostringstream strstrm;

		std::fstream m_xmlStream(m_log.c_str(), ios::in | ios::out | ios::app);
		if (!m_xmlStream.bad())
		{
			m_xmlStream << pxmlError;
			m_xmlStream.close();
		}
    }

//::11
// +-----------------+
// |  IsValidTime()  |
// +-----------------+

    bool CImageError::IsValidTime()
    {
        struct tm *ptime;
        time_t tm;
        char strTime[3];

        tm = time(NULL);
        ptime = localtime(&tm);
        strftime(strTime ,3 , "%H", ptime);

        string nowTime;
        nowTime = strTime;
        int tok = atoi(nowTime.c_str() );
        ////////////////////////////////////////////
        // true if less than 22:00 hours (10 pm)  //
        ////////////////////////////////////////////
        if ( (tok < 23) && (tok > 1) )
            return true;
        else
            return false;
    }

//::10
// +----------------+
// |  operator =()  |
// +----------------+

    _ThisClass& CImageError::operator =(
                                       const _ThisClass& rhs_)             // right-hand-side of assignment
    {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
            //TODO:  Add code here to assign values from rhs_ to this object.
            m_log = rhs_.m_log;
            m_xmlError = rhs_.m_xmlError;
        }

        return *this;           // Return a reference to this object.
    }

//::3
// +-------------+
// |  theTime()  |
// +-------------+

    string CImageError::theTime()
    {
        struct tm *ptime;
        time_t tm;
        char strTime[60];

        tm = time(NULL);
        ptime = localtime(&tm);
//    strftime(strTime ,60 , "At %a %b %d %H:%M ", ptime);
        strftime(strTime ,60 , "%a-%b-%d-%H:%M", ptime);

        string nowTime;
        nowTime = strTime;
        return(nowTime);
    }

    string CImageError::FileTime(void)
    {
        struct tm *ptime;
        time_t tm;
        char strTime[60];

        tm = time(NULL);
        ptime = localtime(&tm);
        strftime(strTime ,30 , "%m_%d_%H_%M", ptime);

        string nowTime;
        nowTime = strTime;
        return nowTime;
    }
}   // end SlapWare namespace


//:Special
#undef _ThisClass
#undef _NumBaseClass


