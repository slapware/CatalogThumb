#pragma once

#ifdef WIN32
    #pragma warning( disable : 4267 )  // Disable warning messages
#endif

#ifdef _DEBUG
    #define _RWCONFIG 15s
#else
    #define _RWCONFIG 12s
#endif

#include <rw/pointer/RWBodyBase.h>
#include <rw/pointer/RWHandleBase.h>

#include <rw/rstream.h>
#include <rw/db/db.h>
#include <rw/db/dbmgr.h>
#include <rw/db/osql.h>
#include <rw/db/status.h>
#include <rw/db/tbuffer.h>
#include <string>
#include<map>

#define _ThisClass		CCOciImp
using namespace std;

namespace slapware 
{    // begin SlapWare namespace
    class CCOciImp :
    public RWBodyBase
    {
    public:
        friend class CCOciHandle;
    protected:
        virtual ~CCOciImp(void);
    private:
        CCOciImp(void);
        CCOciImp(const RWCString& _server, const RWCString _user, const RWCString _pswd);
        RWCString m_server;
        RWCString m_user;
        RWCString m_pswd;
        RWCString m_db;
        RWDBDatabase mySql;
        RWDBConnection m_conn;
        // Params here for sql result
        RWCString m_param1;
        RWCString m_param2;

        bool check(void);   // is connection valid
    public:
        void init(void);    // make the connection
        RWCString GetURL();
        RWCString GetType();
		RWDBStatus GetStatus();
		int GetCount(RWCString& pSql);
		int Update(RWCString& pSql);
		int GetStrInt(RWCString& pSql, RWCString& param1, int& param2);
		int GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2);
        bool DoSelect(const RWCString& _param1, const RWCString& _param2);
		int make_docMap(RWCString& pSql, map<int,RWCString>&myRef);
    };

}   // end SlapWare namespace
#undef _ThisClass
