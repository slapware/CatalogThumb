//:Source:5, "CImageGlobals", 41b09148
//
// $File:CImageGlobals.cpp$
//
// Copyright (C) 2004 SlapWare, All rights reserved.
//
// $History$
// 03 Dec 2004, stephen lapierre -- Generated 11:16:08 by Genitor OCS V4.50.915.2
//
//:---------------------------------------------------------------------------

//:ClassInc
#include "CImageGlobals.h"
//#include <boost/algorithm/string.hpp>
//#include "boost/algorithm/string/replace.hpp"
using namespace std;
//using namespace boost;

//:Include
#if !defined(_INC_SSTREAM)
#include <sstream>
#endif

//:Special
#define _ThisClass		CImageGlobals
#define _NumBaseClass	0

//:>                  +-----------------------------------+
//:>------------------|    Member Function Definitions    |-------------------
//:>                  +-----------------------------------+

//::1
// +---------------+
// |  Constructor  |
// +---------------+

namespace slapware {    // begin SlapWare namespace
    CImageGlobals::CImageGlobals(const _ThisClass& rhs_)             // Existing object being copied
    {
        //TODO:  Add copy construction code here.
        m_localSmall = rhs_.m_localSmall;
        m_localLarge = rhs_.m_localLarge;
        m_medLocal = rhs_.m_medLocal;
        m_fileStore = rhs_.m_fileStore;
        m_imgFormat = rhs_.m_imgFormat;
        m_dwShareCount = rhs_.m_dwShareCount;
        m_dwSmallWidth = rhs_.m_dwSmallWidth;
        m_dwSmallHeight = rhs_.m_dwSmallHeight;
        m_dwLargeWidth = rhs_.m_dwLargeWidth;
        m_dwLargeHeight = rhs_.m_dwLargeHeight;
        m_dwMedWidth = rhs_.m_dwMedWidth;
        m_dwMedHeight = rhs_.m_dwMedHeight;
		m_dwMedLargeHeight = rhs_.m_dwMedLargeHeight;
		m_dwMedLargeWidth = rhs_.m_dwMedLargeWidth;
        m_addr = rhs_.m_addr;
        m_port = rhs_.m_port;
 		m_authMode = rhs_.m_authMode;
		m_pushTable = rhs_.m_pushTable;
		m_renameMode = rhs_.m_renameMode;
		m_rename = rhs_.m_rename;
		m_stepIn = rhs_.m_stepIn;
       makeShareMap();
    }

//::2
// +---------------+
// |  Constructor  |
// +---------------+

    CImageGlobals::CImageGlobals()
    {
        //TODO:  Add construction code here.
        // Tip:  Keep default constructor code as simple as possible to
        //       minimize cost of creating temporaries or arrays.
    }

//::3
// +--------------+
// |  Destructor  |
// +--------------+

    CImageGlobals::~CImageGlobals()
    {
        //TODO:  Add clean-up code here.
    }

//::44
// +-------------+
// |  GetAddr()  |
// +-------------+

    string CImageGlobals::GetAddr() const
    {
        return m_addr;
    }

//::4
// +------------------+
// |  GetDeleteRec()  |
// +------------------+

    DWORD CImageGlobals::GetDeleteRec() const
    {
        return m_deleteRec;
    }

//::5
// +------------------+
// |  GetImgFormat()  |
// +------------------+

    string CImageGlobals::GetImgFormat() const
    {
        return m_imgFormat;
    }

//::6
// +--------------------+
// |  GetLargeHeight()  |
// +--------------------+

    DWORD CImageGlobals::GetLargeHeight() const
    {
        return m_dwLargeHeight;
    }

	DWORD CImageGlobals::GetvLargeHeight() const
	{
		return m_vLargeHeight;
	}

//::7
// +-------------------+
// |  GetLargeWidth()  |
// +-------------------+

    DWORD CImageGlobals::GetLargeWidth() const
    {
        return m_dwLargeWidth;
    }

	DWORD CImageGlobals::GetvLargeWidth() const
	{
		return m_vLargeWidth;
	}

//::8
// +-------------------+
// |  GetLocalLarge()  |
// +-------------------+

