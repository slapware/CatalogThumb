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
#include "COciImp.h"

#define _ThisClass		CCOciHandle
using namespace std;

namespace slapware // begin SlapWare namespace
{
    class CCOciHandle : public RWHandleBase
    {
    public:
        CCOciHandle(void);
        ~CCOciHandle(void);
        CCOciHandle(const RWCString& _server, const RWCString _user, const RWCString _pswd);
        bool check(void);
        bool DoSelect(const RWCString& _param1, const RWCString& _param2);
        RWCString GetURL();
        RWCString GetType();
		RWDBStatus GetStatus();
		int GetCount(RWCString& pSql);
		int GetStrInt(RWCString& pSql, RWCString& param1, int& param2);
		int GetStrStr(RWCString& pSql, RWCString& param1, RWCString& param2);
		int Update(RWCString& pSql);
		int make_docMap(RWCString& pSql, map<int,RWCString>&myRef);
   protected:
        CCOciImp & body() const;
    };
}   // end SlapWare namespace
#undef _ThisClass

