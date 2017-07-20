//:Header:5, "CImageGlobals", 41b09148
//
// $File:CImageGlobals.h$
//
// Copyright (C) 2004 SlapWare, All rights reserved.
//
// $History$
// 03 Dec 2004, stephen lapierre -- Generated 11:16:08 by Genitor OCS V4.50.915.2
//
//:---------------------------------------------------------------------------

#if !defined(_INC_CIMAGEGLOBALS)
#define _INC_CIMAGEGLOBALS

#ifdef _DEBUG
#define _RWCONFIG 15s
#else
#define _RWCONFIG 12s
#endif


//:Custom
#pragma once
//:End Custom

//:StdInc
#if !defined(_INC_GTORSYS)
//#include "gtorsys.h"
#endif

//:Include
#include "Windows.h"

#if !defined(_INC_MAP)
#include <map>
#endif

#if !defined(_INC_STRING)
#include <string>
#endif

#include "Markup.h"
#include <rw/tools/regex.h>

//:Special
#define _ThisClass		CImageGlobals
#define _NumBaseClass	0

//:Custom
using namespace std;

namespace slapware {    // begin SlapWare namespace
    typedef std::map<string, string, less<string> > sharemap;
    typedef sharemap::value_type share_type;
//:End Custom

//:>                +---------------------------------------+
//:>----------------|    CImageGlobals Class Declaration    |-----------------
//:>                +---------------------------------------+
//:Class
    class CImageGlobals
    {
    public:
        string Clean(string& strin);
        bool IsSnapShot(string& pLoc);
        string GetLargeFtp() const;
		string GetvLargeFtp() const;
        void SetLargeFtp(string pFtp);
		void SetvLargeFtp(string pFtp);
        string GetMedFtp() const;
        void SetMedFtp(string pFtp);
        string GetMedLargeFtp() const;
        void SetMedLargeFtp(string pFtp);
        string GetSmallFtp() const;
        void SetSmallFtp(string pFtp);
        string GetFtpPass() const;
        void SetFtpPass(string pPass);
        string GetFtpUser() const;
        void SetFtpUser(string pUser);
        unsigned int GetFtpPort() const;
        void SetFtpPort(unsigned int iPort);
        string GetFtpHost() const;
        void SetFtpHost(string pHost);
        bool GetUseFTP();
        void SetUseFTP(unsigned int iFtp);
		string GetDirectFtp() const;
		void SetDirectFtp(string pFtp);

        CImageGlobals(const _ThisClass& rhs_);        // Existing object being copied

        CImageGlobals();

        virtual ~CImageGlobals();

        string GetAddr() const;
        DWORD GetDeleteRec() const;
        string GetImgFormat() const;
        DWORD GetLargeHeight() const;
        DWORD GetLargeWidth() const;
        string GetLocalLarge() const;
		DWORD GetvLargeHeight() const;
		DWORD GetvLargeWidth() const;
		string GetvLocalLarge() const;

        string GetLocalSmall() const;
        string GetLog() const;
        DWORD GetMedHeight() const;
        DWORD GetMedLargeHeight() const;
        string GetMedLocal() const;
        string GetMedLargeLocal() const;
        DWORD GetMedWidth() const;
        DWORD GetMedLargeWidth() const;
        string GetPort() const;
        DWORD GetShareCount() const;
        DWORD GetSmallHeight() const;
        DWORD GetSmallWidth() const;
        string GetSourceServer() const;
        string GetTNS() const;
        bool Init();

        string LocateFile(string& pFile);

        _ThisClass & operator =(const _ThisClass& rhs_);   

        void SetAddr(string addr_);                        
        void SetDeleteRec(DWORD deleteRec_);              
        void SetImgFormat(string imgFormat_);             
        void SetLargeHeight(DWORD dwLargeHeight_);         
        void SetLargeWidth(DWORD dwLargeWidth_);           
        void SetLocalLarge(string localLarge_);
		void SetvLargeHeight(DWORD vLargeHeight_);   // VERY LARGE      
		void SetvLargeWidth(DWORD vLargeWidth_);           
		void SetvLocalLarge(string vlocalLarge_);