    string CImageGlobals::GetLocalLarge() const
    {
        return m_localLarge;
    }

	string CImageGlobals::GetvLocalLarge() const
	{
		return m_vlocalLarge;
	}

//::9
// +-------------------+
// |  GetLocalSmall()  |
// +-------------------+

    string CImageGlobals::GetLocalSmall() const
    {
        return m_localSmall;
    }

//::10
// +------------+
// |  GetLog()  |
// +------------+

    string CImageGlobals::GetLog() const
    {
        return m_log;
    }

//::11
// +------------------+
// |  GetMedHeight()  |
// +------------------+

    DWORD CImageGlobals::GetMedHeight() const
    {
        return m_dwMedHeight;
    }


    DWORD CImageGlobals::GetMedLargeHeight() const
    {
        return m_dwMedLargeHeight;  // ISBN 13
    }


//::12
// +-----------------+
// |  GetMedLocal()  |
// +-----------------+

    string CImageGlobals::GetMedLocal() const
    {
        return m_medLocal;
    }

    string CImageGlobals::GetMedLargeLocal() const
    {
        return m_medLargeLocal;
    }

//::13
// +-----------------+
// |  GetMedWidth()  |
// +-----------------+

    DWORD CImageGlobals::GetMedWidth() const
    {
        return m_dwMedWidth;
    }


    DWORD CImageGlobals::GetMedLargeWidth() const
    {
        return m_dwMedLargeWidth;
    }


//::45
// +-------------+
// |  GetPort()  |
// +-------------+

    string CImageGlobals::GetPort() const
    {
        return m_port;
    }

//::42
// +-----------------+
// |  GetSettings()  |
// +-----------------+

    bool CImageGlobals::GetSettings()
    {
        bool task = false;
        HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
        HKEY m_hKey;

        DWORD dw = RegCreateKeyEx (hKeyRoot, "Software\\North Plains Systems\\NTFS File Broker\\CurrentVersion\\NTFS Shares", 0L, NULL,
                                   REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
                                   &m_hKey, &dw);

        if (dw == ERROR_SUCCESS)
        {
            DWORD dwType;
            DWORD dwSize = sizeof (DWORD);
            DWORD dwDest;

            LONG lRet = RegQueryValueEx (m_hKey, (LPSTR) "ShareCount", NULL,
                                         &dwType, (BYTE *) &dwDest, &dwSize);

            if (lRet == ERROR_SUCCESS)
            {
                m_dwShareCount = dwDest;
                task = true;
            }
            else
            {
                m_dwShareCount = 0;
                task = false;
            }
        }
        RegCloseKey (m_hKey);

        if (!task)
        {
            return false;  // return TRUE  unless you set the focus to a control
        }


        char szPath[MAX_PATH];
        ::GetCurrentDirectory (sizeof (szPath), szPath);
        std::string pXmlSetting = szPath;
        pXmlSetting += "\\cat_config.xml";
		//CkString strContent;
		CMarkup xml;
		if (!xml.Load(pXmlSetting.c_str() ) )
        {
            return false; 
        }
        else
        {
			try
			{
                xml.FindElem();
                xml.IntoElem();

                xml.FindElem("FileStore");
                SetFileStore(xml.GetData().c_str());
                xml.FindElem("TNS");
                SetTNS(xml.GetData().c_str());
                xml.FindElem("Delete");
                SetDeleteRec(atoi(xml.GetData().c_str() ) );
                xml.FindElem("BaseDir");
                SetBaseDir(xml.GetData().c_str());

                xml.FindElem("STEPIN");
                SetStepIn(atoi(xml.GetData().c_str() ) );

                string sAttribName = xml.GetAttribName(0);
                SetUserDir(xml.GetAttrib(sAttribName));
				string m_userStep;

                xml.FindElem("USE_DIR");
                SetUseDir(atoi(xml.GetData().c_str() ) );

                xml.FindElem("SORT_SIZE");
                SetSizeSort(atoi(xml.GetData().c_str() ) );

                xml.FindElem("FTP_HOST");
                SetFtpHost(xml.GetData());
                xml.FindElem("FTP_PORT");
                SetFtpPort(atoi(xml.GetData().c_str() ) );
                xml.FindElem("FTP_USER");
                SetFtpUser(xml.GetData() );
                xml.FindElem("FTP_PASS");
                SetFtpPass(xml.GetData());
                sAttribName = xml.GetAttribName(0);
                SetAuthMode(atoi(xml.GetAttrib(sAttribName).c_str()));

                xml.FindElem("RENAME");
                SetRename(atoi(xml.GetData().c_str() ) );
                sAttribName = xml.GetAttribName(0);
                SetRenameMode(atoi(xml.GetAttrib(sAttribName).c_str()));

                xml.FindElem("DB_TABLE");
                SetDbTable(xml.GetData());
                xml.FindElem("LogName");
                SetLog(xml.GetData());

                xml.FindElem("LocalSmall");
                xml.FindChildElem("Height");
                SetSmallHeight(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Width");
                SetSmallWidth(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Path");
                SetLocalSmall(xml.GetChildData() );
                xml.FindChildElem("FTP_PATH");
                SetSmallFtp(xml.GetChildData() );

                xml.FindElem("LocalMed");
                xml.FindChildElem("Height");
                SetMedHeight(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Width");
                SetMedWidth(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Path");
                SetMedLocal(xml.GetChildData() );
                xml.FindChildElem("FTP_PATH");
                SetMedFtp(xml.GetChildData() );

                xml.FindElem("LocalMedLarge");
                xml.FindChildElem("Height");
                SetMedLargeHeight(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Width");
                SetMedLargeWidth(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Path");
                SetMedLargeLocal(xml.GetChildData() );
                xml.FindChildElem("FTP_PATH");
                SetMedLargeFtp(xml.GetChildData() );

                xml.FindElem("LocalLarge");
                xml.FindChildElem("Height");
                SetLargeHeight(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Width");
                SetLargeWidth(atoi(xml.GetChildData().c_str() ) );
                xml.FindChildElem("Path");
                SetLocalLarge(xml.GetChildData() );
                xml.FindChildElem("FTP_PATH");
                SetLargeFtp(xml.GetChildData() );

				xml.FindElem("LocalVeryLarge");
				xml.FindChildElem("Height");
				SetvLargeHeight(atoi(xml.GetChildData().c_str() ) );
				xml.FindChildElem("Width");
				SetvLargeWidth(atoi(xml.GetChildData().c_str() ) );
				xml.FindChildElem("Path");
				SetvLocalLarge(xml.GetChildData() );
				xml.FindChildElem("FTP_PATH");
				SetvLargeFtp(xml.GetChildData() );


                xml.FindElem("DirectSend");
                xml.FindChildElem("FTP_PATH");
                SetDirectFtp(xml.GetChildData() );
			}
			catch(...)
			{
				return false;
			}
			
        }
        return(task);
    }

//::14
// +-------------------+
// |  GetShareCount()  |
// +-------------------+

    DWORD CImageGlobals::GetShareCount() const
    {
        return m_dwShareCount;
    }

//::15
// +--------------------+
// |  GetSmallHeight()  |
// +--------------------+

    DWORD CImageGlobals::GetSmallHeight() const
    {
        return m_dwSmallHeight;
    }

//::16
// +-------------------+
// |  GetSmallWidth()  |
// +-------------------+

    DWORD CImageGlobals::GetSmallWidth() const
    {
        return m_dwSmallWidth;
    }

    string CImageGlobals::GetTNS() const
    {
        return m_tns;
    }

//::22
// +----------+
// |  Init()  |
// +----------+

    bool CImageGlobals::Init()
    {
        bool t1 = GetSettings();
        bool t2 = makeShareMap();

        if (t1 && t2)
            return(true);
        else
            return(false);
    }

//::23
// +----------------+
// |  LocateFile()  |
// +----------------+

    string CImageGlobals::LocateFile(
                                    string& pFile)
    {
        basic_string <char>::size_type fndindex, endidx, indexins, verindx;
         string m_realDeal;
         string m_bname, m_bpath, m_teleVer;
         bool m_tele7;
         //////////////////////////////
         // Special seperator chars  //
         //////////////////////////////
         char p3tx = 0x03;   // 
         char p4tx = 0x04;   // 
         std::ostringstream strstrm;

         strstrm << p3tx << "C:" << p4tx;
         m_teleVer = strstrm.str();
         strstrm.str("");
         verindx = pFile.find ( m_teleVer , 0 );
         m_tele7 = ( (verindx != string::npos) ? true : false );
         ////////////////////////////////////////////////////////
         // Check valid FILE_LOCATION found in DOC_RENDITIONS. //
         // Changed from LONG_NAME 3_28_05 to improve utility. //
         ////////////////////////////////////////////////////////
         if (m_tele7)
         {
             fndindex = pFile.find ( 0x04 , 0 );
         }
         else
         {
             fndindex = pFile.find ( 0x03 , 0 );
         }
         ////////////////////////////////////////////////
         // Return if INVALID name with empty string.  //
         ////////////////////////////////////////////////
         if (fndindex == string::npos)
         {
 #if _DEBUG
             printf("fndindex == npos\n");
 #endif
             return m_realDeal;
         }

         if (m_tele7)
         {
             endidx = pFile.find ( 0x04 , fndindex + 2 );
         }
         else
         {
             endidx = pFile.find ( 0x03 , fndindex + 2 );
         }

         string ftmp = pFile.substr(fndindex + 1, endidx - fndindex - 1);
         sharemap::iterator fitr = shareMap.find(string(ftmp.c_str()));
         if (fitr != shareMap.end() )
         {
             m_bname = (*fitr).first;           // Get SHARE NAME to process
             m_bpath = (*fitr).second;          // Get PATH LOCATION to process
         }
         else
         {
             //////////////////////////////////////////////////////
             // In case detailed dubug information is required.  //
             //////////////////////////////////////////////////////
 #if _DEBUG_REPORT
             OutputDebugString("NOT in MAP\n");
             printf("ftmp = %s\n", ftmp.c_str());
             fitr = shareMap.begin();
             while (fitr != shareMap.end() )
             {
                 printf("m_bname = %s : ", (*fitr).first.c_str());           // Get SHARE NAME to process
                 printf("m_bpath = %s\n", (*fitr).second.c_str());          // Get PATH LOCATION to process
                 fitr++;
             }
 #endif
             return m_realDeal;
         }
         /////////////////////////////////////////////
         // Char fix for translation in telescope.  //
         /////////////////////////////////////////////
         Clean(pFile);

         if (!m_tele7)
         {
             endidx = pFile.find ( 0x04 , 0 );
         }

         m_bpath.resize(m_bpath.length() -1);
         pFile.replace(0, endidx, m_bpath);

         indexins = 0;
         while ((indexins = pFile.find ( 0x04, indexins ) ) != string::npos) // 0x04 Fix
         {
             pFile.replace(indexins, 1, "\\");
             indexins++;      
         }

         m_realDeal = pFile;
         return m_realDeal;
     }

//::43
// +------------------+
// |  makeShareMap()  |
// +------------------+

    bool CImageGlobals::makeShareMap()
    {
        shareMap.erase(shareMap.begin(), shareMap.end());
        string m_name, m_path;
        string m_kname, m_kpath;
        std::ostringstream strstrm;
        bool task = false;

        HKEY hKeyRoot = HKEY_LOCAL_MACHINE;
        HKEY m_hKey;
        DWORD dw = RegCreateKeyEx (hKeyRoot, "Software\\North Plains Systems\\NTFS File Broker\\CurrentVersion\\NTFS Shares", 0L, NULL,
                                   REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE, NULL,
                                   &m_hKey, &dw);

        DWORD dwType;
        DWORD dwSize = 200;
        char  resString[200];
        if (dw == ERROR_SUCCESS)
        {
            for (DWORD x = 0; x < m_dwShareCount; x++)
            {
                ////////////////////////////
                // IMPORTANT reset size.  //
                ////////////////////////////
                dwSize = 200;
				ZeroMemory(resString, 200);
                strstrm << "ShareName" << x;
                m_kname = strstrm.str();
                strstrm.str("");
                LONG lReturn = RegQueryValueEx (m_hKey, (LPSTR) m_kname.c_str(), NULL,
                                                &dwType, (BYTE *) resString, &dwSize);

                if (lReturn == ERROR_SUCCESS)
                    m_name = resString;
                ////////////////////////////
                // IMPORTANT reset size.  //
                ////////////////////////////
                dwSize = 200;

				ZeroMemory(resString, 200);
                strstrm << "SharePath" << x;
                m_kpath = strstrm.str();
                strstrm.str("");
                lReturn = RegQueryValueEx (m_hKey, (LPSTR) m_kpath.c_str(), NULL,
                                           &dwType, (BYTE *) resString, &dwSize);

                if (lReturn == ERROR_SUCCESS)
                    m_path = resString;

                if ( (!m_name.empty() ) && (!m_path.empty() ) )
                {
                    shareMap.insert(share_type(m_name, m_path) );
                }
            }
            task = true;
        }
        RegCloseKey (m_hKey);
        return(task);
    }

//::24
// +----------------+
// |  operator =()  |
// +----------------+

    _ThisClass & CImageGlobals::operator =(
                                          const _ThisClass& rhs_)             // right-hand-side of assignment
    {
        if (&rhs_ != this)      // Always test for assignment to self.
        {
            m_localSmall = rhs_.m_localSmall;
            m_localLarge = rhs_.m_localLarge;
			m_vlocalLarge = rhs_.m_vlocalLarge;
            m_medLocal = rhs_.m_medLocal;
            m_fileStore = rhs_.m_fileStore;
            m_imgFormat = rhs_.m_imgFormat;
            m_dwShareCount = rhs_.m_dwShareCount;
            m_dwSmallWidth = rhs_.m_dwSmallWidth;
            m_dwSmallHeight = rhs_.m_dwSmallHeight;
            m_dwLargeWidth = rhs_.m_dwLargeWidth;
			m_vLargeWidth = rhs_.m_vLargeWidth;
            m_dwLargeHeight = rhs_.m_dwLargeHeight;
			m_vLargeHeight = rhs_.m_vLargeHeight;
            m_dwMedWidth = rhs_.m_dwMedWidth;
            m_dwMedHeight = rhs_.m_dwMedHeight;
			m_dwMedLargeHeight = rhs_.m_dwMedLargeHeight;
			m_dwMedLargeWidth = rhs_.m_dwMedLargeWidth;
            m_addr = rhs_.m_addr;
            m_port = rhs_.m_port;
     		m_authMode = rhs_.m_authMode;
    		m_pushTable = rhs_.m_pushTable;
    		m_renameMode = rhs_.m_renameMode;
    		m_rename = rhs_.m_rename;
    		m_stepIn = rhs_.m_stepIn;
           makeShareMap();
        }

        return *this;           // Return a reference to this object.
    }

//::46
// +-------------+
// |  SetAddr()  |
// +-------------+

    void CImageGlobals::SetAddr(
                               string addr_)                       // New value for addr property
    {
        m_addr = addr_;
    }

//::25
// +------------------+
// |  SetDeleteRec()  |
// +------------------+

    void CImageGlobals::SetDeleteRec(
                                    DWORD deleteRec_)                   // New value for deleteRec property
    {
        m_deleteRec = deleteRec_;
    }

//::26
// +------------------+
// |  SetImgFormat()  |
// +------------------+

    void CImageGlobals::SetImgFormat(
                                    string imgFormat_)                  // New value for imgFormat property
    {
        m_imgFormat = imgFormat_;
    }

//::27
// +--------------------+
// |  SetLargeHeight()  |
// +--------------------+

    void CImageGlobals::SetLargeHeight(
                                      DWORD dwLargeHeight_)               // New value for LargeHeight property
    {
        m_dwLargeHeight = dwLargeHeight_;
    }

    void CImageGlobals::SetvLargeHeight(
                                      DWORD vLargeHeight_)               // New value for LargeHeight property
    {
        m_vLargeHeight = vLargeHeight_;
    }

//::28
// +-------------------+
// |  SetLargeWidth()  |
// +-------------------+

    void CImageGlobals::SetLargeWidth(
                                     DWORD dwLargeWidth_)                // New value for LargeWidth property
    {
        m_dwLargeWidth = dwLargeWidth_;
    }

    void CImageGlobals::SetvLargeWidth(
                                     DWORD vLargeWidth_)                // New value for LargeWidth property
    {
        m_vLargeWidth = vLargeWidth_;
    }

//::29
// +-------------------+
// |  SetLocalLarge()  |
// +-------------------+

    void CImageGlobals::SetLocalLarge(
                                     string localLarge_)                 // New value for localLarge property
    {
        m_localLarge = localLarge_;
    }

    void CImageGlobals::SetvLocalLarge(
                                     string vlocalLarge_)                 // New value for localLarge property
    {
        m_vlocalLarge = vlocalLarge_;
    }

//::30
// +-------------------+
// |  SetLocalSmall()  |
// +-------------------+

    void CImageGlobals::SetLocalSmall(
                                     string localSmall_)                 // New value for localSmall property
    {
        m_localSmall = localSmall_;
    }

//::31
// +------------+
// |  SetLog()  |
// +------------+

    void CImageGlobals::SetLog(
                              string log_)                        // New value for log property
    {
        m_log = log_;
    }

//::32
// +------------------+
// |  SetMedHeight()  |
// +------------------+

    void CImageGlobals::SetMedHeight(
                                    DWORD dwMedHeight_)                 // New value for dwMedHeight property
    {
        m_dwMedHeight = dwMedHeight_;
    }


    void CImageGlobals::SetMedLargeHeight(
                                         DWORD dwMedLargeHeight_)            // New ISBN 13 value
    {
        m_dwMedLargeHeight = dwMedLargeHeight_;
    }

//::33
// +-----------------+
// |  SetMedLocal()  |
// +-----------------+

    void CImageGlobals::SetMedLocal(
                                   string medLocal_)                   // New value for medLocal property
    {
        m_medLocal = medLocal_;
    }


    void CImageGlobals::SetMedLargeLocal(
                                        string medLargeLocal_)                  // ISBN13
    {
        m_medLargeLocal = medLargeLocal_;
    }

//::34
// +-----------------+
// |  SetMedWidth()  |
// +-----------------+

    void CImageGlobals::SetMedWidth(
                                   DWORD dwMedWidth_)                  // New value for dwMedWidth property
    {
        m_dwMedWidth = dwMedWidth_;
    }


    void CImageGlobals::SetMedLargeWidth(
                                        DWORD dwMedLargeWidth_)                 // New value for dwMedWidth property
    {
        m_dwMedLargeWidth = dwMedLargeWidth_;
    }

//::47
// +-------------+
// |  SetPort()  |
// +-------------+

    void CImageGlobals::SetPort(
                               string port_)                       // New value for port property
    {
        m_port = port_;
    }

//::35
// +--------------------+
// |  SetSmallHeight()  |
// +--------------------+

    void CImageGlobals::SetSmallHeight(
                                      DWORD dwSmallHeight_)               // New value for SmallHeight property
    {
        m_dwSmallHeight = dwSmallHeight_;
    }

//::36
// +-------------------+
// |  SetSmallWidth()  |
// +-------------------+

    void CImageGlobals::SetSmallWidth(
                                     DWORD dwSmallWidth_)                // New value for SmallWidth property
    {
        m_dwSmallWidth = dwSmallWidth_;
    }

    void CImageGlobals::SetTNS(
                              string tns_)                        // New value for tns property
    {
        m_tns = tns_;
    }

    void CImageGlobals::SetUseFTP(unsigned int iFtp)
    {
        m_useFTP = iFtp;
    }

    bool CImageGlobals::GetUseFTP()
    {
        return((m_useFTP == 0) ? false : true);
    }

    void CImageGlobals::SetFtpHost(string pHost)
    {
        m_ftpHost = pHost;
    }

    string CImageGlobals::GetFtpHost() const
    {
        return m_ftpHost;
    }

    void CImageGlobals::SetFtpPort(unsigned int iPort)
    {
        m_ftpPort = iPort;
    }

    unsigned int CImageGlobals::GetFtpPort() const
    {
        return m_ftpPort;
    }

    void CImageGlobals::SetFtpUser(string pUser)
    {
        m_ftpUser = pUser;
    }

    string CImageGlobals::GetFtpUser() const
    {
        return m_ftpUser;
    }

    void CImageGlobals::SetFtpPass(string pPass)
    {
        m_ftpPass = pPass;
    }

    string CImageGlobals::GetFtpPass() const
    {
        return m_ftpPass;
    }

    void CImageGlobals::SetSmallFtp(string pFtp)
    {
        m_smallFTP = pFtp;
    }

    string CImageGlobals::GetSmallFtp() const
    {
        return m_smallFTP;
    }

    void CImageGlobals::SetMedFtp(string pFtp)
    {
        m_medFTP = pFtp;
    }


    void CImageGlobals::SetMedLargeFtp(string pFtp)
    {
        m_medLargeFTP = pFtp;
    }

    string CImageGlobals::GetMedFtp() const
    {
        return m_medFTP;
    }

    string CImageGlobals::GetMedLargeFtp() const
    {
        return m_medLargeFTP;
    }

    void CImageGlobals::SetLargeFtp(string pFtp)
    {
        m_largeFTP = pFtp;
    }

	void CImageGlobals::SetvLargeFtp(string pFtp)
	{
		m_vlargeFTP = pFtp;
	}

    string CImageGlobals::GetLargeFtp() const
    {
        return m_largeFTP;
    }

	string CImageGlobals::GetvLargeFtp() const
	{
		return m_vlargeFTP;
	}

	void CImageGlobals::SetDirectFtp(string pFtp)
	{
		m_directFTP = pFtp;
	}

	string CImageGlobals::GetDirectFtp() const
	{
		return m_directFTP;
	}

    bool CImageGlobals::IsSnapShot(string& pLoc)
    {
        basic_string <char>::size_type findidx;
        findidx = pLoc.find ( "napshot" , 0 );
        return( (findidx != string::npos) ? true : false);
    }

string CImageGlobals::Clean(string& strin)
{
    /////////////////////////////////////////////////////////////
    // ** MUST be first as $'s introduced in this function **  //
    /////////////////////////////////////////////////////////////
    if ( strin.find("$") != string::npos )
    {
		RWTRegex<char> re("$");
		re.replace(strin, "$24", 0);
        //boost::replace_all(strin, "$", "$24");
    }

    if ( strin.find("/") != string::npos )
    {
		RWTRegex<char> re("/");
		re.replace(strin, "$2f", 0);
		//boost::replace_all(strin, "/", "$2f");
    }

    if ( strin.find("?") != string::npos )
    {
		RWTRegex<char> re("\\?");
		re.replace(strin, "$3f", 0);
        //boost::replace_all(strin, "?", "$3f");
    }

    if ( strin.find("<") != string::npos )
    {
		RWTRegex<char> re("<");
		re.replace(strin, "$3c", 0);
        //boost::replace_all(strin, "<", "$3c");
    }

    if ( strin.find(">") != string::npos )
    {
		RWTRegex<char> re(">");
		re.replace(strin, "$3e", 0);
        //boost::replace_all(strin, ">", "$3e");
    }

    if ( strin.find("\\") != string::npos )
    {
		RWTRegex<char> re("\\");
		re.replace(strin, "$5c", 0);
        //boost::replace_all(strin, "\\", "$5c");
    }

    if ( strin.find("\"") != string::npos )
    {
		RWTRegex<char> re("\"");
		re.replace(strin, "$22", 0);
        //boost::replace_all(strin, "\"", "$22");
    }

    return strin;
}

}   // end SlapWare namespace


//:Special
#undef _ThisClass
#undef _NumBaseClass