        void SetLocalSmall(string localSmall_);            
        void SetLog(string log_);                          
        void SetMedHeight(DWORD dwMedHeight_);             
        void SetMedLargeHeight(DWORD dwMedlargeHeight_);   
        void SetMedLocal(string medLocal_);                
        void SetMedLargeLocal(string medLargeLocal_);      
        void SetMedWidth(DWORD dwMedWidth_);               
        void SetMedLargeWidth(DWORD dwMedLargeWidth_);     
        void SetPort(string port_);                        
        void SetSmallHeight(DWORD dwSmallHeight_);         
        void SetSmallWidth(DWORD dwSmallWidth_);           
        void SetSourceServer(string sourceServer_);        
        void SetTNS(string tns_);                        
		string GetFileStore() const { return m_fileStore; }
		void SetFileStore(string val) { m_fileStore = val; }
		string GetDbTable() const { return m_pushTable; }
		void SetDbTable(string val) { m_pushTable = val; }
		int GetRenameMode() const { return m_renameMode; }
		void SetRenameMode(int val) { m_renameMode = val; }
		int GetAuthMode() const { return m_authMode; }
		void SetAuthMode(int val) { m_authMode = val; }
		string GetBaseDir() const { return m_baseDir; }
		void SetBaseDir(string val) { m_baseDir = val; }
		bool GetStepIn() const { return m_stepIn == 0 ? false : true; }
		void SetStepIn(int val) { m_stepIn = val; }
		string GetUserDir() const { return m_userDir; }
		void SetUserDir(string val) { m_userDir = val; }
		int GetUseDir() const { return m_usedir; }
		void SetUseDir(int val) { m_usedir = val; }
		int GetRename() const { return m_rename; }
		void SetRename(int val) { m_rename = val; }
		bool GetSizeSort() const { return m_sizeSort == 0 ? false : true; }
		void SetSizeSort(int val) { m_sizeSort = val; }

    protected:
        bool GetSettings();
        bool makeShareMap();

    private:
        string m_largeFTP;
		string m_vlargeFTP;
        string m_medFTP;
        string m_medLargeFTP;
        string m_smallFTP;
		string m_directFTP;
        string m_ftpPass;
        string m_ftpUser;
        string m_ftpHost;
        unsigned int m_ftpPort;

        string m_localSmall;                
        string m_localLarge;                
		string m_vlocalLarge;                
        string m_fileStore;              
        string m_imgFormat;                 
        DWORD m_dwShareCount;               
        DWORD m_dwSmallWidth;               
        DWORD m_dwSmallHeight;              
        DWORD m_dwLargeWidth;               
        DWORD m_dwLargeHeight;              
		DWORD m_vLargeWidth;               
		DWORD m_vLargeHeight;              
        sharemap shareMap;                  
        DWORD m_deleteRec;                  
        unsigned int m_useFTP;              
        string m_tns;                       
        string m_log;                       
        DWORD m_dwMedHeight;                
        DWORD m_dwMedWidth;                 
		string m_pushTable;			// DB target table for source.
		int m_renameMode;
		int m_authMode;
		string m_baseDir;
        DWORD m_dwMedLargeWidth;
        DWORD m_dwMedLargeHeight;
        string m_medLocal;                  
        string m_medLargeLocal;             
        string m_addr;                      
        string m_port;
		int m_stepIn;				// Must step into user dir
		string m_userDir;			// user dir to step into
		int m_usedir;
		int m_sizeSort;
		int m_rename;
    };
}   // end SlapWare namespace


//:Special
#undef _ThisClass
#undef _NumBaseClass

#endif  								// _INC_CIMAGEGLOBALS

